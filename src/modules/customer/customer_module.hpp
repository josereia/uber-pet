#ifndef customer_module
#define customer_module

#include <vector>
#include "ftxui/component/component.hpp"

using namespace std;
using namespace ftxui;

namespace CustomerModule {
Component main();
}

namespace CustomerRepository {
vector<vector<string>> find_all();
vector<vector<string>> find_by_id(string id);
void create(vector<string> data);
void update(string id, vector<string> data);
void remove(string id);
}  // namespace CustomerRepository

namespace CustomerWidgets {
namespace CreateModal {
Component create_modal(void (*on_cancel)(), void (*on_create)());
}
namespace UpdateModal {
Component update_modal(void (*on_cancel)(), void (*on_update)());
}

namespace DeleteModal {
Component delete_modal(void (*on_cancel)(), void (*on_delete)());
}
}  // namespace CustomerWidgets

#endif
