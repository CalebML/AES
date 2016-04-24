#include "stdafx.h"
#include "cAES.h"

const uint8_t cAES::SBoxLookupTable[16][16] = {
	//0     1     2     3     4     5     6     7     8     9     10(A) 11(B) 12(C) 13(D) 14(E) 15(F)
	{ 0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76 },//0
	{ 0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0 },//1
	{ 0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15 },//2
	{ 0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75 },//3
	{ 0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0, 0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84 },//4
	{ 0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B, 0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF },//5
	{ 0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8 },//6
	{ 0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5, 0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2 },//7
	{ 0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17, 0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73 },//8
	{ 0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88, 0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB },//9
	{ 0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C, 0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79 },//10(A)
	{ 0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9, 0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08 },//11(B)
	{ 0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6, 0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A },//12(C)
	{ 0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E, 0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E },//13(D)
	{ 0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94, 0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF },//14(E)
	{ 0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68, 0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16 } //15(F)
};

const uint8_t cAES::invertSBoxLookupTable[16][16] = {
	//0     1     2     3     4     5     6     7     8     9     10(A) 11(B) 12(C) 13(D) 14(E) 15(F)
	{ 0x52, 0x09, 0x6A, 0xD5, 0x30, 0x36, 0xA5, 0x38, 0xBF, 0x40, 0xA3, 0x9E, 0x81, 0xF3, 0xD7, 0xFB },//0
	{ 0x7C, 0xE3, 0x39, 0x82, 0x9B, 0x2F, 0xFF, 0x87, 0x34, 0x8E, 0x43, 0x44, 0xC4, 0xDE, 0xE9, 0xCB },//1
	{ 0x54, 0x7B, 0x94, 0x32, 0xA6, 0xC2, 0x23, 0x3D, 0xEE, 0x4C, 0x95, 0x0B, 0x42, 0xFA, 0xC3, 0x4E },//2
	{ 0x08, 0x2E, 0xA1, 0x66, 0x28, 0xD9, 0x24, 0xB2, 0x76, 0x5B, 0xA2, 0x49, 0x6D, 0x8B, 0xD1, 0x25 },//3
	{ 0x72, 0xF8, 0xF6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xD4, 0xA4, 0x5C, 0xCC, 0x5D, 0x65, 0xB6, 0x92 },//4
	{ 0x6C, 0x70, 0x48, 0x50, 0xFD, 0xED, 0xB9, 0xDA, 0x5E, 0x15, 0x46, 0x57, 0xA7, 0x8D, 0x9D, 0x84 },//5
	{ 0x90, 0xD8, 0xAB, 0x00, 0x8C, 0xBC, 0xD3, 0x0A, 0xF7, 0xE4, 0x58, 0x05, 0xB8, 0xB3, 0x45, 0x06 },//6
	{ 0xD0, 0x2C, 0x1E, 0x8F, 0xCA, 0x3F, 0x0F, 0x02, 0xC1, 0xAF, 0xBD, 0x03, 0x01, 0x13, 0x8A, 0x6B },//7
	{ 0x3A, 0x91, 0x11, 0x41, 0x4F, 0x67, 0xDC, 0xEA, 0x97, 0xF2, 0xCF, 0xCE, 0xF0, 0xB4, 0xE6, 0x73 },//8
	{ 0x96, 0xAC, 0x74, 0x22, 0xE7, 0xAD, 0x35, 0x85, 0xE2, 0xF9, 0x37, 0xE8, 0x1C, 0x75, 0xDF, 0x6E },//9
	{ 0x47, 0xF1, 0x1A, 0x71, 0x1D, 0x29, 0xC5, 0x89, 0x6F, 0xB7, 0x62, 0x0E, 0xAA, 0x18, 0xBE, 0x1B },//10(A)
	{ 0xFC, 0x56, 0x3E, 0x4B, 0xC6, 0xD2, 0x79, 0x20, 0x9A, 0xDB, 0xC0, 0xFE, 0x78, 0xCD, 0x5A, 0xF4 },//11(B)
	{ 0x1F, 0xDD, 0xA8, 0x33, 0x88, 0x07, 0xC7, 0x31, 0xB1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xEC, 0x5F },//12(C)
	{ 0x60, 0x51, 0x7F, 0xA9, 0x19, 0xB5, 0x4A, 0x0D, 0x2D, 0xE5, 0x7A, 0x9F, 0x93, 0xC9, 0x9C, 0xEF },//13(D)
	{ 0xA0, 0xE0, 0x3B, 0x4D, 0xAE, 0x2A, 0xF5, 0xB0, 0xC8, 0xEB, 0xBB, 0x3C, 0x83, 0x53, 0x99, 0x61 },//14(E)
	{ 0x17, 0x2B, 0x04, 0x7E, 0xBA, 0x77, 0xD6, 0x26, 0xE1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0C, 0x7D } //15(F)
};

