#include "root_module.hpp"
#include <modules/customer/customer_module.hpp>
#include <modules/driver/driver_module.hpp>
#include <modules/pet/pet_module.hpp>
#include <modules/service/service_module.hpp>
#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"

namespace RootModule {
void main() {
  using namespace ftxui;

  std::vector<std::string> tab_values{
      "Vendas", "Clientes", "Pets", "Serviços", "Motoristas",
  };
  int tab_selected = 0;
  auto tab_toggle = Toggle(&tab_values, &tab_selected);

  auto tab_container = Container::Tab(
      {
          Container::Vertical({}),
          CustomerModule::main(),
          PetModule::main(),
          ServiceModule::main(),
          DriverModule::main(),
      },
      &tab_selected);

  auto container = Container::Vertical({
      tab_toggle,
      tab_container,
  });

  auto renderer = Renderer(container, [tab_toggle, tab_container] {
    return vbox({
               tab_toggle->Render(),
               separator(),
               tab_container->Render(),
           }) |
           border;
  });

  auto screen = ScreenInteractive::Fullscreen();
  screen.Loop(renderer);
}
}  // namespace RootModule