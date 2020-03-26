#include <Core/Storage/Mongo/MongoBackend.h>

namespace Vortex {
	namespace Core {
		namespace Storage {
			namespace Mongo {
				MongoBackend::MongoBackend() {

				}

				MongoBackend::~MongoBackend() {

				}

				void MongoBackend::simple_insert(std::string database, std::string collection, std::string json_value) {
					client_.get_collection(database, collection).insert_one(json_value);
				}

				std::string MongoBackend::simple_find_all(std::string database, std::string collection, std::string json_simple_query) {
					return client_.get_collection(database, collection).find(json_simple_query).to_json();
				}

				std::string MongoBackend::simple_find_first(std::string database, std::string collection, std::string json_simple_query) {
					return client_.get_collection(database, collection).find_one(json_simple_query).to_json();
				}
				
				void MongoBackend::simple_replace_first(std::string database, std::string collection, std::string json_simple_query, std::string replacement_json_value) {
					client_.get_collection(database, collection).replace_one(json_simple_query, replacement_json_value);
				}

				void MongoBackend::simple_delete_all(std::string database, std::string collection, std::string json_simple_query) {
					client_.get_collection(database, collection).delete_many(json_simple_query);
				}

				void MongoBackend::simple_delete_first(std::string database, std::string collection, std::string json_simple_query) {
					client_.get_collection(database, collection).delete_one(json_simple_query);
				}

				std::vector<std::string> MongoBackend::get_database_list() {
					return client_.list_databases();
				}

				std::vector<std::string> MongoBackend::get_collection_list(std::string database) {
					return client_.list_collections(database);
				}

				Storage::Mongo::Mongo* MongoBackend::get_client() {
					return &this->client_;
				}

				Storage::IStorageBackend* get_mongo_backend() {
					static MongoBackend instance;
					return &instance;
				}
			}  // namespace Mongo
		}  // namespace Storage
	}  // namespace Core
}  // namespace Vortex
