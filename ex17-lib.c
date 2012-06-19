#include "ex17.h"

/* void die (const char * message)  */
/* { */
/* if (errno) { */
/* perror(message); */
/* } else { */
/* printf("ERROR: %s\n", message);  */
/* } */

/* exit(1); */
/* } */

static void
truncpy(char *target, const char *source) {
    if (strlen(source) <= MAXDATA - 1)
        strncpy(target, source, strlen(source) + 1);
    else {
        strncpy(target, source, MAXDATA - 1);
        target[MAXDATA - 1] = '\0';
    }
}

/*
  email, name are mandatory fields,
  idx, set = 0
  nickname will be defaulted to name
  returns NULL, if an error occurs
*/
Address        *
Address_create(const char *nickname,
               const char *name, const char *email) {
    Address        *address;

    check(email, "email is NULL");

    check(name, "name is NULL");

    address = malloc(sizeof(Address));
    check_mem(address);

    address->idx = 0;
    address->set = 0;

    truncpy(address->email, email);
    truncpy(address->name, name);

    if (nickname)
        truncpy(address->nickname, nickname);
    else
        strcpy(address->nickname, address->name);

    return address;
error:
    return NULL;
}

/*
  free allocated memory of record
  return 0/1, if OK/failure
*/
int
Address_delete(Address * record) {
    check(record, "record is NULL");
    cfree(record);
    return 0;
error:
    return 1;
}

