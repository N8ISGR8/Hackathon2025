#pragma once
#include <string>
#include <bsoncxx/builder/basic/document.hpp>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/uri.hpp>
#include <random>

class MongoDB
{
public:
	MongoDB& operator=(const MongoDB& rhs) = delete;
	MongoDB(const MongoDB&&) = delete;
	static void SendImage(std::string name, int64_t parent, std::vector<std::string> tags, const std::string data);
	static std::string ReadImageFromName(std::string name);
	static std::string ReadImageFromId(int64_t id);
private:
	void _SendImage(std::string name, int64_t parent, std::vector<std::string> tags, const std::string data);
	std::string _ReadImageFromId(int64_t id);
	std::string _ReadImageFromName(std::string name);
	static MongoDB* Instance() {
		if (instance == nullptr) {
			instance = new MongoDB();
		}
		return instance;
	}
	static MongoDB* instance;
	mongocxx::instance mongoInstance;
	mongocxx::client client;
	mongocxx::v_noabi::collection collection;
	mongocxx::v_noabi::database db;
	std::mt19937 generator;
	MongoDB();
	std::string uriString = "mongodb+srv://app_user:ex17OefiFYvMfKM3@cluster0.sz37p.mongodb.net/?retryWrites=true&w=majority";
};