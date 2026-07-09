#include "can.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <sys/ioctl.h>

#include <net/if.h>

#include <linux/can/raw.h>

static int can_socket = -1;

int can_init(const char *ifname)
{
    struct sockaddr_can addr;
    struct ifreq ifr;

    can_socket = socket(PF_CAN, SOCK_RAW, CAN_RAW);

    if(can_socket < 0)
    {
        perror("socket");
        return -1;
    }

    strcpy(ifr.ifr_name, ifname);

    ioctl(can_socket, SIOCGIFINDEX, &ifr);

    addr.can_family = AF_CAN;
    addr.can_ifindex = ifr.ifr_ifindex;

    if(bind(can_socket, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {
        perror("bind");
        return -1;
    }

    return 0;
}

int can_receive(struct can_frame *frame)
{
    return read(can_socket, frame, sizeof(struct can_frame));
}

int can_send(struct can_frame *frame)
{
    return write(can_socket, frame, sizeof(struct can_frame));
}

void can_close(void)
{
    if(can_socket >= 0)
        close(can_socket);
}