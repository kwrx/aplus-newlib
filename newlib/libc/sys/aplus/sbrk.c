/*
 * Author:
 *      Antonino Natale <antonio.natale97@hotmail.com>
 * 
 * Copyright (c) 2013-2019 Antonino Natale
 * 
 * 
 * This file is part of aPlus.
 * 
 * aPlus is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * aPlus is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with aPlus.  If not, see <http://www.gnu.org/licenses/>.
 */


#include <stdint.h>
#include <stddef.h>
#include <unistd.h>
#include <errno.h>

extern long __syscall(long, long, long, long, long, long, long);


void* sbrk(intptr_t increment) {
    
    uintptr_t ibrk = __syscall(12, 0, 0, 0, 0, 0, 0);
    uintptr_t ebrk = __syscall(12, ibrk + increment, 0, 0, 0, 0, 0);

    if(ibrk == ebrk)
        return errno = ENOMEM, NULL;

    return (void*) ibrk;

}
