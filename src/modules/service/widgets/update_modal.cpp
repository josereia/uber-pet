#include <core/widgets/widgets.hpp>
#include <string>
#include <vector>
#include "../service_module.hpp"
#include "ftxui/component/component.hpp"

namespace ServiceWidgets {
using namespace std;
using namespace ftxui;

namespace UpdateModal {
string id;
string name;
string description;
string price;

vector<string> service;

Component update_modal(void (*on_cancel)(), void (*on_update)()) {
  auto on_cancel_click = [on_cancel] {
    id.clear();
    name.clear();
    description.clear();
    price.clear();

    service.clear();

    on_cancel();
  };

  auto on_update_click = [on_cancel_click, on_update] {
    ServiceRepository::update(id, {
                                      name,
                                      description,
                                      price,
                                  });
    on_update();
    on_cancel_click();
  };

  auto on_search_click = [] {
    auto results = ServiceRepository::find_by_id(id);
    service = results[0];

    name = service[1];
    description = service[2];
    price = service[3];
  };

  auto id_input = Widgets::input(&id, "Digite o id do serviço");
  auto name_input = Widgets::input(&name, "Digite o nome");
  auto description_input = Widgets::input(&description, "Digite uma descrição");
  auto price_input = Widgets::input(&price, "Digite o preço(R$)");

  auto cancel_button = Button("Cancelar", on_cancel_click);
  auto create_button = Button("Atualizar", on_update_click);
  auto search_button = Button("Buscar", on_search_click);

  auto container = Container::Vertical({
      Container::Horizontal({
          id_input,
          search_button,
      }),
      name_input,
      description_input,
      price_input,
      Container::Horizontal({
          cancel_button,
          create_button,
      }),
  });

  auto body = Renderer(container, [name_input, description_input, price_input,
                                   id_input, search_button] {
    return vbox({
        hbox(id_input->Render(), search_button->Render()),
        separator(),
        hbox(text("Nome: ") | center, name_input->Render()),
        hbox(text("Descrição: ") | center, description_input->Render()),
        hbox(text("Preço(R$): ") | center, price_input->Render()),
    });
  });

  auto footer = Renderer([cancel_button, create_button] {
    return hbox(cancel_button->Render(), create_button->Render());
  });

  return Widgets::modal("Atualizar serviço", body, footer);
}
}  // namespace UpdateModal
}  // namespace ServiceWidgets