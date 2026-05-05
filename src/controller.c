/*
 * NES-emu
 * Copyright (C) 2026 Alex Dolgopolov
 *
 * This file is part of NES-emu.
 *
 * NES-emu is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * NES-emu is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with NES-emu. If not, see <https://www.gnu.org/licenses/>.
 */

#include "controller.h"
#include "stdio.h"
#include "debug.h"
#include "SDL3/SDL_keyboard.h"
#include "SDL3/SDL_scancode.h"
uint8_t buttons;
bool strobe = false;

enum NESButtons {
    NES_A      = 0x01,
    NES_B      = 0x02,
    NES_SELECT = 0x04,
    NES_START  = 0x08,
    NES_UP     = 0x10,
    NES_DOWN   = 0x20,
    NES_LEFT   = 0x40,
    NES_RIGHT  = 0x80
};

void get_buttons(uint8_t* buttons){
	const bool* keys = SDL_GetKeyboardState(NULL);

	if (keys[SDL_SCANCODE_Z])         *buttons |= NES_A;
    if (keys[SDL_SCANCODE_X])         *buttons |= NES_B;
    if (keys[SDL_SCANCODE_RSHIFT])    *buttons |= NES_SELECT;
    if (keys[SDL_SCANCODE_RETURN])    *buttons |= NES_START;
    if (keys[SDL_SCANCODE_UP])        *buttons |= NES_UP;
    if (keys[SDL_SCANCODE_DOWN])      *buttons |= NES_DOWN;
    if (keys[SDL_SCANCODE_LEFT])      *buttons |= NES_LEFT;
    if (keys[SDL_SCANCODE_RIGHT])     *buttons |= NES_RIGHT;

    // защита от невозможных направлений
    if ((*buttons & NES_UP) && (*buttons & NES_DOWN)) {
        *buttons &= ~(NES_UP | NES_DOWN);
    }

    if ((*buttons & NES_LEFT) && (*buttons & NES_RIGHT)) {
        *buttons &= ~(NES_LEFT | NES_RIGHT);
    }
}

void controller_signal(ControllerSignalType signal){
	if(signal == SignalStrobe){
		DEBUG_CONTROLLER("signal strobe\n");
		strobe = true;
		return;
	} else if(signal == SignalLatch){
		DEBUG_CONTROLLER("signal latch\n");
		strobe = false;
		get_buttons(&buttons);
		DEBUG_CONTROLLER("buttons = %x\n", buttons);
	}
}

uint8_t controller_read(uint8_t num){
	if(num > 0){
		return 0;
	}
	uint8_t retval = buttons & 1;
	buttons = strobe ? buttons : buttons >> 1;
	DEBUG_CONTROLLER("controller_read = %x\n", retval);
	return retval;
}