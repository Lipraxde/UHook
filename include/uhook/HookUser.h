#include <uhook/Hook.h>

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
  class __hook_user_##Name : uhook::HookUser<__hook_user_##Name, CTXClass> {   \
    __hook_user_##Name() : HookUser<__hook_user_##Name, CTXClass>() {}         \
    static const char *getName() { return #Name; }                             \
    static int New(CTXClass &ctx);                                             \
    static __hook_user_##Name instance;                                        \
    friend uhook::HookUser<__hook_user_##Name, CTXClass>;                      \
    friend int (*orig_hook_##Name())(CTXClass &);                              \
  };                                                                           \
  __hook_user_##Name __hook_user_##Name::instance;                             \
  int (*orig_hook_##Name())(CTXClass &) {                                      \
    return (int (*)(CTXClass &))__hook_user_##Name::instance.orig_hook;        \
  }                                                                            \
  int __hook_user_##Name::New(CTXClass &ctx)
