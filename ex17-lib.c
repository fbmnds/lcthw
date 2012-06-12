#include "ex17.h"

void die (const char * message) 
{
  if (errno) {
    perror(message);
  } else {
    printf("ERROR: %s\n", message); 
  }
  
  exit(1);
}

static void truncpy (char * target, const char * source)
{
  if (strlen(source) <= MAXDATA - 1) 
    strncpy(target, source, strlen(source)+1); 
  else {
    strncpy(target, source, MAXDATA-1);
    target[MAXDATA-1] = '\0';
  }
}

/*
  email, name are mandatory fields, 
  idx, set = 0 
  nickname will be defaulted to name
  returns NULL, if an error occurs
*/
Address * Address_create(const char * nickname, 
			 const char * name, const char * email)
{
  Address * address;

  if (!email) return NULL;

  if (!name) return NULL;

  address = malloc(sizeof(Address)); 
  if (!address) die("ERROR: malloc address\n"); 

  address->idx = 0;
  address->set = 0;

  truncpy(address->email, email);
  truncpy(address->name, name);

  if(nickname)
    truncpy(address->nickname, nickname);
  else
    strcpy(address->nickname, address->name);

  return address;
}

/*
  free allocated memory of record
  return 0/1, if OK/failure
*/
int Address_delete(Address * record)
{
  if (!record) return 1;

  free(record);
  return 0;
}

void Address_print(const Address * record)
{
  if (record) {
    printf("idx: %d \t\t set: %d\n", record->idx, record->set);
    printf("nickname: %s\n", record->nickname);
    printf("name: %s\n", record->name);
    printf("email: %s\n", record->email);
  }
}


/*
  create db structure in db file, if connection mode permits
  set mode to 'w', if OK
  return 0/1, if OK/failure
*/
int Database_createdb(Connection * conn)
{
  assert(conn);
  assert(conn->db);
  assert(conn->db_file);
  assert(conn->mode == 'c');

  for(int i = 0; i < MAXRECORDS; i++) {
    // make a prototype to initialize it
    Address addr = {.idx = i, .set = 0};
    // then just assign it
    conn->db->records[i] = addr;
  }

  Database_flushdb(conn);

  conn->mode = 'w';
  return 0;
}

/*
  flush database to db_file
*/
void Database_flushdb(Connection * conn)
{
  size_t rc;

  rewind(conn->db_file);
  rc = fwrite(conn->db, sizeof(Database), 1, conn->db_file);
  if (rc != 1) die("ERROR: createdb failed to write database.");

  rc = fflush(conn->db_file);
  if (rc == -1) die("ERROR: createdb cannot flush database.");

  return;
}

/* 
  delete db file, if connection is valid and mode permits
  free memory allocated for db 
  return 0/1, if OK/failure
*/
int Database_deletedb(Connection * conn)
{
  int rc;

  assert(conn);
  assert(conn->db);
  assert(conn->db_file);

  if (conn->mode != 'w')
    return 1;

  rc += fclose(conn->db_file);
  rc += remove(conn->db_name);
  free(conn->db_name);

  free(conn->db);

  free(conn);

  return (rc != 0);
}

//DataBase_open();

//Database_close();

/*
  load database from file
  die, if error/failure
  return 0, if OK
*/
int Database_loaddb(Connection * conn)
{
  size_t rc;

  assert(conn);
  assert(conn->db);
  assert(conn->db_file);

  rewind(conn->db_file);
  for (int i = 0; i < MAXRECORDS; i++) {
    rc = fread(&conn->db->records[i], sizeof(Address), 1, conn->db_file);
    if (rc != 1) die("ERROR: createdb failed to write database.");
  }

  return 0;
}

