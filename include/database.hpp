#ifndef _IIKH_DATABASE_HPP_
#define _IIKH_DATABASE_HPP_

#include <vector>
#include <memory>

#include "recipe.hpp"

namespace IIKH {

  // Database of recipes
  class DB {
    private:
      std::vector<std::shared_ptr<Recipe> > _all_recipes;
    protected:
      void edit_recipe_name(std::string old_name, std::string new_name);
    public:
      DB() {}
      ~DB() {}

      static uint32_t _recipe_count;

      void add_recipe(std::string name,
                      std::vector<std::string> ings,
                      std::vector<std::string> methods);
      void edit_recipe(std::string name);
      Recipe view_recipe(const uint32_t index);
  };

}

#endif