const uint8_t cAES::GaloisLTable[16][16] = {
	//0     1     2     3     4     5     6     7     8     9     10(A) 11(B) 12(C) 13(D) 14(E) 15(F)
	{ 0x00, 0x00, 0x19, 0x01, 0x32, 0x02, 0x1A, 0xC6, 0x4B, 0xC7, 0x1B, 0x68, 0x33, 0xEE, 0xDF, 0x03 },//0
	{ 0x64, 0x04, 0xE0, 0x0E, 0x34, 0x8D, 0x81, 0xEF, 0x4C, 0x71, 0x08, 0xC8, 0xF8, 0x69, 0x1C, 0xC1 },//1
	{ 0x7D, 0xC2, 0x1D, 0xB5, 0xF9, 0xB9, 0x27, 0x6A, 0x4D, 0xE4, 0xA6, 0x72, 0x9A, 0xC9, 0x09, 0x78 },//2
	{ 0x65, 0x2F, 0x8A, 0x05, 0x21, 0x0F, 0xE1, 0x24, 0x12, 0xF0, 0x82, 0x45, 0x35, 0x93, 0xDA, 0x8E },//3
	{ 0x96, 0x8F, 0xDB, 0xBD, 0x36, 0xD0, 0xCE, 0x94, 0x13, 0x5C, 0xD2, 0xF1, 0x40, 0x46, 0x83, 0x38 },//4
	{ 0x66, 0xDD, 0xFD, 0x30, 0xBF, 0x06, 0x8B, 0x62, 0xB3, 0x25, 0xE2, 0x98, 0x22, 0x88, 0x91, 0x10 },//5
	{ 0x7E, 0x6E, 0x48, 0xC3, 0xA3, 0xB6, 0x1E, 0x42, 0x3A, 0x6B, 0x28, 0x54, 0xFA, 0x85, 0x3D, 0xBA },//6
	{ 0x2B, 0x79, 0x0A, 0x15, 0x9B, 0x9F, 0x5E, 0xCA, 0x4E, 0xD4, 0xAC, 0xE5, 0xF3, 0x73, 0xA7, 0x57 },//7
	{ 0xAF, 0x58, 0xA8, 0x50, 0xF4, 0xEA, 0xD6, 0x74, 0x4F, 0xAE, 0xE9, 0xD5, 0xE7, 0xE6, 0xAD, 0xE8 },//8
	{ 0x2C, 0xD7, 0x75, 0x7A, 0xEB, 0x16, 0x0B, 0xF5, 0x59, 0xCB, 0x5F, 0xB0, 0x9C, 0xA9, 0x51, 0xA0 },//9
	{ 0x7F, 0x0C, 0xF6, 0x6F, 0x17, 0xC4, 0x49, 0xEC, 0xD8, 0x43, 0x1F, 0x2D, 0xA4, 0x76, 0x7B, 0xB7 },//10(A)
	{ 0xCC, 0xBB, 0x3E, 0x5A, 0xFB, 0x60, 0xB1, 0x86, 0x3B, 0x52, 0xA1, 0x6C, 0xAA, 0x55, 0x29, 0x9D },//11(B)
	{ 0x97, 0xB2, 0x87, 0x90, 0x61, 0xBE, 0xDC, 0xFC, 0xBC, 0x95, 0xCF, 0xCD, 0x37, 0x3F, 0x5B, 0xD1 },//12(C)
	{ 0x53, 0x39, 0x84, 0x3C, 0x41, 0xA2, 0x6D, 0x47, 0x14, 0x2A, 0x9E, 0x5D, 0x56, 0xF2, 0xD3, 0xAB },//13(D)
	{ 0x44, 0x11, 0x92, 0xD9, 0x23, 0x20, 0x2E, 0x89, 0xB4, 0x7C, 0xB8, 0x26, 0x77, 0x99, 0xE3, 0xA5 },//14(E)
	{ 0x67, 0x4A, 0xED, 0xDE, 0xC5, 0x31, 0xFE, 0x18, 0x0D, 0x63, 0x8C, 0x80, 0xC0, 0xF7, 0x70, 0x07 } //15(F)
};

