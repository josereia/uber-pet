#include <core/widgets/widgets.hpp>
#include <string>
#include <vector>
#include "../driver_module.hpp"
#include "ftxui/component/component.hpp"

namespace DriverWidgets {
using namespace std;
using namespace ftxui;

namespace UpdateModal {
string id;
string name;
string cnh;
string marital;
string criminal;
string address;
string license_plate;
string phone1;
string phone2;

vector<string> driver;

Component update_modal(void (*on_cancel)(), void (*on_update)()) {
  auto on_cancel_click = [on_cancel] {
    id.clear();
    name.clear();
    cnh.clear();
    marital.clear();
    criminal.clear();
    address.clear();
    license_plate.clear();
    phone1.clear();
    phone2.clear();

    driver.clear();

    on_cancel();
  };

  auto on_update_click = [on_cancel_click, on_update] {
    DriverRepository::update(id, {
                                     name,
                                     cnh,
                                     marital,
                                     criminal,
                                     address,
                                     license_plate,
                                     phone1,
                                     phone2,
                                 });
    on_update();
    on_cancel_click();
  };

  auto on_search_click = [] {
    auto results = DriverRepository::find_by_id(id);
    driver = results[0];

    name = driver[1];
    cnh = driver[2];
    marital = driver[3];
    criminal = driver[4];
    address = driver[5];
    license_plate = driver[6];
    phone1 = driver[7];
    phone2 = driver[8];
  };

  auto id_input = Widgets::input(&id, "Digite o id do motorista");

  auto name_input = Widgets::input(&name, "Digite o nome");
  auto cnh_input = Widgets::input(&cnh, "Digite a CNH");
  auto marital_status_input = Widgets::input(&marital, "Digite o status civil");
  auto criminal_input =
      Widgets::input(&criminal, "Digite os antecedentes criminais");
  auto address_input = Widgets::input(&address, "Digite o endereço");
  auto license_plate_input =
      Widgets::input(&license_plate, "Digite a placa do carro");
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
      cnh_input,
      marital_status_input,
      criminal_input,
      address_input,
      license_plate_input,
      phone1_input,
      phone2_input,
      Container::Horizontal({
          cancel_button,
          create_button,
      }),
  });

  auto body = Renderer(container, [name_input, cnh_input, marital_status_input,
                                   criminal_input, address_input,
                                   license_plate_input, phone1_input,
                                   phone2_input, id_input, search_button] {
    return vbox({
        hbox(id_input->Render(), search_button->Render()),
        separator(),
        hbox(text("Nome: ") | center, name_input->Render()),
        hbox(text("CNH: ") | center, cnh_input->Render()),
        hbox(text("Status Civil: ") | center, marital_status_input->Render()),
        hbox(text("Antecedentes Criminais: ") | center,
             criminal_input->Render()),
        hbox(text("Endereço: ") | center, address_input->Render()),
        hbox(text("Placa do Carro: ") | center, license_plate_input->Render()),
        hbox(text("Telefone 1: ") | center, phone1_input->Render()),
        hbox(text("Telefone 2: ") | center, phone2_input->Render()),
    });
  });

  auto footer = Renderer([cancel_button, create_button] {
    return hbox(cancel_button->Render(), create_button->Render());
  });

  return Widgets::modal("Atualizar motorista", body, footer);
}
}  // namespace UpdateModal
}  // namespace DriverWidgets