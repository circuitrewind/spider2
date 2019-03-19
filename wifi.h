#ifndef __WIFI_H__
#define __WIFI_H__



#include <ESP8266WiFi.h>
#include <lwip/netif.h>



void wifi_setup();
void wifi_loop();



extern int _broadcastPort;




struct EtherFrame {
	uint8_t destMAC[6];
	uint8_t srcMAC[6];
	uint16_t typeLength;
} __attribute__((packed));




struct etharp_packet {
	struct EtherFrame hdr;
	uint16_t hwtype;
	uint16_t proto;
	uint8_t  hwlen;
	uint8_t  protolen;
	uint16_t opcode;
	uint8_t  src_eth_addr[6];
	uint8_t  src_ip_addr[4];
	uint8_t  dst_eth_addr[6];
	uint8_t  dst_ip_addr[4];
} __attribute__((packed));




struct IP_Frame {
	// #if BYTE_ORDER == LITTLE_ENDIAN
	uint8_t   ip_hlen:4;  // header length
	uint8_t   ip_ver:4;   // version

	uint8_t   ip_tos;     // type of service
	uint16_t  ip_len;     // total length
	uint16_t  ip_id;      // identification
	uint16_t  ip_off;     // fragment offset field
	uint8_t   ip_ttl;     // time to live
	uint8_t   ip_proto;   // protocol
	uint16_t  ip_sum;     // checksum
	uint8_t   ip_src_addr[4];  // destination address
	uint8_t   ip_dst_addr[4];  // source address
} __attribute__((packed));




struct udp_packet {
	struct EtherFrame hdr;
	struct IP_Frame ip;
	uint16_t  src_port;
	uint16_t  dst_port;
	uint16_t length;
	uint16_t checksum;
} __attribute__((packed));




inline uint16_t swap16(uint16_t n) {
	return ((n>>8)&0xff) | ((n<<8)&0xff00);
}




err_t netif_input_local(struct pbuf* p, struct netif* inp);
/*
int MACsprintf(const uint8_t* MAC, char* buffer, size_t bufferLength);
int IPsprintf(const uint8_t* IP, char* buffer, size_t bufferLength);
void printPacketInfo(struct pbuf* p);
void printARP(uint8_t* data);
void printIP(uint8_t* data);
void printMyMac();
*/

#endif //__WIFI_H__
