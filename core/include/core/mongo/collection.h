#ifndef VORTEX_CORE_MONGO_COLLECTION_H
#define VORTEX_CORE_MONGO_COLLECTION_H

#include <string>
#include <mongocxx/collection.hpp>
#include <maze/array.h>
#include <maze/object.h>

namespace vortex {
namespace core {
namespace mongo {

class collection {
 private:
  mongocxx::collection collection_;

 public:
  collection(mongocxx::collection collection);

  maze::array find(maze::object query);
  maze::array find(std::string json_query);
  maze::object find_by_id(std::string oid);
  maze::object find_one(maze::object query);
  maze::object find_one(std::string json_query);

  void delete_one(maze::object query);
  void delete_one(std::string json_query);

  void insert_one(maze::object value);
  void insert_one(std::string json_value);

  void insert_many(maze::array values);
  void insert_many(std::vector<std::string> json_values_array);

  void replace_one(maze::object query, maze::object replacement_value);
  void replace_one(std::string json_query, std::string json_replacement_value);
};

}  // namespace mongo
}  // namespace core
}  // namespace vortex

#endif  // VORTEX_CORE_MONGO_COLLECTION_H
