#include <iostream>
#include <uhook/UHookProvider.h>

#include <map>
#include <string>

using namespace uhook;

typedef std::map<std::string, void **> HookMap;

HookMap &getHookMap() {
  static HookMap map;
  return map;
}

void uhook::HookRegister(const char *Name, const char *Desc, void *OrigF,
                         void **Hook) {
  std::cout << Name << ": " << Desc << '\n';
  getHookMap()[Name] = Hook;
  *Hook = OrigF;
}

void *uhook::HookReplace(const char *Name, void *NewF) {
  void **Hook = getHookMap()[Name];
  if (Hook == nullptr) {
    std::cerr << "Hook '" << Name << "' not found!\n";
    abort();
  }
  void *PrevF = *Hook;
  *Hook = NewF;
  return PrevF;
}
