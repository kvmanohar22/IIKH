#include <iostream>
#include <stdlib.h>

#include "recipe.hpp"
#include "database.hpp"
#include "plan.hpp"

using namespace std;
using namespace IIKH;

int main(int argc, char** argv) {

  int clear = system("clear");
  DB::parse_recipe_log();
  Plan present_plan;

  while(true) {
  	std::cout << "------------------------------------------------\n"
  		      << "Welcome to IIKH (Interactive Intelligent Kitchen Helper)";
  	int option;
  	std::cout << "\n------------------------------------------------\n"
  			  << "Here's the menu:\n"
  			  << "1. Make a plan\n"
  			  << "2. View plans\n"
  			  << "3. Edit plans\n"
  			  << "4. View Recipes\n"
  			  << "5. Add new Recipes\n"
  			  << "6. Edit Recipes List\n"
  			  << "7. Exit\n"
  			  << "Choose your option: ";
  	std::cin >> option;
  	clear = system("clear");

  	switch(option) {
  		case 1:
  			if (DB::_recipe_count == 0) {
  				std::cerr << "There are no recipes in the database !\n"
  						      << "Consider adding recipes before making a plan!\n";
  				DB::add_recipes();
  			} else {
  				present_plan.make_plans();
  			}
  			break;
  		case 2:
  			present_plan.view_plans();
  			break;
  		case 3:
  			present_plan.edit_plans();
  			break;
      case 4:
        DB::view_recipes();
        break;
      case 5:
        DB::add_recipes();
        break;
      case 6:
        DB::edit_recipes();
        break;
      case 7:
        std::cout << "Exiting !\n";
        clear = system("clear");
        exit(0);
        break;
  		default:
  			std::cerr << "There is no such option, please choose a valid option !\n";
  	}
  }

  return 0;
}
