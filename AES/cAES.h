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

	void rotateWord(uint8_t* rot);

	void subWord(uint8_t* sub);

	void shiftRow(uint8_t* sub);

	void addRoundKey(uint8_t* state);

	void keyExpansion();

private:
	//member variables
	uint8_t *m_msg;
	uint8_t *m_key;
	std::vector<Column> m_keyColumns;		//changed to vector
						//list are usually linked list, or used as such.
						//no fast random access, which we will want.  

	uint8_t m_state[16];

	uint8_t kRetVal[4];
	
	const static uint8_t SBoxLookupTable[16][16];
		

	const static uint8_t invertSBoxLookupTable[16][16];

	const static uint8_t GaloisLTable[16][16];

	const static uint8_t GaloisETable[16][16];

	const static uint8_t EncryptMultiplicationMatrix[4][4];

	const static uint8_t DecryptMultiplicationMatrix[4][4];
	

	//testing functions
	void testRotateWord();

	bool testSubWord();

	bool testShiftRow();

	//private methods
	uint8_t* rcon(int round);

	uint8_t* k(int offset);

	uint8_t* ek(int offset);

	uint8_t galoisMult(uint8_t byte1, uint8_t byte2);

};

