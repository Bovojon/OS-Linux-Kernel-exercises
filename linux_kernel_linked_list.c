/* NOTE: Makefile contains "make" to compile */
#include <linux/list.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/types.h>
#include <linux/module.h>
#include <linux/init.h>

#define BIRTHDAYS_NUM    5
/* Define the birthday struct below */
struct birthday {
    int day;
    int month;
    int year;
    struct list_head list;
};
/* LIST_HEAD is defined in list.h. We declare and initialize linked list head below. */
LIST_HEAD(birthday_list);

/* Function 1 - main function that loads birthdays*/
int load_birthdays(void){
    /* Allocate memory for 5 birthday elements in the linked list */
    struct birthday *person;
    int i = 0;
    for(i = 0; i < BIRTHDAYS_NUM; i++){
        /* kmalloc is the normal method of allocating memory in the kernel. slab.h is needed to use kmalloc. GFP_KERNEL allocates normal kernel ram. */
        person = kmalloc(sizeof(*person), GFP_KERNEL);
        person->day = 2 + i;
        person->month = 7 + i;
        person->year = 1995 + i;
        /* INIT_LIST_HEAD is from list.h */
        INIT_LIST_HEAD(&person->list);
        list_add_tail(&person->list, &birthday_list);
    }

    /*  Traverse linked list and print each birthday to the kernel log */
    // birthday *person;
    // list_for_each_entry is from list.h and it iterates over a list of given type
    list_for_each_entry(person, &birthday_list, list) {
        printk(KERN_INFO "Birthday: %d/%d/%d\n", person->month, person->day, person->year);
    }
    return 0;
}
/* Function 2 - called when the module is loaded */
int simple_init(void) {
  printk(KERN_INFO "Loading Module\n");
  // Call main function that loads birthdays
  load_birthdays();
  return 0;
}
/////////////////////////////
/* Function 3 - main function to delete linked list from kernel memory */
int remove_birthdays(void) {
  /* Traverse the linked list and delete its elements. */
  struct birthday *ptr, *next;
  // list_for_each_entry_safe is from list.h and it iterates over list of given type safe against removal of list entry
  list_for_each_entry_safe(ptr, next, &birthday_list, list) {
      printk(KERN_INFO "Removing Birthday: %d/%d/%d\n", ptr->month, ptr->day, ptr->year);
      list_del(&ptr->list);
      kfree(ptr);
  }
  return 0;
}
/* Function 4 - called when the module is removed */
void simple_exit(void) {
    printk(KERN_INFO "Removing module\n");
    remove_birthdays();
    printk(KERN_INFO "Freed memory\n");
}
/////////////////////////////
/* Macros for registering module entry and exit points */
module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");
