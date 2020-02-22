# UHook
Add hook mechanism to your project

UHook can help turn a function into a hook.
The hook can have different behaviors by loading different *HookLibrary*.
It is especially useful when the project is almost complete.
Because only a little modification is needed.

For example, here we have a function `calc`:
```c++
uint64_t calc(uint64_t i) {
  // Fibonacci
  if (i > 1)
    return calc(i - 1) + calc(i - 2);
  else
    return 1;
}
```

To turn `calc` into a hook, use `PROVIDE_HOOK` and `ORIG_HOOK` macros to help us:
```c++
#include <uhook/HookProvider.h>

PROVIDE_HOOK(uint64_t, calc, "Description about calc", uint64_t)
uint64_t ORIG_HOOK(calc)(uint64_t i) {
  // Fibonacci
  if (i > 1)
    return calc::self(i - 1) + calc::self(i - 2);
  else
    return 1;
}
```

Example of using the hook `calc`:
```c
int main(int argc, char *argv[]) {
  // Load the hook library with the input path
  if (argc > 1 && (dlopen(argv[1], RTLD_NOW) == nullptr))
      std::cerr << "[Error] Fail to open the hook library\n";
  std::cout << "Calc(" << argc << ") = " << calc::hook(argc) << '\n';
}
```

The default behavior of `calc::hook()` is to calculate the Fibonacci number.
Let's hook `calc`, create a hook library.
The hook library contains the following code, use `USE_HOOK` and `NEW_HOOK`:
```c++
USE_HOOK(uint64_t, calc, uint64_t)
uint64_t NEW_HOOK(calc)(uint64_t i) {
  // Factorial
  if (i > 1)
    return i * calc::self(i - 1);
  else
    return 1;
}
```

If we execute command `./main HookLib.so 3 4 5`,the `main` program should print `Calc(5) = 120`.
