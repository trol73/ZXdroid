/* event.c: Routines needed for dealing with the event list
   Copyright (c) 2000-2008 Philip Kendall

   $Id: event.c 3942 2009-01-10 14:18:46Z pak21 $

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

   E-mail: philip-fuse@shadowmagic.org.uk

*/

#include <config.h>

#include <string.h>

#include <libspectrum.h>

#include "event.h"
#include "ui/ui.h"

/* A large value to mean `no events due' */
static const libspectrum_dword event_no_events = 0xffffffff;

/* When will the next event happen? */
libspectrum_dword event_next_event;

/* The actual list of events */
static GSList *event_list = NULL;

/* An event ready to be reused */
static event_t *event_free = NULL;

/* A null event */
int event_type_null;

typedef struct event_descriptor_t {
  event_fn_t fn;
  char *description;
} event_descriptor_t; 

typedef struct event_typeuser_t {
  int type;
  gpointer data;
} event_typeuser_t;

static GArray *registered_events;

int
event_init( void )
{
  registered_events = g_array_new( FALSE, FALSE, sizeof( event_descriptor_t ) );
  if( !registered_events ) {
    ui_error( UI_ERROR_ERROR, "out of memory at %s:%d\n", __FILE__, __LINE__ );
    return 1;
  }

  event_type_null = event_register( NULL, "[Deleted event]" );
  if( event_type_null == -1 ) return 1;

  event_next_event = event_no_events;
  return 0;
}

int
event_register( event_fn_t fn, const char *description )
{
  event_descriptor_t descriptor;

  descriptor.fn = fn;
  descriptor.description = strdup( description );
  if( !descriptor.description ) {
    ui_error( UI_ERROR_ERROR, "out of memory at %s:%d\n", __FILE__, __LINE__ );
    return -1;
  }

  g_array_append_val( registered_events, descriptor );

  return registered_events->len - 1;
}

static gint
event_add_cmp( gconstpointer a1, gconstpointer b1 )
{
  const event_t *a = a1, *b = b1;

  return a->tstates != b->tstates ? a->tstates - b->tstates
		                  : a->type - b->type;
}

/* Add an event at the correct place in the event list */
int
event_add_with_data( libspectrum_dword event_time, int type, void *user_data )
{
  event_t *ptr;

  if( event_free ) {
    ptr = event_free;
    event_free = NULL;
  } else {
    ptr = malloc( sizeof( *ptr ) );
    if( !ptr ) return 1;
  }

  ptr->tstates = event_time;
  ptr->type =type;
  ptr->user_data = user_data;

  if( event_time < event_next_event ) {
    event_next_event = event_time;
    event_list = g_slist_prepend( event_list, ptr );
  } else {
    event_list = g_slist_insert_sorted( event_list, ptr, event_add_cmp );
  }

  return 0;
}

/* Do all events which have passed */
int
event_do_events( void )
{
  event_t *ptr;

  while(event_next_event <= tstates) {
    ptr = event_list->data;
    event_descriptor_t descriptor =
      g_array_index( registered_events, event_descriptor_t, ptr->type );

    /* Remove the event from the list *before* processing */
    event_list = g_slist_remove( event_list, ptr );

    if( event_list == NULL ) {
      event_next_event = event_no_events;
    } else {
      event_next_event = ((event_t*)(event_list->data))->tstates;
    }

    if( descriptor.fn ) descriptor.fn( ptr->tstates, ptr->type, ptr->user_data );

    if( event_free ) {
      free( ptr );
    } else {
      event_free = ptr;
    }
  }

  return 0;
}

static void
event_reduce_tstates( gpointer data, gpointer user_data )
{
  event_t *ptr = data;
  libspectrum_dword *tstates_per_frame = user_data;

  ptr->tstates -= *tstates_per_frame;
}

/* Called at end of frame to reduce T-state count of all entries */
int
event_frame( libspectrum_dword tstates_per_frame )
{
  g_slist_foreach( event_list, event_reduce_tstates, &tstates_per_frame );

  event_next_event = event_list ?
    ((event_t*)(event_list->data))->tstates : event_no_events;

  return 0;
}

/* Do all events that would happen between the current time and when
   the next interrupt will occur; called only when RZX playback is in
   effect */
int
event_force_events( void )
{
  while( event_next_event < machine_current->timings.tstates_per_frame ) {

    /* Jump along to the next event */
    tstates = event_next_event;
    
    /* And do that event */
    event_do_events();

  }

  return 0;
}

static void
set_event_null( gpointer data, gpointer user_data )
{
  event_t *ptr = data;
  int *type = user_data;

  if( ptr->type == *type ) ptr->type = event_type_null;
}

static void
set_event_null_2( gpointer data, gpointer user_data )
{
  event_t *ptr = data;
  event_typeuser_t *e = user_data;

  if( ptr->type == e->type && ptr->user_data == e->data )
    ptr->type = event_type_null;
}

/* Remove all events of a specific type from the stack */
int
event_remove_type( int type )
{
  g_slist_foreach( event_list, set_event_null, &type );
  return 0;
}

/* Remove all events of a specific type and user data from the stack */
int
event_remove_type_user_data( int type, gpointer user_data )
{
  event_typeuser_t e;

  e.type = type;
  e.data = user_data;
  g_slist_foreach( event_list, set_event_null_2, &e );
  return 0;
}

/* Free the memory used by a specific entry */
static void
event_free_entry( gpointer data, gpointer user_data GCC_UNUSED )
{
  free( data );
}

/* Clear the event stack */
int
event_reset( void )
{
  g_slist_foreach( event_list, event_free_entry, NULL );
  g_slist_free( event_list );
  event_list = NULL;

  event_next_event = event_no_events;

  free( event_free );
  event_free = NULL;

  return 0;
}

/* Call a user-supplied function for every event in the current list */
int
event_foreach( GFunc function, gpointer user_data )
{
  g_slist_foreach( event_list, function, user_data );
  return 0;
}

/* A textual representation of each event type */
const char*
event_name( int type )
{
  return g_array_index( registered_events, event_descriptor_t, type ).description;
}

/* Tidy-up function called at end of emulation */
int
event_end( void )
{
  return event_reset();
}
