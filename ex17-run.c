#include "ex17.h"

#define TESTDB "test.db"

/*
  run database lifecycle
*/
void Database_run(void)
{
  Connection * conn;
  Address * record;

  if(fopen(TESTDB, "r")) 
    conn = Connection_open(TESTDB, 'w');
  else
    conn = Connection_open(TESTDB, 'c');

  if (!conn) die("ERROR: Database run failure");

  Database_list(conn);
  
  for (int i = -1; i < 5; i++)
    Address_print(Database_getbyidx(conn, i));

  strcpy(record->nickname,"Joe");
  strcpy(record->name,"Hans Glück");
  strcpy(record->email,"james@forrest.org");
 
  if (Database_set(conn, record)) die("ERROR: database set() record");

  strcpy(record->nickname,"Grit");
  strcpy(record->name,"Gretel Glück");
  strcpy(record->email,"grit@forrest.org");
 
  if (Database_set(conn, record)) die("ERROR: database set() record");

  strcpy(record->nickname,"rs");
  strcpy(record->name,"Rumpelstilzchen");
  strcpy(record->email,"rs@forrest.org");
 
  if (Database_set(conn, record)) die("ERROR: database set() record");

  Database_list(conn);

  record = Database_getbyidx(conn, 1);

  if (Database_set(conn, record)) die("ERROR: database set() record");

  Database_list(conn);

  for(int i = 0; i < MAXRECORDS; i++)
    if (conn->db->records[i].set)
      Database_writebyidx(conn, i);

  Database_list(conn);

  Connection_close(conn);
  
  return;
}
