namespace uhook {

void HookRegister(const char *Name, const char *Desc, void *OrigF, void **Hook);
void *HookReplace(const char *Name, void *NewF);

} // namespace uhook
