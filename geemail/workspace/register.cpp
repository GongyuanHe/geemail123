#include <stdio.h>
#include <gcrypt.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <iostream>  
using namespace std;



static int callback(void *NotUsed, int argc, char **argv, char **azColName){
   int i;
   for(i=0;i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}



int main (int argc, char* argv[]) {
    
    
    
    size_t index;
    size_t txtLength = strlen(argv[2]) ;
    char * hashBuffer = (char*) malloc(33);
    char * textBuffer = (char*) malloc(txtLength+1);
    char * passwd = (char*) malloc (65);
    
    memset(hashBuffer, 0, 33);

    strncpy(textBuffer, argv[2], txtLength);


    gcry_md_hash_buffer(
        GCRY_MD_SHA256, // gcry_cipher_hd_t
        hashBuffer,    // void *
        textBuffer,    // const void *
        txtLength);   // size_t

    printf("hashBuffer = ");
    for (index = 0; index<32; index++)
        printf("%02X", (unsigned char)hashBuffer[index]);
    printf("\n");
    
    printf("passwd     = ");
    for(index = 0; index < 32; index++)  
    {  

        sprintf(passwd + 2*index, "%02X", (unsigned char)hashBuffer[index]);  
        
    } 
    for (index = 0; index<64; index++)
        printf("%c",passwd[index]);
    printf("\n");
    
    
    
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;


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
   sqlstr +=  "INSERT INTO user (username,passwd) ";
   sqlstr +=  "VALUES ('";
   sqlstr +=  argv[1];
   sqlstr +=  "','";
   for (index = 0; index<64; index++){
        sqlstr +=  passwd[index];
   }
   sqlstr +=  "');";
   
    char *sql = const_cast<char*>(sqlstr.c_str());

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "Records created successfully\n");
   }
   sqlite3_close(db);
   return 0;
    
}