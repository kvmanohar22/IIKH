#include <memory>
#include <ostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>

#include "database.hpp"
#include "recipe.hpp"

namespace IIKH {

	uint32_t DB::_recipe_count = 0;
	std::vector<std::shared_ptr<Recipe> > DB::_all_recipes = {};
	const std::string DB::recipe_log_file = "../data/recipe.log";

	void DB::add_recipes() {
		char repeat;
		while (true) {
			std::string name;
			std::vector<std::string> ings;
			std::vector<std::string> methods;

			std::cout << "Enter the name of recipe: ";
			std::cin >> name;
			DB::read_methods(&methods);
			DB::read_ings(&ings);
			DB::add_recipe(name, ings, methods);
			std::cout << "Recipe \"" << name << "\" is added to the database !\n";
			std::cout << "Add one more recipe (y/n): ";
			std::cin >> repeat;
			if (repeat == 'n') {
				int clear = system("clear");
				break;
			}
		}
	}

	void DB::read_methods(std::vector<std::string> *methods) {
		std::cout << "Enter the method(s) of preperation of recipe:\n";
		methods->clear();
		std::string method;
		while (true) {
			char choice;
			std::cin >> method;
			methods->push_back(method);
			std::cout << "Add one more method (y/n): ";
			std::cin >> choice;
			if (choice == 'n') {
				break;
			}
		}
	}

	void DB::read_ings(std::vector<std::string> *ings) {
		std::cout << "Enter the ingredient(s) of recipe:\n";
		ings->clear();
		std::string ing;
		while (true) {
			char choice;
			std::cin >> ing;
			ings->push_back(ing);
			std::cout << "Add one more ingredient (y/n): ";
			std::cin >> choice;
			if (choice == 'n') {
				break;
			}
		}
	}

	void DB::add_recipe(std::string name,
		std::vector<std::string> ings,
		std::vector<std::string> methods,
		bool from_database) {

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

		DB::_all_recipes.push_back(new_recipe);
		DB::_recipe_count += 1;

		if (!from_database) {
			DB::log_recipe(name, ings, methods);
		}
	}

	void DB::log_recipe(std::string name,
		std::vector<std::string> ings,
		std::vector<std::string> methods) {
			std::ofstream file;
			file.open(DB::recipe_log_file.c_str(), std::fstream::app);
			file << name << "\n";
			for (size_t i = 0; i < ings.size(); ++i) {
				file << ings[i] << ":";
			}
			file << "\n";
			for (size_t i = 0; i < methods.size(); ++i) {
				file << methods[i] << ":";
			}
			file << "\n";
			file.close();
		}

	void DB::parse_recipe_log() {
		std::ifstream file(DB::recipe_log_file.c_str());
		std::string line, token, name;
		std::vector<std::string> ings;
		std::vector<std::string> methods;

		size_t pos = 0;
		while (std::getline(file, line)) {
			std::istringstream iss(line);
			while (std::getline(iss, token, ':'))	{
				if (pos == 0) {
					name = token;
				} else if (pos == 1) {
					ings.push_back(token);
				} else {
					methods.push_back(token);
				}
			}
			if (pos < 2) {
				++pos;
			} else {
				pos = 0;
				DB::add_recipe(name, ings, methods, true);
				methods.clear();
				ings.clear();
			}
		}
	}

	void DB::view_recipes(bool ing, bool methods) {
		if (DB::_recipe_count == 0) {
			std::cerr << "There are no recipes in the database !\n";
		} else {
			std::cout << "Following recipes are available:\n";
			for (size_t i = 0; i < DB::_recipe_count; ++i) {
				view_recipe(i, ing, methods);
			}
		}
	}

	void DB::view_recipe(const uint32_t index, bool ing, bool methods) {
		if (index > DB::_recipe_count) {
			std::cerr << "There are only " << DB::_recipe_count << " recipes !\n";
		} else {
			std::cout << index << ": Name: " << DB::_all_recipes[index]->get_name() << "\n";
			if (ing) {
				std::cout << "\tIngredient(s):\n\t\t";
				for (size_t i = 0; i < DB::_all_recipes[index]->get_ingredient_count(); ++ i) {
					std::cout << DB::_all_recipes[index]->get_ingredient(i) << " | ";
				}
			}
			if (methods) {
				std::cout << "\n\tMethod(s) of preperation:\n\t\t";
				for (size_t i = 0; i < DB::_all_recipes[index]->get_method_count(); ++ i) {
					std::cout << DB::_all_recipes[index]->get_method(i) << " | ";
				}
				std::cout << "\n";
			}
		}
	}

