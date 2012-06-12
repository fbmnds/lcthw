#ifndef EX17_H
#define EX17_H

#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#define MAXDATA    20
#define MAXRECORDS 200 

typedef struct Address {
  int idx;                  /* index in conn->db[] */
  int set;                  /* set = 1: address is stored at conn->db[idx] */ 
  char nickname[MAXDATA];
  char name[MAXDATA];
  char email[MAXDATA];
} Address;

typedef struct Database {
  Address records[MAXRECORDS];
} Database;

typedef struct Connection {
  FILE * db_file;
  char * db_name;
  Database * db;
  int mode;                  /* modes for Connection_open() */
} Connection;

void die (const char * message);

/*
  copy source to target 
  truncate such that target fits to MAXDATA
  return 0/1, if OK/failure
  (hidden implementation in ex17-lib.h)

  static void truncpy (char * target, const char * source);
*/

/*
  email, name are mandatory fields 
  idx, set = 0 
  nickname will be defaulted 
  returns NULL, if an error occurs
*/
Address * Address_create(const char * nickname, 
			 const char * name, const char * email);

/*
  free allocated memory of record
  return 0/1, if OK/failure
*/
int Address_delete(Address * record);

void Address_print(const Address * record);

/*
  run database lifecycle
*/
void Database_run(void);

/*
  create db structure in db file, if connection mode permits
  set mode to 'w', if OK 
  return 0/1, if OK/failure
*/
int Database_createdb(Connection * conn);

/*
  flush database to db_file
*/
void Database_flushdb(Connection * conn);

/*
  delete db file, if connection is valid and mode permits
  free memory allocated for db 
  return 0/1, if OK/failure
*/
int Database_deletedb(Connection * conn);

//DataBase_open();

//Database_close();

/*
  load database from file
  die, if error/failure
  return 0, if OK
*/
int Database_loaddb(Connection * conn);

/*
  write record at idx to file, if connection mode permits
  return 0/1, if OK/failure
*/
int Database_writebyidx(Connection * conn, const int idx);

/*
  free index in connected database, if connection mode permits
  free allocated memory of record
  return 0/1, if OK/failure
*/
int Database_deletebyidx(Connection * conn, const int idx);

/*
  return free idx, if OK
  return MAXRECORDS, if failure
*/
int Database_getfreeidx(Connection * conn);

/*
  set address.set and address.idx
  write record at idx to file
  return 0/1, if OK/failure
*/
int Database_set(Connection * conn, const Address * record);

/*
  return NULL, if Address not found/error
*/
Address * Database_getbyidx(Connection * conn, const int idx);


/*
  return 0/1, if OK/failure
*/
int Database_list(Connection * conn);

/*
  mode 'c': create & init local database file; die, if file exists
  mode 'w': open database file, permit 'rw' access; die, if file not exists
  mode 'r': open database file, permit only 'r' access; die, if file not exists
  > return connection
  ### mode 'd': delete database file; die, if file not exists
  > return NULL
*/
Connection * Connection_open(const char * db_name, const char mode);

/*
  return 0/1, if OK/failure
*/
int Connection_close(Connection * conn);

#endif
