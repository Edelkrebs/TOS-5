#ifndef __MATHS_H
#define __MATHS_H

#include <stdint.h>

static inline uint32_t round_up(uint32_t number, uint32_t alignment){
	return (number + (alignment - number % alignment));
}

#endif