#include <iostream>
#include <uhook/UHookProvider.h>

using namespace uhook;

void uhook::HookRegister(const char *Name, const char *Desc, void *OrigF,
                         void **Hook) {
  std::cout << Name << ": " << Desc << '\n';
  *Hook = OrigF;
}
