#pragma once
#include <iostream>
#include <vector>
struct version{
    std::string sv_local_version;
    std::string cl_version;
    std::string sv_save_version;
    version(std::string sv_local_version,std::string cl_version,std::string sv_save_version){
      this->sv_local_version=sv_local_version;
      this->cl_version=cl_version;
      this->sv_save_version=sv_save_version;
    }
};
class database {
 private:
 public:
  database() {}
  std::vector<version> sv_local_getversions() {
    std::vector<version> versions;
    versions.push_back(version("0.0.3","0.0.1<=0.0.5","0.0.1"));
    versions.push_back(version("0.0.4","0.0.4<=0.0.6","0.0.1"));
    return versions;
  }
   std::vector<version> cl_getversions() {
    std::vector<version> versions;
    versions.push_back(version("0.0.5","0.0.1<=0.0.5","0.0.1"));
    versions.push_back(version("0.0.6","0.0.4<=0.0.6","0.0.1"));
    return versions;
  }
  std::vector<version> sv_save_getversions() {
    std::vector<version> versions;
    versions.push_back(version("0.0.7","0.0.1<=0.0.5","0.0.1"));
    versions.push_back(version("0.0.8","0.0.4<=0.0.6","0.0.1"));
    return versions;
  }
  ~database() {}
};
