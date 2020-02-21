#include <uhook/UHookProvider.h>

#include <iostream>

using namespace uhook;

class CTX {
public:
  int argc;
  char **argv;
  CTX(int argc, char **argv) : argc(argc), argv(argv) {}
};

PROVIDE_HOOK(hello, "A simple hellow world", CTX) {
  std::cout << "Hello, world!\n";
  return 0;
}

int main(int argc, char **argv) {
  CTX ctx(argc, argv);
  hook_hello(ctx);
}
