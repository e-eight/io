#include <iostream>
#include "ini.h"

int main() {
  io::INIParser config("params.ini");

  auto name = config.Get<std::string>("name", "UNKNOWN");
  auto num = config.Get<int>("num", 42);
  auto time = config.Get<double>("time", 12.0);
  auto b = config.GetBool("fiction", true);

  std::cout << io::trim(" Hello! World! ") << "\n";
  std::cout << name << " made " << num << " Kessel run(s) in " << time << " parsecs." << "\n";
  std::cout << "Is it fiction? " << std::boolalpha << b << "\n";
}
