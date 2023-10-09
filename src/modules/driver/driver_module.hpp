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
}

#endif
