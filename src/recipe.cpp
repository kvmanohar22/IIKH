#include "recipe.hpp"

namespace IIKH {

  void Recipe::add_ingredient(const std::string name) {
    this->ingredients.push_back(name);
    this->ingredient_count += 1;
  }

  std::string Recipe::get_ingredient(const uint32_t index) {
    if (index > this->ingredient_count ) {
      std::cerr << "There are " << this->ingredient_count << " ingredients !";
    } else {
      return this->ingredients[index];
    }
  }

  void Recipe::set_ingredient(const uint32_t index, const std::string name) {
    if (index > this->ingredient_count) {
      std::cerr << "There are " << this->ingredient_count << " ingredients !";
    } else {
      this->ingredients[index] = name;
    }
  }

  void Recipe::add_method(const std::string instruct) {
  	this->methods.push_back(instruct);
  	this->method_count += 1;
  }

  std::string Recipe::get_method(const uint32_t index) {
    if (index > this->method_count) {
      std::cerr << "There are " << this->method_count << " instructions !";
    } else {
      return this->methods[index];
    }
  }

  void Recipe::set_method(const uint32_t index, const std::string instruct) {
    if (index > this->method_count) {
      std::cerr << "There are " << this->method_count << " instructions !";
    } else {
      this->methods[index] = name;
    }
  }

}
