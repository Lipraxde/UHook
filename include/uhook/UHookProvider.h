#include <uhook/UHook.h>

namespace uhook {

template <typename Provider, typename CTX> class HookProvider {
  int (*_hook)(CTX &);
  const char *getName() { return Provider::getName(); }
  const char *getDesc() { return Provider::getDesc(); }
  void *getOrigHook() { return (void *)&Provider::Orig; }

  HookProvider() {
    HookRegister(getName(), getDesc(), getOrigHook(), (void **)&_hook);
  }
  HookProvider(const HookProvider &) = delete;
  HookProvider(HookProvider &&) = delete;
  HookProvider operator=(const HookProvider &) = delete;
  HookProvider operator=(HookProvider &&) = delete;

  friend Provider;

public:
  int hook(CTX &ctx) { this->_hook(ctx); }
};

} // namespace uhook

#define PROVIDE_HOOK(Name, Desc, CTXClass)                                     \
  int hook_##Name(CTXClass &);                                                 \
  class __##Name : public uhook::HookProvider<__##Name, CTXClass> {            \
    __##Name() : HookProvider<__##Name, CTXClass>() {}                         \
    static const char *getName() { return #Name; }                             \
    static const char *getDesc() { return Desc; }                              \
    static int Orig(CTXClass &ctx);                                            \
    static __##Name instance;                                                  \
    friend uhook::HookProvider<__##Name, CTXClass>;                            \
    friend int hook_##Name(CTXClass &);                                        \
  };                                                                           \
  __##Name __##Name::instance;                                                 \
  int hook_##Name(CTXClass &ctx) { return __##Name::instance.hook(ctx); }      \
  int __##Name::Orig(CTXClass &ctx)
