#ifndef MME_H
#define MME_H

#include "utils.h"
#include "gtp.h"
#include "s1ap.h"
#include "diameter.h"
#include "packet.h"
#include "network.h"
#include "sctp_server.h"
#include "sctp_client.h"
#include "udp_client.h"

struct UeContext {
	/* UE id */
	uint64_t imsi; /* International Mobile Subscriber Identity */
	string ip_addr;
	uint32_t enodeb_s1ap_id; /* eNodeB S1AP UE ID */
	uint32_t mme_s1ap_id; /* MME S1AP UE ID */

	/* UE location info */
	uint64_t tai; /* Tracking Area Identifier */
	vector<uint64_t> tai_list; /* Tracking Area Identifier list */

	/* UE security context */
	/* To be filled */

	/* EPS info, EPS bearer info */
	uint64_t default_apn; /* Default Access Point Name */
	uint64_t apn_in_use; /* Access Point Name in Use */
	uint8_t eps_bearer_id; /* Evolved Packet System Bearer ID */
	uint32_t s1_teid_ul; /* S1 Tunnel Endpoint Identifier - Uplink */
	uint32_t s1_teid_dl; /* S1 Tunnel Endpoint Identifier - Downlink */
	uint32_t s5_teid_ul; /* S5 Tunnel Endpoint Identifier - Uplink */
	uint32_t s5_teid_dl; /* S5 Tunnel Endpoint Identifier - Downlink */
};

class Mme {
public:
	/* MME Identifiers */
	uint16_t mcc; /* Mobile Country Code */
	uint16_t mnc; /* Mobile Network Code */
	uint16_t plmn_id; /* Public Land Mobile Network ID */
	uint16_t mmegi; /* MME Group Identifier */
	uint8_t mmec; /* MME Code */
	uint32_t mmei; /* MME Identifier */
	uint64_t gummei; /* Globally Unique MME Identifier */
	unordered_map<uint64_t, UeContext> ue_context_table; 
	unordered_map<uint32_t, uint64_t> ue_identification_table;

	Mme();
	~Mme();
};

#endif /* MME_H */