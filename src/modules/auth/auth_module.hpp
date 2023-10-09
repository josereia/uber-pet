#ifndef auth_module
#define auth_module

namespace AuthModule {
void main();
}  // namespace AuthModule

namespace AuthRepository {
bool login(const char* username, const char* password);
}  // namespace AuthRepository

#endif
