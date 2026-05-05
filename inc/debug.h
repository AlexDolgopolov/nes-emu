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

#ifndef DEBUG_H
#define DEBUG_H

//#define DEBUG_CPU_ALLOW
//#define DEBUG_PPU_ALLOW
//#define DEBUG_STACK_ALLOW
//#define DEBUG_RAM_ALLOW
//#define DEBUG_CONTROLLER_ALLOW
//#define CPU_TEST_MODE

#ifdef DEBUG_CONTROLLER_ALLOW

	#define DEBUG_CONTROLLER(x, ...) do{ \
								printf(x, ##__VA_ARGS__); \
								fflush(stdout); \
							}while(0)

#else

	#define DEBUG_CONTROLLER(x, ...)

#endif


#ifdef DEBUG_RAM_ALLOW

	#define DEBUG_RAM(x, ...) do{ \
								printf(x, ##__VA_ARGS__); \
								fflush(stdout); \
							}while(0)

#else

	#define DEBUG_RAM(x, ...)

#endif


#ifdef DEBUG_STACK_ALLOW

	#define DEBUG_STACK(x, ...) do{ \
								printf(x, ##__VA_ARGS__); \
								fflush(stdout); \
							}while(0)

#else

	#define DEBUG_STACK(x, ...)

#endif

#ifdef DEBUG_CPU_ALLOW

	#define DEBUG(x, ...) do{ \
								printf(x, ##__VA_ARGS__); \
								fflush(stdout); \
							}while(0)

#else

	#define DEBUG(x, ...)

#endif

#ifdef DEBUG_PPU_ALLOW

	#define DEBUG_PPU(x, ...) do{ \
								printf(x, ##__VA_ARGS__); \
								fflush(stdout); \
							}while(0)

#else

	#define DEBUG_PPU(x, ...)

#endif

#endif