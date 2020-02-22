#include "CTX.h"
#include <uhook/HookUser.h>

#include <iostream>

USE_HOOK(hello, CTX) {
  for (int i = 0; i < ctx.argc; ++i) {
    std::cout << "Arg " << i << ": " << ctx.argv[i] << '\n';
  }
  old_hook_hello(ctx);
  return 0;
}