const uint8_t cAES::GaloisETable[16][16] = {
	//0     1     2     3     4     5     6     7     8     9     10(A) 11(B) 12(C) 13(D) 14(E) 15(F)
	{ 0x01, 0x03, 0x05, 0x0F, 0x11, 0x33, 0x55, 0xFF, 0x1A, 0x2E, 0x72, 0x96, 0xA1, 0xF8, 0x13, 0x35 },//0
	{ 0x5F, 0xE1, 0x38, 0x48, 0xD8, 0x73, 0x95, 0xA4, 0xF7, 0x02, 0x06, 0x0A, 0x1E, 0x22, 0x66, 0xAA },//1
	{ 0xE5, 0x34, 0x5C, 0xE4, 0x37, 0x59, 0xEB, 0x26, 0x6A, 0xBE, 0xD9, 0x70, 0x90, 0xAB, 0xE6, 0x31 },//2
	{ 0x53, 0xF5, 0x04, 0x0C, 0x14, 0x3C, 0x44, 0xCC, 0x4F, 0xD1, 0x68, 0xB8, 0xD3, 0x6E, 0xB2, 0xCD },//3
	{ 0x4C, 0xD4, 0x67, 0xA9, 0xE0, 0x3B, 0x4D, 0xD7, 0x62, 0xA6, 0xF1, 0x08, 0x18, 0x28, 0x78, 0x88 },//4
	{ 0x83, 0x9E, 0xB9, 0xD0, 0x6B, 0xBD, 0xDC, 0x7F, 0x81, 0x98, 0xB3, 0xCE, 0x49, 0xDB, 0x76, 0x9A },//5
	{ 0xB5, 0xC4, 0x57, 0xF9, 0x10, 0x30, 0x50, 0xF0, 0x0B, 0x1D, 0x27, 0x69, 0xBB, 0xD6, 0x61, 0xA3 },//6
	{ 0xFE, 0x19, 0x2B, 0x7D, 0x87, 0x92, 0xAD, 0xEC, 0x2F, 0x71, 0x93, 0xAE, 0xE9, 0x20, 0x60, 0xA0 },//7
	{ 0xFB, 0x16, 0x3A, 0x4E, 0xD2, 0x6D, 0xB7, 0xC2, 0x5D, 0xE7, 0x32, 0x56, 0xFA, 0x15, 0x3F, 0x41 },//8
	{ 0xC3, 0x5E, 0xE2, 0x3D, 0x47, 0xC9, 0x40, 0xC0, 0x5B, 0xED, 0x2C, 0x74, 0x9C, 0xBF, 0xDA, 0x75 },//9
	{ 0x9F, 0xBA, 0xD5, 0x64, 0xAC, 0xEF, 0x2A, 0x7E, 0x82, 0x9D, 0xBC, 0xDF, 0x7A, 0x8E, 0x89, 0x80 },//10(A)
	{ 0x9B, 0xB6, 0xC1, 0x58, 0xE8, 0x23, 0x65, 0xAF, 0xEA, 0x25, 0x6F, 0xB1, 0xC8, 0x43, 0xC5, 0x54 },//11(B)
	{ 0xFC, 0x1F, 0x21, 0x63, 0xA5, 0xF4, 0x07, 0x09, 0x1B, 0x2D, 0x77, 0x99, 0xB0, 0xCB, 0x46, 0xCA },//12(C)
	{ 0x45, 0xCF, 0x4A, 0xDE, 0x79, 0x8B, 0x86, 0x91, 0xA8, 0xE3, 0x3E, 0x42, 0xC6, 0x51, 0xF3, 0x0E },//13(D)
	{ 0x12, 0x36, 0x5A, 0xEE, 0x29, 0x7B, 0x8D, 0x8C, 0x8F, 0x8A, 0x85, 0x94, 0xA7, 0xF2, 0x0D, 0x17 },//14(E)
	{ 0x39, 0x4B, 0xDD, 0x7C, 0x84, 0x97, 0xA2, 0xFD, 0x1C, 0x24, 0x6C, 0xB4, 0xC7, 0x52, 0xF6, 0x01 } //15(F)
};

