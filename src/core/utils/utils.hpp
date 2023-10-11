#ifndef utils
#define utils

#include <string>
#include <vector>

namespace Utils {
using namespace std;

vector<vector<string>> filter(vector<vector<string>> data, string filter);
string calc_val_discount(string total, string discount);
string calc_percent_discount(string total, string discount);
}  // namespace Utils

#endif  // utils
