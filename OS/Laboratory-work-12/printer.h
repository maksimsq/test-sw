#ifndef PRINTER_H
#define PRINTER_H

#include <stdio.h>
#include <stdlib.h>
#include <libpq-fe.h>

PGconn* connect_printer(void);
ExecStatusType add_printer(PGconn *conn); // додано
ExecStatusType get_printer(PGconn *conn); // додано

#endif
