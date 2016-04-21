#pragma once
#include <stdint.h>

class Column
{
public:
	Column();
	Column(uint8_t initRow0, uint8_t initRow1, uint8_t initRow2, uint8_t initRow3);
	~Column();

	uint8_t row0;
	uint8_t row1;
	uint8_t row2;
	uint8_t row3;
};

