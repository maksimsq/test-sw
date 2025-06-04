#include <stdio.h>
#include <libpq-fe.h>
#include "printer.h"

PGconn* connect_printer() {
    const char *conninfo = "host=localhost port=5432 dbname=ai241-karaulnyi_db user=ai241-karaulnyi password=1234";
    PGconn *conn = PQconnectdb(conninfo);

    if (PQstatus(conn) != CONNECTION_OK) {
        fprintf(stderr, "Connection to database ai241-karaulnyi_db failed: %s\n", PQerrorMessage(conn));
        PQfinish(conn);
        return NULL;
    }
    printf("Successfully connected to database ai241-karaulnyi_db\n");
    return conn;
}
