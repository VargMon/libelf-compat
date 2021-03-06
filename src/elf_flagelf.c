/* Manipulate ELF file flags.
   Copyright (C) 1999, 2000, 2001, 2002 Red Hat, Inc.
   This file is part of elfutils.
   Written by Ulrich Drepper <drepper@redhat.com>, 1999.

   This file is free software; you can redistribute it and/or modify
   it under the terms of either

     * the GNU Lesser General Public License as published by the Free
       Software Foundation; either version 3 of the License, or (at
       your option) any later version

   or

     * the GNU General Public License as published by the Free
       Software Foundation; either version 2 of the License, or (at
       your option) any later version

   or both in parallel, as here.

   elfutils is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received copies of the GNU General Public License and
   the GNU Lesser General Public License along with this program.  If
   not, see <http://www.gnu.org/licenses/>.  */

#ifdef HAVE_CONFIG_H
# include <config.h>
#endif

#include <stddef.h>

#include "libelf.h"
#include "libelfP.h"


unsigned int
elf_flagelf (elf, cmd, flags)
     Elf *elf;
     Elf_Cmd cmd;
     unsigned int flags;
{
  unsigned int result;

  if (elf == NULL)
    return 0;

  if (unlikely (elf->kind != ELF_K_ELF))
    {
      __libelf_seterrno (ELF_E_INVALID_HANDLE);
      return 0;
    }

  if (likely (cmd == ELF_C_SET))
    result = (elf->flags
	      |= (flags & (ELF_F_DIRTY | ELF_F_LAYOUT | ELF_F_PERMISSIVE)));
  else if (likely (cmd == ELF_C_CLR))
    result = (elf->flags
	      &= ~(flags & (ELF_F_DIRTY | ELF_F_LAYOUT | ELF_F_PERMISSIVE)));
  else
    {
      __libelf_seterrno (ELF_E_INVALID_COMMAND);
      return 0;
    }

  return result;
}
