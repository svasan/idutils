/* idfile.h -- defs for mkid database file header & interface to idfile.c
   Copyright (C) 1986, 1995 Greg McGary
  
   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.
  
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
  
   You should have received a copy of the GNU General Public License
   along with this program; see the file COPYING.  If not, write to the
   Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*/

#ifndef _idfile_h_
#define _idfile_h_ 1

#include <sys/types.h>
#include <stdio.h>

#define	IDFILE	"ID"

struct idhead
{
  char idh_magic[2];
#define	IDH_MAGIC "\311\304"	/* ("ID" with hi bits set) */
  char idh_pad_1;
  char idh_version;
#define	IDH_VERSION	3
  unsigned short idh_flags;
#define IDH_COUNTS 0x0001	/* occurrence counts are included with each token */
  long idh_args;		/* total # of args for mkid update */
  long idh_paths;		/* total # of file names for mkid update */
  long idh_tokens;		/* total # of tokens */
  long idh_buf_size;		/* # of bytes in longest entry (bufsiz for lid) */
  long idh_vec_size;		/* # of hits in longest entry (max vector size for lid) */
  off_t idh_args_offset;	/* file offset of args */
  off_t idh_tokens_offset;	/* file offset of tokens section */
  off_t idh_end_offset;		/* file offset beyond tokens section */
};

#define	GETARG(argc, argv)	((argc)--, *(argv)++)
#define	UNGETARG(argc, argv)	((argc)++, --(argv))

struct idarg;
FILE *init_idfile (char const *id_file, struct idhead *idhp, struct idarg **id_args);
int read_idhead (FILE *input_FILE, struct idhead *idh);
int write_idhead (FILE *input_FILE, struct idhead *idh);
int sizeof_idhead (void);

#endif /* _idfile_h_ */