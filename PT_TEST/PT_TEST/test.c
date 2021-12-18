#include "pt.h"

PT_THREAD(sender(struct pt *pt))
{
	PT_BEGIN(pt);
	do {
		send_packet();
		/* Wait until an ackowledgement has been received, or until the
		   timer expires. If the timer expires, we should send the packet
		   again. */
		timer_set(&timer, TIMEOUT);
		PT_WAIT_UNTIL(pt, acknowledgment_received() ||
			timer_expired(&timer));
	} while (timer_expired(&timer));
	PT_END(pt);
}

PT_THREAD(receiver(struct pt *pt))
{
	PT_BEGIN(pt);
	/* Wait until a packet has been received, and send an
	   acknowledgment. */
	PT_WAIT_UNTIL(pt, packet_received());
	send_acknowledgement();
	PT_END(pt);
}