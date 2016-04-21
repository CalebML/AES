// AES.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "cAES.h"
#include "Column.h"
#include <stdio.h>
#include <iostream>

int _tmain(int argc, _TCHAR* argv[])
{
	char* message;
	char* key;
	message = new char[500];
	key = new char[100];

	std::cout << "Please enter a message to encrypt: ";
	gets_s(message, 500);

	std::cout << "Please enter a key (Default is CSETOIT): ";
	gets_s(key, 100);
	if (key[0] == '\0')
		key = "CSETOIT";

	cAES((uint8_t*)message, (uint8_t*)key);

	//first the key is expanded.
	//this takes 43 rounds of expansion, leaving a 43 column key(I think?)

	//then run the AES operations
	//this takes 9 rounds excluding the first add round key operation
	//each round uses 16 bytes of the key (4 columns)

    return 0;
}

