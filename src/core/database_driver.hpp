#ifndef database_driver
#define database_driver

#include <sqlite3.h>
#include <tuple>
#include <vector>

using namespace std;

namespace DatabaseDriver {
sqlite3* get_db();
int execute(string sql, char** err);
tuple<vector<vector<string>>, int> step(string sql, vector<string> bindings);
bool exists(const char* tableName);
}  // namespace DatabaseDriver

#endif  // database_driver
