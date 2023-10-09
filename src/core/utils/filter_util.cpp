#include <string>
#include <vector>
#include "utils.hpp"

namespace Utils {
using namespace std;

vector<vector<string>> filter(vector<vector<string>> data, string filter) {
  vector<vector<string>> filtered;
  for (auto row : data) {
    for (auto cell : row) {
      if (cell.find(filter) != string::npos) {
        filtered.push_back(row);
        break;
      }
    }
  }

  return filtered;
}
}  // namespace Utils