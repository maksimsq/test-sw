#include <stdio.h>
#include <libpq-fe.h>
#include "printer.h"

ExecStatusType get_printer(PGconn *conn) {
    PGresult *res;

    // START TRANSACTION
    res = PQexec(conn, "START TRANSACTION");
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        printf("START TRANSACTION failed: %s\n", PQerrorMessage(conn));
        PQclear(res);
        return PQresultStatus(res);
    }
    printf("Transaction started.\n");
    PQclear(res);

    // LOCK TABLE
    res = PQexec(conn, "LOCK TABLE printer IN ACCESS SHARE MODE");
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        printf("LOCK TABLE failed: %s\n", PQerrorMessage(conn));
        PQclear(res);
        return PQresultStatus(res);
    }
    printf("Table locked.\n");
    PQclear(res);

    // SELECT
    res = PQexec(conn, "SELECT * FROM printer");
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        printf("SELECT failed: %s\n", PQerrorMessage(conn));
        PQclear(res);
        return PQresultStatus(res);
    }

    int rows = PQntuples(res);
    printf("Rows in printer table:\n");
    for (int i = 0; i < rows; i++) {
        printf("ID: %s, Model: %s, Year: %s\n",
               PQgetvalue(res, i, 0),
               PQgetvalue(res, i, 1),
               PQgetvalue(res, i, 2));
    }
    PQclear(res);

    // COMMIT
    res = PQexec(conn, "COMMIT");
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        printf("COMMIT failed: %s\n", PQerrorMessage(conn));
        PQclear(res);
        return PQresultStatus(res);
    }
    printf("Transaction committed.\n");
    PQclear(res);

    return PGRES_COMMAND_OK;
}
