#include <sqlite3.h>
#include <core/database_driver.hpp>
#include <string>
#include <tuple>
#include "driver_module.hpp"

namespace DriverRepository {
using namespace std;

vector<vector<string>> find_all() {
  string sql = "SELECT * FROM drivers";
  auto [results, _] = DatabaseDriver::step(sql, {});

  return results;
}

vector<vector<string>> find_by_id(string id) {
  string sql = "SELECT * FROM drivers WHERE id = ?";
  auto [results, _] = DatabaseDriver::step(sql, {id});

  return results;
}

void create(vector<string> data) {
  string sql =
      "INSERT INTO drivers ("
      "name,"
      "cnh,"
      "marital_status,"
      "criminal,"
      "address,"
      "license_plate,"
      "phone1,"
      "phone2"
      ")"
      "VALUES ("
      "?,"
      "?,"
      "?,"
      "?,"
      "?,"
      "?,"
      "?,"
      "?);";

  DatabaseDriver::step(sql, data);
}

void update(string id, vector<string> data) {
  string sql =
      "UPDATE drivers SET name = ?, cnh = ?, marital_status = ?, criminal = ?, "
      "address = ?, license_plate = ?, phone1 = ?, phone2 = ? WHERE id = " +
      id;

  DatabaseDriver::step(sql, data);
}

void remove(string id) {
  string sql = "DELETE FROM drivers WHERE id = ?";
  DatabaseDriver::step(sql, {id});
};
}  // namespace DriverRepository