void
Address_print(const Address * record) {
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
int
Database_createdb(Connection * conn) {
    assert(conn);
    assert(conn->db);
    assert(conn->db_file);
    assert(conn->mode == 'c');

    for (int i = 0; i < MAXRECORDS; i++) {
        //make a prototype to initialize it
        Address addr = {
            .idx = i,.set = 0
        };
        //then just assign it
        conn->db->records[i] = addr;
    }

    check(!(Database_flushdb(conn)), "database flush failed");

    conn->mode = 'w';
    return 0;
error:
    return 1;
}

/*
  flush database to db_file
  return 0/1, if OK/failure
*/
int
Database_flushdb(Connection * conn) {
    size_t          rc;

    rewind(conn->db_file);

    rc = fwrite(conn->db, sizeof(Database), 1, conn->db_file);
    check((rc == 1), "createdb failed to write database.");

    rc = fflush(conn->db_file);
    check((rc != -1), "createdb cannot flush database.");

    return 0;
error:
    return 1;
}

/*
 * delete db file, if connection is valid and mode permits free memory
 * allocated for db return 0/1, if OK/failure
 */
int
Database_deletedb(Connection * conn) {
    assert(conn);
    assert(conn->db);
    assert(conn->db_file);

    check((conn->mode == 'w'),
          "Connection mode '%d' invalid", conn->mode);
    check(fclose(conn->db_file),
          "close db_file failed");
    check(remove(conn->db_name),
          "remove db_file failed");

    cfree(conn->db_name);
    cfree(conn->db);
    cfree(conn);

    return 0;
error:
    return 1;
}

//DataBase_open();

//Database_close();

/*
  load database from file
  return 0, if OK
*/
int
Database_loaddb(Connection * conn) {
    size_t          rc;

    assert(conn);
    assert(conn->db);
    assert(conn->db_file);

    rewind(conn->db_file);
    for (int i = 0; i < MAXRECORDS; i++) {
        rc = fread(&conn->db->records[i], sizeof(Address), 1, conn->db_file);
        check((rc == 1), "createdb failed to write database.");
    }

    return 0;
error:
    return 1;
}

/*
  write record at idx to file, if connection mode permits
  return 0/1, if OK/failure
*/
int
Database_writebyidx(Connection * conn, const int idx) {
    assert(conn);
    assert(conn->db);

    check((conn->mode == 'w'),
          "connection mode '%d' != 'w' is invalid", conn->mode);
    check((idx > -1 && idx < MAXRECORDS),
          "idx %d out of bound", idx);

    assert(conn->db->records[idx].set);
    assert(conn->db->records[idx].name);
    assert(conn->db->records[idx].email);

    check((fseeko(conn->db_file,
                  (idx * sizeof(Address) - ftell(conn->db_file)),
                  SEEK_CUR) != -1),
          "fseek with offset failed");
    check(fwrite(&conn->db->records[idx],
                 sizeof(Address), 1,
                 conn->db_file),
          "fwrite failed");

    return 0;
error:
    return 1;
}

/*
  free index in connected database, if connection mode permits
  free allocated memory of record
  return 0/1, if OK/failure
*/
int
Database_deletebyidx(Connection * conn, const int idx) {
    return 0;
}

/*
  return free idx, if OK
  return MAXRECORDS, if failure
*/
int
Database_getfreeidx(Connection * conn) {
    for (int i = 0; i < MAXRECORDS; i++)
        if (!conn->db->records[i].set)
            return i;
    return MAXRECORDS;
}

/*
  set address.set and address.idx
  write record at idx to file
  return 0/1, if OK/failure
*/
int
Database_set(Connection * conn, const Address * record) {
    int             idx;

    assert(conn);
    assert(record);

    idx = Database_getfreeidx(conn);
    assert(idx > -1);
    if (idx < MAXRECORDS) {
        assert(conn->db->records[idx].idx == idx);
        conn->db->records[idx].set = 1;
        strcpy(conn->db->records[idx].nickname, record->nickname);
        strcpy(conn->db->records[idx].name, record->name);
        strcpy(conn->db->records[idx].email, record->email);
        return 0;
    }
    log_err("record idx out of bound");
    return 1;
}

/*
  return NULL, if Address not found/error
*/
Address        *
Database_getbyidx(Connection * conn, const int idx) {
    assert(conn);

    if (idx < 0 || idx >= MAXRECORDS)
        return NULL;

    return &(conn->db->records[idx]);
}

/*
  dump database to stdout
*/
void
Database_list(Connection * conn) {
    assert(conn);
    assert(conn->db);

    for (int i = 0; i < MAXRECORDS; i++)
        if (conn->db->records[i].set)
            Address_print(&(conn->db->records[i]));

    return;
}

/*
  mode 'c': create & init local database file; die, if file exists
  mode 'w': open database file, permit 'rw' access; die, if file not exists
  mode 'r': open database file, permit only 'r' access; die, if file not exists
  > return connection
*/
Connection     *
Connection_open(const char *db_name, const char mode) {
    Connection     *conn = malloc(sizeof(Connection));
    check_mem(conn);

    conn->db = malloc(sizeof(Database));
    check_mem(conn->db);

    conn->db_name = malloc(strlen(db_name));
    check_mem(conn->db_name);

    switch (mode) {
    case 'c':
        check(!(fopen(db_name, "r")), "connection open(create) on existing file");
        conn->db_file = fopen(db_name, "w");
        conn->mode = 'c';
        check(!(Database_createdb(conn)), "database create failed");
        break;
    case 'w':
        conn->db_file = fopen(db_name, "r+");
        check(!(Database_loaddb(conn)), "database load failed");
        conn->mode = 'w';
        break;
    case 'r':
        conn->db_file = fopen(db_name, "r");
        check(!(Database_loaddb(conn)), "database load failed");
        conn->mode = 'r';
        break;
    default:
        sentinel("connection open mode invalid");
    }

    check(conn->db_file, "db_file is NULL");

    return conn;
error:
    return NULL;
}

/*
  return 0/1, if OK/failure
*/
int
Connection_close(Connection * conn) {
    assert(conn);
    assert(conn->db_file);
    assert(conn->db_name);
    assert(conn->db);

    check(!(Database_flushdb(conn)), "database flush failed");
    fclose(conn->db_file);
    cfree(conn->db_name);
    cfree(conn->db);
    cfree(conn);
    return 0;
error:
    return 1;
}
