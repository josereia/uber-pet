#ifndef database_driver
#define database_driver

#include <sqlite3.h>
#include <tuple>
#include <vector>

using namespace std;

namespace DatabaseDriver {
int execute(string sql);
vector<vector<string>> step(string sql);
bool exists(const char* tableName);
}  // namespace DatabaseDriver

#endif  // database_driver
