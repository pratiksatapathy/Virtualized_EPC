#ifndef HSS_H
#define HSS_H

#include "utils.h"
#include "packet.h"
#include "udp_server.h"
#include "mysql.h"

struct UEData {
	unsigned long long imsi;
	unsigned long long msisdn;
	unsigned long long autn_num;
	unsigned long long rand_num;
	unsigned long long autn_xres;
	unsigned long long key_id;
};

struct HSS {
	MySql db_client;
	MYSQL_ROW query_res;
	
	string query;
	string res_row;
	int num_fields;
	
	time_t curr_time;
	tm *local_time;
	int curr_sec;
	
	struct sockaddr_in client_sock_addr;
	Packet pkt;

	int type;
	int subtype;
	int ue_num;

	UEData ue_data;

	int status;
	
	HSS();	
	void handle_query_error();
	void read_data();
	void set_metadata();
	void process_req();
	void set_key_id();
	void set_autn_tokens();
	void set_autn_xres();
	void send_res();
	~HSS();
};

extern UDPServer g_hss_server;
extern vector<pthread_t> g_tid;
extern int g_tcount;

#endif //HSS_H