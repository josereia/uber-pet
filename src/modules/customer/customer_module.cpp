#include "customer_module.hpp"
#include <core/utils/utils.hpp>
#include <core/widgets/widgets.hpp>
#include <ftxui/dom/table.hpp>
#include <string>
#include <vector>
#include "ftxui/component/component.hpp"

namespace CustomerModule {
using namespace std;
using namespace ftxui;

string search;
bool create_modal_shown = false;
bool update_modal_shown = false;
bool delete_modal_shown = false;

vector<vector<string>> content = CustomerRepository::find_all();
vector<vector<string>> filtered = content;

void on_cancel() {
  create_modal_shown = false;
  update_modal_shown = false;
  delete_modal_shown = false;
}

void on_update() {
  auto results = CustomerRepository::find_all();
  content = results;
  filtered = results;
}

Component main() {
  auto search_input = Widgets::input(
      &search, "Busque por clientes",
      {
          .multiline = false,
          .on_change = [] { filtered = Utils::filter(content, search); },
      });

  auto new_button = Button("Novo", [] { create_modal_shown = true; });
  auto update_button = Button("Atualizar", [] { update_modal_shown = true; });
  auto delete_button = Button("Excluir", [] { delete_modal_shown = true; });

  auto container = Container::Vertical({
      Container::Horizontal({
          search_input,
          new_button,
          update_button,
          delete_button,
      }),
  });

  auto renderer = Renderer(
      container, [search_input, new_button, update_button, delete_button] {
        vector<string> table_header = {
            "ID", "Nome", "Email", "Endereço", "Telefone 1", "Telefone 2",
        };

        auto table = Widgets::table(filtered, table_header);

        return vbox({
            hbox({
                search_input->Render(),
                separatorEmpty(),
                new_button->Render(),
                update_button->Render(),
                delete_button->Render(),
            }),

            flex_grow(table | frame),
        });
      });

  renderer |=
      Modal(CustomerWidgets::CreateModal::create_modal(on_cancel, on_update),
            &create_modal_shown);

  renderer |=
      Modal(CustomerWidgets::UpdateModal::update_modal(on_cancel, on_update),
            &update_modal_shown);

  renderer |=
      Modal(CustomerWidgets::DeleteModal::delete_modal(on_cancel, on_update),
            &delete_modal_shown);

  return renderer;
}
}  // namespace CustomerModule