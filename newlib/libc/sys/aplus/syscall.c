#include <errno.h>


#if defined(__x86_64__)


long __syscall(long nr, long p1, long p2,
                        long p3, long p4,
                        long p5, long p6);

__asm__ (

    ".global __syscall              \n\
    .type __syscall,@function       \n\
    __syscall:                      \n\
        movq %rdi,%rax              \n\
        movq %rsi,%rdi              \n\
        movq %rdx,%rsi              \n\
        movq %rcx,%rdx              \n\
        movq %r8,%r10               \n\
        movq %r9,%r8                \n\
        movq 8(%rsp),%r9            \n\
        syscall                     \n\
        ret                         \n"

);


#elif defined(__i386__)

long __syscall(long nr, long p1, long p2,
                        long p3, long p4,
                        long p5, long p6) {


    // TODO: ...                            
    errno = ENOSYS;
    return -1;
}

#endif



#define SC_6(args, nr, name)                    \
    __attribute__((weak))                       \
    long name (long p1, long p2,                \
               long p3, long p4,                \
               long p5, long p6) {              \
        long r = __syscall(nr, p1, p2, p3,      \
                               p4, p5, p6);     \
        if(r < 0 && r > -4096L)                 \
            return errno = -r, -1;              \
        return r;                               \
    }

#define SC_5(args, nr, name)                    \
    __attribute__((weak))                       \
    long name (long p1, long p2,                \
               long p3, long p4,                \
               long p5         ) {              \
        long r = __syscall(nr, p1, p2, p3,      \
                               p4, p5, 0L);     \
        if(r < 0 && r > -4096L)                 \
            return errno = -r, -1;              \
        return r;                               \
    }

#define SC_4(args, nr, name)                    \
    __attribute__((weak))                       \
    long name (long p1, long p2,                \
               long p3, long p4                 \
                               ) {              \
        long r = __syscall(nr, p1, p2, p3,      \
                               p4, 0L, 0L);     \
        if(r < 0 && r > -4096L)                 \
            return errno = -r, -1;              \
        return r;                               \
    }

#define SC_3(args, nr, name)                    \
    __attribute__((weak))                       \
    long name (long p1, long p2,                \
               long p3                          \
                               ) {              \
        long r = __syscall(nr, p1, p2, p3,      \
                               0L, 0L, 0L);     \
        if(r < 0 && r > -4096L)                 \
            return errno = -r, -1;              \
        return r;                               \
    }

#define SC_2(args, nr, name)                    \
    __attribute__((weak))                       \
    long name (long p1, long p2                 \
                                                \
                               ) {              \
        long r = __syscall(nr, p1, p2, 0L,      \
                               0L, 0L, 0L);     \
        if(r < 0 && r > -4096L)                 \
            return errno = -r, -1;              \
        return r;                               \
    }

#define SC_1(args, nr, name)                    \
    __attribute__((weak))                       \
    long name (long p1                          \
                                                \
                               ) {              \
        long r = __syscall(nr, p1, 0L, 0L,      \
                               0L, 0L, 0L);     \
        if(r < 0 && r > -4096L)                 \
            return errno = -r, -1;              \
        return r;                               \
    }

#define SC_0(args, nr, name)                    \
    __attribute__((weak))                       \
    long name (                                 \
                                                \
                               ) {              \
        long r = __syscall(nr, 0L, 0L, 0L,      \
                               0L, 0L, 0L);     \
        if(r < 0 && r > -4096L)                 \
            return errno = -r, -1;              \
        return r;                               \
    }


#define SC(args, nr, name)  \
    SC_##args (args, nr, name)





SC(2, 501, statvfs)
SC(1, 502, nice)
SC(3, 8, _lseek64)