const uint8_t cAES::EncryptMultiplicationMatrix[4][4] =
{
	{2, 3, 1, 1},
	{1, 2, 3, 1},
	{1, 1, 2, 3},
	{3, 1, 1, 2}
};

const uint8_t cAES::DecryptMultiplicationMatrix[4][4] =
{
	{ 0x0E, 0x0B, 0x0D, 0x09 },
	{ 0x09, 0x0E, 0x0B, 0x0D },
	{ 0x0D, 0x09, 0x0E, 0x0B },
	{ 0x0B, 0x0D, 0x09, 0x0E }
};

cAES::cAES(uint8_t* initmsg, uint8_t* initKey)
{
	m_msg = new uint8_t[17];
	m_key = new uint8_t[17];

	int keyLen = 0;
	int keyLenMult = 1;
	int messageEnd = 0;

	for (int i = 0; i < 17; i++)
	{
		if (!messageEnd && initmsg[i] != '\0')
		{
			m_msg[i] = initmsg[i];
		}
		else
		{
			messageEnd = 1;
			m_msg[i] = '0';
		}

		//copy the first 16 bytes of the message into the state
		//m_state[i] = m_msg[i];
		//moved to encrypt		-The object can't return a value on construction, a public encrypt fnction can

		//make sure the state is initalized
		m_state[0] = 0;

		//copy key argument to key variable, expand if key is smaller than 16 bytes
		if (keyLen == 0 && initKey[i] != '\0')
		{
			m_key[i] = initKey[i];
		}
		else if (keyLen == 0 && initKey[i] == '\0')
		{
			keyLen = i;
			//keyLenMult = 1;
			m_key[i] = initKey[0];
		}
		else
		{
			//make it loop multiple times (more than just 2)
			if ((i - keyLen*keyLenMult) == keyLen)
			{
				keyLenMult += 1;
			}
			m_key[i] = initKey[i - keyLen*keyLenMult];
		}
	}

	m_msg[17] = '\0';
	m_key[17] = '\0';



	/****************TESTING****************
	m_keyColumns.push_back(Column(1, 2, 3, 4));
	m_keyColumns.push_back(Column(5, 6, 7, 8));

	uint8_t* test = ek(2);
	***************************************/

	//testAddRoundKey(); //disabled for now. Was filling up the keyColumns and not clearing them after, interfering with keyExpansion();
	testRotateWord();
	testSubWord();
	testMixColumns();
	testShiftRow();
	//keyExpansion();
}

cAES::~cAES()
{
}



uint8_t* cAES::Encrypt()
{
	
	//first the key is expanded.
	//this takes 43 rounds of expansion, leaving a 43 column key(I think?)
	/**************************************/
	//for testing aginst this tool http://people.eku.edu/styere/Encrypt/JS-AES.html
	//m_key = 0x0f1571c947d9e8590cb7add6af7f6798
	m_key[0] = 0x0f;
	m_key[1] = 0x15;
	m_key[2] = 0x71;
	m_key[3] = 0xc9;
	m_key[4] = 0x47;
	m_key[5] = 0xd9;
	m_key[6] = 0xe8;
	m_key[7] = 0x59;
	m_key[8] = 0x0c;
	m_key[9] = 0xb7;
	m_key[10] = 0xad;
	m_key[11] = 0xd6;
	m_key[12] = 0xaf;
	m_key[13] = 0x7f;
	m_key[14] = 0x67;
	m_key[15] = 0x98;
	/***********************************/
	keyExpansion();
	
	//then run the AES operations
	//this takes 9 rounds excluding the first add round key operation
	//each round uses 16 bytes of the key (4 columns)
	
	//start by initalizing the state to the initial message to encrypt
	for(int i = 0; i < 16; i++)
	{
		m_state[i] = m_msg[i];
	}
	
	//then XOR in the first 4 columns of the key (XORing with 0's is like copying, XORing with all 1's is like inverting)
	addRoundKey(m_state, 0);
	
	//do rounds 0-8 (example table rounds) or rounds 1-9 (real rounds)
	for (int i = 1; i <= 9; i++)
	{

		byteSub(m_state);
		shiftRow(m_state);
		mixColumns(m_state);
		addRoundKey(m_state, i);
	}

	//do final round
	byteSub(m_state);
	shiftRow(m_state);
	addRoundKey(m_state, 10);
	
	return m_state;
}

