/*
** showip.c -- show IP addresses for a host given on the command line
*/

#ifndef _XOPEN_SOURCE
#  define _XOPEN_SOURCE 700
#endif

#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <netinet/ip.h>

int main(int argc, char **argv)
{
	struct addrinfo *res, *p, hints = {0};
	int status;
	char ipstr[INET6_ADDRSTRLEN];

	if (argc != 2) {
		fprintf(stderr,"usage: showip hostname\n");
		return 1;
	}

	/* AF_INET or AF_INET6 to force version */
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;

	if ((status = getaddrinfo(argv[1], NULL, &hints, &res))) {
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
		return 2;
	}

	printf("IP addresses for %s:\n\n", argv[1]);

	for(p = res; p; p = p->ai_next) {
		void *addr;
		char *ipver;

		/*
		 * get the pointer to the address itself,
		 * different fields in IPv4 and IPv6:
		 */
		if (p->ai_family == AF_INET) {
			/* IPv4 */
			addr = &((struct sockaddr_in *)p->ai_addr)->sin_addr;
			ipver = "IPv4";
		} else {
			/* IPv6 */
			addr = &((struct sockaddr_in6 *)p->ai_addr)->sin6_addr;
			ipver = "IPv6";
		}

		/* convert the IP to a string and print it: */
		inet_ntop(p->ai_family, addr, ipstr, sizeof ipstr);
		printf("  %s: %s\n", ipver, ipstr);
	}

	/* free the linked list */
	freeaddrinfo(res);

	return 0;
}
