#ifndef database_driver
#define database_driver

#include <sqlite3.h>
#include <tuple>

namespace DatabaseDriver
{
  void init(sqlite3 *_db);
  int open(const char *filename);
  int close();
  int execute(const char *sql);
  std::tuple<int, sqlite3_stmt *> prepare(const char *sql);
  int step(sqlite3_stmt *stmt);
  bool exists(const char *tableName);
} // namespace DatabaseDriver

#endif // database_driver