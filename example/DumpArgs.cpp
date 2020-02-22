#include <uhook/HookUser.h>

#include <iostream>

USE_HOOK(int, hello, int, char **)

int NEW_HOOK(hello)(int argc, char **argv) {
  for (int i = 0; i < argc; ++i) {
    std::cout << "Arg " << i << ": " << argv[i] << '\n';
  }
  hello::old_hook(argc, argv);
  return 0;
}
