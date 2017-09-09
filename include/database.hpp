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
      static void edit_recipe_ings(uint32_t idx, std::vector<std::string> ings);
      static void edit_recipe_methods(uint32_t idx, std::vector<std::string> methods);

      static void view_recipes(bool ing=false, bool methods=false);
      static void view_recipe(const uint32_t index, bool ing=false,
                      bool methods=false);

      static void log_recipe(std::string name,
                      std::vector<std::string> ings,
                      std::vector<std::string> methods);

      static void parse_recipe_log();

      static bool recipe_exists(std::string name);
      static bool recipe_exists(uint32_t index);

      static uint32_t get_recipe_idx(std::string name);
      static std::string get_recipe_name(uint32_t idx);

      static void read_methods(std::vector<std::string> *methods);
      static void read_ings(std::vector<std::string> *ings);
  };

}

#endif
