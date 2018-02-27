/*
 * server.c -- a stream socket server demo
 */

#ifndef _GNU_SOURCE
#	define _GNU_SOURCE
#endif

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <sys/wait.h>
#include <signal.h>
#include <netinet/tcp.h>

/* the port users will be connecting to */
#define PORT "3490"
/* how many pending connections queue will hold */
#define BACKLOG 10

static inline void sigchld_handler(int sig)
{
	/* quiet unused variable warning */
	(void)sig;

	/* waitpid() might overwrite errno, so we save and restore it: */
	int saved_errno = errno;
	while (waitpid(-1, NULL, WNOHANG) > 0);
	errno = saved_errno;
}

/* get sockaddr, IPv4 or IPv6: */
static inline void *get_in_addr(struct sockaddr *sa)
{
	if (sa->sa_family == AF_INET)
		return (void *)&((struct sockaddr_in*)sa)->sin_addr;
	/* else it's ipv6 */
	return (void *)&((struct sockaddr_in6*)sa)->sin6_addr;
}

int main(void)
{
	int gai_ret, yes = 1;
	/* listen on sock_fd */
	int sockfd;
	char s[INET6_ADDRSTRLEN] = {0};
	struct addrinfo *servinfo, *p, hints = {0};
	/* connector's address information */
	struct sockaddr_storage their_addr = {0};
	struct sigaction sa = {0};
	socklen_t sin_size;

	/* use my IP */
	hints.ai_flags = AI_PASSIVE;
	/* hints.ai_family = AF_INET; */
	/* hints.ai_family = AF_INET6; */
	hints.ai_family = AF_UNSPEC;

	if ((gai_ret = getaddrinfo(NULL, PORT, &hints, &servinfo))) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(gai_ret));
		return 1;
	}

	/* loop through all the results and bind to the first we can */
	for (p = servinfo; p; p = p->ai_next) {
		if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
			perror("server: socket");
			continue;
		}
		/* reuse old sockets and disable Nagle's algorithm */
		if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof yes) == -1) {
			perror("setsockopt");
			return 1;
		}
		if (setsockopt(sockfd, SOL_TCP, TCP_NODELAY, &yes, sizeof yes) == -1) {
			perror("setsockopt");
			return 1;
		}
		if (bind(sockfd, p->ai_addr, p->ai_addrlen) == -1) {
			close(sockfd);
			perror("server: bind");
			continue;
		}

		break;
	}

	/* all done with this structure */
	freeaddrinfo(servinfo);
	if (!p)  {
		fprintf(stderr, "server: failed to bind\n");
		exit(1);
	}
	if (listen(sockfd, BACKLOG) == -1) {
		perror("listen");
		exit(1);
	}

	/* reap all dead processes */
	sa.sa_handler = sigchld_handler;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);
	if (sigaction(SIGCHLD, &sa, NULL) == -1) {
		perror("sigaction");
		exit(1);
	}

	puts("server: waiting for connections...");

	/* main accept() loop */
	for (;;) {
		/* new connection */
		int newfd;
		sin_size = sizeof their_addr;
		if ((newfd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size)) == -1) {
			perror("accept");
			continue;
		}

		inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr *)&their_addr), s, sizeof s);
		printf("server: got connection from %s\n", s);

		if (!fork()) {
			/* this is the child process */
			char const msg[] = "\n\033[93m\033[41m\tpoop\033[0m\n\n";

			/* child doesn't need the listener */
			close(sockfd);
			if (send(newfd, msg, sizeof msg, 0) == -1)
				perror("send");
			close(newfd);

			exit(0);
		}

		/* parent doesn't need this */
		close(newfd);
	}

	return 0;
}
