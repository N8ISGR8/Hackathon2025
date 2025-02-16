#include "DBHandler.h"
#include <bsoncxx/types.hpp>

using bsoncxx::builder::basic::kvp;
using bsoncxx::builder::basic::document;
using bsoncxx::builder::basic::array;
using bsoncxx::builder::basic::make_document;

MongoDB* MongoDB::instance = nullptr;

void MongoDB::SendImage(std::string name, int64_t parent, std::vector<std::string> tags, const std::string data)
{
    Instance()->_SendImage(name, parent, tags, data);
}

std::vector<int64_t> MongoDB::ReadImagesFromName(std::string name)
{
    return Instance()->_ReadImagesFromName(name);
}

std::string MongoDB::ReadImageFromId(int64_t id)
{
    return Instance()->_ReadImageFromId(id);
}

std::vector<int64_t> MongoDB::GetNRandomIDs(int n)
{
    return Instance()->_GetNRandomIDs(n);
}

std::string MongoDB::GetNameFromID(int64_t id)
{
    return Instance()->_GetNameFromID(id);
}

int64_t MongoDB::GetParent(int64_t id)
{
    return Instance()->_GetParent(id);
}

std::vector<int64_t> MongoDB::GetChildren(int64_t id)
{
    return Instance()->_GetChildren(id);
}

std::vector<std::string> MongoDB::GetTags(int64_t id)
{
    return Instance()->_GetTags(id);
}

void MongoDB::_SendImage(std::string name, int64_t parent, std::vector<std::string> tags, const std::string data)
{
    document doc = document{};
    array arrTags = array{};
    for (std::string s : tags)
    {
        arrTags.append(s);
    }
    array arrChildren = array{};
    doc.append(kvp("name", name));
    doc.append(kvp("parent", parent));
    doc.append(kvp("tags", arrTags));
    doc.append(kvp("children", arrChildren));
    doc.append(kvp("data", data));
    bsoncxx::types::b_int64 id;
    std::uniform_int_distribution<int64_t> distribution(0,999999);
    do
    {
        id.value = distribution(generator);
    } while (collection.find_one(make_document(kvp("id", id))).has_value());
    doc.append(kvp("id", bsoncxx::types::b_int64(id)));

    collection.insert_one(doc.view());

    if (parent != 0)
    {
        auto update_doc = make_document(kvp("$push", make_document(kvp("children", id))));

        bsoncxx::document::value value = collection.find_one(bsoncxx::builder::basic::make_document(kvp("id", parent))).value();
        collection.update_one(value.view(), update_doc.view());
    }
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

std::vector<int64_t> MongoDB::_ReadImagesFromName(std::string name)
{
    std::vector<int64_t> v;
    mongocxx::cursor cursor = collection.find(bsoncxx::builder::basic::make_document(kvp("name", make_document(kvp("$regex", name)))));
    for (bsoncxx::document::view c : cursor)
    {
        v.push_back((*c.find("id")).get_int64());
    }
    return v;
}

std::vector<int64_t> MongoDB::_GetNRandomIDs(int n)
{
    std::vector<int64_t> v{};
    mongocxx::pipeline p{};
    p.sample(n);
    mongocxx::cursor cursor = collection.aggregate(p);
    for (bsoncxx::document::view c : cursor)
    {
        v.push_back((*c.find("id")).get_int64());
    }

    return v;
}

std::string MongoDB::_GetNameFromID(int64_t id)
{
    bsoncxx::stdx::optional<bsoncxx::document::value> o = collection.find_one(bsoncxx::builder::basic::make_document(kvp("id", id)));
    if (o.has_value())
    {
        bsoncxx::document::view::const_iterator viewIt = o.value().view().find("name");
        if (*viewIt)
        {
            bsoncxx::stdx::string_view sv = (*viewIt).get_string().value;
            return std::string(sv.begin(), sv.end());
        }
    }
    return "";
}

int64_t MongoDB::_GetParent(int64_t id)
{
    bsoncxx::stdx::optional<bsoncxx::document::value> o = collection.find_one(bsoncxx::builder::basic::make_document(kvp("id", id)));
    if (o.has_value())
    {
        bsoncxx::document::view::const_iterator viewIt = o.value().view().find("parent");
        if (*viewIt)
        {
            return (*viewIt).get_int64().value;
        }
    }
    return 0;
}

std::vector<int64_t> MongoDB::_GetChildren(int64_t id)
{
    std::vector<int64_t> v;
    bsoncxx::stdx::optional<bsoncxx::document::value> o = collection.find_one(bsoncxx::builder::basic::make_document(kvp("id", id)));
    if (o.has_value())
    {
        bsoncxx::document::view::const_iterator viewIt = o.value().view().find("children");
        if (*viewIt)
        {
            bsoncxx::array::view arr = (*viewIt).get_array().value;
            for (const bsoncxx::array::element& a : arr)
            {
                v.push_back(a.get_int64());
            }
        }
    }
    return v;
}

std::vector<std::string> MongoDB::_GetTags(int64_t id)
{
    std::vector<std::string> tags;
    bsoncxx::stdx::optional<bsoncxx::document::value> o = collection.find_one(bsoncxx::builder::basic::make_document(kvp("id", id)));
    if (o.has_value())
    {
        bsoncxx::document::view::const_iterator viewIt = o.value().view().find("tags");
        if (*viewIt)
        {
            bsoncxx::array::view arr = (*viewIt).get_array().value;
            for (const bsoncxx::array::element& a : arr)
            {
                bsoncxx::stdx::string_view sv = a.get_string().value;
                tags.push_back(std::string(sv.begin(), sv.end()));
            }
        }
    }
    return tags;
}

MongoDB::MongoDB()
{
    generator = std::mt19937(std::random_device{}());
    mongocxx::uri uri = mongocxx::uri(uriString);
	client = mongocxx::client(uri);
	db = client["ArtDB"];
	collection = db["Art"];
}

