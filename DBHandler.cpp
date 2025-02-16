#include "DBHandler.h"
#include <bsoncxx/types.hpp>

using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::document;
using bsoncxx::builder::basic::array;

MongoDB* MongoDB::instance = nullptr;

void MongoDB::SendImage(std::string name, int64_t parent, std::vector<std::string> tags, const char* data)
{
    Instance()->_SendImage(name, parent, tags, data);
}

void MongoDB::_SendImage(std::string name, int64_t parent, std::vector<std::string> tags, const char* data)
{
    document doc = document{};
    array arrTags = array{};
    arrTags.append("tag1");
    arrTags.append("tag2");
    arrTags.append("tag3");
    array arrChildren = array{};
    doc.append(kvp("name", name));
    doc.append(kvp("parent", parent));
    doc.append(kvp("tags", arrTags));
    doc.append(kvp("children", arrChildren));
    doc.append(kvp("data", data));
    bsoncxx::types::b_int64 id;
    std::uniform_int_distribution<uint64_t> distribution(0,999999);
    do
    {
        id.value = distribution(generator);
    } while (collection.find_one(bsoncxx::builder::basic::make_document(kvp("id", id))).has_value());
    doc.append(kvp("id", bsoncxx::types::b_int64(id)));

    instance->collection.insert_one(doc.view());
}

MongoDB::MongoDB()
{
    generator = std::mt19937(std::random_device{}());
    mongocxx::uri uri = mongocxx::uri(uriString);
	client = mongocxx::client(uri);
	db = client["ArtDB"];
	collection = db["Art"];
}

