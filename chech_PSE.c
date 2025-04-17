#include <linux/module.h>
#include <linux/kernel.h>


static int __init cr4_init(void)
{
    unsigned long cr4;

    asm volatile("mov %%cr4, %0" : "r=" (cr4));

    if(cr4 & (1 << 4)){
        :wq

    }
}
