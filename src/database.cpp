#include <memory>

#include "database.hpp"
#include "recipe.hpp"

namespace IIKH {

	DB::_recipe_count = 0;

	void DB::add_recipe(std::string name,
		std::vector<std::string> ings,
		std::vector<std::string> methods) {

		std::shared_ptr<Recipe> new_recipe(new Recipe);
		new_recipe->set_index(DB::_recipe_count);
		new_recipe->set_name(name);
		for (std::vector<std::string>::iterator itr = ings.begin();
			itr != ings.end(); ++itr) {
			new_recipe->add_ingredient(*itr);
		}
		for (std::vector<std::string>::iterator itr = methods.begin();
			itr != methods.end(); ++itr) {
			new_recipe->add_method(*itr);
		}

		this->_all_recipes.push_back(new_recipe);
		DB::_recipe_count += 1;		
	}

	Recipe DB::view_recipe(const uint32_t index) {
		if (index > DB::_recipe_count) {
			std::cerr << "There are only " << DB::_recipe_count << " recipes !\n";
		} else {
			return *(this->_all_recipes[index]);	
		}
	}

	void DB::edit_recipe_name(std::string old_name, std::string new_name) {
		uint32_t index = -1;
		for (size_t i = 0; i < DB::_recipe_count; ++i) {
			if (this->_all_recipes[i]->get_name() == old_name) {
				index = i;
				break;
			}
		}
		if (index == -1) {
			std::cerr << "No recipe found with name: " << old_name << "\n";
		} else {
			this->_all_recipes[index]->set_name(new_name);
		}
	}
}