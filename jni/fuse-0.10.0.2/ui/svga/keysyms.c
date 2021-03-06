/* keysyms.c: UI keysym to Fuse input layer keysym mappings
   Copyright (c) 2000-2007 Philip Kendall, Matan Ziv-Av, Russell Marks
                           Fredrick Meunier, Catalin Mihaila, Stuart Brady

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

/* This file is autogenerated from keysyms.dat by keysyms.pl.
   Do not edit unless you know what you're doing! */

#include <config.h>


#include "input.h"
#include "keyboard.h"

#include <vgakeyboard.h>

keysyms_map_t keysyms_map[] = {

  { SCANCODE_TAB,              INPUT_KEY_Tab         },
  { SCANCODE_ENTER,            INPUT_KEY_Return      },
  { SCANCODE_ESCAPE,           INPUT_KEY_Escape      },
  { SCANCODE_SPACE,            INPUT_KEY_space       },
  { SCANCODE_BACKSLASH,        INPUT_KEY_numbersign  },
  { SCANCODE_APOSTROPHE,       INPUT_KEY_apostrophe  },
  { SCANCODE_COMMA,            INPUT_KEY_comma       },
  { SCANCODE_MINUS,            INPUT_KEY_minus       },
  { SCANCODE_PERIOD,           INPUT_KEY_period      },
  { SCANCODE_SLASH,            INPUT_KEY_slash       },
  { SCANCODE_0,                INPUT_KEY_0           },
  { SCANCODE_1,                INPUT_KEY_1           },
  { SCANCODE_2,                INPUT_KEY_2           },
  { SCANCODE_3,                INPUT_KEY_3           },
  { SCANCODE_4,                INPUT_KEY_4           },
  { SCANCODE_5,                INPUT_KEY_5           },
  { SCANCODE_6,                INPUT_KEY_6           },
  { SCANCODE_7,                INPUT_KEY_7           },
  { SCANCODE_8,                INPUT_KEY_8           },
  { SCANCODE_9,                INPUT_KEY_9           },
  { SCANCODE_SEMICOLON,        INPUT_KEY_semicolon   },
  { SCANCODE_EQUAL,            INPUT_KEY_equal       },
  { SCANCODE_A,                INPUT_KEY_A           },
  { SCANCODE_B,                INPUT_KEY_B           },
  { SCANCODE_C,                INPUT_KEY_C           },
  { SCANCODE_D,                INPUT_KEY_D           },
  { SCANCODE_E,                INPUT_KEY_E           },
  { SCANCODE_F,                INPUT_KEY_F           },
  { SCANCODE_G,                INPUT_KEY_G           },
  { SCANCODE_H,                INPUT_KEY_H           },
  { SCANCODE_I,                INPUT_KEY_I           },
  { SCANCODE_J,                INPUT_KEY_J           },
  { SCANCODE_K,                INPUT_KEY_K           },
  { SCANCODE_L,                INPUT_KEY_L           },
  { SCANCODE_M,                INPUT_KEY_M           },
  { SCANCODE_N,                INPUT_KEY_N           },
  { SCANCODE_O,                INPUT_KEY_O           },
  { SCANCODE_P,                INPUT_KEY_P           },
  { SCANCODE_Q,                INPUT_KEY_Q           },
  { SCANCODE_R,                INPUT_KEY_R           },
  { SCANCODE_S,                INPUT_KEY_S           },
  { SCANCODE_T,                INPUT_KEY_T           },
  { SCANCODE_U,                INPUT_KEY_U           },
  { SCANCODE_V,                INPUT_KEY_V           },
  { SCANCODE_W,                INPUT_KEY_W           },
  { SCANCODE_X,                INPUT_KEY_X           },
  { SCANCODE_Y,                INPUT_KEY_Y           },
  { SCANCODE_Z,                INPUT_KEY_Z           },
  { SCANCODE_A,                INPUT_KEY_a           },
  { SCANCODE_B,                INPUT_KEY_b           },
  { SCANCODE_C,                INPUT_KEY_c           },
  { SCANCODE_D,                INPUT_KEY_d           },
  { SCANCODE_E,                INPUT_KEY_e           },
  { SCANCODE_F,                INPUT_KEY_f           },
  { SCANCODE_G,                INPUT_KEY_g           },
  { SCANCODE_H,                INPUT_KEY_h           },
  { SCANCODE_I,                INPUT_KEY_i           },
  { SCANCODE_J,                INPUT_KEY_j           },
  { SCANCODE_K,                INPUT_KEY_k           },
  { SCANCODE_L,                INPUT_KEY_l           },
  { SCANCODE_M,                INPUT_KEY_m           },
  { SCANCODE_N,                INPUT_KEY_n           },
  { SCANCODE_O,                INPUT_KEY_o           },
  { SCANCODE_P,                INPUT_KEY_p           },
  { SCANCODE_Q,                INPUT_KEY_q           },
  { SCANCODE_R,                INPUT_KEY_r           },
  { SCANCODE_S,                INPUT_KEY_s           },
  { SCANCODE_T,                INPUT_KEY_t           },
  { SCANCODE_U,                INPUT_KEY_u           },
  { SCANCODE_V,                INPUT_KEY_v           },
  { SCANCODE_W,                INPUT_KEY_w           },
  { SCANCODE_X,                INPUT_KEY_x           },
  { SCANCODE_Y,                INPUT_KEY_y           },
  { SCANCODE_Z,                INPUT_KEY_z           },
  { SCANCODE_BACKSPACE,        INPUT_KEY_BackSpace   },
  { SCANCODE_CURSORBLOCKUP,    INPUT_KEY_Up          },
  { SCANCODE_CURSORBLOCKDOWN,  INPUT_KEY_Down        },
  { SCANCODE_CURSORBLOCKLEFT,  INPUT_KEY_Left        },
  { SCANCODE_CURSORBLOCKRIGHT, INPUT_KEY_Right       },
  { SCANCODE_INSERT,           INPUT_KEY_Insert      },
  { SCANCODE_REMOVE,           INPUT_KEY_Delete      },
  { SCANCODE_HOME,             INPUT_KEY_Home        },
  { SCANCODE_END,              INPUT_KEY_End         },
  { SCANCODE_PAGEUP,           INPUT_KEY_Page_Up     },
  { SCANCODE_PAGEDOWN,         INPUT_KEY_Page_Down   },
  { SCANCODE_CAPSLOCK,         INPUT_KEY_Caps_Lock   },
  { SCANCODE_F1,               INPUT_KEY_F1          },
  { SCANCODE_F2,               INPUT_KEY_F2          },
  { SCANCODE_F3,               INPUT_KEY_F3          },
  { SCANCODE_F4,               INPUT_KEY_F4          },
  { SCANCODE_F5,               INPUT_KEY_F5          },
  { SCANCODE_F6,               INPUT_KEY_F6          },
  { SCANCODE_F7,               INPUT_KEY_F7          },
  { SCANCODE_F8,               INPUT_KEY_F8          },
  { SCANCODE_F9,               INPUT_KEY_F9          },
  { SCANCODE_F10,              INPUT_KEY_F10         },
  { SCANCODE_F11,              INPUT_KEY_F11         },
  { SCANCODE_F12,              INPUT_KEY_F12         },
  { SCANCODE_LEFTSHIFT,        INPUT_KEY_Shift_L     },
  { SCANCODE_RIGHTSHIFT,       INPUT_KEY_Shift_R     },
  { SCANCODE_LEFTCONTROL,      INPUT_KEY_Control_L   },
  { SCANCODE_RIGHTCONTROL,     INPUT_KEY_Control_R   },
  { SCANCODE_LEFTALT,          INPUT_KEY_Alt_L       },
  { SCANCODE_RIGHTALT,         INPUT_KEY_Alt_R       },
#ifdef SCANCODE_LEFTWIN
  { SCANCODE_LEFTWIN,          INPUT_KEY_Meta_L      },
#endif                          /* #ifdef Meta_L */
#ifdef SCANCODE_RIGHTWIN
  { SCANCODE_RIGHTWIN,         INPUT_KEY_Meta_R      },
#endif                          /* #ifdef Meta_R */
  { 127,                       INPUT_KEY_Mode_switch },

  { 0, 0 }			/* End marker: DO NOT MOVE! */

};

