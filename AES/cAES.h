#pragma once
#include <stdint.h>
#include <list>
#include "Column.h"
class cAES
{
public:
	cAES(uint8_t* initMsg, uint8_t* initKey);
	~cAES();


	uint8_t SBoxLookup(uint8_t hexValue);

	uint8_t inverseSBoxLookup(uint8_t hexValue);

	void rotateWord(uint8_t* rot);

private:
	//member variables
	uint8_t *m_msg;
	uint8_t *m_key;
	std::list<Column> m_collumns;
	
	const static uint8_t SBoxLookupTable[16][16];
		

	const static uint8_t invertSBoxLookupTable[16][16];
	
	//testing functions
	void testRotateWord();

};

