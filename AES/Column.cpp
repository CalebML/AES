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

Column::Column(uint8_t* rowData)
{
	row0 = *rowData;
	rowData++;
	row1 = *rowData;
	rowData++;
	row2 = *rowData;
	rowData++;
	row3 = *rowData;
}

bool Column::operator==(Column other)
{
	bool retVal = false;

	if (row0 == other.row0)
	{
		if (row1 == other.row1)
		{
			if (row2 == other.row2)
			{
				if (row3 == other.row3)
				{
					retVal = true;
				}
			}
		}
	}
	return retVal;
}

Column::~Column()
{
}
