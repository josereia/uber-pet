#include <core/widgets/widgets.hpp>
#include <string>
#include <vector>
#include "../pet_module.hpp"
#include "ftxui/component/component.hpp"

namespace PetWidgets {
using namespace std;
using namespace ftxui;

namespace UpdateModal {
string id;
string name;
string breed;
string sex;
string size;
string weight;
string observation;

vector<string> pet;

Component update_modal(void (*on_cancel)(), void (*on_update)()) {
  auto on_cancel_click = [on_cancel] {
    id.clear();
    name.clear();
    breed.clear();
    sex.clear();
    size.clear();
    weight.clear();
    observation.clear();

    pet.clear();

    on_cancel();
  };

  auto on_update_click = [on_cancel_click, on_update] {
    PetRepository::update(id, {
                                  name,
                                  breed,
                                  sex,
                                  size,
                                  weight,
                                  observation,
                              });
    on_update();
    on_cancel_click();
  };

  auto on_search_click = [] {
    auto results = PetRepository::find_by_id(id);
    pet = results[0];

    name = pet[1];
    breed = pet[2];
    sex = pet[3];
    size = pet[4];
    weight = pet[5];
    observation = pet[6];
  };

  auto id_input = Widgets::input(&id, "Digite o id do pet");
  auto name_input = Widgets::input(&name, "Digite o nome");
  auto breed_input = Widgets::input(&breed, "Digite a raça");
  auto sex_input = Widgets::input(&sex, "Digite o sexo");
  auto size_input =
      Widgets::input(&size, "Digite o tamanho(pequeno, médio, grande)");
  auto weight_input = Widgets::input(&weight, "Digite o peso(Kg)");
  auto observation_input =
      Widgets::input(&observation, "Digite uma observação");

  auto cancel_button = Button("Cancelar", on_cancel_click);
  auto create_button = Button("Atualizar", on_update_click);
  auto search_button = Button("Buscar", on_search_click);

  auto container = Container::Vertical({
      Container::Horizontal({
          id_input,
          search_button,
      }),
      name_input,
      breed_input,
      sex_input,
      size_input,
      weight_input,
      observation_input,
      Container::Horizontal({
          cancel_button,
          create_button,
      }),
  });

  auto body = Renderer(
      container, [name_input, breed_input, sex_input, size_input, weight_input,
                  observation_input, id_input, search_button] {
        return vbox({
            hbox(id_input->Render(), search_button->Render()),
            separator(),
            hbox(text("Nome: ") | center, name_input->Render()),
            hbox(text("Raça: ") | center, breed_input->Render()),
            hbox(text("Sexo: ") | center, sex_input->Render()),
            hbox(text("Tamanho: ") | center, size_input->Render()),
            hbox(text("Peso(Kg): ") | center, weight_input->Render()),
            hbox(text("Observação: ") | center, observation_input->Render()),
        });
      });

  auto footer = Renderer([cancel_button, create_button] {
    return hbox(cancel_button->Render(), create_button->Render());
  });

  return Widgets::modal("Atualizar pet", body, footer);
}
}  // namespace UpdateModal
}  // namespace PetWidgets