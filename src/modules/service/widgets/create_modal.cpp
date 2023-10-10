#include <core/widgets/widgets.hpp>
#include <string>
#include <vector>
#include "../service_module.hpp"
#include "ftxui/component/component.hpp"

namespace ServiceWidgets {
using namespace std;
using namespace ftxui;

namespace CreateModal {
string name;
string description;
string price;

Component create_modal(void (*on_cancel)(), void (*on_create)()) {
  auto on_cancel_click = [on_cancel] {
    name.clear();
    description.clear();
    price.clear();

    on_cancel();
  };

  auto on_create_click = [on_cancel_click, on_create] {
    ServiceRepository::create({
        name,
        description,
        price,
    });
    on_create();
    on_cancel_click();
  };

  auto name_input = Widgets::input(&name, "Digite o nome");
  auto description_input = Widgets::input(&description, "Digite uma descrição");
  auto price_input = Widgets::input(&price, "Digite o preço(R$)");

  auto cancel_button = Button("Cancelar", on_cancel_click);
  auto create_button = Button("Criar", on_create_click);

  auto container = Container::Vertical({
      name_input,
      description_input,
      price_input,
      Container::Horizontal({
          cancel_button,
          create_button,
      }),
  });

  auto body = Renderer(container, [name_input, description_input, price_input] {
    return vbox({
        hbox(text("Nome: ") | center, name_input->Render()),
        hbox(text("Descrição: ") | center, description_input->Render()),
        hbox(text("Preço(R$): ") | center, price_input->Render()),
    });
  });

  auto footer = Renderer([cancel_button, create_button] {
    return hbox(cancel_button->Render(), create_button->Render());
  });

  return Widgets::modal("Novo serviço", body, footer);
}
}  // namespace CreateModal
}  // namespace ServiceWidgets