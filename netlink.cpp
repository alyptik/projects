 // open a netlink socket
  auto *nlsock = mnl_socket_open2(NETLINK_ROUTE, SOCK_CLOEXEC);
  if (!nlsock)
    throw sys::error("can't open netlink socket");

  // check if interface already exists
  struct ifreq ifr_index = {};
  std::strcpy(ifr_index.ifr_name, iface);
  sys::check(ioctl(mnl_socket_get_fd(nlsock), SIOCGIFINDEX, &ifr_index),
             "can't query interface index");
  int ifnum = ifr_index.ifr_ifindex;
  std::cout << "interface number: " << ifnum << std::endl;

  int rcvbufsz = sizeof (nlbuf);
  sys::check(setsockopt(mnl_socket_get_fd(nlsock), SOL_SOCKET, SO_RCVBUF, &rcvbufsz, sizeof (int)),
             "can't set netlink socket receive buffer size");

  sys::check(mnl_socket_bind(nlsock, 0, 0), "can't bind netlink socket");

  uint32_t seq = 0;

  struct nlmsghdr *hdr = mnl_nlmsg_put_header(nlbuf);
  hdr->nlmsg_type = RTM_GETROUTE;
  hdr->nlmsg_flags = NLM_F_REQUEST;
  hdr->nlmsg_seq = ++seq;
  auto *msg = (struct rtmsg *)mnl_nlmsg_put_extra_header(hdr, sizeof (struct rtmsg));
  msg->rtm_family = AF_INET;
  msg->rtm_dst_len = 0;

  auto addr = inet_addr("0.0.0.0");
  mnl_attr_put(hdr, RTA_DST, sizeof (addr), &addr);
  mnl_attr_put_u32(hdr, RTA_OIF, ifnum);

  sys::check(mnl_socket_sendto(nlsock, nlbuf, hdr->nlmsg_len));
  int size = mnl_socket_recvfrom(nlsock, nlbuf, sizeof (nlbuf));

  for (auto *nlm = (struct nlmsghdr *)nlbuf;
       mnl_nlmsg_ok(nlm, size);
       nlm = mnl_nlmsg_next(nlm, &size))
  {
    std::clog << "one response: " << nlm->nlmsg_type << std::endl;

    if (nlm->nlmsg_type == NLMSG_ERROR)
    {
      auto *err = reinterpret_cast<struct nlmsgerr *>(mnl_nlmsg_get_payload(nlm));
      std::clog << "can't get response: " << strerror(-err->error) << std::endl;
      break;
    }

    auto *rtmsg = reinterpret_cast<struct rtmsg *>(mnl_nlmsg_get_payload(nlm));
    int rtsize = RTM_PAYLOAD(nlm);

    for (auto *rtattr = RTM_RTA(msg);
         RTA_OK(rtattr, rtsize);
         rtattr = RTA_NEXT(rtattr, rtsize))
    {
      std::clog << "one attribute: " << rtattr->rta_type << std::endl;
      if (rtattr->rta_type == RTA_PREFSRC)
      {
        auto *a = reinterpret_cast<struct in_addr *>(RTA_DATA(rtattr));

        std::cout << "response: " << inet_ntoa(*a) << std::endl;
        break;
      }
    }
  }

  mnl_socket_close(nlsock);

  return 0;
