#pragma once
#include <stdint.h>
#include <vector>
#include "Column.h"
class cAES
{
public:
	cAES(uint8_t* initMsg, uint8_t* initKey);
	~cAES();


	uint8_t SBoxLookup(uint8_t hexValue);

	uint8_t inverseSBoxLookup(uint8_t hexValue);

private:
	//member variables
	uint8_t *m_msg;
	uint8_t *m_key;
	std::vector<Column> m_collumns;		//changed to vector
						//list are usually linked list, or used as such.
						//no fast random access, which we will want.  
	
	
	//private methods
	const static uint8_t SBoxLookupTable[16][16];
		

	const static uint8_t invertSBoxLookupTable[16][16];
	
	uint8_t* rcon(int round);

	uint8_t* k(int offset);

	uint8_t* ek(int offset);

};

