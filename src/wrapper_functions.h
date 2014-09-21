#ifndef WRAPPERFUNCTIONS_H_
#define WRAPPERFUNCTIONS_H_

#include "sqlite3ext.h"

void stringmetricsFunc(sqlite3_context *context, int argc, sqlite3_value **argv);

#endif /* WRAPPERFUNCTIONS_H_ */