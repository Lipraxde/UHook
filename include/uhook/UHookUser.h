#include <uhook/UHook.h>

namespace uhook {

template <typename User, typename CTX> class HookUser {
  const char *getName() { return User::getName(); }
  void *getNewHook() { return (void *)&User::New; }

  HookUser() { orig_hook = HookReplace(getName(), getNewHook()); }
  HookUser(const HookUser &) = delete;
  HookUser(HookUser &&) = delete;
  HookUser operator=(const HookUser &) = delete;
  HookUser operator=(HookUser &&) = delete;

  friend User;

public:
  void *orig_hook;
};

} // namespace uhook

#define USE_HOOK(Name, CTXClass)                                               \
  int (*orig_hook_##Name())(CTXClass &);                                       \
  class __##Name : uhook::HookUser<__##Name, CTXClass> {                       \
    __##Name() : HookUser<__##Name, CTXClass>() {}                             \
    static const char *getName() { return #Name; }                             \
    static int New(CTXClass &ctx);                                             \
    static __##Name instance;                                                  \
    friend uhook::HookUser<__##Name, CTXClass>;                                \
    friend int (*orig_hook_##Name())(CTXClass &);                              \
  };                                                                           \
  __##Name __##Name::instance;                                                 \
  int (*orig_hook_##Name())(CTXClass &) {                                      \
    return (int (*)(CTXClass &))__##Name::instance.orig_hook;                  \
  }                                                                            \
  int __##Name::New(CTXClass &ctx)
