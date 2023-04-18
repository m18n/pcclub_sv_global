#pragma once
#include <iostream>
#include <vector>
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
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
    sql::Driver *driver;
    sql::Connection *con;
    sql::Statement *stmt;
 public:
  database() {
    

    /* Create a connection */
    driver = get_driver_instance();
   
    try{
      con = driver->connect("tcp://192.168.0.104:3306", "test", "1");
      con->setSchema("pc_club");
      stmt = con->createStatement();
    }catch (sql::SQLException &e) {
      std::cout << "# ERR: SQLException in " << __FILE__;
      std::cout << "(" << __FUNCTION__ << ") on line "
        << __LINE__ << std::endl;
      std::cout << "# ERR: " << e.what();
      std::cout << " (MySQL error code: " << e.getErrorCode();
      std::cout << ", SQLState: " << e.getSQLState() << " )" << std::endl;
    }
    
  }
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
  ~database() {
    delete stmt;
    delete con;
  }
};
