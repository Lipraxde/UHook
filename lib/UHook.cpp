#include <uhook/Hook.h>

#include <cstring>
#include <iostream>
#include <set>

using namespace uhook;

struct HookMapComparator {
  bool operator()(const HookBase *a, const HookBase *b) {
    return std::strcmp(a->Name, b->Name) < 0;
  }
};

typedef std::set<HookBase *, HookMapComparator> HookMap;

static HookMap &getHookMap() {
  static HookMap map;
  return map;
}

HookBase::HookBase(void *_hook, const char *Name, const char *Desc,
                   bool isProvider)
    : _hook(_hook), Name(Name), Desc(Desc) {
  HookMap &Map = getHookMap();
  if (isProvider) {
    const auto [_, success] = Map.insert(this);
    if (!success) {
      std::cerr << "[UHook] Multiple registration of hook '" << Name << "'\n";
      abort();
    }
  } else { // is HookUser
    HookMap::iterator IT = Map.find(this);
    if (IT == Map.end()) {
      std::cerr << "[UHook] Unregistered reference to hook '" << Name << "'\n";
      abort();
    } else {
      this->_hook = (*IT)->_hook;
      (*IT)->_hook = _hook;
    }
  }
}
