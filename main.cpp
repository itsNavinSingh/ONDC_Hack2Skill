#include "crow.h"
#include <iostream>
#include <stdexcept>
#include <sstream>
#include "Pincodes.h"
#include "Merchant.h"
bool isNotValid(unsigned int pin){
    return (pin>859999 || pin<110000);
}
int main()
{
    static Pincodes pincode_data = Pincodes();
    static Merchant merchant_data = Merchant();
    static auto home_page = crow::mustache::load("home.html");
    static auto error_page = crow::mustache::load("error.html");
    static auto create_seller = crow::mustache::load("create_seller.html");
    static auto add_pincode_page = crow::mustache::load("add_pincode.html");
    static auto show_sellers_page = crow::mustache::load("show_sellers.html");
    static auto show_pincodes_page = crow::mustache::load("show_pincodes.html");
    static auto validate_page = crow::mustache::load("validate.html");
    static auto result_page = crow::mustache::load("result.html");
    crow::SimpleApp app;
    app.loglevel(crow::LogLevel::Warning);
    CROW_ROUTE(app, "/")
    ([]()
     { return home_page.render(); });
    CROW_ROUTE(app, "/create")([](const crow::request &req)
                                                                    {
        auto pincode_str = req.url_params.get("pincode");
        if(pincode_str != nullptr)
        {
            try{
                unsigned int pincode = std::stoul(pincode_str);
                if(isNotValid(pincode)){
                    return error_page.render();
                }
                addseller_data datas = merchant_data.addSeller(pincode);
                pincode_data.add(datas.pointer, pincode);
                std::string output = "Your Seller ID is ";
                output.append(std::to_string(datas.id));
                crow::mustache::context ctx({{"output", output}});
                return result_page.render(ctx);
            }
            catch (const std::invalid_argument& e){
                return error_page.render();
            }
        }
        return create_seller.render(); });
    CROW_ROUTE(app, "/add")([](const crow::request &req){
            auto seller_id_str = req.url_params.get("seller_id");
            auto pincode_str = req.url_params.get("pincode");
            if(seller_id_str != nullptr && pincode_str != nullptr){
            try{
                unsigned int pincode = std::stoul(pincode_str);
                if(isNotValid(pincode)){
                    return error_page.render();
                }
                unsigned long int seller_id = std::stoul(seller_id_str);
                Seller* datas = merchant_data.addPincode(seller_id, pincode);
                std::string res = "Adding Unsuccessful";
                if(datas != nullptr){
                    if (pincode_data.add(datas, pincode)) {
                        res = "Added Succussfully!";
                    }
                }
                crow::mustache::context ctx({{"output", res}});
                return result_page.render(ctx);
            }
            catch (const std::invalid_argument& e){
                return error_page.render();
            }
        }
        return add_pincode_page.render(); });
    CROW_ROUTE(app, "/show_sellers")([](const crow::request &req){
            auto pincode_str = req.url_params.get("data");
            if(pincode_str != nullptr){
            try{
                unsigned int pincode = std::stoul(pincode_str);
                if(isNotValid(pincode)){
                    return error_page.render();
                }
                std::vector<unsigned long int> datas = pincode_data.showSellers(pincode);
                std::stringstream ss;
                ss<< "Result for Pincode " << pincode << ":\n";
                for(const auto& elem : datas){
                    ss<< elem << ", ";
                }
                crow::mustache::context ctx({{"output", ss.str()}});
                return result_page.render(ctx);
            }
            catch (const std::invalid_argument& e){
                return error_page.render();
            }
        }
        return show_sellers_page.render(); });
    CROW_ROUTE(app, "/show_pincodes")([](const crow::request &req){
            auto seller_str = req.url_params.get("data");
            if(seller_str != nullptr){
            try{
                unsigned long int seller_id = std::stoul(seller_str);
                std::vector<unsigned int> datas = merchant_data.showLocations(seller_id);
                std::stringstream ss;
                ss<< "Result for Seller " << seller_id << ":\n";
                for(const auto& elem : datas){
                    ss<< elem << ", ";
                }
                crow::mustache::context ctx({{"output", ss.str()}});
                return result_page.render(ctx);
            }
            catch (const std::invalid_argument& e){
                return error_page.render();
            }
        }
        return show_pincodes_page.render(); });
    CROW_ROUTE(app, "/validate")([](const crow::request &req){
            auto seller_id_str = req.url_params.get("seller_id");
            auto pincode_str = req.url_params.get("pincode");
            if(seller_id_str != nullptr && pincode_str != nullptr){
            try{
                unsigned long int seller_id = std::stoul(seller_id_str);
                unsigned int pincode = std::stoul(pincode_str);
                if(isNotValid(pincode)){
                    return error_page.render();
                }
                std::stringstream ss;
                ss<< "Seller " <<seller_id << " is ";
                if(!merchant_data.isServing(seller_id, pincode)){
                    ss<<"not ";
                }
                ss<<"serving at " << pincode <<".";
                crow::mustache::context ctx({{"output", ss.str()}});
                return result_page.render(ctx);
            }
            catch (const std::invalid_argument& e){
                return error_page.render();
            }
        }
        return validate_page.render(); });
    app.port(8080).multithreaded().run();
}