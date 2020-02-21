#include <iostream>

class CTX {
public:
  int argc;
  char **argv;
  CTX(int argc, char **argv) : argc(argc), argv(argv) {}
};

struct HookProviderBase {
  void *F;
  HookProviderBase(const char *Name, const char *Desc, void *F) : F(F) {}
};

template <typename Provider, typename CTX>
class HookProvider : HookProviderBase {
public:
  HookProvider()
      : HookProviderBase(Provider::Name, Provider::Desc,
                         (void *)&Provider::Orig) {}

  int hook(CTX &ctx) { return ((typeof Provider::Orig *)F)(ctx); }
};

static struct _Hello : HookProvider<_Hello, CTX> {
  _Hello() : HookProvider<_Hello, CTX>() {}
  constexpr static const char *Name = "Hello";
  constexpr static const char *Desc = "A simple hello world";
  static int Orig(CTX &ctx) {
    // for (int i = 0; i < ctx.argc; ++i)
    //   std::cout << ctx.argv[i] << '\n';
    std::cout << "Hello, world!\n";
    return 0;
  }
} Hello;

int main(int argc, char **argv) {
  CTX ctx(argc, argv);
  Hello.hook(ctx);
}
