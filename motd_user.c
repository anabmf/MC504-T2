/*
    Custom system calls: set_motd (468) and get_motd (469) for MC504 project.
 
    Entries added:
      468    common    set_motd    sys_set_motd
      469    common    get_motd    sys_get_motd
 
    You must ensure these numbers (468 and 469) are not already used by other syscalls.
 */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/syscall.h>

#define __NR_set_motd 468
#define __NR_get_motd 469
#define MOTD_MAX_LEN 256

int main() {
    char motd_buf[MOTD_MAX_LEN];
    char user_input[MOTD_MAX_LEN];

    // User input
    printf("Enter the new Message of the Day (MOTD): ");
    if (fgets(user_input, sizeof(user_input), stdin) == NULL) {
        fprintf(stderr, "Failed to read user input.\n");
        return 1;
    }

    // Remove trailing newline if present
    user_input[strcspn(user_input, "\n")] = '\0';

    // Set the new MOTD in the kernel
    long ret = syscall(__NR_set_motd, user_input);
    if (ret != 0) {
        perror("Failed to set MOTD");
        return 1;
    }
    printf("MOTD successfully updated!\n");

    // Retrieve and print the current MOTD from the kernel
    ret = syscall(__NR_get_motd, motd_buf, sizeof(motd_buf));
    if (ret != 0) {
        perror("Failed to get MOTD");
        return 1;
    }

    printf("Current MOTD: %s\n", motd_buf);
    return 0;
}
