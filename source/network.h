#ifndef NETWORK_H
#define NETWORK_H

/* (C) socket */
#include <sys/socket.h>

/* (C) open */
#include <fcntl.h>

/* (C) read, write, close */
#include <unistd.h>

/* (C) select */
#include <sys/select.h>

/* (C) inet_aton, inet_ntop */
#include <arpa/inet.h>

/* (C) ioctl */
#include <sys/ioctl.h>

/* (C) IFF_TUN, IFF_NO_PI, TUNSETIFF */
#include <linux/if_tun.h>

/* (C) ifreq, IFNAMSIZ */
#include <net/if.h>

#include "utils.h"

extern socklen_t g_sock_addr_len;

void set_inet_sock_addr(const char*, int, struct sockaddr_in&);
void bind_sock(int, struct sockaddr_in);
void get_sock_addr(int, struct sockaddr_in&);
void set_sock_reuse(int);
void set_timeout(int);

#endif /* NETWORK_H */