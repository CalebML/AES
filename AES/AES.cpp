// AES.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "cAES.h"
#include "Column.h"
#include <stdio.h>
#include <iostream>

int main()
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

    return 0;
}

