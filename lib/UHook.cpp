#include <uhook/Hook.h>

#include <cstring>
#include <iostream>
#include <set>

using namespace uhook;

bool HookSetComparator::operator()(const HookBase *a, const HookBase *b) {
  return std::strcmp(a->Name, b->Name) < 0;
}

static HookSet &getHookSet() {
  static HookSet set;
  return set;
}

const HookSet &uhook::getHookSet() { return ::getHookSet(); }

HookBase::HookBase(void *_hook, const char *Name, const char *Desc,
                   bool isProvider)
    : _hook(_hook), Name(Name), Desc(Desc) {
  HookSet &Set = ::getHookSet();
  if (isProvider) {
    const auto [_, success] = Set.insert(this);
    if (!success) {
      std::cerr << "[UHook] Multiple registration of hook '" << Name << "'\n";
      abort();
    }
  } else { // is HookUser
    HookSet::iterator IT = Set.find(this);
    if (IT == Set.end()) {
      std::cerr << "[UHook] Unregistered reference to hook '" << Name << "'\n";
      abort();
    } else {
      this->_hook = (*IT)->_hook;
      (*IT)->_hook = _hook;
    }
  }
}
