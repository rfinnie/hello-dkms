#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/seq_file.h>

#define MOD_LICENSE "GPL"
#define MOD_DESC "Hello World example"
#define MOD_AUTHOR "Ryan Finnie <ryan@finnie.org>"

static int hello_proc_data(struct seq_file *m, void *v) {
  seq_printf(m, "Hello, world!\n");
  return 0;
}

static int hello_proc_open(struct inode *i, struct file *f) {
  return single_open(f, hello_proc_data, NULL);
}

static const struct file_operations hello_proc_fops = {
  .owner = THIS_MODULE,
  .open = hello_proc_open,
  .read = seq_read,
  .llseek = seq_lseek,
  .release = single_release,
};

static int __init hello_init(void) {
  printk(KERN_INFO "hello: Hello, world!\n");
  proc_create("hello", 0, NULL, &hello_proc_fops);
  return 0;
}

static void __exit hello_exit(void) {
  printk(KERN_INFO "hello: Goodbye, world!\n");
  remove_proc_entry("hello", NULL);
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE(MOD_LICENSE);
MODULE_DESCRIPTION(MOD_DESC);
MODULE_AUTHOR(MOD_AUTHOR);

