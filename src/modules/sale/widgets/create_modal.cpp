#include <algorithm>
#include <core/widgets/widgets.hpp>
#include <modules/customer/customer_module.hpp>
#include <modules/driver/driver_module.hpp>
#include <modules/pet/pet_module.hpp>
#include <modules/service/service_module.hpp>

#include <string>
#include <vector>
#include "../sale_module.hpp"
#include "ftxui/component/component.hpp"

namespace SaleWidgets {
using namespace std;
using namespace ftxui;

namespace CreateModal {
vector<string> services_dropdown_entries;
vector<string> pets_dropdown_entries;
vector<string> customers_dropdown_entries;
vector<string> drivers_dropdown_entries;

vector<vector<string>> services;
vector<vector<string>> pets;
vector<vector<string>> customers;
vector<vector<string>> drivers;

string service;
string pet;
string customer;
string driver;
string total;

string money_discount;
string percent_discount;

int selected_service_dropdown = 0;
int selected_pet_dropdown = 0;
int selected_customer_dropdown = 0;
int selected_driver_dropdown = 0;

string second_element(vector<string> e) {
  return e[1];
}

void load_data() {
  services_dropdown_entries = {};
  pets_dropdown_entries = {};
  customers_dropdown_entries = {};
  drivers_dropdown_entries = {};

  services = ServiceRepository::find_all();
  transform(services.begin(), services.end(),
            back_inserter(services_dropdown_entries), second_element);

  pets = PetRepository::find_all();
  transform(pets.begin(), pets.end(), back_inserter(pets_dropdown_entries),
            second_element);

  customers = CustomerRepository::find_all();
  transform(customers.begin(), customers.end(),
            back_inserter(customers_dropdown_entries), second_element);

  drivers = DriverRepository::find_all();
  transform(drivers.begin(), drivers.end(),
            back_inserter(drivers_dropdown_entries), second_element);
}

Component create_modal(void (*on_cancel)(), void (*on_create)()) {
  auto on_cancel_click = [on_cancel] {
    service.clear();
    pet.clear();
    customer.clear();
    driver.clear();
    money_discount.clear();
    percent_discount.clear();
    total.clear();

    on_cancel();
  };

  auto on_create_click = [on_cancel_click, on_create] {
    SaleRepository::create({
        service,
        pet,
        customer,
        driver,
        total,
    });
    on_create();
    on_cancel_click();
  };

  auto services_dropdown =
      Dropdown(&services_dropdown_entries, &selected_service_dropdown);
  auto pets_dropdown = Dropdown(&pets_dropdown_entries, &selected_pet_dropdown);
  auto customers_dropdown =
      Dropdown(&customers_dropdown_entries, &selected_customer_dropdown);
  auto drivers_dropdown =
      Dropdown(&drivers_dropdown_entries, &selected_driver_dropdown);

  auto money_discount_input =
      Widgets::input(&money_discount, "Digite um desconto em R$");
  auto percent_discount_input =
      Widgets::input(&percent_discount, "Digite um desconto em R$");

  auto cancel_button = Button("Cancelar", on_cancel_click);
  auto create_button = Button("Criar", on_create_click);

  auto container = Container::Vertical({
      services_dropdown,
      pets_dropdown,
      customers_dropdown,
      drivers_dropdown,
      money_discount_input,
      percent_discount_input,
      Container::Horizontal({
          cancel_button,
          create_button,
      }),
  });

  auto body = Renderer(container, [services_dropdown, pets_dropdown,
                                   customers_dropdown, drivers_dropdown,
                                   money_discount_input,
                                   percent_discount_input] {
    load_data();

    service = services_dropdown_entries[selected_service_dropdown];
    pet = pets_dropdown_entries[selected_pet_dropdown];
    customer = customers_dropdown_entries[selected_customer_dropdown];
    driver = drivers_dropdown_entries[selected_driver_dropdown];

    total = services[selected_service_dropdown][3];

    if (!money_discount.empty()) {
      string total_temp = total;
      string money_discount_temp = money_discount;

      replace(total_temp.begin(), total_temp.end(), ',', '.');
      replace(money_discount_temp.begin(), money_discount_temp.end(), ',', '.');

      double total_val = stod(total);
      double discount_val = stod(money_discount);
      double total_with_discount = total_val - discount_val;

      total = to_string(total_with_discount);
      replace(total.begin(), total.end(), '.', ',');
    }

    if (!percent_discount.empty()) {
      string total_temp = total;
      string money_discount_temp = percent_discount;

      replace(total_temp.begin(), total_temp.end(), ',', '.');
      replace(money_discount_temp.begin(), money_discount_temp.end(), ',', '.');

      double total_val = stod(total);
      double discount_val = stod(percent_discount);
      double total_with_discount =
          total_val - (total_val * (discount_val / 100));

      total = to_string(total_with_discount);
      replace(total.begin(), total.end(), '.', ',');
    }

    return vbox({
        hbox(text("Serviço: ") | center, services_dropdown->Render()),
        hbox(text("Pet: ") | center, pets_dropdown->Render()),
        hbox(text("Cliente: ") | center, customers_dropdown->Render()),
        hbox(text("Motorista: ") | center, drivers_dropdown->Render()),
        hbox(text("Desconto em R$: ") | center, money_discount_input->Render()),
        hbox(text("Desconto em %: ") | center,
             percent_discount_input->Render()),
        separator(),
        hbox(text("Total: "), text(total)) | bold,
    });
  });

  auto footer = Renderer([cancel_button, create_button] {
    return hbox(cancel_button->Render(), create_button->Render());
  });

  return Widgets::modal("Nova venda", body, footer);
}
}  // namespace CreateModal
}  // namespace SaleWidgets