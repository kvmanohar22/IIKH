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
			std::string name, ing, method;
			std::vector<std::string> ings;
			std::vector<std::string> methods;

			std::cout << "Enter the name of recipe: ";
			std::cin >> name;
			std::cout << "Enter the ingredients of recipe:\n";
			while (true) {
				char choice;
				std::cin >> ing;
				ings.push_back(ing);
				std::cout << "Add one more ingredient (y/n): ";
				std::cin >> choice;
				if (choice == 'n') {
					break;
				}
			}
			std::cout << "Enter the method(s) of preperation of recipe:\n";
			while (true) {
				char choice;
				std::cin >> method;
				methods.push_back(method);
				std::cout << "Add one more method (y/n): ";
				std::cin >> choice;
				if (choice == 'n') {
					break;
				}
			}
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

	void DB::view_recipes() {
		if (DB::_recipe_count == 0) {
			std::cerr << "There are no recipes in the database !\n";
		} else {
			std::cout << "Following recipes are available:\n";
			for (size_t i = 0; i < DB::_recipe_count; ++i) {
				view_recipe(i);
			}
		}
	}

	void DB::view_recipe(const uint32_t index) {
		if (index > DB::_recipe_count) {
			std::cerr << "There are only " << DB::_recipe_count << " recipes !\n";
		} else {
			// std::cout << "------------------------------------------------\n";
			std::cout << "Name: " << DB::_all_recipes[index]->get_name() << "\n";
			// std::cout << "Ingredients:\n";
			// for (size_t i = 0; i < DB::_all_recipes[index]->get_ingredient_count(); ++ i) {
			// 	std::cout << i+1 << " " << DB::_all_recipes[index]->get_ingredient(i) << "\n";
			// }
			// std::cout << "Method(s) of preperation:\n";
			// for (size_t i = 0; i < DB::_all_recipes[index]->get_method_count(); ++ i) {
			// 	std::cout << i+1 << " " << DB::_all_recipes[index]->get_method(i) << "\n";
			// }
		}
	}

	void DB::edit_recipes() {
		std::cerr << "Not implemented !\n";
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
}
