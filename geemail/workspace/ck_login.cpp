#include <stdio.h>
#include <gcrypt.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <iostream>  
using namespace std;
bool b;

static int callback(void *data, int argc, char **argv, char **azColName){       // put the select record
   int i;
   int a=0;
   fprintf(stderr, "%s: ", (const char*)data);
   if (argc==0){
       b=false;
   }
   for(i=0;i<argc; i++){
       printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
       size_t queryLength = strlen(argv[i]) ;
       char * queryBuffer = (char*) malloc(queryLength+1);
       strncpy(queryBuffer, argv[i], queryLength);
       char * check;

      
       check = (char *)data;
       for (int index = 0; index<64; index++){
             printf("%c",check[index]);
             
             if(check[index]==queryBuffer[index]){
                 a++;
             }
             
             
             
       if(a==64){
       b=true;
       }else{
       b=false;
       }
       }
       printf("\n");
    
       


   }
   printf("\n");

   return 0;
}



int main (int argc, char* argv[]) {
    size_t index;
    size_t txtLength = strlen(argv[2]) ;                                           
    char * hashBuffer = (char*) malloc(33);
    char * textBuffer = (char*) malloc(txtLength+1);
    char * passwd = (char*) malloc (65);                                         //buffer for hashed passwd
    
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
    
    printf("passwd     = ");                                                      //hashed value into passwd buffer
    for(index = 0; index < 32; index++)  
    {  

        sprintf(passwd + 2*index, "%02X", (unsigned char)hashBuffer[index]);  
        
    } 
    for (index = 0; index<64; index++)
        printf("%c",passwd[index]);
    printf("\n");
    
    
   sqlite3 *db;                                                                   //start database
   char *zErrMsg = 0;
   int rc;
   // string sql;
   
   const char* data = passwd;
   
   
   /* Open database */
   rc = sqlite3_open("geemail.db", &db);
   if( rc ){
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      exit(0);
   }else{
      fprintf(stderr, "Opened database successfully\n");
   }

   /* Create SQL statement */                                                    //write query
   string sqlstr="";
   sqlstr += "select passwd from user where username='";
   sqlstr +=argv[1];
   sqlstr += "'";
   char *sql = const_cast<char*>(sqlstr.c_str());
   

   
   rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);                 //sqlite3 core function, put each record into callback function
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      fprintf(stdout, "Operation done successfully\n");
   }
   sqlite3_close(db);
    
   printf(b ? "true" : "false");
   if (b==1){
       return true;
   }else{
       return false;
   }
}