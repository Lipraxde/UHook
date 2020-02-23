#include <uhook/Hook.h>
#include <uhook/HookProvider.h>

#include <cstdint>
#include <cstdlib>
#include <iostream>

#include <dlfcn.h>

PROVIDE_HOOK(int, hello, "A simple hellow world", int, char **)
int ORIG_HOOK(hello)(int, char **) {
  std::cout << "Hello, world!\n";
  return 0;
}

PROVIDE_HOOK(uint64_t, calc, "Output the calculation result", uint64_t)
uint64_t ORIG_HOOK(calc)(uint64_t i) {
  // Fibonacci
  // Use calc::hook(...) lost the optimization opportunity
  if (i > 1)
    return calc::self(i - 1) + calc::self(i - 2);
  else
    return 1;
}

// Do not put ", void" to 4th argument
PROVIDE_HOOK(void, last_hook, "Do something (@_@)")
void ORIG_HOOK(last_hook)() {}

int main(int argc, char **argv) {
  // You need to load the hook library by yourself
  // Loading the hook library by set "LD_PRELOAD" is a bit dirty
  if (argc > 1)
    if (dlopen(argv[1], RTLD_NOW) == nullptr) {
      std::cerr << "[Error]\n";
      std::cerr << "  Fail to open the hook library\n";
    }

  // The hello world hook
  hello::hook(argc, argv);

  if (argc > 2) {
    std::cout << "[Calculation]\n";
    uint64_t input = std::strtoull(argv[2], nullptr, 0);
    std::cout << "  The result: " << calc::hook(input) << '\n';
  }

  if (!last_hook::is_me()) {
    std::cout << "[Do something]\n";
    last_hook::hook();
  }
}
