#include <core/widgets/widgets.hpp>
#include <string>
#include "../driver_module.hpp"

namespace DriverWidgets {
namespace DeleteModal {
string id;

Component delete_modal(void (*on_cancel)(), void (*on_delete)()) {
  auto on_cancel_click = [on_cancel] {
    id.clear();
    on_cancel();
  };

  auto on_delete_click = [on_cancel_click, on_delete] {
    DriverRepository::remove(id);
    on_delete();
    on_cancel_click();
  };

  auto id_input = Widgets::input(&id, "Digite o id do motorista");

  auto cancel_button = Button("Cancelar", on_cancel_click);
  auto delete_button = Button("Excluir", on_delete_click);

  auto container = Container::Vertical({
      id_input,
      Container::Horizontal({
          cancel_button,
          delete_button,
      }),
  });

  auto body = Renderer(container, [id_input] {
    return vbox({
        hbox(text("Id do motorista: ") | center, id_input->Render()),
    });
  });

  auto footer = Renderer([cancel_button, delete_button] {
    return hbox(cancel_button->Render(), delete_button->Render());
  });

  return Widgets::modal("Excluir motorista", body, footer);
}
}  // namespace DeleteModal
}  // namespace DriverWidgets