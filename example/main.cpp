#include <uhook/Hook.h>
#include <uhook/HookProvider.h>

#include <iostream>

#include <dlfcn.h>

PROVIDE_HOOK(int, hello, "A simple hellow world", int, char **)

int ORIG_HOOK(hello)(int, char **) {
  std::cout << "Hello, world!\n";
  return 0;
}

int main(int argc, char **argv) {
  if (argc > 1)
    dlopen(argv[1], RTLD_NOW);
  hello::hook(argc, argv);
}
