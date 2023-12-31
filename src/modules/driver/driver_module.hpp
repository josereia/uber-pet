#ifndef driver_module
#define driver_module

#include <vector>
#include "ftxui/component/component.hpp"

using namespace std;
using namespace ftxui;

namespace DriverModule {
Component main();
}

namespace DriverRepository {
vector<vector<string>> find_all();
vector<vector<string>> find_by_id(string id);
void create(vector<string> data);
void update(string id, vector<string> data);
void remove(string id);
}  // namespace DriverRepository

namespace DriverWidgets {
namespace CreateModal {
Component create_modal(void (*on_cancel)(), void (*on_create)());
}
namespace UpdateModal {
Component update_modal(void (*on_cancel)(), void (*on_update)());
}

namespace DeleteModal {
Component delete_modal(void (*on_cancel)(), void (*on_delete)());
}
}  // namespace DriverWidgets

#endif
