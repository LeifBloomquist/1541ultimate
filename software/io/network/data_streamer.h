#ifndef DATA_STREAMER_H
#define DATA_STREAMER_H

#include "netif/etharp.h"
#include "lwip/inet.h"
#include "lwip/tcpip.h"
#include "lwip/pbuf.h"
#include <lwip/stats.h>
#include "menu.h"
#include "subsys.h"
#include "config.h"

extern "C" {
#include "arch/sys_arch.h"
}


typedef struct {
    int      stream_id;
    uint32_t dest_ip;
    int      dest_port;
    uint8_t  dest_mac[6];
    uint8_t  enable;
} stream_config_t;


class DataStreamer : public ObjectWithMenu
{
    ConfigStore *cfg;

    uint8_t  my_mac[6];
    uint32_t my_ip;

    stream_config_t streams[4];

    static int S_startStream(SubsysCommand *cmd);
    static int S_stopStream(SubsysCommand *cmd);

    int startStream(SubsysCommand *cmd);
    int stopStream(SubsysCommand *cmd);

    void calculate_udp_headers(int id);
    void send_udp_packet(uint32_t ip, uint16_t port);
public:
    DataStreamer();
    virtual ~DataStreamer();

    // from ObjectWithMenu
    int fetch_task_items(Path *path, IndexedList<Action*> &item_list);

};

extern DataStreamer dataStreamer;

#endif
