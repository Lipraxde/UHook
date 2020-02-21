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
  if (argc > 2)
    dlopen("example/libDumpArgs.so", RTLD_NOW);
  hook_hello(ctx);
}
