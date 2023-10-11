#include <sqlite3.h>
#include <core/database_driver.hpp>
#include <string>
#include <tuple>
#include "sale_module.hpp"

namespace SaleRepository {
using namespace std;

vector<vector<string>> find_all() {
  string sql = "SELECT * FROM sales";
  auto [results, _] = DatabaseDriver::step(sql, {});

  return results;
}

vector<vector<string>> find_by_id(string id) {
  string sql = "SELECT * FROM sales WHERE id = ?";
  auto [results, _] = DatabaseDriver::step(sql, {id});

  return results;
}

void create(vector<string> data) {
  string sql =
      "INSERT INTO sales ("
      "service,"
      "pet,"
      "customer,"
      "driver,"
      "total"
      ")"
      "VALUES ("
      "?,"
      "?,"
      "?,"
      "?,"
      "?);";

  DatabaseDriver::step(sql, data);
}

void remove(string id) {
  string sql = "DELETE FROM sales WHERE id = ?";
  DatabaseDriver::step(sql, {id});
};
}  // namespace SaleRepository