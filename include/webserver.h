#pragma once
#include "crow.h"
#include "database.h"
#define WEBPORT 9999
class pcwebserver {
 public:
  pcwebserver() {
    crow::mustache::set_global_base("./web");
    initcontrollers();
    sv_local_versions = db.sv_local_getversions();
    json_local_version.resize(sv_local_versions.size());
    for (int i = 0; i < sv_local_versions.size(); i++) {
      json_local_version[i]["version"] = sv_local_versions[i];
      std::cout << json_local_version[i].dump() << "\n";
    }
  }
  void start() { app.port(WEBPORT).run(); }
  void stop() {}
  void initcontrollers() {
    CROW_ROUTE(app, "/")
    ([]() { return "HELLO\n"; });
    CROW_ROUTE(app, "/api/sv_local/getversion")
    ([this] {
      crow::mustache::context ctx;
      ctx["versions"] = sv_local_versions;
      return crow::mustache::load("api/version.html").render(ctx);
    });
  }

  ~pcwebserver() { stop(); }

 private:
  database db;
  std::vector<std::string> sv_local_versions;
  std::vector<crow::json::wvalue> json_local_version;
  crow::SimpleApp app;
};