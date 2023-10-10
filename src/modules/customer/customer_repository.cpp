#include <sqlite3.h>
#include <core/database_driver.hpp>
#include <string>
#include <tuple>
#include "customer_module.hpp"

namespace CustomerRepository {
using namespace std;

vector<vector<string>> find_all() {
  string sql = "SELECT * FROM customers";
  auto [results, _] = DatabaseDriver::step(sql, {});

  return results;
}

vector<vector<string>> find_by_id(string id) {
  string sql = "SELECT * FROM customers WHERE id = ?";
  auto [results, _] = DatabaseDriver::step(sql, {id});

  return results;
}

void create(vector<string> data) {
  string sql =
      "INSERT INTO customers ("
      "name,"
      "email,"
      "address,"
      "phone1,"
      "phone2"
      ")"
      "VALUES ("
      "?,"
      "?,"
      "?,"
      "?,"
      "?);";

  DatabaseDriver::step(sql, data);
}

class MyException : public std::exception {
 public:
  MyException(const char* message) : message_(message) {}
  const char* what() const noexcept { return message_; }

 private:
  const char* message_;
};

void update(string id, vector<string> data) {
  string sql =
      "UPDATE customers SET name = ?, email = ?, address = ?, phone1 = ?, "
      "phone2 = ? WHERE id = " +
      id;

  DatabaseDriver::step(sql, data);
}

void remove(string id) {
  string sql = "DELETE FROM customers WHERE id = ?";
  DatabaseDriver::step(sql, {id});
};
}  // namespace CustomerRepository