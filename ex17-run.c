#include "ex17.h"

#define TESTDB "test.db"

/*
  run database lifecycle
*/
void Database_run(void)
{
  Connection * conn;
  Address * record = malloc(sizeof(Address));

  check(record, "address alloc failed");

  if(fopen(TESTDB, "r")) 
    conn = Connection_open(TESTDB, 'w');
  else
    conn = Connection_open(TESTDB, 'c');

  check(conn, "database connection failure");

  Database_list(conn);
  
  for (int i = -1; i < 5; i++)
    Address_print(Database_getbyidx(conn, i));

  strcpy(record->nickname,"Joe");
  strcpy(record->name,"Hans Glück");
  strcpy(record->email,"james@forrest.org");
 
  check(!(Database_set(conn, record)), "database set() record");

  strcpy(record->nickname,"Grit");
  strcpy(record->name,"Gretel Glück");
  strcpy(record->email,"grit@forrest.org");
 
  check(!(Database_set(conn, record)),"database set() record");

  strcpy(record->nickname,"rs");
  strcpy(record->name,"Rumpelstilzchen");
  strcpy(record->email,"rs@forrest.org");
 
  check(!(Database_set(conn, record)), "database set() record");

  Database_list(conn);
  
  /* avoid memory leak */
  cfree(record);
  /* reuse record */
  record = Database_getbyidx(conn, 1);

  check(!(Database_set(conn, record)), "database set() record");

  Database_list(conn);

  for(int i = 0; i < MAXRECORDS; i++)
    if (conn->db->records[i].set)
      check(!(Database_writebyidx(conn, i)), "write-by-idx error");

  Database_list(conn);

  check(!(Connection_close(conn)), "connection close failed");
  /* leaves record as dangling pointer, hence reset it */
  record = NULL;

  return;
error:
  exit(-1);
}
