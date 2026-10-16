#include <stdio.h>
#include <libpq-fe.h>

int main(int argc, char *argv[]) {
    if (argc != 6) {
        printf("Usage: %s <host> <port> <dbname> <user> <password>\n", argv[0]);
        return 1;
    }

    char conninfo[256];
    snprintf(conninfo, sizeof(conninfo),
             "host=%s port=%s dbname=%s user=%s password=%s",
             argv[1], argv[2], argv[3], argv[4], argv[5]);

    PGconn *conn = PQconnectdb(conninfo);

    if (PQstatus(conn) == CONNECTION_OK) {
        printf("Connected to database: %s\n", argv[3]);
    } else {
        printf("Connection to database failed: %s\n", PQerrorMessage(conn));
    }

    PQfinish(conn);
    return 0;
}
