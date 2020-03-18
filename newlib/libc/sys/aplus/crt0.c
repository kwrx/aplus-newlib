#include <stdint.h>
#include <stddef.h>

extern void __libc_init_array();
extern void __libc_fini_array();

extern char** environ;

extern int main(int, char**, char**);




void __libc_init_traps() {

}

void __libc_init_tls() {

}


void _start(uintptr_t* args) {

    extern int __bss_start;
    extern int end;

    long i;
    for(i = (long) &__bss_start; i < (long) &end; i += sizeof(unsigned long))
        *(unsigned long*) i = 0;


    __libc_init_array();
    __libc_init_traps();
    __libc_init_tls();

    atexit(__libc_fini_array);
    tzset();


    int argc = (int) args[0];
    char** argv = (char**) args[1];
    char** envp = (char**) args[2];

    environ = envp;


    exit(main(argc, argv, envp));

}