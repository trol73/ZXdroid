/* memory.c: memory allocator routines
   Copyright (c) 2008 Philip Kendall

   $Id$

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License along
   with this program; if not, write to the Free Software Foundation, Inc.,
   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

   Author contact information:

   E-mail: Philip Kendall <philip-fuse@shadowmagic.org.uk>

*/

#include <config.h>

#include <stdlib.h>

#include "internals.h"

libspectrum_malloc_fn_t libspectrum_malloc_fn = malloc;
libspectrum_calloc_fn_t libspectrum_calloc_fn = calloc;
libspectrum_realloc_fn_t libspectrum_realloc_fn = realloc;
libspectrum_free_fn_t libspectrum_free_fn = free;

void*
libspectrum_malloc( size_t size )
{
  void *ptr = libspectrum_malloc_fn( size );

  /* If size == 0, acceptable to return NULL */
  if( size && !ptr ) abort();

  return ptr;
}

void*
libspectrum_calloc( size_t nmemb, size_t size )
{
  void *ptr = libspectrum_calloc_fn( nmemb, size );

  /* If nmemb * size == 0, acceptable to return NULL */
  if( ( nmemb * size ) && !ptr ) abort();

  return ptr;
}

void*
libspectrum_realloc( void *ptr, size_t size )
{
  ptr = libspectrum_realloc_fn( ptr, size );

  /* If size == 0, acceptable to return NULL */
  if( size && !ptr ) abort();

  return ptr;
}

void
libspectrum_free( void *ptr )
{
  libspectrum_free_fn( ptr );
}

void
libspectrum_mem_set_vtable( libspectrum_mem_vtable_t *table )
{
  libspectrum_malloc_fn = table->malloc;
  libspectrum_calloc_fn = table->calloc;
  libspectrum_realloc_fn = table->realloc;
  libspectrum_free_fn = table->free;

#ifdef HAVE_LIB_GLIB
  {
    GMemVTable glib_table;

    glib_table.malloc = table->malloc;
    glib_table.realloc = table->realloc;
    glib_table.free = table->free;

    g_mem_set_vtable( &glib_table );
  }
#endif                  /* #ifdef HAVE_LIB_GLIB */
}
