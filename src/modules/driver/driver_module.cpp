#include "driver_module.hpp"
#include <core/utils/utils.hpp>
#include <core/widgets/widgets.hpp>
#include <ftxui/dom/table.hpp>
#include <string>
#include <vector>
#include "ftxui/component/component.hpp"

namespace DriverModule {
using namespace std;
using namespace ftxui;

string search;
vector<vector<string>> content = DriverRepository::find_all();
vector<vector<string>> filtered = content;

Component main() {
  auto search_input =
      Input(&search, "Busque por nome",
            {
                .multiline = false,
                .on_change = [] { filtered = Utils::filter(content, search); },
            });

  auto search_button = Button("Novo", [] {});

  auto container = Container::Vertical({
      Container::Horizontal({
          search_input,
          search_button,
      }),
  });

  auto renderer = Renderer(container, [search_input, search_button] {
    auto table = Widgets::table(filtered);

    return vbox({
        hbox({
            search_input->Render() | border,
            separatorEmpty(),
            search_button->Render(),
        }),

        flex_grow(table | frame),
    });
  });

  return renderer;
}
}  // namespace DriverModule