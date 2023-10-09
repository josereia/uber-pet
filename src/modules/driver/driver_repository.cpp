#include <sqlite3.h>
#include <core/database_driver.hpp>
#include <string>
#include <tuple>
#include "driver_module.hpp"

namespace DriverRepository {
using namespace std;

vector<vector<string>> find_all() {
  sqlite3* db;
  sqlite3_open("database.db", &db);

  std::string sql = "SELECT * FROM drivers";
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

  return results;
}
}  // namespace DriverRepository