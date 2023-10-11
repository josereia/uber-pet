#include <cmath>
#include <iomanip>
#include <sstream>
#include <string>
#include "utils.hpp"

namespace Utils {
using namespace std;

string calc_val_discount(string total, string discount) {
  string total_temp = total;
  string discount_temp = discount;

  replace(total_temp.begin(), total_temp.end(), ',', '.');
  replace(discount_temp.begin(), discount_temp.end(), ',', '.');

  double total_val = stod(total_temp);
  double discount_val = stod(discount_temp);
  double total_with_discount = total_val - discount_val;

  ostringstream value;
  value << fixed << setprecision(2) << total_with_discount;

  total = value.str();
  replace(total.begin(), total.end(), '.', ',');

  return total;
}
}  // namespace Utils