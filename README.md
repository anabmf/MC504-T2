# Custom System Call – MC504 (Unicamp - 1st Semester 2025)

This project was developed as part of the MC504 – Operating Systems course at the University of Campinas (Unicamp) during the first semester of 2025, taught by Professor Islene Calciolari Garcia.

## Description

The goal of this project is to implement custom system calls in the Linux kernel that allow setting and retrieving a "Message of the Day" (MOTD). These system calls enable user-space programs to interact with the kernel to store and access a global message.

Project developed by Ana Beatriz Mota (@anabmf), Arthur Kina (@ArthurKina), Matheus Seiji Noda (@SeijiNoda), and Vinicius Borges (@viniciusborgeslei).

---

## Tutorials and Resources

This implementation was guided by the following resources:

- [Creating System Calls](https://docs.lkcamp.dev/unicamp_group/systemcalls/)
- [Booting the Kernel](https://docs.lkcamp.dev/intro_tutorials/boot/)
- [Device Drivers – Shared Folder Section](https://docs.lkcamp.dev/intro_tutorials/device_drivers/)

The project used the **Debian Linux source code** to implement and test the system calls in a virtual machine.

---

## System Call Implementation

Two system calls were introduced:

- `set_motd`: Stores a message string as the current "Message of the Day".
- `get_motd`: Retrieves the stored "Message of the Day".

---

## Kernel Source Code Modifications

Below are the modifications made to integrate the new system calls:

---

### `linux/kernel/sys_ni.c`

Added the conditional syscall macros:

```c
COND_SYSCALL(sys_set_motd);
COND_SYSCALL(sys_get_motd);
```

---

### `linux/include/uapi/asm-generic/unistd.h`

Defined syscall numbers and declared them using the `__SYSCALL` macro:

```c
#define __NR_set_motd 468
__SYSCALL(__NR_set_motd, sys_set_motd)

#define __NR_get_motd 469
__SYSCALL(__NR_get_motd, sys_get_motd)

#undef __NR_syscalls
#define __NR_syscalls 470
```

---

### `linux/arch/x86/entry/syscalls/syscall_64.tbl`

Mapped syscall numbers to kernel function names for 64-bit architecture:

```plaintext
468    common    set_motd    sys_set_motd
469    common    get_motd    sys_get_motd
```

---

### `linux/include/linux/syscalls.h`

Declared the syscall functions:

```c
asmlinkage long sys_set_motd(const char __user *msg, size_t len);
asmlinkage long sys_get_motd(char __user *buf, size_t len);
```

---

### `linux/kernel/Makefile`

Added the object file for the MOTD implementation:

```make
obj-y += motd.o
```

---
