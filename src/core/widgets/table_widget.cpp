#include <ftxui/dom/table.hpp>
#include <string>
#include <vector>
#include "widgets.hpp"

namespace Widgets {
using namespace std;
using namespace ftxui;

Element table(vector<vector<string>> data) {
  auto table = Table(data);

  table.SelectAll().Border(LIGHT);
  table.SelectAll().Separator(LIGHT);
  table.SelectAll().DecorateAlternateRow(bgcolor(Color::Grey27), 2, 1);

  if (data.size() > 0) {
    table.SelectColumn(0).Border(LIGHT);
    table.SelectRow(0).Decorate(bold);
    table.SelectRow(0).SeparatorVertical(LIGHT);
    table.SelectRow(0).Border(DOUBLE);
  }

  return table.Render();
}
}  // namespace Widgets