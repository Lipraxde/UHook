#ifndef UHOOK_HOOKPROVIDER_H
#define UHOOK_HOOKPROVIDER_H

#include <uhook/Hook.h>

namespace uhook {

template <typename Provider, typename... Args> class HookProvider : HookBase {
public:
  HookProvider()
      : HookBase((void *)&Provider::Orig, Provider::getName(),
                 Provider::getDesc(), true) {}

  static auto hook(Args... args) {
    return ((typename Provider::FTy *)Provider::instance.getHook())(args...);
  }

  static auto self(Args... args) { return Provider::Orig(args...); }
  static bool is_me() {
    return Provider::instance.getHook() == &Provider::Orig;
  }
};

} // namespace uhook

#define PROVIDE_HOOK(Ret, Name, Desc, ...)                                     \
  class Name : public uhook::HookProvider<Name, ##__VA_ARGS__> {               \
    using FTy = Ret(__VA_ARGS__);                                              \
    Name() : uhook::HookProvider<Name, ##__VA_ARGS__>() {}                     \
    static const char *getName() { return #Name; }                             \
    static const char *getDesc() { return Desc; }                              \
    static Ret Orig(__VA_ARGS__);                                              \
    static Name instance;                                                      \
    friend uhook::HookProvider<Name, ##__VA_ARGS__>;                           \
  };                                                                           \
  Name Name::instance;

#define ORIG_HOOK(Name) Name::Orig

#endif // UHOOK_HOOKPROVIDER_H
