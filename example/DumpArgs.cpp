#include "CTX.h"
#include <uhook/UHookUser.h>

#include <iostream>

USE_HOOK(hello, CTX) {
  for (int i = 0; i < ctx.argc; ++i) {
    std::cout << "Arg " << i << ": " << ctx.argv[i] << '\n';
  }
  orig_hook_hello()(ctx);
  return 0;
}
