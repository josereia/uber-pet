#ifndef sale_module
#define sale_module

#include <vector>
#include "ftxui/component/component.hpp"

using namespace std;
using namespace ftxui;

namespace SaleModule {
Component main();
}

namespace SaleRepository {
vector<vector<string>> find_all();
vector<vector<string>> find_by_id(string id);
void create(vector<string> data);
void remove(string id);
}  // namespace SaleRepository

namespace SaleWidgets {
namespace CreateModal {
Component create_modal(void (*on_cancel)(), void (*on_create)());
}

namespace DeleteModal {
Component delete_modal(void (*on_cancel)(), void (*on_delete)());
}
}  // namespace SaleWidgets

#endif
