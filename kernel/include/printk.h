#ifndef __PRINTK_H
#define __PRINTK_H

#include <stdint.h>

int printk(const char* str, uint32_t row, uint32_t column);

#endif