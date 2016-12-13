#include <stdio.h>
#include <gcrypt.h>
#include <sqlite3.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <iostream>
using namespace std;
string sen = "";
string rec = "";
string PK = "";
static int callback(void *data, int argc, char **argv, char **azColName){
   int i;
  // fprintf(stderr, "%s: ", (const char*)data);
   for(i=0; i<argc; i++){
      //printf("%s  ", argv[i] ? argv[i] : "NULL");
      sen = argv[0];
      rec = argv[1];
   }
 
   printf("\n");
   return 0;
}

static int callback1(void *data, int argc, char **argv, char **azColName){
   int i;
  // fprintf(stderr, "%s: ", (const char*)data);
   for(i=0; i<argc; i++){
      //printf("%s  ", argv[i] ? argv[i] : "NULL");
     PK = argv[0];
     
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
   }
   
    /* Create SQL statement */
   string sqlstr="";
   sqlstr +=  "select sender, receiver from message where mid='";     
   sqlstr +=  argv[1];
   sqlstr +=  "';";
   
   char *sql = const_cast<char*>(sqlstr.c_str());
    

   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);
   
   string sqlstr2="";
   sqlstr2 +=  "select PK from passphrase where (username1='";     
   sqlstr2 +=  sen;
   sqlstr2 +=  "' and username2='";
   sqlstr2 +=  rec;
   sqlstr2 +=  "') or (username1='";
   sqlstr2 +=  rec;
   sqlstr2 +=  "' and username2='";
   sqlstr2 +=  sen;
   sqlstr2 +=  "');";
   
   char *sql1 = const_cast<char*>(sqlstr2.c_str());
   rc = sqlite3_exec(db, sql1, callback1, (void*)data, &zErrMsg);
   
   if( rc != SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }else{
      //fprintf(stdout, "Operation done successfully\n");
   }
   sqlite3_close(db);
   cout <<sen<<"    "<<PK <<endl;
   return 0;
}