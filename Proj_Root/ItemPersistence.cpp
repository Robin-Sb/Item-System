#include "ItemPersistence.h"
#include "json.hpp"
#include <fstream>
#include <sstream> 

using json = nlohmann::json;

string file_name = "items.json";

void to_json(json& j, const Item& item) {
    j = json{ {"name", item.name}, {"color", item.color} };
}


void from_json(const json& j, Item& item) {
    j.at("name").get_to(item.name);
    j.at("color").get_to(item.color);
}

void write_file(string jsonString) {
    ofstream myfile;
    myfile.open("items.json");
    myfile << jsonString << "\n";
}

string read_file() {
    std::ifstream t("items.json");
    std::stringstream buffer;
    buffer << t.rdbuf();
    return buffer.str();
}

void ItemPersistence::serializeInventory(vector<Item> items) {
    json j = items;
    string json_string = j.dump();
    write_file(json_string);
}

vector<Item> ItemPersistence::deserializeInventory() {
    string file_as_string = read_file();
    vector<Item> items;
    try {
        json jsonObj = json::parse(file_as_string);
        items = jsonObj.get<vector<Item>>();
    }
    catch (const std::exception & e) {
        printf(e.what());
    }
    return items;
}