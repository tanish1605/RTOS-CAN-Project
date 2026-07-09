#ifndef CAN_H
#define CAN_H

#include <linux/can.h>

int can_init(const char *ifname);
int can_send(struct can_frame *frame);
int can_receive(struct can_frame *frame);
void can_close(void);

#endif