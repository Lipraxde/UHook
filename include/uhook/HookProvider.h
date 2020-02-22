#ifndef UHOOK_HOOKPROVIDER_H
#define UHOOK_HOOKPROVIDER_H

#include <uhook/Hook.h>

namespace uhook {

template <typename Provider, typename... Args> class HookProvider : HookBase {
public:
  HookProvider()
      : HookBase((void *)&Provider::Orig, Provider::getName(),
                 Provider::getDesc(), true) {}
  auto _hook(Args... args) {
    return ((typename Provider::FTy *)this->HookBase::_hook)(args...);
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
                                                                               \
  public:                                                                      \
    template <typename... Args> static Ret hook(Args... args) {                \
      return instance._hook(args...);                                          \
    }                                                                          \
  };                                                                           \
  Name Name::instance;

#define ORIG_HOOK(Name) Name::Orig

#endif // UHOOK_HOOKPROVIDER_H
