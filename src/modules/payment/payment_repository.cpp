#include <sqlite3.h>
#include <core/database_driver.hpp>
#include <string>
#include <tuple>
#include "payment_module.hpp"

namespace PaymentRepository {
using namespace std;

vector<vector<string>> find_all() {
  string sql = "SELECT * FROM payments";
  auto [results, _] = DatabaseDriver::step(sql, {});

  return results;
}

vector<vector<string>> find_by_id(string id) {
  string sql = "SELECT * FROM payments WHERE id = ?";
  auto [results, _] = DatabaseDriver::step(sql, {id});

  return results;
}

void create(vector<string> data) {
  string sql =
      "INSERT INTO payments ("
      "name,"
      "tax_type,"
      "tax"
      ")"
      "VALUES ("
      "?,"
      "?,"
      "?);";

  DatabaseDriver::step(sql, data);
}

void update(string id, vector<string> data) {
  string sql =
      "UPDATE payments SET name = ?, tax_type = ?, tax = ? WHERE id = " + id;

  DatabaseDriver::step(sql, data);
}

void remove(string id) {
  string sql = "DELETE FROM payments WHERE id = ?";
  DatabaseDriver::step(sql, {id});
};
}  // namespace PaymentRepository