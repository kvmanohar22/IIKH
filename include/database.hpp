#ifndef _IIKH_DATABASE_HPP_
#define _IIKH_DATABASE_HPP_

#include <vector>
#include <memory>

#include "recipe.hpp"

namespace IIKH {

  // Database of recipes
  class DB {
    public:
      DB() {}
      ~DB() {}

      static const std::string recipe_log_file;

      static uint32_t _recipe_count;
      static std::vector<std::shared_ptr<Recipe> > _all_recipes;

      static void add_recipes();
      static void add_recipe(std::string name,
                      std::vector<std::string> ings,
                      std::vector<std::string> methods,
                      bool from_database=false);

      static void edit_recipes();
      static void edit_recipe_name(std::string old_name,
                      std::string new_name);

      static void view_recipes();
      static void view_recipe(const uint32_t index);

      static void log_recipe(std::string name,
                      std::vector<std::string> ings,
                      std::vector<std::string> methods);

      static void parse_recipe_log();

      static bool recipe_exists(std::string name);
  };

}

#endif
