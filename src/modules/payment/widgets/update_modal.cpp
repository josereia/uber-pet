#include <core/widgets/widgets.hpp>
#include <string>
#include <vector>
#include "../payment_module.hpp"
#include "ftxui/component/component.hpp"

namespace PaymentWidgets {
using namespace std;
using namespace ftxui;

namespace UpdateModal {
string id;
string name;
string tax_type;
string tax;

vector<string> tax_types_dropdown_entries{"Porcentagem", "Bruto"};
int selected_tax_types_dropdown = 0;

vector<string> payment;

Component update_modal(void (*on_cancel)(), void (*on_update)()) {
  auto on_cancel_click = [on_cancel] {
    id.clear();
    name.clear();
    tax_type.clear();
    tax.clear();

    payment.clear();

    on_cancel();
  };

  auto on_update_click = [on_cancel_click, on_update] {
    PaymentRepository::update(id, {name, tax_type, tax});
    on_update();
    on_cancel_click();
  };

  auto on_search_click = [] {
    auto results = PaymentRepository::find_by_id(id);
    payment = results[0];

    name = payment[1];
    tax_type = payment[2];
    tax = payment[3];

    if (tax_type == "Porcentagem") {
      selected_tax_types_dropdown = 0;
    } else if (tax_type == "Bruto") {
      selected_tax_types_dropdown = 1;
    }
  };

  auto id_input = Widgets::input(&id, "Digite o id do método de pagamento");
  auto name_input = Widgets::input(&name, "Digite o nome");
  auto tax_type_dropdown =
      Dropdown(&tax_types_dropdown_entries, &selected_tax_types_dropdown);
  auto tax_input = Widgets::input(&tax, "Digite a taxa");

  auto cancel_button = Button("Cancelar", on_cancel_click);
  auto create_button = Button("Atualizar", on_update_click);
  auto search_button = Button("Buscar", on_search_click);

  auto container = Container::Vertical({
      Container::Horizontal({
          id_input,
          search_button,
      }),
      name_input,
      tax_type_dropdown,
      tax_input,
      Container::Horizontal({
          cancel_button,
          create_button,
      }),
  });

  auto body = Renderer(container, [name_input, tax_type_dropdown, tax_input,
                                   id_input, search_button] {
    tax_type = tax_types_dropdown_entries[selected_tax_types_dropdown];

    return vbox({
        hbox(id_input->Render(), search_button->Render()),
        separator(),
        hbox(text("Nome: ") | center, name_input->Render()),
        hbox(text("Tipo da taxa: ") | center, tax_type_dropdown->Render()),
        hbox(text("Taxa: ") | center, tax_input->Render()),
    });
  });

  auto footer = Renderer([cancel_button, create_button] {
    return hbox(cancel_button->Render(), create_button->Render());
  });

  return Widgets::modal("Atualizar método de pagamento", body, footer);
}
}  // namespace UpdateModal
}  // namespace PaymentWidgets