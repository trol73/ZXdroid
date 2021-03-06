/* specplus3e.c: Spectrum +3e specific routines
   Copyright (c) 1999-2004 Philip Kendall, Darren Salt

   $Id: specplus3e.c 3601 2008-04-09 13:32:12Z fredm $

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

#include "disk/upd_fdc.h"
#include "machines.h"
#include "periph.h"
#include "settings.h"
#include "specplus3.h"
#include "ui/ui.h"

static int specplus3e_reset( void );
extern upd_fdc *specplus3_fdc;

int
specplus3e_init( fuse_machine_info *machine )
{
  machine->machine = LIBSPECTRUM_MACHINE_PLUS3E;
  machine->id = "plus3e";

  machine->reset = specplus3e_reset;

  machine->timex = 0;
  machine->ram.port_from_ula	     = specplus3_port_from_ula;
  machine->ram.contend_delay	     = spectrum_contend_delay_76543210;
  machine->ram.contend_delay_no_mreq = spectrum_contend_delay_none;

  machine->unattached_port = spectrum_unattached_port_none;

  machine->shutdown = specplus3_shutdown;

  machine->memory_map = specplus3_memory_map;

  return 0;
}

static int
specplus3e_reset( void )
{
  int error;

  error = machine_load_rom( 0, 0, settings_current.rom_plus3e_0,
                            settings_default.rom_plus3e_0, 0x4000 );
  if( error ) return error;
  error = machine_load_rom( 2, 1, settings_current.rom_plus3e_1,
                            settings_default.rom_plus3e_1, 0x4000 );
  if( error ) return error;
  error = machine_load_rom( 4, 2, settings_current.rom_plus3e_2,
                            settings_default.rom_plus3e_2, 0x4000 );
  if( error ) return error;
  error = machine_load_rom( 6, 3, settings_current.rom_plus3e_3,
                            settings_default.rom_plus3e_3, 0x4000 );
  if( error ) return error;

  error = specplus3_plus2a_common_reset();
  if( error ) return error;

  error = periph_setup( specplus3_peripherals, specplus3_peripherals_count );
  if( error ) return error;
  periph_setup_kempston( PERIPH_PRESENT_OPTIONAL );
  periph_setup_interface1( PERIPH_PRESENT_OPTIONAL );
  periph_update();

  upd_fdc_master_reset( specplus3_fdc );
  specplus3_menu_items();

  return 0;
}
