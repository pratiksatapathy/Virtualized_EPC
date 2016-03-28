#ifndef PGW_SERVER_H
#define PGW_SERVER_H

#include "diameter.h"
#include "gtp.h"
#include "network.h"
#include "packet.h"
#include "pgw.h"
#include "s1ap.h"
#include "sync.h"
#include "udp_client.h"
#include "udp_server.h"
#include "utils.h"

extern Pgw g_pgw;
extern int g_s5_server_threads_count;
extern int g_sgi_server_threads_count;
extern vector<thread> g_s5_server_threads;
extern vector<thread> g_sgi_server_threads;

void check_usage(int);
void init(char**);
void run();
void handle_s5_server();
void handle_sgi_server();

#endif /* PGW_SERVER_H */