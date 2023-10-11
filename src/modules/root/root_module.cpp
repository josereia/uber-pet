#include "root_module.hpp"
#include <modules/customer/customer_module.hpp>
#include <modules/driver/driver_module.hpp>
#include <modules/payment/payment_module.hpp>
#include <modules/pet/pet_module.hpp>
#include <modules/sale/sale_module.hpp>
#include <modules/service/service_module.hpp>
#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"

namespace RootModule {
void main() {
  using namespace ftxui;

  int tab_selected = 0;

  std::vector<std::string> tab_values{
      "Vendas",     "Clientes", "Pets", "Serviços", "Métodos de pagamento",
      "Motoristas",
  };

  auto tab_toggle = Toggle(&tab_values, &tab_selected);

  auto tab_container = Container::Tab(
      {
          SaleModule::main(),
          CustomerModule::main(),
          PetModule::main(),
          ServiceModule::main(),
          PaymentModule::main(),
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