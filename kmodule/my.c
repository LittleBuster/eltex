#include <linux/init.h> 
#include <linux/module.h>
#include <asm/uaccess.h>
#include <linux/kernel.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>


MODULE_LICENSE("GPL"); 
MODULE_AUTHOR("Sergey Denisov <DenisovS21@gmail.com>"); 

struct nf_hook_ops bundle;


unsigned int HookPackets(uint hooknum, struct sk_buff *skb, const struct net_device *in, const struct net_device *out, int (*okfn)(struct sk_buff *))
{
	return NF_ACCEPT;
}


static int __init InitModule(void)
{
        printk(KERN_INFO "Hello, netfilter.\n");
        bundle.hook = HookPackets;
        //bundle.owner = THIS_MODULE;
        bundle.pf = PF_INET;
        bundle.hooknum = NF_INET_PRE_ROUTING;
        bundle.priority = NF_IP_PRI_FIRST;
        nf_register_hook(&bundle);
        return 0;
}

static void __exit ExitModule(void)
{
        printk(KERN_INFO "Goodbye, netfilter.\n");
        nf_unregister_hook(&bundle);
}

module_init(InitModule);
module_exit(ExitModule);