/*
  write record at idx to file, if connection mode permits
  return 0/1, if OK/failure
*/
int Database_writebyidx(Connection * conn, const int idx)
{
  assert(conn);
  assert(conn->db);

  if (conn->mode != 'w') 
    return 1;

  if (idx < 0 || idx >= MAXRECORDS)
    return 1;

  assert(conn->db->records[idx].set);
  assert(conn->db->records[idx].name);
  assert(conn->db->records[idx].email);

  if (!fseeko(conn->db_file, 
	      (idx*sizeof(Address) - ftell(conn->db_file)),
	      SEEK_CUR))
    return 1;

  if (!(fwrite(&conn->db->records[idx], sizeof(Address), 1, conn->db_file)))
    return 1;;

  return 0;
}

/*
  free index in connected database, if connection mode permits
  free allocated memory of record
  return 0/1, if OK/failure
*/
int Database_deletebyidx(Connection * conn, const int idx)
{
  return 0;
}

/*
  return free idx, if OK
  return MAXRECORDS, if failure
*/
int Database_getfreeidx(Connection * conn)
{
  for (int i = 0; i < MAXRECORDS; i++)
    if (!conn->db->records[i].set) return i; 
  return MAXRECORDS;
}

/*
  set address.set and address.idx
  write record at idx to file
  return 0/1, if OK/failure
*/
int Database_set(Connection * conn, const Address * record)
{
  int idx;

  assert(conn);
  assert(record);

  idx = Database_getfreeidx(conn);
  assert(idx > -1);
  if (idx < MAXRECORDS) {
    assert(conn->db->records[idx].idx == idx);
    conn->db->records[idx].set = 1;
    strcpy(conn->db->records[idx].nickname,record->nickname);
    strcpy(conn->db->records[idx].name,record->name);
    strcpy(conn->db->records[idx].email,record->email);
    return 0;
  }
  
  return 1;
}

/*
  return NULL, if Address not found/error
*/
Address * Database_getbyidx(Connection * conn, const int idx)
{
  assert(conn);

  if (idx < 0 || idx >= MAXRECORDS)
    return NULL;

  return &(conn->db->records[idx]);
}

/*
  return 0/1, if OK/failure
*/
int Database_list(Connection * conn)
{
  assert(conn);

  for (int i = 0; i < MAXRECORDS; i++)
    if (conn->db->records[i].set) Address_print(&(conn->db->records[i]));

  return 0;
}

/*
  mode 'c': create & init local database file; die, if file exists
  mode 'w': open database file, permit 'rw' access; die, if file not exists
  mode 'r': open database file, permit only 'r' access; die, if file not exists
  > return connection
*/
Connection * Connection_open(const char * db_name, const char mode)
{
  Connection * conn = malloc(sizeof(Connection));
  if (!conn) die("ERROR: connection alloc connection failed");

  conn->db = malloc(sizeof(Database));
  if(!conn->db) die("ERRROR: connection alloc database failed");

  if (!(conn->db_name = malloc(strlen(db_name))))
    die("ERROR: alloc db_name");
  
  switch (mode) {
  case 'c':
    if(fopen(db_name, "r")) 
      die("ERROR: connection open(create) on existing file");
    conn->db_file = fopen(db_name, "w");
    conn->mode = 'c';
    if (Database_createdb(conn)) 
      die ("ERROR: create database failed");
    break;
  case 'w':
    conn->db_file = fopen(db_name, "r+");
    Database_loaddb(conn);
    conn->mode = 'w';
    break;
  case 'r':
    conn->db_file = fopen(db_name, "r");
    Database_loaddb(conn);
    conn->mode = 'r';
    break;
  default:
    die ("ERROR: connection open mode invalid");
  }

  if (conn->db_file)
    return conn;
  else
    return NULL;
}

/*
  return 0/1, if OK/failure
*/
int Connection_close(Connection * conn)
{
  assert(conn);
  assert(conn->db_file);
  assert(conn->db_name);
  assert(conn->db);

  Database_flushdb(conn);
  fclose(conn->db_file);
  free(conn->db_name);
  free(conn->db);
  free(conn);
  return 0;
}
