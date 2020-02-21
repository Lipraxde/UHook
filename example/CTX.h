class CTX {
public:
  int argc;
  char **argv;
  CTX(int argc, char **argv) : argc(argc), argv(argv) {}
};
