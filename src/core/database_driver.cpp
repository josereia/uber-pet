#include "database_driver.hpp"
#include <sqlite3.h>
#include <stdio.h>
#include <iostream>
#include <tuple>
#include <vector>

sqlite3* db;
const char* filename = "database.db";

namespace DatabaseDriver {
using namespace std;

int execute(string sql) {
  sqlite3_open("database.db", &db);

  int rc = sqlite3_exec(db, sql.c_str(), NULL, NULL, NULL);

  sqlite3_close(db);

  return rc;
}

vector<vector<string>> step(string sql) {
  sqlite3_open("database.db", &db);

  sqlite3_stmt* stmt;
  sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

  std::vector<std::vector<std::string>> results;
  while (sqlite3_step(stmt) == SQLITE_ROW) {
    std::vector<std::string> row;
    for (int i = 0; i < sqlite3_column_count(stmt); i++) {
      row.push_back(std::string(
          reinterpret_cast<const char*>(sqlite3_column_text(stmt, i))));
    }
    results.push_back(row);
  }

  sqlite3_finalize(stmt);
  sqlite3_close(db);

  return results;
}

bool exists(const char* tableName) {
  sqlite3_open("database.db", &db);

  string sql = "SELECT name FROM sqlite_master WHERE type='table' AND name='" +
               string(tableName) + "';";

  sqlite3_stmt* stmt;
  sqlite3_prepare_v2(db, sql.c_str(), -1, &stmt, nullptr);

  int rc = sqlite3_step(stmt);

  sqlite3_finalize(stmt);
  sqlite3_close(db);

  return rc == SQLITE_ROW;
}
}  // namespace DatabaseDriver