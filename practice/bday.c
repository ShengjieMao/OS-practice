#include <linux/module.h>   
#include <linux/kernel.h>   
#include <linux/init.h>     
#include <linux/list.h>     
#include <linux/types.h>    
#include <linux/slab.h>     

typedef struct _birthday {

    int day;
    int month;
    int year;
    struct list_head list;

}birthday;

LIST_HEAD(birthday_list);

int birthday_init(void) {

    printk(KERN_INFO "Loading Module\n");

    birthday *person;
    int i = 0;
    for(i = 0; i < 5; i++) {
        person = kmalloc(sizeof(*person), GFP_KERNEL);
        person->day = 2 + i;
        person->month = 8 + i;
        person->year = 1995 + i;

        INIT_LIST_HEAD(&person->list);
        list_add_tail(&person->list, &birthday_list);

    }

    birthday *ptr;
    list_for_each_entry(ptr, &birthday_list, list) {

        printk(KERN_INFO "Month:%d Day:%d Year:%d\n", ptr->month, ptr->day, ptr->year);
    }

    return 0;
}

void birthday_exit(void) {

    printk(KERN_INFO "Removing Module\n");

    birthday *ptr, *next;
    list_for_each_entry_safe(ptr, next, &birthday_list, list) {

        printk(KERN_INFO "Removing Month:%d Day:%d Year:%d\n", ptr->month, ptr->day, ptr->year);

        list_del(&ptr->list);
        kfree(ptr);  
    }

    printk(KERN_INFO "Memory free\n");

}


module_init(birthday_init);
module_exit(birthday_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("BIRTHDAY MODULE");
MODULE_AUTHOR("SGG");
