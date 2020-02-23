#ifndef UHOOK_HOOKUSER_H
#define UHOOK_HOOKUSER_H

#include <uhook/Hook.h>

namespace uhook {

template <typename User, typename... Args> class HookUser : HookBase {
  HookUser() : HookBase((void *)&User::New, User::getName(), "", false) {}
  inline static User instance;

public:
  static auto old_hook(Args... args) {
    return ((typename User::FTy *)instance.getHook())(args...);
  }

  static auto self(Args... args) { return User::New(args...); }

  friend User;
};

} // namespace uhook

#define USE_HOOK(Ret, Name, ...)                                               \
  class Name : public uhook::HookUser<Name, ##__VA_ARGS__> {                   \
    using FTy = Ret(__VA_ARGS__);                                              \
    Name() : HookUser<Name, ##__VA_ARGS__>() {}                                \
    static const char *getName() { return #Name; }                             \
    static Ret New(__VA_ARGS__);                                               \
    friend uhook::HookUser<Name, ##__VA_ARGS__>;                               \
  };                                                                           \
  template class uhook::HookUser<Name, ##__VA_ARGS__>;

#define NEW_HOOK(Name) Name::New

#endif // UHOOK_HOOKUSER_H
