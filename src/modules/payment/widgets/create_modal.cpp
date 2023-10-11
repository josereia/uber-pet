#include <core/widgets/widgets.hpp>
#include <string>
#include <vector>
#include "../payment_module.hpp"
#include "ftxui/component/component.hpp"

namespace PaymentWidgets {
using namespace std;
using namespace ftxui;

namespace CreateModal {
string name;
string tax_type;
string tax;

vector<string> tax_types_dropdown_entries{"Porcentagem", "Bruto"};
int selected_tax_types_dropdown = 0;

Component create_modal(void (*on_cancel)(), void (*on_create)()) {
  auto on_cancel_click = [on_cancel] {
    name.clear();
    tax_type.clear();
    tax.clear();

    on_cancel();
  };

  auto on_create_click = [on_cancel_click, on_create] {
    PaymentRepository::create({name, tax_type, tax});

    on_create();
    on_cancel_click();
  };

  auto name_input = Widgets::input(&name, "Digite o nome");
  auto tax_type_dropdown =
      Dropdown(&tax_types_dropdown_entries, &selected_tax_types_dropdown);
  auto tax_input = Widgets::input(&tax, "Digite a taxa");

  auto cancel_button = Button("Cancelar", on_cancel_click);
  auto create_button = Button("Criar", on_create_click);

  auto container = Container::Vertical({
      name_input,
      tax_type_dropdown,
      tax_input,
      Container::Horizontal({
          cancel_button,
          create_button,
      }),
  });

  auto body = Renderer(container, [name_input, tax_type_dropdown, tax_input] {
    tax_type = tax_types_dropdown_entries[selected_tax_types_dropdown];

    return vbox({
        hbox(text("Nome: ") | center, name_input->Render()),
        hbox(text("Tipo da taxa: ") | center, tax_type_dropdown->Render()),
        hbox(text("Taxa: ") | center, tax_input->Render()),
    });
  });

  auto footer = Renderer([cancel_button, create_button] {
    return hbox(cancel_button->Render(), create_button->Render());
  });

  return Widgets::modal("Novo método de pagamento", body, footer);
}
}  // namespace CreateModal
}  // namespace PaymentWidgets