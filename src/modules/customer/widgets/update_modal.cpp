#include <core/widgets/widgets.hpp>
#include <string>
#include <vector>
#include "../customer_module.hpp"
#include "ftxui/component/component.hpp"

namespace CustomerWidgets {
using namespace std;
using namespace ftxui;

namespace UpdateModal {
string id;
string name;
string email;
string address;
string phone1;
string phone2;

vector<string> customer;

Component update_modal(void (*on_cancel)(), void (*on_update)()) {
  auto on_cancel_click = [on_cancel] {
    id.clear();
    name.clear();
    email.clear();
    address.clear();
    phone1.clear();
    phone2.clear();

    customer.clear();

    on_cancel();
  };

  auto on_update_click = [on_cancel_click, on_update] {
    CustomerRepository::update(id, {
                                       name,
                                       email,
                                       address,
                                       phone1,
                                       phone2,
                                   });
    on_update();
    on_cancel_click();
  };

  auto on_search_click = [] {
    auto results = CustomerRepository::find_by_id(id);
    customer = results[0];

    name = customer[1];
    email = customer[2];
    address = customer[3];
    phone1 = customer[4];
    phone2 = customer[5];
  };

  auto id_input = Widgets::input(&id, "Digite o id do cliente");
  auto name_input = Widgets::input(&name, "Digite o nome");
  auto email_input = Widgets::input(&email, "Digite o email");
  auto address_input = Widgets::input(&address, "Digite o endereço");
  auto phone1_input =
      Widgets::input(&phone1, "Digite um telefone para contato");
  auto phone2_input =
      Widgets::input(&phone2, "Digite outro telefone para contato");

  auto cancel_button = Button("Cancelar", on_cancel_click);
  auto create_button = Button("Atualizar", on_update_click);
  auto search_button = Button("Buscar", on_search_click);

  auto container = Container::Vertical({
      Container::Horizontal({
          id_input,
          search_button,
      }),
      name_input,
      email_input,
      address_input,
      phone1_input,
      phone2_input,
      Container::Horizontal({
          cancel_button,
          create_button,
      }),
  });

  auto body =
      Renderer(container, [name_input, email_input, address_input, phone1_input,
                           phone2_input, id_input, search_button] {
        return vbox({
            hbox(id_input->Render(), search_button->Render()),
            separator(),
            hbox(text("Nome: ") | center, name_input->Render()),
            hbox(text("Email: ") | center, email_input->Render()),
            hbox(text("Endereço: ") | center, address_input->Render()),
            hbox(text("Telefone 1: ") | center, phone1_input->Render()),
            hbox(text("Telefone 2: ") | center, phone2_input->Render()),
        });
      });

  auto footer = Renderer([cancel_button, create_button] {
    return hbox(cancel_button->Render(), create_button->Render());
  });

  return Widgets::modal("Atualizar cliente", body, footer);
}
}  // namespace UpdateModal
}  // namespace CustomerWidgets