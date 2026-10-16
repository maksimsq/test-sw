#include <stdio.h>
#include <libpq-fe.h>
#include "printer.h"

ExecStatusType add_printer(PGconn *conn) {
    PGresult *res;

    // 1. START TRANSACTION
    res = PQexec(conn, "START TRANSACTION");
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        printf("START TRANSACTION failed: %s\n", PQerrorMessage(conn));
        PQclear(res);
        return PQresultStatus(res);
    }
    printf("Transaction started.\n");
    PQclear(res);

    // 2. LOCK TABLE
    res = PQexec(conn, "LOCK TABLE printer IN ACCESS EXCLUSIVE MODE");
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        printf("LOCK TABLE failed: %s\n", PQerrorMessage(conn));
        PQclear(res);
        return PQresultStatus(res);
    }
    printf("Table locked.\n");
    PQclear(res);

    // 3. INSERT INTO
    res = PQexec(conn, "INSERT INTO printer VALUES (1, 'Samsung ML100', 2010)");
    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        printf("INSERT failed: %s\n", PQerrorMessage(conn));
        PQclear(res);
        return PQresultStatus(res);
    }
    printf("Row inserted into printer.\n");
    PQclear(res);

    // 4. COMMIT
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
