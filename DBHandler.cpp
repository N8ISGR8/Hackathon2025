#include "DBHandler.h"
#include <bsoncxx/types.hpp>

using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::document;
using bsoncxx::builder::basic::array;

MongoDB* MongoDB::instance = nullptr;

void MongoDB::SendImage(std::string name, int64_t parent, std::vector<std::string> tags, const std::string data)
{
    Instance()->_SendImage(name, parent, tags, data);
}

std::string MongoDB::ReadImageFromId(int64_t id)
{
    return Instance()->_ReadImageFromId(id);
}

void MongoDB::_SendImage(std::string name, int64_t parent, std::vector<std::string> tags, const std::string data)
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

    collection.insert_one(doc.view());
}

std::string MongoDB::_ReadImageFromId(int64_t id)
{
    bsoncxx::stdx::optional<bsoncxx::document::value> o = collection.find_one(bsoncxx::builder::basic::make_document(kvp("id", id)));
    if (o.has_value())
    {
        bsoncxx::document::view::const_iterator viewIt = o.value().view().find("data");
        if (*viewIt)
        {
            bsoncxx::stdx::string_view sv = (*viewIt).get_string().value;
            return std::string (sv.begin(), sv.end());
        }
    }
    return "";
}

MongoDB::MongoDB()
{
    generator = std::mt19937(std::random_device{}());
    mongocxx::uri uri = mongocxx::uri(uriString);
	client = mongocxx::client(uri);
	db = client["ArtDB"];
	collection = db["Art"];
}

