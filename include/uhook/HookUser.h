#ifndef UHOOK_HOOKUSER_H
#define UHOOK_HOOKUSER_H

#include <uhook/Hook.h>

namespace uhook {

template <typename User, typename... Args> class HookUser : HookBase {
public:
  HookUser() : HookBase((void *)&User::New, User::getName(), "", false) {}
  auto _old_hook(Args... args) {
    ((typename User::FTy *)this->HookBase::_hook)(args...);
  }
};

} // namespace uhook

#define USE_HOOK(Ret, Name, ...)                                               \
  class Name : uhook::HookUser<Name, ##__VA_ARGS__> {                          \
    using FTy = Ret(__VA_ARGS__);                                              \
    Name() : HookUser<Name, ##__VA_ARGS__>() {}                                \
    static const char *getName() { return #Name; }                             \
    static Ret New(__VA_ARGS__);                                               \
    static Name instance;                                                      \
    friend uhook::HookUser<Name, ##__VA_ARGS__>;                               \
                                                                               \
  public:                                                                      \
    template <typename... Args> static Ret old_hook(Args... args) {            \
      instance._old_hook(args...);                                             \
    }                                                                          \
  };                                                                           \
  Name Name::instance;

#define NEW_HOOK(Name) Name::New

#endif // UHOOK_HOOKUSER_H
