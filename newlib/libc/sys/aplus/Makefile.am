AUTOMAKE_OPTIONS = cygnus
INCLUDES = $(NEWLIB_CFLAGS) $(CROSS_CFLAGS) $(TARGET_CFLAGS)
AM_CCASFLAGS = $(INCLUDES)
 
noinst_LIBRARIES = lib.a
 
if MAY_SUPPLY_SYSCALLS
extra_objs = _exit.o _isatty.o _lseek64.o close.o fstat.o getpid.o gettimeofday.o kill.o lseek.o read.o sbrk.o write.o
else
extra_objs =
endif

 
lib_a_SOURCES =
lib_a_LIBADD = $(extra_objs) dlmalloc.o
EXTRA_lib_a_SOURCES = crt0.c _exit.c _isatty.c _lseek64.c close.c dlmalloc.c fstat.c getpid.c gettimeofday.c kill.c lseek.c read.c sbrk.c write.c
lib_a_DEPENDENCIES = $(extra_objs) dlmalloc.o
lib_a_CCASFLAGS = $(AM_CCASFLAGS)
lib_a_CFLAGS = $(AM_CFLAGS)
 
if MAY_SUPPLY_SYSCALLS
all: crt0.o
endif
 
ACLOCAL_AMFLAGS = -I ../../..
CONFIG_STATUS_DEPENDENCIES = $(newlib_basedir)/configure.host