#include <stdio.h>
#include <gcrypt.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <iostream>  
#include "salsa.h"
#include "hex.h"
#include <time.h> 
#include "osrng.h"
#include <cryptopp/base64.h>




using namespace std;
using namespace CryptoPP;
bool b;
char SPKBuffer[65];


static int callback1(void *data, int argc, char **argv, char **azColName){
   int i;
   fprintf(stderr, "%s: ", (const char*)data);

   for(i=0;i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
      b=true;
      strncpy(SPKBuffer, argv[i], 64);
   }
   
   printf("\n");

   return 0;
}

static int callback2(void *NotUsed, int argc, char **argv, char **azColName){
   int i;
   for(i=0;i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}



int main (int argc, char* argv[]){
    
   srand((unsigned)time(NULL));  
   b=false; 
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   
   const char* data = "Callback function called";

   /* Open database */
   rc = sqlite3_open("geemail.db", &db);
   if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      exit(0);
   }else{
      fprintf(stderr, "Opened database successfully\n");
   }



   /* Create SQL statement */
   string sqlstr="";
   sqlstr +=  "select PK from passphrase where (username1='";     
   sqlstr +=  argv[1];
   sqlstr +=  "' and username2='";
   sqlstr +=  argv[2];
   sqlstr +=  "') or (username1='";
   sqlstr +=  argv[2];
   sqlstr +=  "' and username2='";
   sqlstr +=  argv[1];
   sqlstr +=  "');";
      
   
    char *sql = const_cast<char*>(sqlstr.c_str());
    
    
    

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback1, (void*)data, &zErrMsg);
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "Operation done successfully\n");
   }
   sqlite3_close(db);
   
   
   
   
   
   if (b==false){
       
       sqlite3 *db;
       char *zErrMsg = 0;
       int rc;
       int PK=rand() % 935;
       char C_PK[3];

       for(int i=0;i<3;i++){
          sprintf(C_PK,"%d",PK);
          cout << C_PK[i] << endl;
       }

       
       size_t index; 
       size_t txtLength = 3;
       char * hashBuffer = (char*) malloc(33);

       
       
       
       memset(hashBuffer, 0, 33);
       
       gcry_md_hash_buffer(
       GCRY_MD_SHA256, // gcry_cipher_hd_t
       hashBuffer,    // void *
       C_PK,    // const void *
       txtLength);   // size_t

       printf("hashBuffer = ");
       for (index = 0; index<32; index++)
            printf("%02X", (unsigned char)hashBuffer[index]);
       printf("\n");

       
       printf("SPKBuffer   = ");
       for(index = 0; index < 32; index++)  
       {  

          sprintf(SPKBuffer + 2*index, "%02X", (unsigned char)hashBuffer[index]);  
        
       } 
       
       for (index = 0; index<64; index++)
             printf("%c",SPKBuffer[index]);
       printf("\n");
   
   
   

       /* Open database */
       rc = sqlite3_open("geemail.db", &db);
       if( rc ){
           fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
           exit(0);
        }else{
           fprintf(stderr, "Opened database successfully\n");
         }

        string sqlstr="";
        sqlstr +=  "insert into passphrase (username1,username2,PK)";     
        sqlstr +=  "values ('";
        sqlstr +=  argv[1];
        sqlstr +=  "','";
        sqlstr +=  argv[2];
        sqlstr +=  "','";
        
        for (index = 0; index<64; index++){
          sqlstr +=  SPKBuffer[index];
         }
        
        sqlstr +=  "');";
   
      
   
         char *sql = const_cast<char*>(sqlstr.c_str());

        /* Execute SQL statement */
        rc = sqlite3_exec(db, sql, callback2, 0, &zErrMsg);
        if( rc != SQLITE_OK ){
           fprintf(stderr, "SQL error: %s\n", zErrMsg);
           sqlite3_free(zErrMsg);
        }else{
           fprintf(stdout, "Records created successfully\n");
        }
        sqlite3_close(db);   
    }
    printf("SPKBuffer=");
    for (int index = 0; index<64; index++)
        printf("%c",SPKBuffer[index]);
    printf("\n");
    
    
    
    //Encryption 
    //initialization

	
	string ciphertextStr(""), plaintextStr("a b werwe sf s sdf asdfa sdf asd 123123 234234 weiguo");
    byte *plaintextBytes = (byte *) plaintextStr.c_str();
    byte *ciphertextBytes = new byte[plaintextStr.length()];
    
    
    // key string
    string key_str="";
    
    for (int index = 0; index<64; index++){
          key_str +=  SPKBuffer[index];
    }

    printf("\n");

    
    
    // key str 2 byte
    byte key[32];
    {
      HexDecoder decoder;
      decoder.Put((byte*)key_str.data(), key_str.size());
      decoder.MessageEnd();
      decoder.Get(key, sizeof(key));
    }
    
    for(int i=0;i<32;i++){
      printf("%02X",key[i]);
    }
    printf("\n");
    //fixed iv string, str 2 byte 
    
    
    string iv_str="4d5ca28b1e5f1de9";
    byte iv[8];
    {
        HexDecoder decoder;
        decoder.Put((byte*)iv_str.data(), iv_str.size());
        decoder.MessageEnd();
        decoder.Get(iv, sizeof(iv));
    }


    //Encryption salsa20

    
    Salsa20::Encryption salsa;	
	salsa.SetKeyWithIV(key, 32, iv);
	salsa.ProcessData(ciphertextBytes, plaintextBytes, plaintextStr.length());
   




    
    //ciphertext  byte 2 string
    
    StringSource ss(ciphertextBytes,plaintextStr.length(),true, new HexEncoder( new StringSink(ciphertextStr) ) ); 






    
	//Output plaintext/ciphertext for sanity check

	cout << "Ciphertext: "<< ciphertextStr<<endl;

    
    
    //decryption
    string cipher_raw;
    {
      HexDecoder decoder;
      decoder.Put((byte*)ciphertextStr.data(), ciphertextStr.size());
      decoder.MessageEnd();

      long long size = decoder.MaxRetrievable();
      cipher_raw.resize(size);
      decoder.Get((byte*)cipher_raw.data(), cipher_raw.size());

    }
    
    
    Salsa20::Decryption desalsa;
    desalsa.SetKeyWithIV(key, 32, iv);

    StringSource ss1(cipher_raw, true, new StreamTransformationFilter(desalsa, new StringSink(plaintextStr)));


    
    
    cout << "Plaintext: " << plaintextStr << endl;
    
    
    
   delete ciphertextBytes;
    
   return 0;
    
}