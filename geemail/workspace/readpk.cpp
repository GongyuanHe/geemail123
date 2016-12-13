#include <stdio.h>
#include <gcrypt.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <iostream>
using namespace std;
string rec = "";
static int callback(void *data, int argc, char **argv, char **azColName){
   int i;
  // fprintf(stderr, "%s: ", (const char*)data);
   for(i=0; i<argc; i++){
      //printf("%s  ", argv[i] ? argv[i] : "NULL");
      rec = argv[0];
   }
 
   printf("\n");
   return 0;
}

int main(int argc, char* argv[])
{
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
    //  fprintf(stderr, "Opened database successfully\n");
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
   rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      //fprintf(stdout, "Operation done successfully\n");
   }
   sqlite3_close(db);
   cout << argv[2] <<"    "<< rec<<endl;
   return 0;
}