uint8_t* cAES::rcon(int round)
{
	//uint8_t retval[4] = { 0 };
	int key = round / 4;
	key = key - 1;

	switch (key)
	{
	case 0:
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
		rconRetVal[0] = 1;
		rconRetVal[0] = rconRetVal[0] << key;
		break;
	case 8:
		rconRetVal[0] = 0x1B;
		break;
	case 9:
		rconRetVal[0] = 0x36;
		break;
	case 10:
		rconRetVal[0] = 0x6C;
		break;
	case 11:
		rconRetVal[0] = 0xD8;
		break;
	case 12:
		rconRetVal[0] = 0xAB;
		break;
	case 13:
		rconRetVal[0] = 0x4D;
		break;
	case 14:
		rconRetVal[0] = 0x9A;
		break;
	default:
		break;
	}

	return rconRetVal;
}

uint8_t cAES::SBoxLookup(uint8_t hexValue)
{
	uint8_t retVal = 0;
	uint8_t hex0 = 0;
	uint8_t hex1 = 0;

	hex0 = hexValue & 0x0F;
	hex1 = (hexValue & 0xF0) >> 4;

	retVal = cAES::SBoxLookupTable[hex1][hex0];

	return retVal;
}

uint8_t cAES::inverseSBoxLookup(uint8_t hexValue)
{
	uint8_t retVal = 0;
	uint8_t hex0 = 0;
	uint8_t hex1 = 0;

	hex0 = hexValue & 0x0F;
	hex1 = (hexValue & 0xF0) >> 4;

	retVal = cAES::invertSBoxLookupTable[hex1][hex0];

	return retVal;
}


void cAES::rotateWord(uint8_t* rot)
{
	uint8_t* rotOriginal = rot;
	uint8_t temp[4];
	temp[3] = *rot; //rot[0]
	rot++; //rot now at rot[1]
	for (int i = 0; i <= 2; i++, rot++)
	{
		//temp[0] to temp[2] = rot[1] to rot[3]
		temp[i] = *rot;
	}
	
	rot = rotOriginal;
	for (int i = 0; i <= 3; i++, rot++)
	{
		*rot = temp[i];
	}
}

void cAES::testRotateWord()
{
	uint8_t tempArray[4] = { 4, 3, 2, 1 };
	rotateWord(tempArray);
}

uint8_t* cAES::k(int offset)
{

	kRetVal[4] = { 0 }; // can't return an array of local values without allocating them?
	kRetVal[0] = m_key[offset];
	kRetVal[1] = m_key[offset + 1];
	kRetVal[2] = m_key[offset + 2];
	kRetVal[3] = m_key[offset + 3];

	return kRetVal;
}

uint8_t* cAES::ek(int offset)
{
	//uint8_t retval[4] = { 0 };

	int collumn = offset / 4;
	int row = offset % 4;

	//we should really restructure the collunm class so it holds an array of rows or something.  
	//we could even turn it into a struct because there are no methods, and nothing is private.  
	for (int i = 0; i < 4; i++)
	{
		switch (row)
		{
		case 0:
			ekRetVal[i] = m_keyColumns[collumn].row0;
			break;
		case 1:
			ekRetVal[i] = m_keyColumns[collumn].row1;
			break;
		case 2:
			ekRetVal[i] = m_keyColumns[collumn].row2;
			break;
		case 3:
			ekRetVal[i] = m_keyColumns[collumn].row3;
			break;
		default:
			break;
		}

		if (++row > 3)
		{
			collumn++;
			row = 0;
		}
	}

	return ekRetVal;
}

