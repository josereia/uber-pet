#include <sqlite3.h>
#include <core/database_driver.hpp>
#include <string>
#include <tuple>
#include "pet_module.hpp"

namespace PetRepository {
using namespace std;

vector<vector<string>> find_all() {
  string sql = "SELECT * FROM pets";
  auto [results, _] = DatabaseDriver::step(sql, {});

  return results;
}

vector<vector<string>> find_by_id(string id) {
  string sql = "SELECT * FROM pets WHERE id = ?";
  auto [results, _] = DatabaseDriver::step(sql, {id});

  return results;
}

void create(vector<string> data) {
  string sql =
      "INSERT INTO pets ("
      "name,"
      "breed,"
      "sex,"
      "size,"
      "weight,"
      "observation"
      ")"
      "VALUES ("
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
      "UPDATE pets SET name = ?, breed = ?, sex = ?, size = ?, "
      "weight = ?, observation = ? WHERE id = " +
      id;

  DatabaseDriver::step(sql, data);
}

void remove(string id) {
  string sql = "DELETE FROM pets WHERE id = ?";
  DatabaseDriver::step(sql, {id});
};
}  // namespace PetRepository