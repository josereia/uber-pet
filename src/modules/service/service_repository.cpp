#include <sqlite3.h>
#include <core/database_driver.hpp>
#include <string>
#include <tuple>
#include "service_module.hpp"

namespace ServiceRepository {
using namespace std;

vector<vector<string>> find_all() {
  string sql = "SELECT * FROM services";
  auto [results, _] = DatabaseDriver::step(sql, {});

  return results;
}

vector<vector<string>> find_by_id(string id) {
  string sql = "SELECT * FROM services WHERE id = ?";
  auto [results, _] = DatabaseDriver::step(sql, {id});

  return results;
}

void create(vector<string> data) {
  string sql =
      "INSERT INTO services ("
      "name,"
      "description,"
      "price"
      ")"
      "VALUES ("
      "?,"
      "?,"
      "?);";

  DatabaseDriver::step(sql, data);
}

void update(string id, vector<string> data) {
  string sql =
      "UPDATE services SET name = ?, description = ?, price = ? WHERE id = " +
      id;

  DatabaseDriver::step(sql, data);
}

void remove(string id) {
  string sql = "DELETE FROM services WHERE id = ?";
  DatabaseDriver::step(sql, {id});
};
}  // namespace ServiceRepository