uint8_t cAES::galoisMult(uint8_t byte1, uint8_t byte2)
{
	int hexPart1 = 0;
	int hexPart2 = 0;
	int retVal;

	//lookup byte 1 in galois L table
	//first find part 1 (first part of the byte in hex); if byte1 is less than 16, it is 0
	if (byte1 > 16)
	{
		hexPart1 = byte1 / 16;
	}
	hexPart2 = byte1 % 16;

	byte1 = GaloisLTable[hexPart1][hexPart2];

	//repeat process for byte 2
	hexPart1 = byte2 / 16;
	hexPart2 = byte2 % 16;

	byte2 = GaloisLTable[hexPart1][hexPart2];

	//if sum greater than 0xFF, subtract 0xFF
	retVal = byte1 + byte2;
	if (retVal > 255)
	{
		retVal = retVal - 255;
	}

	//look up the (possably) modified sum on the E table to complete the multiply
	hexPart1 = retVal / 16;
	hexPart2 = retVal % 16;
	retVal = GaloisETable[hexPart1][hexPart2];

	return retVal;
}

void cAES::mixColumns(uint8_t* localState)
{
	int oldState[16];
	for (int i = 0; i < 16; i++)
	{
		oldState[i] = localState[i];
	}
	
	for(int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			*localState = galoisMult(oldState[(i*4)], EncryptMultiplicationMatrix[j][0])
				^ galoisMult(oldState[(i * 4) + 1], EncryptMultiplicationMatrix[j][1])
				^ galoisMult(oldState[(i * 4) + 2], EncryptMultiplicationMatrix[j][2])
				^ galoisMult(oldState[(i * 4) + 3], EncryptMultiplicationMatrix[j][3]);
			localState++;
		}
	}
	
	//std::vector<Column> oldState = m_state;
	//
	//for (int i = 0; i < 4; i++)
	//{
	//	m_state[i].row0 = galoisMult(oldState[i].row0, EncryptMultiplicationMatrix[0][0])
	//		^ galoisMult(oldState[i].row1, EncryptMultiplicationMatrix[0][1])
	//		^ galoisMult(oldState[i].row2, EncryptMultiplicationMatrix[0][2])
	//		^ galoisMult(oldState[i].row3, EncryptMultiplicationMatrix[0][3]);
	//
	//	m_state[i].row1 = galoisMult(oldState[i].row0, EncryptMultiplicationMatrix[1][0])
	//		^ galoisMult(oldState[i].row1, EncryptMultiplicationMatrix[1][1])
	//		^ galoisMult(oldState[i].row2, EncryptMultiplicationMatrix[1][2])
	//		^ galoisMult(oldState[i].row3, EncryptMultiplicationMatrix[1][3]);
	//
	//	m_state[i].row2 = galoisMult(oldState[i].row0, EncryptMultiplicationMatrix[2][0])
	//		^ galoisMult(oldState[i].row1, EncryptMultiplicationMatrix[2][1])
	//		^ galoisMult(oldState[i].row2, EncryptMultiplicationMatrix[2][2])
	//		^ galoisMult(oldState[i].row3, EncryptMultiplicationMatrix[2][3]);
	//
	//	m_state[i].row3 = galoisMult(oldState[i].row0, EncryptMultiplicationMatrix[3][0])
	//		^ galoisMult(oldState[i].row1, EncryptMultiplicationMatrix[3][1])
	//		^ galoisMult(oldState[i].row2, EncryptMultiplicationMatrix[3][2])
	//		^ galoisMult(oldState[i].row3, EncryptMultiplicationMatrix[3][3]);
	//}
}

//test the mix columns function
void cAES::testMixColumns()
{
	//populate m_state
	//m_state.push_back(Column(0xD4, 0xBF, 0x5D, 0x30));
	//m_state.push_back(Column(0xD4, 0xBF, 0x5D, 0x30));
	//m_state.push_back(Column(0xD4, 0xBF, 0x5D, 0x30));
	//m_state.push_back(Column(0xD4, 0xBF, 0x5D, 0x30));

	//mixColumns();
	//m_state should now contain { 0x04, 0x66, 0x81, 0xE5 } in each column
	//TODO: make this return a bool for auto testing
}

//runs the sbox subsitution on all 4 bytes passed in
void cAES::subWord(uint8_t* sub)
{
	for (int i = 0; i < 4; i++, sub++)
	{
		*sub = SBoxLookup(*sub);
	}
}

//true means passed, false means failed
bool cAES::testSubWord()
{
	bool retVal = true;
	//hex 0x41, 0x42, 0x43, 0x44
	uint8_t testArray[4] = { 'A', 'B', 'C', 'D' };
	subWord(testArray);
	//resulting hex values: 0x83, 0x2c, 0x1A, 0x1B
	uint8_t resultArray[4] = { 0x83, 0x2C, 0x1A, 0x1B };
	for (int i = 0; i < 3; i++)
	{
		if (testArray[i] != resultArray[i])
		{
			retVal = false;
		}
	}
	return retVal;
}

