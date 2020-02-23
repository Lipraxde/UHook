#ifndef UHOOK_HOOKPROVIDER_H
#define UHOOK_HOOKPROVIDER_H

#include <uhook/Hook.h>

namespace uhook {

template <typename Provider, typename... Args> class HookProvider : HookBase {
  HookProvider()
      : HookBase((void *)&Provider::Orig, Provider::getName(),
                 Provider::getDesc(), true) {}
  inline static Provider instance;

public:
  static auto hook(Args... args) {
    return ((typename Provider::FTy *)instance.getHook())(args...);
  }

  static auto self(Args... args) { return Provider::Orig(args...); }
  static bool is_me() { return instance.getHook() == &Provider::Orig; }

  friend Provider;
};

} // namespace uhook

#define PROVIDE_HOOK(Ret, Name, Desc, ...)                                     \
  class Name : public uhook::HookProvider<Name, ##__VA_ARGS__> {               \
    using FTy = Ret(__VA_ARGS__);                                              \
    Name() : uhook::HookProvider<Name, ##__VA_ARGS__>() {}                     \
    static const char *getName() { return #Name; }                             \
    static const char *getDesc() { return Desc; }                              \
    static Ret Orig(__VA_ARGS__);                                              \
    friend uhook::HookProvider<Name, ##__VA_ARGS__>;                           \
  };                                                                           \
  template class uhook::HookProvider<Name, ##__VA_ARGS__>;

#define ORIG_HOOK(Name) Name::Orig

#endif // UHOOK_HOOKPROVIDER_H
