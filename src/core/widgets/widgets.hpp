#ifndef widgets
#define widgets

#include <ftxui/component/component.hpp>
#include <ftxui/dom/table.hpp>
#include <string>
#include <vector>

namespace Widgets {
using namespace std;
using namespace ftxui;

Element table(vector<vector<string>> data, vector<string> header = {});
Component modal(string title, Component body, Component footer);
Component input(StringRef content,
                string placeholder,
                InputOption option = InputOption());
}  // namespace Widgets

#endif  // widgets
