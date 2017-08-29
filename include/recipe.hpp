#ifndef _IIKH_RECIPE_HPP_
#define _IIKH_RECIPE_HPP_

#include <iostream>
#include <vector>
#include <memory>

namespace IIKH {

  // Recipe
  class Recipe {
    private:
      uint32_t index;
      std::string name;
      std::vector<std::string> ingredients;
      std::vector<std::string> methods;
      uint32_t method_count;
      uint32_t ingredient_count;
    public:
      Recipe() : ingredient_count(0), method_count(0) {}
      ~Recipe() {}
      
      void inline set_index(const uint32_t index) {
        this->index = index;
      }
      uint32_t inline get_index() {
        return this->index;
      }
      void inline set_name(const std::string name) {
        this->name = name;
      }
      std::string get_name() {
        return this->name;
      }
      void inline set_ingredient_count(const uint32_t count) {
        this->ingredient_count = count;
      }
      uint32_t inline get_ingredient_count() {
        return this->ingredient_count;
      }
      uint32_t inline get_method_count() {
        return this->method_count;
      }

      void add_ingredient(const std::string name);
      std::string get_ingredient(const uint32_t index);
      void set_ingredient(const uint32_t index, const std::string name);
      
      void add_method(const std::string instruct);
      std::string get_method(const uint32_t index);
      void set_method(const uint32_t index, const std::string instruct);
  };
  
}

#endif