/*
 * * Copyright (C) 2014 Andrea Peri et al. All rights reserved.
 *
 * This file is part of libstringmetrics
 *
 * libstringmetrics is a SQLite Extension for the Library libsimmetrics.
 * The Library libsimmetrics is a C port of the Java project called Simmetrics.
 *
 * The original C libsimmetrics can be found here: https://github.com/jokillsya/libsimmetrics
 * The original Java code can be found here: https://github.com/Simmetrics/simmetrics
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 *
 * stringmetrics.c
 *
 *  Created on: 15 Sept 2014
 *      Author: Andrea Peri <aperi2007@gmail.com>
 */

#include "wrapper_functions.h"
#include <sqlite3ext.h> /* Do not use <sqlite3.h>! */

SQLITE_EXTENSION_INIT1

__declspec(dllexport) int __cdecl sqlite3_stringmetrics_init(
  sqlite3 *db,
  char **pzErrMsg,
  const sqlite3_api_routines *pApi
){
  int rc = SQLITE_OK;
  SQLITE_EXTENSION_INIT2(pApi);
  sqlite3_create_function(db, "stringmetrics", -1, SQLITE_UTF8, 0, stringmetricsFunc, 0, 0);
  return rc;
}

