#include <ftxui/component/component.hpp>
#include <string>
#include "widgets.hpp"

namespace Widgets {
using namespace std;
using namespace ftxui;

Component input(StringRef content, string placeholder, InputOption option) {
  return Input(content, placeholder, option) | border;
}
}  // namespace Widgets