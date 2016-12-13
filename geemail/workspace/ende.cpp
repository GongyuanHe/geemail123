#include <iostream>
#include "salsa.h"
#include "hex.h"


using namespace std;
using namespace CryptoPP;

  

string encrypt(string plaintext, string key_str, string iv_str){
  string ciphertext = "";
  byte *ciphertextBytes = (byte *) plaintext.c_str();


  byte iv[8];
  
  HexEncoder encoder;
  encoder.Put((byte*)iv_str.data(), iv_str.size());
  encoder.MessageEnd();
  encoder.Get(iv, sizeof(iv));
  
  byte key[32];
  {
    HexEncoder encoder;
    encoder.Put((byte*)key_str.data(), key_str.size());
    encoder.MessageEnd();
    encoder.Get(key, sizeof(key));
  }

  string plain_raw;
  {
    HexEncoder encoder;
    encoder.Put((byte*)plaintext.data(), plaintext.size());
    encoder.MessageEnd();

    long long size = encoder.MaxRetrievable();
    plain_raw.resize(size);
    encoder.Get((byte*)plain_raw.data(), plain_raw.size());

  }
  // Encryption
  Salsa20::Encryption salsa;
  salsa.SetKeyWithIV(key, 32, iv);
  StringSource ss(plain_raw, true, new StreamTransformationFilter(salsa, new StringSink(ciphertext)));

  return ciphertext;
}

string decrypt(string ciphertext, string key_str, string iv_str) {
  string plaintext = "";
  byte *plaintextBytes = (byte *) ciphertext.c_str();

  byte iv[8];
  
  HexDecoder decoder;
  decoder.Put((byte*)iv_str.data(), iv_str.size());
  decoder.MessageEnd();
  decoder.Get(iv, sizeof(iv));
  
  
  byte key[32];
  {
    HexDecoder decoder;
    decoder.Put((byte*)key_str.data(), key_str.size());
    decoder.MessageEnd();
    decoder.Get(key, sizeof(key));
  }

  string cipher_raw;
  {
    HexDecoder decoder;
    decoder.Put((byte*)ciphertext.data(), ciphertext.size());
    decoder.MessageEnd();

    long long size = decoder.MaxRetrievable();
    cipher_raw.resize(size);
    decoder.Get((byte*)cipher_raw.data(), cipher_raw.size());

  }
  // Decryption
  Salsa20::Decryption salsa;
  salsa.SetKeyWithIV(key, 32, iv);

  StringSource ss(cipher_raw, true, new StreamTransformationFilter(salsa, new StringSink(plaintext)));

  return plaintext;
}

int main() {
  string key_str = "fc2bd3656165f8fd2a5363b49a514a7a10d0e129f51042ab34975cd2ab4fd1d1";
  string iv_str = "bb1f148064917508";
  string ciphertext = "";
  string plaintext = "Since 1940, the year Chuck Norris was born, roundhouse kick related deaths have increased 13,000 percent.";
 
  
  ciphertext = encrypt(plaintext, key_str, iv_str);
  
  //Output decrypted plaintext
  cout << "Ciphertext: " << ciphertext << endl << endl;
  
  plaintext = decrypt(ciphertext, key_str, iv_str);

  //Output decrypted plaintext
  cout << "Plaintext: " << plaintext << endl << endl;

  return 0;

}