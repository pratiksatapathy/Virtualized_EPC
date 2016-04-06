#include "utils.h"

int g_reuse = 1;
int g_freeport = 0;
int g_trafmon_port = 4000;
int g_mme_port = 5000;
int g_hss_port = 6000;
int g_sgw_s11_port = 7000;
int g_sgw_s1_port = 7100;
int g_sgw_s5_port = 7200;
int g_pgw_s5_port = 8000;
int g_pgw_sgi_port = 8100;
int g_sink_port = 8500;
string g_ran_ip_addr = "10.14.13.29";
string g_trafmon_ip_addr = "10.14.13.29";
string g_mme_ip_addr = "10.14.13.29";
string g_hss_ip_addr = "10.14.13.29";
string g_sgw_s11_ip_addr = "10.14.13.29";
string g_sgw_s1_ip_addr = "10.14.13.29";
string g_sgw_s5_ip_addr = "10.14.13.29";
string g_pgw_s5_ip_addr = "10.14.13.29";
string g_pgw_sgi_ip_addr = "10.14.13.29";
string g_sink_ip_addr = "10.129.5.193";
struct timeval g_timeout = {20, 0};
Utils g_utils;

/* Action - Exit the program */
void Utils::handle_type1_error(int arg, string msg) {
	if (arg < 0) {
		perror(msg.c_str());
		exit(EXIT_FAILURE);
	}	
}

/* Action - Nothing */
void Utils::handle_type2_error(int arg, string msg) {
	if (arg < 0 && errno != EWOULDBLOCK && errno != EAGAIN) {
		perror(msg.c_str());
		exit(EXIT_FAILURE);
	}
}

char* Utils::allocate_str_mem(int len) {
	char *tem;

	if (len <= 0) {
		handle_type1_error(-1, "Memory length error: utils_allocatestrmem");
	}
	tem = (char*)malloc(len * sizeof (char));
	if (tem != NULL) {
		memset(tem, 0, len * sizeof (char));
		return tem;
	}
	else {
		handle_type1_error(-1, "Memory allocation error: utils_allocatestrmem");
	}
}

uint8_t* Utils::allocate_uint8_mem(int len) {
	uint8_t *tem;

	if (len <= 0) {
		handle_type1_error(-1, "Memory length error: utils_allocateuint8mem");
	}
	tem = (uint8_t*)malloc(len * sizeof (uint8_t));
	if (tem != NULL) {
		memset(tem, 0, len * sizeof (uint8_t));
		return tem;
	} 
	else {
		handle_type1_error(-1, "Memory allocation error: utils_allocateuint8mem");
	}
}

void Utils::time_check(time_t start_time, double duration_time, bool &time_exceeded) {
	double elapsed_time;

	if ((elapsed_time = difftime(time(0), start_time)) > duration_time) {
		time_exceeded = true;
	}
}