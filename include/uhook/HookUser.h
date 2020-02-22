#ifndef UHOOK_HOOKUSER_H
#define UHOOK_HOOKUSER_H

#include <uhook/Hook.h>

namespace uhook {

template <typename User, typename... Args> class HookUser : HookBase {
public:
  HookUser() : HookBase((void *)&User::New, User::getName(), "", false) {}

  static auto old_hook(Args... args) {
    return ((typename User::FTy *)User::instance.getHook())(args...);
  }

  static auto self(Args... args) { return User::New(args...); }
};

} // namespace uhook

#define USE_HOOK(Ret, Name, ...)                                               \
  class Name : public uhook::HookUser<Name, ##__VA_ARGS__> {                   \
    using FTy = Ret(__VA_ARGS__);                                              \
    Name() : HookUser<Name, ##__VA_ARGS__>() {}                                \
    static const char *getName() { return #Name; }                             \
    static Ret New(__VA_ARGS__);                                               \
    static Name instance;                                                      \
    friend uhook::HookUser<Name, ##__VA_ARGS__>;                               \
  };                                                                           \
  Name Name::instance;

#define NEW_HOOK(Name) Name::New

#endif // UHOOK_HOOKUSER_H
