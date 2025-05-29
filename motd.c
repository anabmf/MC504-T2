// kernel/motd.c

#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/uaccess.h>
#include <linux/slab.h>

#define MOTD_MAX_LEN 256

static char motd[MOTD_MAX_LEN] = "Welcome";

SYSCALL_DEFINE1(set_motd, const char __user *, user_msg)
{
    char buf[MOTD_MAX_LEN];

    if (copy_from_user(buf, user_msg, MOTD_MAX_LEN))
        return -EFAULT;

    buf[MOTD_MAX_LEN - 1] = '\0'; 
    strncpy(motd, buf, MOTD_MAX_LEN);
    motd[MOTD_MAX_LEN - 1] = '\0'; 

    return 0;
}

SYSCALL_DEFINE2(get_motd, char __user *, user_buf, size_t, len)
{
    size_t motd_len = strnlen(motd, MOTD_MAX_LEN);

    if (len < motd_len + 1)
        return -EINVAL;

    if (copy_to_user(user_buf, motd, motd_len + 1))
        return -EFAULT;

    return 0;
}

