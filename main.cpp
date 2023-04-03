#include "crow.h"
#include<iostream>
int main()
{
    crow::SimpleApp app;

    CROW_ROUTE(app, "/")
    ([](const crow::request& req, crow::response& res) {
        
        std::cout<<req.remote_ip_address<<"\n";
        res.end();
        
    });
    
    app.port(9999).run();
}
