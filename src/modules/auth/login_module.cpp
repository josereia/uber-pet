#include <stdio.h>
#include <modules/root/root_module.hpp>
#include <string>
#include "auth_module.hpp"

#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"

using namespace std;
using namespace ftxui;

auto screen = ftxui::ScreenInteractive::Fullscreen();

void login(string username, string password) {
  bool logged = AuthRepository::login(username.c_str(), password.c_str());
  if (logged) {
    screen.ExitLoopClosure()();
    RootModule::main();
  }
}

namespace AuthModule {
void main() {
  string username;
  string password;

  auto username_input =
      Input(&username, "Digite seu nome de usuário", {.multiline = false});

  auto password_input = Input(&password, "Digite sua senha",
                              {.multiline = false, .password = true});

  auto login_button = Button("Entrar", [&] { login(username, password); });

  auto container = Container::Vertical({
      username_input,
      password_input,
      login_button,
  });

  auto renderer = Renderer(container, [&] {
    return vbox({
               hbox(text("Olá! Bem-vindo(a) "), text(username) | bold),
               separator(),
               vbox(text("Nome de usuário: "),
                    username_input->Render() | border),
               vbox(text("Senha: "), password_input->Render() | border),
               separatorEmpty(),
               login_button->Render(),
           }) |
           border;
  });

  screen.Loop(renderer);
}
}  // namespace AuthModule