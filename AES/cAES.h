#pragma once
#include <stdint.h>
#include <list>
#include "Column.h"
class cAES
{
public:
	cAES(uint8_t* initMsg, uint8_t* initKey);
	~cAES();


private:
	//member variables
	uint8_t *m_msg;
	uint8_t *m_key;
	std::list<Column> m_collumns;
	
	const static uint8_t SBoxLookupTable[16][16];
		

	const static uint8_t invertSBoxLookupTable[16][16];
	


};

