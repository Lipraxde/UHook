#include <uhook/Hook.h>
#include <uhook/HookUser.h>

#include <iomanip>
#include <iostream>

USE_HOOK(int, hello, int, char **)

int NEW_HOOK(hello)(int argc, char **argv) {
  hello::old_hook(argc, argv);
  for (int i = 0; i < argc; ++i) {
    std::cout << "Arg " << i << ": " << argv[i] << '\n';
  }
  return 0;
}

USE_HOOK(uint64_t, calc, uint64_t)
uint64_t NEW_HOOK(calc)(uint64_t i) {
  // Factorial
  if (i > 1)
    return i * calc::New(i - 1);
  else
    return 1;
}

USE_HOOK(void, last_hook)
void NEW_HOOK(last_hook)() {
  const uhook::HookSet &HSet = uhook::getHookSet();
  for (auto IT : HSet) {
    std::cout << "  " << std::setw(16) << std::left << IT->Name << ": "
              << IT->Desc << '\n';
  }
}
