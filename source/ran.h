#ifndef RAN_H
#define RAN_H

#include "diameter.h"
#include "gtp.h"
#include "network.h"
#include "packet.h"
#include "s1ap.h"
#include "security.h"
#include "sctp_client.h"
#include "sync.h"
#include "telecom.h"
#include "tun.h"
#include "udp_client.h"
#include "udp_server.h"
#include "utils.h"

class RanContext {
public:
	/* EMM state 
	 * 0 - Deregistered
	 * 1 - Registered 
	 */	
	int emm_state; /* EPS Mobililty Management state */

	/* ECM state 
	 * 0 - Disconnected
	 * 1 - Connected 
	 * 2 - Idle 
	 */
	int ecm_state; /* EPS Connection Management state */

	/* UE id */
	uint64_t imsi; /* International Mobile Subscriber Identity */
	uint64_t guti; /* Globally Unique Temporary Identifier */
	string ip_addr;
	uint32_t enodeb_s1ap_ue_id; /* eNodeB S1AP UE ID */
	uint32_t mme_s1ap_ue_id; /* MME S1AP UE ID */

	/* UE location info */
	uint64_t tai; /* Tracking Area Identifier */
	vector<uint64_t> tai_list; /* Tracking Area Identifier list */
	uint64_t tau_timer;

	/* UE security context */
	uint64_t key; /* Primary key used in generating secondary keys */
	uint64_t k_asme; /* Key for Access Security Management Entity */
	uint64_t ksi_asme; /* Key Selection Identifier for Access Security Management Entity */
	uint64_t k_nas_enc; /* Key for NAS Encryption / Decryption */
	uint64_t k_nas_int; /* Key for NAS Integrity check */
	uint64_t nas_enc_algo; /* Idenitifier of NAS Encryption / Decryption */
	uint64_t nas_int_algo; /* Idenitifier of NAS Integrity check */
	uint64_t count;
	uint64_t bearer;
	uint64_t dir;

	/* EPS info, EPS bearer info */
	uint64_t apn_in_use; /* Access Point Name in Use */
	uint8_t eps_bearer_id; /* Evolved Packet System Bearer ID */
	uint8_t e_rab_id; /* Evolved Radio Access Bearer ID */
	uint32_t s1_uteid_ul; /* S1 Userplane Tunnel Endpoint Identifier - Uplink */
	uint32_t s1_uteid_dl; /* S1 Userplane Tunnel Endpoint Identifier - Downlink */

	/* Network Operator info */
	uint16_t mcc; /* Mobile Country Code */
	uint16_t mnc; /* Mobile Network Code */
	uint16_t plmn_id; /* Public Land Mobile Network ID */	
	uint64_t msisdn; /* Mobile Station International Subscriber Directory Number - Mobile number */
	uint16_t nw_capability;

	RanContext();
	void init(uint32_t);
	~RanContext();	
};

class EpcAddrs {
public:
	uint64_t mme_port;
	uint64_t sgw_s1_port;
	string mme_ip_addr;
	string sgw_s1_ip_addr;

	EpcAddrs();
	~EpcAddrs();
};

class UplinkInfo {
public:
	uint32_t s1_uteid_ul;
	string sgw_s1_ip_addr;
	uint64_t sgw_s1_port;

	void init(uint32_t, string, uint64_t);
};

class TrafficMonitor {
	bool get_uplink_info(string, uint32_t&, string&, uint64_t&);

public:
	UdpServer server;
	Tun tun;
	unordered_map<string, UplinkInfo> uplink_info;
	
	/* Lock parameter */
	pthread_mutex_t uplinkinfo_mux; /* Handles uplink_info */

	TrafficMonitor();
	void handle_uplink_udata();
	void handle_downlink_udata();
	void update_uplink_info(string, uint32_t, string, uint64_t);
	~TrafficMonitor();
};

class Ran {
private:
	void set_crypt_context();
	void set_integrity_context();
	
public:
	RanContext ran_ctx;
	EpcAddrs epc_addrs;
	SctpClient mme_client;
	Crypt crypt;
	Integrity integrity;
	Packet pkt;

	Ran();
	void init(int);
	void initial_attach();
	void authenticate();
	void set_security();
	void set_eps_session(TrafficMonitor&);
	void transfer_data();
	void detach();	
	~Ran();
};

#endif /* RAN_H */
