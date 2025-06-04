#include "printer.h"

int main() {
    PGconn *conn = connect_printer();
    if (PQstatus(conn) != CONNECTION_OK) return 1;

    add_printer(conn);  // виклик нової функції
    get_printer(conn);  // виклик нової функції

    PQfinish(conn);
    return 0;
}
