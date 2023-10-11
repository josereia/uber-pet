#include <ftxui/component/component.hpp>
#include <string>
#include <vector>
#include "widgets.hpp"

namespace Widgets {
using namespace std;
using namespace ftxui;

Component modal(string title, Component body, Component footer) {
  auto renderer = Renderer(body, [title, body, footer] {
    return vbox({
               hbox({
                   text(title) | bold | center,
               }),
               separator(),
               body->Render(),
               separator(),
               footer->Render() | align_right,
           }) |
           border | center;
  });

  return renderer;
}
}  // namespace Widgets