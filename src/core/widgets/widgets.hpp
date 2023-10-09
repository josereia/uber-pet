#ifndef widgets
#define widgets

#include <ftxui/dom/table.hpp>
#include <string>
#include <vector>

namespace Widgets {
using namespace std;
using namespace ftxui;

Element table(vector<vector<string>> data);
}  // namespace Widgets

#endif  // widgets