//takes 16 bytes, puts them into columns and rows, 
// 1 5 9  13
// 2 6 10 14
// 3 7 11 15
// 4 8 12 16
//then rotates each row left across the columns
//row 0 rotates 0 times
//row 1 rotates 1 times
//row 2 rotates 2 times
//row 3 rotates 3 times
void cAES::shiftRow(uint8_t* sub)
{
	uint8_t* originalSub = sub;
	std::vector<Column> localColumn;

	uint8_t temp = 0;
	//create correctly ordered unint8_t array

	uint8_t localArray[16];
	for (int i = 0; i < 16; i++, sub++)
	{
		localArray[i] = *sub;
	}

	//create columns and rows
	std::vector<Column>::iterator it;

	for (int i = 0; i < 4; i++)
	{
		Column col(localArray[i * 4], localArray[(i * 4) + 1], localArray[(i * 4) + 2], localArray[(i * 4) + 3]);
		//Column col(*sub++, *sub++, *sub++, *sub++);

		it = localColumn.end();
		localColumn.insert(it, col);
	}

	//rotate across rows
	//row 0 = no rotate
	//row 1 = rotate one
	temp = localColumn[0].row1;
	localColumn[0].row1 = localColumn[1].row1;
	localColumn[1].row1 = localColumn[2].row1;
	localColumn[2].row1 = localColumn[3].row1;
	localColumn[3].row1 = temp;

	//row 2 = rotate two
	std::swap(localColumn[0].row2, localColumn[2].row2);
	std::swap(localColumn[1].row2, localColumn[3].row2);

	//row 3 = rotate three
	temp = localColumn[0].row3;
	localColumn[0].row3 = localColumn[3].row3;
	localColumn[3].row3 = localColumn[2].row3;
	localColumn[2].row3 = localColumn[1].row3;
	localColumn[1].row3 = temp;

	sub = originalSub;
	for (int i = 0; i < 4; i++)
	{
		*sub = localColumn[i].row0;
		sub++;
		*sub = localColumn[i].row1;
		sub++;
		*sub = localColumn[i].row2;
		sub++;
		*sub = localColumn[i].row3;
		sub++;
	}
}

bool cAES::testShiftRow()
{
	bool retVal = true;
	uint8_t testArray[16] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
	shiftRow(testArray);

	uint8_t finalArray[16] = { 1, 6, 11, 16, 5, 10, 15, 4, 9, 14, 3, 8, 13, 2, 7, 12 };

	for (int i = 0; i < 16; i++)
	{
		if (testArray[i] != finalArray[i])
		{
			retVal = false;
		}
	}

	/*
	Column testCol0(1, 6, 11, 16);
	Column testCol1(5, 10, 15, 4);
	Column testCol2(9, 14, 3, 8);
	Column testCol3(13, 2, 7, 12);

	if (!(localColumn[0] == testCol0))
	{
		retVal = false;
	}
	else if (!(localColumn[1] == testCol1))
	{
		retVal = false;
	}
	else if (!(localColumn[2] == testCol2))
	{
		retVal = false;
	}
	else if (!(localColumn[3] == testCol3))
	{
		retVal = false;
	}
	*/

	return retVal;
}

void cAES::addRoundKey(uint8_t* localState, int round)
{
	uint8_t* originalState = localState;
	//iterate over the 16 byte array passed in, and xor each byte, storing the result in the passed in byte array
	for (int i = 0; i < 4; i++)
	{
		*localState = *localState ^ m_keyColumns[i + (round * 4)].row0;
		localState++;
		*localState = *localState ^ m_keyColumns[i + (round * 4)].row1;
		localState++;
		*localState = *localState ^ m_keyColumns[i + (round * 4)].row2;
		localState++;
		*localState = *localState ^ m_keyColumns[i + (round * 4)].row3;
		localState++;

		//localState[i].row0 = localState[i].row0 ^ m_keyColumns[i + (round * 4)].row0;
		//localState[i].row1 = localState[i].row1 ^ m_keyColumns[i + (round * 4)].row1;
		//localState[i].row2 = localState[i].row2 ^ m_keyColumns[i + (round * 4)].row2;
		//localState[i].row3 = localState[i].row3 ^ m_keyColumns[i + (round * 4)].row3;
	}
	//reset the pointer at the end (may not be necessary)
	localState = originalState;
}

