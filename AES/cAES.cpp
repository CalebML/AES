#include "stdafx.h"
#include "cAES.h"


cAES::cAES(uint8_t* initmsg, uint8_t* initKey)
{
	m_msg = new uint8_t[17];
	m_key = new uint8_t[17];

	int keyLen = 0;
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

		if (keyLen == 0 && initKey[i] != '\0')
		{
			m_key[i] = initKey[i];
		}
		else if (keyLen == 0 && initKey[i] == '\0')
		{
			keyLen = i;
			m_key[i] = initKey[0];
		}
		else
		{
			m_key[i] = initKey[i - keyLen];
		}
	}

	m_msg[17] = '\0';
	m_key[17] = '\0';
}


cAES::~cAES()
{
}
