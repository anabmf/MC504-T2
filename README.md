# Custom System Call – MC504 (Unicamp - 1st Semester 2025)

This project was developed as part of the **MC504 – Operating Systems** course at the University of Campinas (Unicamp) during the first semester of 2025.

## Description

The goal of this project is to implement a custom system call in the Linux kernel that counts and returns the number of processes belonging to a given user.

Project developed by **Ana Beatriz Mota (@anabmf), Arthur Kina (@ArthurKina) , Matheus Seiji Noda (@SeijiNoda)**, and **Vinicius Borges (@viniciusborgeslei)** for the MC504 – Operating Systems course (Unicamp, 1st Semester 2025).

---

## System Call Implementation Notes

### System Call Numbers Used

We introduced two custom system calls in the Linux kernel:

```
460    common    set_motd    __x64_sys_set_motd
461    common    get_motd    __x64_sys_get_motd
```

### Guidelines and Restrictions

- System call numbers must be **manually assigned** in the syscall table located at:
  ```
  arch/x86/entry/syscalls/syscall_64.tbl
  ```

- The numbers used (460 and 461) were chosen to avoid conflict with existing system calls in our kernel version.

- These numbers must be **unique and unused** in the current syscall table.

- In the user-space code (e.g., C programs using `syscall()`), the same syscall numbers must be defined using:
  ```c
  #define __NR_set_motd 460
  #define __NR_get_motd 461
  ```

- After editing the syscall table and adding the kernel function implementations, it is necessary to:
  1. Recompile the Linux kernel.
  2. Install the new kernel.
  3. Reboot into the newly compiled kernel version.

- The `motd_user.c` program was created using the `syscall()` function to interact with the newly added syscalls. This program allows the user to set and retrieve a "Message of the Day" (MOTD) stored in kernel space.

---
