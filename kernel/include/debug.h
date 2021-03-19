#ifndef __DEBUG_H
#define __DEBUG_H

#include <stdint.h>

int kputch(char c, uint32_t row, uint32_t column);
int printk(const char* str, uint32_t row, uint32_t column);
int printhex(uint32_t number);
void printreg(uint8_t reg);
void printregs();

int warn(const char* str);
int error(const char* str);

#endif