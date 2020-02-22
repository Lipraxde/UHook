#ifndef UHOOK_HOOKUSER_H
#define UHOOK_HOOKUSER_H

#include <uhook/Hook.h>

namespace uhook {

template <typename User, typename CTX, typename FTy = int(CTX &)>
class HookUser : HookBase {
public:
  HookUser() : HookBase((void *)&User::New, User::getName(), "", false) {}
  int old_hook(CTX &ctx) { ((FTy *)this->_hook)(ctx); }
};

} // namespace uhook

#define USE_HOOK(Name, CTXClass)                                               \
  int old_hook_##Name(CTXClass &);                                             \
  class __hook_user_##Name : uhook::HookUser<__hook_user_##Name, CTXClass> {   \
    __hook_user_##Name() : HookUser<__hook_user_##Name, CTXClass>() {}         \
    static const char *getName() { return #Name; }                             \
    static int New(CTXClass &ctx);                                             \
    static __hook_user_##Name instance;                                        \
    friend uhook::HookUser<__hook_user_##Name, CTXClass>;                      \
    friend int old_hook_##Name(CTXClass &);                                    \
  };                                                                           \
  __hook_user_##Name __hook_user_##Name::instance;                             \
  int old_hook_##Name(CTXClass &ctx) {                                         \
    return __hook_user_##Name::instance.old_hook(ctx);                         \
  }                                                                            \
  int __hook_user_##Name::New(CTXClass &ctx)

#endif // UHOOK_HOOKUSER_H
