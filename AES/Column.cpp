#include "stdafx.h"
#include "Column.h"



Column::Column()
{
	row0 = 0;
	row1 = 0;
	row2 = 0;
	row3 = 0;
}

Column::Column(uint8_t initRow0, uint8_t initRow1, uint8_t initRow2, uint8_t initRow3)
{
	row0 = initRow0;
	row1 = initRow1;
	row2 = initRow2;
	row3 = initRow3;
}

Column::~Column()
{
}
