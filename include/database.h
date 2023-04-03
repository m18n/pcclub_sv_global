#pragma once
#include <iostream>
#include <vector>
class database {
 private:
 public:
  database() {}
  std::vector<std::string> sv_local_getversions() {
    std::vector<std::string> versions;
    versions.push_back("0.0.0");
    versions.push_back("0.0.1");
    return versions;
  }
  ~database() {}
};
