#include "stdafx.h"
#include "cAES.h"


cAES::cAES(uint8_t* initmsg, uint8_t* initKey)
{
	m_msg = initmsg;
	m_key = initKey;


}


cAES::~cAES()
{
}
