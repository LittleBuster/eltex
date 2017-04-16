// Ssh blocker
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

#define BLOCK_PORT 22

struct nf_hook_ops nfops;


unsigned int HookPackets(uint hooknum, struct sk_buff *skb, const struct net_device *in, const struct net_device *out, int (*okfn)(struct sk_buff *))
{
        struct iphdr *ip;
        struct tcphdr *tcp;

        if (skb->protocol == htons(ETH_P_IP)) {
                ip = (struct iphdr *)skb_network_header(skb);
        
                if (ip->version == 4 && ip->protocol == IPPROTO_TCP) {
                        skb_set_transport_header(skb, ip->ihl * 4);
                        tcp = (struct tcphdr *)skb_transport_header(skb);
                        if (tcp->dest == htons(BLOCK_PORT)) {
                                pr_info("SSH packet found and dropped!");
                                return NF_DROP; 
                        }
                }
        }
        return NF_ACCEPT;
}


static int __init InitModule(void)
{
        pr_info("Hello, netfilter.\n");

        nfops.hook = (nf_hookfn *)HookPackets;
        nfops.pf = PF_INET;
        nfops.hooknum = 0;
        nfops.priority = NF_IP_PRI_FIRST;

        nf_register_hook(&nfops);
        return 0;
}

static void __exit ExitModule(void)
{
        pr_info("Goodbye, netfilter.\n");
        nf_unregister_hook(&nfops);
}

module_init(InitModule);
module_exit(ExitModule);