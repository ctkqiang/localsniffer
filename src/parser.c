#include <stdio.h>
#include <string.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>

#include "../include/logger.h"
#include "../include/parser.h"


void parse_packet(const unsigned char *packet, int len) {
    const struct ip *ip = (struct ip*)(packet + 0xE);
    const struct tcphdr *tcp;
    const char *payload;

    int ip_len, tcp_len, payload_len;
    
    RequestEvent ev = {0x0};

    inet_ntop(AF_INET, &(ip->ip_src), ev.src_ip, sizeof(ev.src_ip));
    ip_len = ip->ip_hl * 0x4;
    
    tcp = (struct tcphdr*) ((u_char*)ip + ip_len);
    tcp_len = tcp -> th_off * 0x4;
    
    payload = (char*)tcp + tcp_len;
    payload_len = ntohs(ip->ip_len) - (ip_len + tcp_len);

    ev.timestamp = time(NULL);

    if (payload_len > 0x0) {
        if (ntohs(tcp->th_dport) == 0x50 || ntohs(tcp -> th_sport) == 0x50) {
            strcpy(ev.protocol, "HTTP");
            char *host_ptr = strstr(payload, "Host:");

            if (host_ptr) {
                sscanf(host_ptr, "Host: %255s", ev.host);
                char method[8], path[512];
             
                sscanf(payload, "%7s %511s", method, path);
                strncpy(ev.path, path, sizeof(ev.path));
             
                logger_log(&ev);
            }

            if (ntohs(tcp -> th_dport) == 0x1BB || ntohs(tcp -> th_sport) == 0x1BB) {
                strcpy(ev.protocol, "HTTPS");

                strncpy(ev.host, "未知域名", sizeof(ev.host));
                logger_log(&ev);
            }
        }
    }
}