#include "common.h"

#include <linux/if_ether.h>
#include <linux/swab.h>
#include <linux/pkt_cls.h>

__section("classifier_egress_drop") int egress_drop(struct __sk_buff *skb) {
	void *data_end = (void *)(unsigned long long)skb->data_end;
	void *data = (void *)(unsigned long long)skb->data;
	struct ethhdr *eth = data;

	/* Drop mailformated packet	*/
	if (data + sizeof(struct ethhdr) > data_end)
		return TC_ACT_SHOT;

	/* Drop legacy IP traffic */
	if (eth->h_proto == ___constant_swab16(ETH_P_IP))
		return TC_ACT_SHOT;

	return TC_ACT_SHOT;
}

__section("classifier_ingress_drop") int ingress_drop(struct __sk_buff *skb) {
	void *data_end = (void *)(unsigned long long)skb->data_end;
	void *data = (void *)(unsigned long long)skb->data;
	struct ethhdr *eth = data;

	/* Drop mailformated packet	*/
	if (data + sizeof(struct ethhdr) > data_end)
		return TC_ACT_SHOT;

	/* Drop legacy IP traffic */
	if (eth->h_proto == ___constant_swab16(ETH_P_IP))
		return TC_ACT_SHOT;

	return TC_ACT_SHOT;
}
