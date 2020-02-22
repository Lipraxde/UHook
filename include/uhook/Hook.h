#ifndef UHOOK_HOOK_H
#define UHOOK_HOOK_H

#include <set>

namespace uhook {

class HookBase {
public:
  void *_hook;
  const char *const Name;
  const char *const Desc;

  HookBase(void *_hook, const char *Name, const char *Desc, bool isProvider);
  HookBase(const HookBase &) = delete;
  HookBase(HookBase &&) = delete;
  HookBase operator=(const HookBase &) = delete;
  HookBase operator=(HookBase &&) = delete;
};

struct HookSetComparator {
  bool operator()(const HookBase *, const HookBase *);
};
typedef std::set<HookBase *, HookSetComparator> HookSet;

const HookSet &getHookSet();

} // namespace uhook

#endif // UHOOK_HOOK_H
