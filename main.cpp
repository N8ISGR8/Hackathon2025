#include <cstdint>
#include <iostream>
#include <vector>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>

using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::document;
using bsoncxx::builder::basic::array;


int main()
{
    mongocxx::instance instance;
    mongocxx::uri uri("mongodb+srv://app_user:ex17OefiFYvMfKM3@cluster0.sz37p.mongodb.net/?retryWrites=true&w=majority");
    mongocxx::client client(uri);
    auto db = client["ArtDB"];
    auto collection = db["Art"];
    document doc = document{};
    array arrTags = array{};
    arrTags.append("tag1");
    arrTags.append("tag2");
    arrTags.append("tag3");
    array arrChildren = array{};
    arrTags.append(0);
    arrTags.append(1);
    arrTags.append(2);
    doc.append(kvp("name", "test"));
    doc.append(kvp("id", 2));
    doc.append(kvp("parent", 0));
    doc.append(kvp("tags", arrTags));
    doc.append(kvp("children", arrChildren));
    doc.append(kvp("data", "balls"));

    collection.insert_one(doc.view());
    return 0;
}
