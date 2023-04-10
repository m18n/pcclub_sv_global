#pragma once
#include "crow.h"
#include "database.h"
#define WEBPORT 9999
class pcwebserver {
 public:
  std::vector<crow::json::wvalue> parseversions(std::vector<version> vers){
    std::vector<crow::json::wvalue> temp_json;
    temp_json.resize(vers.size());
    for (int i = 0; i < vers.size(); i++) {
      temp_json[i]["cl"] = vers[i].cl_version;
      temp_json[i]["sv_save"] = vers[i].sv_save_version;
      temp_json[i]["sv_local"] = vers[i].sv_local_version;
      std::cout << temp_json[i].dump() << "\n";
    }
    return std::move(temp_json);
  }
  pcwebserver() {
    crow::mustache::set_global_base("./web");
    ctx_sv_local_versions["versions"]=std::move(parseversions(db.sv_local_getversions()));
    ctx_sv_save_versions["versions"]=std::move(parseversions(db.sv_save_getversions()));
    ctx_cl_versions["versions"]=std::move(parseversions(db.cl_getversions()));
    initcontrollers();
  }
  void start() { app.port(WEBPORT).run(); }
  void stop() {}
  void initcontrollers() {
    CROW_ROUTE(app, "/")
    ([]() { return "HELLO\n"; });
    CROW_ROUTE(app, "/api/sv_local/getversion")
    ([this] {
        return crow::mustache::load("api/versionsvlocal.html").render(ctx_sv_local_versions);
    });
    CROW_ROUTE(app, "/api/sv_save/getversion")
    ([this] {
        return crow::mustache::load("api/versionsvsave.html").render(ctx_sv_save_versions);
    });
    CROW_ROUTE(app, "/api/cl/getversion")
    ([this] {
        return crow::mustache::load("api/versioncl.html").render(ctx_cl_versions);
    });
  }

  ~pcwebserver() { stop(); }
public:

 private:
  database db;
  crow::mustache::context ctx_sv_local_versions;
  crow::mustache::context ctx_sv_save_versions;
  crow::mustache::context ctx_cl_versions;
  std::vector<version> temp_versions;
 
  crow::SimpleApp app;
};