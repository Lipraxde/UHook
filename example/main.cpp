#include "CTX.h"
#include <uhook/HookProvider.h>

#include <iostream>

#include <dlfcn.h>

PROVIDE_HOOK(hello, "A simple hellow world", CTX) {
  std::cout << "Hello, world!\n";
  return 0;
}

int main(int argc, char **argv) {
  CTX ctx(argc, argv);
  if (argc > 1)
    dlopen(argv[1], RTLD_NOW);
  hook_hello(ctx);
}
