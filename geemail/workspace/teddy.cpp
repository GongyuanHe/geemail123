#include <iostream>
#include "salsa.h"
#include "hex.h"

using namespace std;
using namespace CryptoPP;

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
  string ciphertext = "e2ddeb87f2de6fc112e5ee42aee56958c9918ed95591fad6025e911a7986e8e548dd9fc94a1d38081b1984165a8c2e0c9861fa3794ed744baed388a80c2ef76dc2dd2e316bfa1e75ddcedaa4\
188671c6664e654e0a1ac1c170ba39a9b58d2fdafa5695651ccd4569f8";
  string key_str = "fc2bd3656165f8fd2a5363b49a514a7a10d0e129f51042ab34975cd2ab4fd1d1";
  string iv_str = "bb1f148064917508";
  string plaintext;

  plaintext = decrypt(ciphertext, key_str, iv_str);

  //Output decrypted plaintext
  cout << "Plaintext: " << plaintext << endl << endl;

  return 0;

}