/* specplus2.c: Spectrum +2 specific routines
   Copyright (c) 1999-2004 Philip Kendall

   $Id: specplus2.c 3566 2008-03-18 12:59:16Z pak21 $

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

#include <stdio.h>

#include <libspectrum.h>

#include "disk/beta.h"
#include "machine.h"
#include "machines.h"
#include "settings.h"
#include "spec128.h"
#include "spec48.h"

/* The +2 emulation just uses the 128K routines */

static int specplus2_reset( void );

int specplus2_init( fuse_machine_info *machine )
{
  machine->machine = LIBSPECTRUM_MACHINE_PLUS2;
  machine->id = "plus2";

  machine->reset = specplus2_reset;

  machine->timex = 0;
  machine->ram.port_from_ula	     = spec48_port_from_ula;
  machine->ram.contend_delay	     = spectrum_contend_delay_65432100;
  machine->ram.contend_delay_no_mreq = spectrum_contend_delay_65432100;

  machine->unattached_port = spectrum_unattached_port;

  machine->shutdown = NULL;

  machine->memory_map = spec128_memory_map;

  return 0;

}

static int
specplus2_reset( void )
{
  int error;

  error = machine_load_rom( 0, 0, settings_current.rom_plus2_0,
                            settings_default.rom_plus2_0, 0x4000 );
  if( error ) return error;
  error = machine_load_rom( 2, 1, settings_current.rom_plus2_1,
                            settings_default.rom_plus2_1, 0x4000 );
  if( error ) return error;

  error = spec128_common_reset( 1 );
  if( error ) return error;

  error = periph_setup( spec128_peripherals, spec128_peripherals_count );
  if( error ) return error;
  periph_setup_kempston( PERIPH_PRESENT_OPTIONAL );
  periph_setup_interface1( PERIPH_PRESENT_OPTIONAL );
  periph_setup_interface2( PERIPH_PRESENT_OPTIONAL );
  periph_setup_plusd( PERIPH_PRESENT_OPTIONAL );
  periph_setup_beta128( PERIPH_PRESENT_OPTIONAL );
  periph_update();

  periph_register_beta128();
  beta_builtin = 0;

  return 0;
}
