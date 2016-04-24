// AES.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "cAES.h"
#include "Column.h"
#include <stdio.h>
#include <iostream>

using std::cout;
using std::endl;

int _tmain(int argc, _TCHAR* argv[])
{
	bool success = true;
	char* message;
	char* key;
	uint8_t* uOutput;
	char* output;
	message = new char[500];
	key = new char[100];
	uOutput = new uint8_t[500];
	output = new char[500];
	uint8_t uOutputReference[] = { 0x49, 0xf4, 0x4e, 0x46, 0xe1, 0x5d, 0x48, 0xc6, 0xcb, 0x48, 0xc0, 0x62, 0xa4, 0x17, 0x14, 0x74, 0x00 }; //note that 0x00 at end is for string complete checking just in case

	std::cout << "Please enter a message to encrypt (Default is ABCDEFGHIJKLNOPQ): ";
	gets_s(message, 500);
	if (message[0] == '\0')
	{
		message = "ABCDEFGHIJKLNOPQ";
	}

	std::cout << "Please enter a key (Default is CSETOIT): ";
	gets_s(key, 100);
	if (key[0] == '\0')
		key = "CSETOIT";

	cAES AES((uint8_t*)message, (uint8_t*)key);

	//TODO: loop input and output to iterate over multiple message blocks
	uOutput = AES.Encrypt();

	std::cout << "Result: " << uOutput << endl << "Note: If your original message wasn't the default this check is not valid." << endl;

	//output check generated from: http://aes.online-domain-tools.com/ (not 100% sure if this is correct)
	//output should be:  {0x49, 0xf4, 0x4e, 0x46, 0xe1, 0x5d, 0x48, 0xc6, 0xcb, 0x48, 0xc0, 0x62, 0xa4, 0x17, 0x14, 0x74}
	success = true;
	for (int i = 0; i < 16; i++)
	{
		if (uOutputReference[i] != uOutput[i])
		{
			success = false;
		}
	}

	if (success)
	{
		cout << "AES encryption succeded" << endl;
	}
	else
	{
		cout << "AES encryption failed" << endl;
	}

	system("pause");

	//delete message;
	//delete key;
	//delete uOutput;
	//delete output;

    return 0;
}