void cAES::testAddRoundKey()
{
	//setup
	//m_state.push_back(Column(1, 2, 3, 4));
	//m_state.push_back(Column(1, 2, 3, 4));
	//m_state.push_back(Column(1, 2, 3, 4));
	//m_state.push_back(Column(1, 2, 3, 4));
	//
	//m_keyColumns.push_back(Column(2, 3, 4, 5));
	//m_keyColumns.push_back(Column(5, 6, 7, 8));
	//m_keyColumns.push_back(Column(12, 13, 15, 14));
	//m_keyColumns.push_back(Column(3, 5, 7, 9));
	//m_keyColumns.push_back(Column(9, 10, 11, 12));
	//m_keyColumns.push_back(Column(13, 14, 15, 16));
	//m_keyColumns.push_back(Column(17, 18, 19, 20));
	//m_keyColumns.push_back(Column(1, 2, 3, 4));

	//addRoundKey();
	//addRoundKey();
}

void cAES::keyExpansion()
{
	std::vector<Column>::iterator it;
	uint8_t operationData[4] = { 0 };
	uint8_t rconData[4] = { 0 };
	uint8_t ekData[4] = { 0 };
	uint8_t ekData2[4] = { 0 };
	uint8_t * operationPointer;
	
	//rounds 0-3
	for (int i = 0; i < 16; i += 4)
	{
		Column localColumn(k(i));
		it = m_keyColumns.end(); //note this only works if the columns are empty when you begin
		m_keyColumns.insert(it, localColumn);
	}

	//rounds 4-43
	for (int i = 4; i < 44; i++)
	{
		if ( (i % 4) == 0) //only do this operation every 4 rounds
		{
			/**********************************************  -- Commented out of master until working

			Column localColumn(subWord(rotateWord(ek(4 - 1) * 4))) ^ rcon((4 / 4) - 1) ^ ek((4 - 4) * 4); // THIS LINE IS INCOMPLETE AND NOT TESTED (not sure what to do about mismatch of pointers for multiplication and XOR)
			it = m_keyColumns.end();
			m_keyColumns.insert(it, localColumn);
			***********************************************/
			operationPointer = ek((i - 1) * 4);
			for (int j = 0; j < 4; j++, operationPointer++)
			{
				operationData[j] = *operationPointer;
			}

			rotateWord(operationData);
			subWord(operationData);

			operationPointer = rcon(i);//rcon((i / (16 / 4)) - 1); //ex for 4th round and a 16 byte key: rcon(4/(16 / 4)) - 1 = 0
			for (int j = 0; j < 4; j++, operationPointer++)
			{
				rconData[j] = *operationPointer;
			}

			operationPointer = ek((i - 4) * 4);
			for (int j = 0; j < 4; j++, operationPointer++)
			{
				ekData[j] = *operationPointer;
			}
			
			//Column localColumn(operationData);
			Column localColumn(operationData[0] ^ rconData[0] ^ ekData[0], operationData[1] ^ rconData[1] ^ ekData[1], operationData[2] ^ rconData[2] ^ ekData[2], operationData[3] ^ rconData[3] ^ ekData[3]);
			it = m_keyColumns.end();
			m_keyColumns.insert(it, localColumn);
		}
		else
		{
			operationPointer = ek((i - 1) * 4);
			for (int j = 0; j < 4; j++, operationPointer++)
			{
				ekData[j] = *operationPointer;
			}

			operationPointer = ek((i - 4) * 4);
			for (int j = 0; j < 4; j++, operationPointer++)
			{
				ekData2[j] = *operationPointer;
			}

			Column localColumn(ekData[0] ^ ekData2[0], ekData[1] ^ ekData2[1], ekData[2] ^ ekData2[2], ekData[3] ^ ekData2[3]);
			it = m_keyColumns.end();
			m_keyColumns.insert(it, localColumn);
		}
	}

}

//runs the sbox substitution on all 16 bytes passed in
void cAES::byteSub(uint8_t* sub)
{
	for (int i = 0; i < 16; i++, sub++)
	{
		*sub = SBoxLookup(*sub);
	}
}