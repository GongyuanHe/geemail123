#include "salsa.h"
using CryptoPP::Salsa20;
#include <stdio.h>
#include "osrng.h"
using CryptoPP::AutoSeededRandomPool;

#include <iostream>
using std::cout;
using std::endl;

using std::string;

int main() {

	AutoSeededRandomPool prng;

	string ciphertextStr(""), plaintextStr("My Plaintext!! My Dear plaintext!!");
	byte *plaintextBytes = (byte *) plaintextStr.c_str();
	//I could statically allocate this, but then changes will require work, and typing
	byte *ciphertextBytes = new byte[plaintextStr.length()];

	//~Key and IV Generation/Initialization======================================
	/////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////
	byte key[32];
	byte iv[8];
	prng.GenerateBlock(key, 32);
	prng.GenerateBlock(iv, 8);

	//~Encryption================================================================
	/////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////
	Salsa20::Encryption salsa;	
	salsa.SetKeyWithIV(key, 32, iv);
	salsa.ProcessData(ciphertextBytes, plaintextBytes, plaintextStr.length());
	ciphertextStr.assign((char *) ciphertextBytes);

	//Output plaintext/ciphertext for sanity check
	cout << "Plaintext: " << plaintextStr << endl;
	int i;
	for(i=0;i<plaintextStr.length();i++)
	{ printf("%02x",ciphertextStr[i]);}

	//Reset plaintext (for sanity again)
	plaintextStr.assign("");

	//Reset Key & IV
	//!!! THIS IS IMPORTANT: If you do not reset the stream cipher the data will
		//be encrypted again with a different part of the streaming key
		//Resetting the key & IV ensure that the same key is used, and we decrypt
	/////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////
	salsa.SetKeyWithIV(key, 32, iv);

	//~Decryption================================================================
	/////////////////////////////////////////////////////////////////////////////
	/////////////////////////////////////////////////////////////////////////////
	salsa.ProcessData(plaintextBytes, ciphertextBytes, ciphertextStr.length());
	plaintextStr.assign((char *) plaintextBytes);

	//Output newly decrypted plaintext
	cout << "Plaintext Again: " << plaintextStr << endl << endl;
	cout << endl << "SALSA!" << endl << endl << "     " << "...20..." << endl;

	delete ciphertextBytes;

	return 0;
}
