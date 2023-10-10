#include <core/widgets/widgets.hpp>
#include <string>
#include <vector>
#include "../pet_module.hpp"
#include "ftxui/component/component.hpp"

namespace PetWidgets {
using namespace std;
using namespace ftxui;

namespace CreateModal {
string name;
string breed;
string sex;
string size;
string weight;
string observation;

Component create_modal(void (*on_cancel)(), void (*on_create)()) {
  auto on_cancel_click = [on_cancel] {
    name.clear();
    breed.clear();
    sex.clear();
    size.clear();
    weight.clear();
    observation.clear();

    on_cancel();
  };

  auto on_create_click = [on_cancel_click, on_create] {
    PetRepository::create({
        name,
        breed,
        sex,
        size,
        weight,
        observation,
    });
    on_create();
    on_cancel_click();
  };

  auto name_input = Widgets::input(&name, "Digite o nome");
  auto breed_input = Widgets::input(&breed, "Digite a raça");
  auto sex_input = Widgets::input(&sex, "Digite o sexo");
  auto size_input =
      Widgets::input(&size, "Digite o tamanho(pequeno, médio, grande)");
  auto weight_input = Widgets::input(&weight, "Digite o peso(Kg)");
  auto observation_input =
      Widgets::input(&observation, "Digite uma observação");

  auto cancel_button = Button("Cancelar", on_cancel_click);
  auto create_button = Button("Criar", on_create_click);

  auto container = Container::Vertical({
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

  auto body =
      Renderer(container, [name_input, breed_input, sex_input, size_input,
                           weight_input, observation_input] {
        return vbox({
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

  return Widgets::modal("Novo pet", body, footer);
}
}  // namespace CreateModal
}  // namespace PetWidgets