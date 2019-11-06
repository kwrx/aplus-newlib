#include <stdint.h>
#include <stddef.h>


extern void __libc_init_array();
extern void __libc_fini_array();

extern int main(int, char**, char**);


void __libc_init_traps() {

}

void __libc_init_tls() {

}


void _start(void) {

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


    int argc = 0;
    char* argv[] = { NULL };
    char* envp[] = { NULL };

    exit(main(argc, argv, envp));

}