SC(3, 0, read)
SC(3, 1, write)
SC(3, 2, open)
SC(1, 3, close)
SC(2, 4, stat)
SC(2, 5, fstat)
SC(2, 6, lstat)
SC(3, 7, poll)
SC(3, 8, lseek)
SC(6, 9, mmap)
SC(3, 10, mprotect)
SC(2, 11, munmap)
SC(1, 12, brk)
SC(4, 13, rt_sigaction)
SC(4, 14, rt_sigprocmask)
SC(3, 16, ioctl)
SC(4, 17, pread64)
SC(4, 18, pwrite64)
SC(3, 19, readv)
SC(3, 20, writev)
SC(2, 21, access)
SC(1, 22, pipe)
SC(5, 23, select)
SC(1, 24, sched_yield)
SC(5, 25, mremap)
SC(3, 26, msync)
SC(3, 27, mincore)
SC(3, 28, madvise)
SC(3, 29, shmget)
SC(3, 30, shmat)
SC(3, 31, shmctl)
SC(1, 32, dup)
SC(2, 33, dup2)
SC(1, 34, pause)
SC(2, 35, nanosleep)
SC(2, 36, getitimer)
SC(1, 37, alarm)
SC(3, 38, setitimer)
SC(1, 39, getpid)
SC(4, 40, sendfile64)
SC(3, 41, socket)
SC(3, 42, connect)
SC(3, 43, accept)
SC(6, 44, sendto)
SC(6, 45, recvfrom)
SC(3, 46, sendmsg)
SC(3, 47, recvmsg)
SC(2, 48, shutdown)
SC(3, 49, bind)
SC(2, 50, listen)
SC(3, 51, getsockname)
SC(3, 52, getpeername)
SC(4, 53, socketpair)
SC(5, 54, setsockopt)
SC(5, 55, getsockopt)
SC(4, 56, clone);
SC(0, 57, fork);
SC(0, 58, vfork);
SC(3, 59, _execve);
SC(1, 60, _exit);
SC(1, 60, exit)
SC(4, 61, wait4)
SC(2, 62, kill)
SC(1, 63, uname)
SC(3, 64, semget)
SC(3, 65, semop)
SC(4, 66, semctl)
SC(1, 67, shmdt)
SC(2, 68, msgget)
SC(4, 69, msgsnd)
SC(5, 70, msgrcv)
SC(3, 71, msgctl)
SC(3, 72, fcntl)
SC(2, 73, flock)
SC(1, 74, fsync)
SC(1, 75, fdatasync)
SC(2, 76, truncate)
SC(2, 77, ftruncate)
SC(3, 78, getdents)
SC(2, 79, getcwd)
SC(1, 80, chdir)
SC(1, 81, fchdir)
SC(2, 82, rename)
SC(2, 83, mkdir)
SC(1, 84, rmdir)
SC(2, 85, creat)
SC(2, 86, link)
SC(1, 87, unlink)
SC(2, 88, symlink)
SC(3, 89, readlink)
SC(2, 90, chmod)
SC(2, 91, fchmod)
SC(3, 92, chown)
SC(3, 93, fchown)
SC(3, 94, lchown)
SC(1, 95, umask)
SC(2, 96, gettimeofday)
SC(2, 97, getrlimit)
SC(2, 98, getrusage)
SC(1, 99, sysinfo)
SC(1, 100, times)
SC(4, 101, ptrace)
SC(1, 102, getuid)
SC(3, 103, syslog)
SC(1, 104, getgid)
SC(1, 105, setuid)
SC(1, 106, setgid)
SC(1, 107, geteuid)
SC(1, 108, getegid)
SC(2, 109, setpgid)
SC(1, 110, getppid)
SC(1, 111, getpgrp)
SC(1, 112, setsid)
SC(2, 113, setreuid)
SC(2, 114, setregid)
SC(2, 115, getgroups)
SC(2, 116, setgroups)
SC(3, 117, setresuid)
SC(3, 118, getresuid)
SC(3, 119, setresgid)
SC(3, 120, getresgid)
SC(1, 121, getpgid)
SC(1, 122, setfsuid)
SC(1, 123, setfsgid)
SC(1, 124, getsid)
SC(2, 125, capget)
SC(2, 126, capset)
SC(2, 127, rt_sigpending)
SC(4, 128, rt_sigtimedwait)
SC(3, 129, rt_sigqueueinfo)
SC(2, 130, rt_sigsuspend)
SC(2, 131, sigaltstack)
SC(2, 132, utime)
SC(3, 133, mknod)
SC(1, 135, personality)
SC(2, 136, ustat)
SC(2, 137, statfs)
SC(2, 138, fstatfs)
SC(3, 139, sysfs)
SC(2, 140, getpriority)
SC(3, 141, setpriority)
SC(2, 142, sched_setparam)
SC(2, 143, sched_getparam)
SC(3, 144, sched_setscheduler)
SC(1, 145, sched_getscheduler)
SC(1, 146, sched_get_priority_max)
SC(1, 147, sched_get_priority_min)
SC(2, 148, sched_rr_get_interval)
SC(2, 149, mlock)
SC(2, 150, munlock)
SC(1, 151, mlockall)
SC(1, 152, munlockall)
SC(1, 153, vhangup)
SC(3, 154, modify_ldt)
SC(2, 155, pivot_root)
SC(1, 156, sysctl)
SC(5, 157, prctl)
SC(2, 158, arch_prctl)
SC(1, 159, adjtimex)
SC(2, 160, setrlimit)
SC(1, 161, chroot)
SC(1, 162, sync)
SC(1, 163, acct)
SC(2, 164, settimeofday)
SC(5, 165, mount)
SC(2, 166, umount)
SC(2, 167, swapon)
SC(1, 168, swapoff)
SC(4, 169, reboot)
SC(2, 170, sethostname)
SC(2, 171, setdomainname)
SC(3, 173, ioperm)
SC(3, 175, init_module)
SC(2, 176, delete_module)
SC(4, 179, quotactl)
SC(1, 186, gettid)
SC(3, 187, readahead)
SC(5, 188, setxattr)
SC(5, 189, lsetxattr)
SC(5, 190, fsetxattr)
SC(4, 191, getxattr)
SC(4, 192, lgetxattr)
SC(4, 193, fgetxattr)
SC(3, 194, listxattr)
SC(3, 195, llistxattr)
SC(3, 196, flistxattr)
SC(2, 197, removexattr)
SC(2, 198, lremovexattr)
SC(2, 199, fremovexattr)
SC(2, 200, tkill)
SC(1, 201, time)
SC(6, 202, futex)
SC(3, 203, sched_setaffinity)
SC(3, 204, sched_getaffinity)
SC(2, 206, io_setup)
SC(1, 207, io_destroy)
SC(5, 208, io_getevents)
SC(3, 209, io_submit)
SC(3, 210, io_cancel)
SC(3, 212, lookup_dcookie)
SC(1, 213, epoll_create)
SC(5, 216, remap_file_pages)
SC(3, 217, getdents64)
SC(1, 218, set_tid_address)
SC(1, 219, restart_syscall)
SC(4, 220, semtimedop)
SC(4, 221, fadvise64)
SC(3, 222, timer_create)
SC(4, 223, timer_settime)
SC(2, 224, timer_gettime)
SC(1, 225, timer_getoverrun)
SC(1, 226, timer_delete)
SC(2, 227, clock_settime)
SC(2, 228, clock_gettime)
SC(2, 229, clock_getres)
SC(4, 230, clock_nanosleep)
SC(1, 231, exit_group)
SC(4, 232, epoll_wait)
SC(4, 233, epoll_ctl)
SC(3, 234, tgkill)
SC(2, 235, utimes)
SC(6, 237, mbind)
SC(3, 238, set_mempolicy)
SC(5, 239, get_mempolicy)
SC(4, 240, mq_open)
SC(1, 241, mq_unlink)
SC(5, 242, mq_timedsend)
SC(5, 243, mq_timedreceive)
SC(2, 244, mq_notify)
SC(3, 245, mq_getsetattr)
SC(4, 246, kexec_load)
SC(5, 247, waitid)
SC(5, 248, add_key)
SC(4, 249, request_key)
SC(5, 250, keyctl)
SC(3, 251, ioprio_set)
SC(2, 252, ioprio_get)
SC(1, 253, inotify_init)
SC(3, 254, inotify_add_watch)
SC(2, 255, inotify_rm_watch)
SC(4, 256, migrate_pages)
SC(4, 257, openat)
SC(3, 258, mkdirat)
SC(4, 259, mknodat)
SC(5, 260, fchownat)
SC(3, 261, futimesat)
SC(4, 262, newfstatat)
SC(3, 263, unlinkat)
SC(4, 264, renameat)
SC(5, 265, linkat)
SC(3, 266, symlinkat)
SC(4, 267, readlinkat)
SC(3, 268, fchmodat)
SC(3, 269, faccessat)
SC(6, 270, pselect6)
SC(5, 271, ppoll)
SC(1, 272, unshare)
SC(2, 273, set_robust_list)
SC(3, 274, get_robust_list)
SC(6, 275, splice)
SC(4, 276, tee)
SC(4, 277, sync_file_range)
SC(4, 278, vmsplice)
SC(6, 279, move_pages)
SC(4, 280, utimensat)
SC(6, 281, epoll_pwait)
SC(3, 282, signalfd)
SC(2, 283, timerfd_create)
SC(1, 284, eventfd)
SC(4, 285, fallocate)
SC(4, 286, timerfd_settime)
SC(2, 287, timerfd_gettime)
SC(4, 288, accept4)
SC(4, 289, signalfd4)
SC(2, 290, eventfd2)
SC(1, 291, epoll_create1)
SC(3, 292, dup3)
SC(2, 293, pipe2)
SC(1, 294, inotify_init1)
SC(5, 295, preadv)
SC(5, 296, pwritev)
SC(4, 297, rt_tgsigqueueinfo)
SC(5, 298, perf_event_open)
SC(5, 299, recvmmsg)
SC(2, 300, fanotify_init)
SC(5, 301, fanotify_mark)
SC(4, 302, prlimit64)
SC(5, 303, name_to_handle_at)
SC(3, 304, open_by_handle_at)
SC(2, 305, clock_adjtime)
SC(1, 306, syncfs)
SC(4, 307, sendmmsg)
SC(2, 308, setns)
SC(3, 309, getcpu)
SC(6, 310, process_vm_readv)
SC(6, 311, process_vm_writev)
SC(5, 312, kcmp)
SC(3, 313, finit_module)
SC(3, 314, sched_setattr)
SC(4, 315, sched_getattr)
SC(5, 316, renameat2)
SC(3, 317, seccomp)
SC(3, 318, getrandom)
SC(2, 319, memfd_create)
SC(5, 320, kexec_file_load)
SC(3, 321, bpf)
SC(1, 323, userfaultfd)
SC(2, 324, membarrier)
SC(3, 325, mlock2)
SC(6, 326, copy_file_range)
SC(6, 327, preadv2)
SC(6, 328, pwritev2)
SC(4, 329, pkey_mprotect)
SC(2, 330, pkey_alloc)
SC(1, 331, pkey_free)