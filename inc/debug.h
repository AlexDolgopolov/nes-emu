#ifndef DEBUG_H
#define DEBUG_H

//#define DEBUG_CPU
//#define DEBUG_PPU
//#define DEBUG_STACK
//#define DEBUG_RAM
//#define CPU_TEST_MODE

#ifdef DEBUG_RAM

	#define DEBUG_RAM(x, ...) do{ \
								printf(x, __VA_ARGS__); \
								fflush(stdout); \
							}while(0)

#else

	#define DEBUG_RAM(x, ...)

#endif


#ifdef DEBUG_STACK

	#define DEBUG_STACK(x, ...) do{ \
								printf(x, __VA_ARGS__); \
								fflush(stdout); \
							}while(0)

#else

	#define DEBUG_STACK(x, ...)

#endif

#ifdef DEBUG_CPU

	#define DEBUG(x, ...) do{ \
								printf(x, __VA_ARGS__); \
								fflush(stdout); \
							}while(0)

#else

	#define DEBUG(x, ...)

#endif

#ifdef DEBUG_PPU

	#define DEBUG_PPU(x, ...) do{ \
								printf(x, __VA_ARGS__); \
								fflush(stdout); \
							}while(0)

#else

	#define DEBUG_PPU(x, ...)

#endif

#endif