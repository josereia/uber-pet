#include <core/database_driver.hpp>
#include <iostream>
#include "auth_module.hpp"

namespace AuthRepository {
bool login(const char* username, const char* password) {
  std::string sql = "SELECT id FROM users WHERE username ='" +
                    std::string(username) + "' AND password ='" +
                    std::string(password) + "'";

  auto [results, _] = DatabaseDriver::step(sql, {});

  return results.size() > 0;
};
}  // namespace AuthRepository