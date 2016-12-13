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





using namespace std;
using namespace CryptoPP;
string ciphertextStr="";
char SPKBuffer[65];
string key_str="";



static int callback(void *data, int argc, char **argv, char **azColName){
   int i;
   //fprintf(stderr, "%s: ", (const char*)data);
   for(i=0; i<argc; i++){
      //printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
      ciphertextStr=argv[0];
   }
   printf("\n");
   return 0;
}


/*static int callback1(void *data, int argc, char **argv, char **azColName){
   int i;
   //fprintf(stderr, "%s: ", (const char*)data);

   for(i=0;i<argc; i++){
      //printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
      
      key_str=argv[0];
   }
   
   printf("\n");

   return 0;
}*/

int main (int argc, char* argv[]){
   
   
   //select cipher
   
   
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
      //fprintf(stderr, "Opened database successfully\n");
   }

   /* Create SQL statement */
   string sqlstr="";
   sqlstr += "select cipher from message where mid=";
   sqlstr +=argv[1];
   sqlstr += ";";
   char *sql = const_cast<char*>(sqlstr.c_str());
   
   

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      //fprintf(stdout, "Operation done successfully\n");
   }
   sqlite3_close(db);
   
   
   
   //select PK
   
   //zErrMsg = 0;
   
   


   /* Open database */
   /*rc = sqlite3_open("geemail.db", &db);
   if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      exit(0);
   }else{
      //fprintf(stderr, "Opened database successfully\n");
   }



   /* Create SQL statement */
   /*sqlstr="";
   sqlstr +=  "select PK from passphrase where (username1='";     
   sqlstr +=  argv[1];
   sqlstr +=  "' and username2='";
   sqlstr +=  argv[2];
   sqlstr +=  "') or (username1='";
   sqlstr +=  argv[2];
   sqlstr +=  "' and username2='";
   sqlstr +=  argv[1];
   sqlstr +=  "');";
      
   
    char *sql1 = const_cast<char*>(sqlstr.c_str());
    
    
    

   /* Execute SQL statement */
   /*rc = sqlite3_exec(db, sql1, callback1, (void*)data, &zErrMsg);
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      //fprintf(stdout, "Operation done successfully\n");
   }
   sqlite3_close(db);*/
   
   
    // hash passphrase into key_str
    
    size_t index;
    size_t txtLength = strlen(argv[2]) ;                                           
    char * hashBuffer = (char*) malloc(33);
    char * textBuffer = (char*) malloc(txtLength+1);
    
    
    memset(hashBuffer, 0, 33);

    strncpy(textBuffer, argv[2], txtLength);


    gcry_md_hash_buffer(                                                          // hash passwd=argv[2]
        GCRY_MD_SHA256, // gcry_cipher_hd_t
        hashBuffer,    // void *
        textBuffer,    // const void *
        txtLength);   // size_t

    printf("hashBuffer = ");
    for (index = 0; index<32; index++)
        printf("%02X", (unsigned char)hashBuffer[index]);
    printf("\n");
    
    printf("key_str     = ");                                                      //hashed value into passwd buffer
    for(index = 0; index < 32; index++)  
    {  

        sprintf(SPKBuffer + 2*index, "%02X", (unsigned char)hashBuffer[index]);  
        
    } 
    
    for (index = 0; index<64; index++)
        printf("%c",SPKBuffer[index]);
    printf("\n");
    
    // key string
    
    
    for (int index = 0; index<64; index++){
          key_str +=  SPKBuffer[index];
    }

    printf("\n");
   
   
   
   //decrption
   string plaintextStr="";
   
   // PK : key_str str 2 byte
    byte key[32];
    {
      HexDecoder decoder;
      decoder.Put((byte*)key_str.data(), key_str.size());
      decoder.MessageEnd();
      decoder.Get(key, sizeof(key));
    }
    
    //fixed IV
    
    
    string iv_str="4d5ca28b1e5f1de9";
    byte iv[8];
    {
        HexDecoder decoder;
        decoder.Put((byte*)iv_str.data(), iv_str.size());
        decoder.MessageEnd();
        decoder.Get(iv, sizeof(iv));
    }
    
    
    
    //ciphertextStr string 2 byte
    string cipher_raw;
    {
      HexDecoder decoder;
      decoder.Put((byte*)ciphertextStr.data(), ciphertextStr.size());
      decoder.MessageEnd();

      long long size = decoder.MaxRetrievable();
      cipher_raw.resize(size);
      decoder.Get((byte*)cipher_raw.data(), cipher_raw.size());

    }
    
    
    //desalsa
    Salsa20::Decryption desalsa;
    desalsa.SetKeyWithIV(key, 32, iv);

    StringSource ss(cipher_raw, true, new StreamTransformationFilter(desalsa, new StringSink(plaintextStr)));


    
    
    cout << "Plaintext: " << plaintextStr << endl;
   
   
   return 0;
   
}