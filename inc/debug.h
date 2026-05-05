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