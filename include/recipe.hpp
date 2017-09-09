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

      inline void set_index(const uint32_t index) {
        this->index = index;
      }

      inline uint32_t get_index() {
        return this->index;
      }

      inline void set_name(const std::string name) {
        this->name = name;
      }

      std::string get_name() {
        return this->name;
      }

      inline void set_ingredient_count(const uint32_t count) {
        this->ingredient_count = count;
      }

      inline uint32_t get_ingredient_count() {
        return this->ingredient_count;
      }

      inline void set_method_count(const uint32_t count) {
        this->method_count = count;
      }

      inline uint32_t get_method_count() {
        return this->method_count;
      }

      inline void clear_ingredients() {
        this->ingredients.clear();
        set_ingredient_count(0);
      }

      inline void clear_methods() {
        this->methods.clear();
        set_method_count(0);
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
