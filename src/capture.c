#include <pcap.h>
#include <stdio.h>

#include "../include/capture.h"
#include "../include/parser.h"

#define SNAP_LEN 0x5EE

static void packet_handler(u_char *args, const struct pcap_pkthdr *header, const u_char *packet) {
    parser_handle_packet(packet, header->caplen);
}

void capture_start(const char *dev) {
    char errbuf[PCAP_ERRBUF_SIZE];

    pcap_t *handle = pcap_open_live(dev, SNAP_LEN, 1, 1000, errbuf);

    if (!handle) {
        fprintf(stderr, "Couldn't open device %s: %s\n", dev, errbuf);
        return;
    }

    pcap_loop(handle, -1, packet_handler, NULL);
    pcap_close(handle);
}