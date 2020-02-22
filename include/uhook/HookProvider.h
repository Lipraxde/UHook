#ifndef UHOOK_HOOKPROVIDER_H
#define UHOOK_HOOKPROVIDER_H

#include <uhook/Hook.h>

namespace uhook {

template <typename Provider, typename CTX, typename FTy = int(CTX &)>
class HookProvider : HookBase {
public:
  HookProvider()
      : HookBase((void *)&Provider::Orig, Provider::getName(),
                 Provider::getDesc(), true) {}
  int hook(CTX &ctx) { ((FTy *)this->_hook)(ctx); }
};

} // namespace uhook

#define PROVIDE_HOOK(Name, Desc, CTXClass)                                     \
  int hook_##Name(CTXClass &);                                                 \
  class __hook_provider_##Name                                                 \
      : uhook::HookProvider<__hook_provider_##Name, CTXClass> {                \
    __hook_provider_##Name()                                                   \
        : HookProvider<__hook_provider_##Name, CTXClass>() {}                  \
    static const char *getName() { return #Name; }                             \
    static const char *getDesc() { return Desc; }                              \
    static int Orig(CTXClass &ctx);                                            \
    static __hook_provider_##Name instance;                                    \
    friend uhook::HookProvider<__hook_provider_##Name, CTXClass>;              \
    friend int hook_##Name(CTXClass &);                                        \
  };                                                                           \
  __hook_provider_##Name __hook_provider_##Name::instance;                     \
  int hook_##Name(CTXClass &ctx) {                                             \
    return __hook_provider_##Name::instance.hook(ctx);                         \
  }                                                                            \
  int __hook_provider_##Name::Orig(CTXClass &ctx)

#endif // UHOOK_HOOKPROVIDER_H
