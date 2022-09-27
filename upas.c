#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/proc_fs.h>
#include <linux/sched.h>
#include <linux/sched/signal.h>
#include <linux/pid.h>
MODULE_LICENSE("Dual BSD/GPL");

int unkill_major = 113;

ssize_t unkill_write(struct file *filp, const char *buf, size_t count, loff_t *f_pos);
ssize_t unkill_read(struct file *filp, char *buf, size_t count, loff_t *f_pos);
int unkill_open(struct inode *inode, struct file *filp);
int unkill_release(struct inode *inode, struct file *filp);


int unkill_open(struct inode *inode, struct file *filp)
{
        return 0;
}

int unkill_release(struct inode *inode, struct file *filp)
{
        return 0;
}

ssize_t unkill_read(struct file *filp, char *buf, size_t count, loff_t *f_pos)
{
        struct pid *pid_struct;
        struct task_struct *ts;

        // count is read as target pid
        printk("Unkill module got the pid : %d", (int) count);

        // get pid struct
        pid_struct = find_get_pid((int) count);

        // get the task_struct
        ts = pid_task(pid_struct, PIDTYPE_PID);


        ts->signal->flags = ts->signal->flags | SIGNAL_UNKILLABLE;
        printk("Unkillable: pid %d marked as unkill\n", (int) count);
        if (*f_pos) {
                return 0;
        } else {                
                *f_pos++;
                return 1;
        }
}

ssize_t unkill_write(struct file *filp, const char *buf, size_t count, loff_t *f_pos)
{
        return 0;
}
struct file_operations unkill_fops = {
        .read = unkill_read,
        .write = unkill_write,
        .open = unkill_open,
        .release = unkill_release
};

int unkill_init(void)
{
        if (register_chrdev(unkill_major, "unkill", &unkill_fops) < 0 ) {
                printk("cannot obtain major number %d\n", unkill_major);
                return 1;
        }

        printk("Insert unkill module\n");
        return 0;
}
void unkill_exit(void)
{
        unregister_chrdev(unkill_major, "unkill");
        printk("Removing unkill module\n");
}


module_init(unkill_init);
module_exit(unkill_exit);
