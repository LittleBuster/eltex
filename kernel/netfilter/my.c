// Netfilter sniffer
//
// Copyright (C) 2017 Sergey Denisov.
// Written by Sergey Denisov aka LittleBuster (DenisovS21@gmail.com)
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU General Public Licence 3
// as published by the Free Software Foundation; either version 3
// of the Licence, or (at your option) any later version.

#include <linux/init.h> 
#include <linux/module.h>
#include <asm/uaccess.h>
#include <linux/kernel.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>
#include <linux/skbuff.h>
#include <linux/udp.h>
#include <linux/ip.h>
#include <net/ip.h>
#include <linux/inet.h>


MODULE_LICENSE("GPL"); 
MODULE_AUTHOR("Sergey Denisov <DenisovS21@gmail.com>"); 

struct nf_hook_ops nfops;


unsigned int HookPackets(uint hooknum, struct sk_buff *skb, const struct net_device *in, const struct net_device *out, int (*okfn)(struct sk_buff *))
{
	struct iphdr *iph = (struct iphdr *)skb_network_header(skb);
 
	if (htonl(in_aton("192.168.1.1")) == htonl(iph->saddr)) {
		printk(KERN_INFO "Packet from router was detected!!!\n");
	}
	return NF_ACCEPT;
}


static int __init InitModule(void)
{
        printk(KERN_INFO "Hello, netfilter.\n");

        nfops.hook = (nf_hookfn *)HookPackets;
        nfops.pf = PF_INET;
        nfops.hooknum = 0;
        nfops.priority = NF_IP_PRI_FIRST;

        nf_register_hook(&nfops);
        return 0;
}

static void __exit ExitModule(void)
{
        printk(KERN_INFO "Goodbye, netfilter.\n");
        nf_unregister_hook(&nfops);
}

module_init(InitModule);
module_exit(ExitModule);