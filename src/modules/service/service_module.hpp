#ifndef service_module
#define service_module

#include <vector>
#include "ftxui/component/component.hpp"

using namespace std;
using namespace ftxui;

namespace ServiceModule {
Component main();
}

namespace ServiceRepository {
vector<vector<string>> find_all();
vector<vector<string>> find_by_id(string id);
void create(vector<string> data);
void update(string id, vector<string> data);
void remove(string id);
}  // namespace ServiceRepository

namespace ServiceWidgets {
namespace CreateModal {
Component create_modal(void (*on_cancel)(), void (*on_create)());
}
namespace UpdateModal {
Component update_modal(void (*on_cancel)(), void (*on_update)());
}

namespace DeleteModal {
Component delete_modal(void (*on_cancel)(), void (*on_delete)());
}
}  // namespace ServiceWidgets

#endif
