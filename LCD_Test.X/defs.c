#include "defs.h"

void wait(uint32_t count)
{
	while (count--);
}

uint8_t countBits(uint32_t num)
{
	uint8_t ret = num & 1;
	while (num) ret += (0x1 & (num >>= 1));
	return ret;
}


// Note doesn't cover the case of 0 (0 returns 1)

uint32_t hibit(uint32_t x)
{
	uint32_t log2Val = 0;
	while (x >>= 1) log2Val++; // eg x=63 (111111), log2Val=5
	return 1 << log2Val; // finds 2^5=32
}

uint32_t lowbit(uint32_t x)
{
	uint32_t log2Val = 0;
	if (x & 1)
		return 1;
	log2Val++;
	while (((x >>= 1) & 1) == 0) log2Val++; // eg x=63 (111111), log2Val=5
	return 1 << log2Val; // finds 2^5=32
}

int32_t maxSize(uint8_t digits)
{
	return POW10(countBits(digits))*10;
}
#if 0

float log2(float num)
{
	return log(num) / LOG2;
}
#else

uint32_t log2(uint32_t num)
{
	uint32_t log2Val = 0;
	while (num >>= 1) log2Val++; // eg x=63 (111111), log2Val=5
	return log2Val;
}
#endif
