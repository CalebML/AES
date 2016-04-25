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
	//uint8_t uOutputReference[] = { 0x49, 0xf4, 0x4e, 0x46, 0xe1, 0x5d, 0x48, 0xc6, 0xcb, 0x48, 0xc0, 0x62, 0xa4, 0x17, 0x14, 0x74, 0x00 }; //note that 0x00 at end is for string complete checking just in case

	//expected output for test key
	//uint8_t uOutputReference[] = { 0x70, 0x75, 0x66, 0x1c, 0xdf, 0x6f, 0x8f, 0x8c, 0x39, 0x2c, 0x1d, 0x25, 0xc8, 0x0f, 0x61, 0x27, 0x00 }; //note that 0x00 at end is for string complete checking just in case
	//expexted value for default key "CSETOIT"
	uint8_t uOutputReference[] = { 0x71, 0xfd, 0xc1, 0xdc, 0xf0, 0xc9, 0x95, 0xc4, 0x6d, 0x0a, 0xc0, 0x54, 0x7b, 0xaf, 0x1d, 0x0d, 0x00 }; //note that 0x00 at end is for string complete checking just in case

	//uint8_t uOutputReference[] = { 0x30, 0x7b, 0xb6, 0x86, 0x3f, 0x2c, 0x09, 0x32, 0x40, 0xfd, 0xc5, 0xec, 0x41, 0x89, 0x29, 0x41 };


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

	//output check generated from: http://people.eku.edu/styere/Encrypt/JS-AES.html using the first key in the drop down
	//output should be: { 0x30, 0x7b, 0xb6, 0x86, 0x3f, 0x2c, 0x09, 0x32, 0x40, 0xfd, 0xc5, 0xec, 0x41, 0x89, 0x29, 0x41 };
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


	cout << "\n\nNext this will decrypt using the same key\n";
	system("pause");

	cAES AESDecrypt((uint8_t*)uOutput, (uint8_t*)key);
	//TODO: loop input and output to iterate over multiple message blocks
	uOutput = AESDecrypt.Decrypt();
	uOutput[16] = '\0';

	std::cout << "Decrypt result: " << uOutput << endl;


	system("pause");

	//delete message;
	//delete key;
	//delete uOutput;
	//delete output;

    return 0;
}