	void DB::edit_recipes() {
		DB::view_recipes(true, true);
		int choice, recipe_idx;
		std::string new_param;
		std::cout << "-------------------\n";
		std::cout << "How would you like to edit recipes ?\n"
							<< "1. Edit by name\n"
							<< "2. Edit by recipe ingredient(s)\n"
							<< "3. Edit by recipe method(s) of preperation\n"
							<< "Your choice (Enter index): ";
		std::cin >> choice;
		if (choice < 1 || choice > 3) {
			std::cerr << "No such option is available !\n"
								<< "Please enter a valid choice: ";
			std::cin >> choice;
		}
		while (true) {
			std::cout << "Enter index of recipe from above list that you would like to edit for: ";
			std::cin >> recipe_idx;
			if (recipe_idx < 1 || recipe_idx > DB::_recipe_count) {
				std::cerr << "Please enter valid recipe index !\n";
			} else {
				break;
			}
		}
		std::vector<std::string> new_vals;
		switch(choice) {
			case 1:
				std::cout << "Enter new name of recipe: "
									<< DB::_all_recipes[recipe_idx]->get_name() << ": ";
				std::cin >> new_param;
				DB::edit_recipe_name(DB::_all_recipes[recipe_idx]->get_name(), new_param);
				break;
			case 2:
				std::cout << "Enter new set of ingreadient(s) for recipe: \""
									<< DB::_all_recipes[recipe_idx]->get_name() << "\":\n";
				DB::read_ings(&new_vals);
				DB::edit_recipe_ings(recipe_idx, new_vals);
				break;
			case 3:
				std::cout << "Enter new set of method(s) for recipe: \""
									<< DB::_all_recipes[recipe_idx]->get_name() << "\":\n";
				DB::read_methods(&new_vals);
				DB::edit_recipe_methods(recipe_idx, new_vals);
				break;
		}
		int clear = system("clear");
		std::cout << "Reply: Your changes are incorporated in the database !\n\n";
	}

	void DB::edit_recipe_ings(uint32_t idx, std::vector<std::string> ings) {
		DB::_all_recipes[idx]->clear_ingredients();
		for (std::vector<std::string>::iterator itr = ings.begin();
			itr != ings.end(); ++itr) {
				DB::_all_recipes[idx]->add_ingredient(*itr);
			}
	}

	void DB::edit_recipe_methods(uint32_t idx, std::vector<std::string> methods) {
		DB::_all_recipes[idx]->clear_methods();
		for (std::vector<std::string>::iterator itr = methods.begin();
		itr != methods.end(); ++itr) {
			DB::_all_recipes[idx]->add_method(*itr);
		}
	}

	void DB::edit_recipe_name(std::string old_name, std::string new_name) {
		uint32_t index = -1;
		for (size_t i = 0; i < DB::_recipe_count; ++i) {
			if (DB::_all_recipes[i]->get_name() == old_name) {
				index = i;
				break;
			}
		}
		if (index == -1) {
			std::cerr << "No recipe found with name: " << old_name << "\n";
		} else {
			DB::_all_recipes[index]->set_name(new_name);
		}
	}

	bool DB::recipe_exists(std::string name) {
		for (size_t i = 0; i < DB::_recipe_count; ++i) {
			if (DB::_all_recipes[i]->get_name() == name) {
				return true;
			}
		}
		return false;
	}

	bool DB::recipe_exists(uint32_t index) {
		if (index < DB::_recipe_count) {
			return true;
		} else {
			return false;
		}
	}

  uint32_t DB::get_recipe_idx(std::string name) {
    if (DB::recipe_exists(name)) {
      for (size_t i = 0; i < DB::_recipe_count; ++i) {
        if (DB::_all_recipes[i]->get_name() == name) {
          return DB::_all_recipes[i]->get_index();
        }
      }
    } else {
      std::cerr << "Recipe " << name << " doesn't exist in database !\n";
    }
  }

	std::string DB::get_recipe_name(uint32_t idx) {
    if (DB::recipe_exists(idx)) {
  		for (size_t i = 0; i < DB::_recipe_count; ++i) {
  			if (DB::_all_recipes[i]->get_index() == idx) {
  				return DB::_all_recipes[i]->get_name();
  			}
  		}
    } else {
      std::cerr << "Recipe with index: " << idx << " doesn't exist in database !\n";
    }
	}
}
