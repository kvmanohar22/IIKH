#include <stdlib.h>

#include "plan.hpp"

namespace IIKH {

	uint32_t Plan::plan_count = 0;
	const std::vector<std::string> Plan::plan_types({"daily", "weekly"});
	const std::string plan_log_file = "../data/plans.log";
	std::vector<std::pair<std::string, std::vector<
		std::pair<int, std::shared_ptr<Recipe> > > > > _plans_db = {};

	Plan::Plan() {}
	Plan::~Plan() {}

	void Plan::make_plans() {
		int clear = system("clear");
		std::cout << "These are the available type of plans:\n";
		for (size_t i = 0; i < Plan::plan_types.size(); ++i) {
			std::cout << i+1 << ": " << Plan::plan_types[i] << "\n";
		}

		uint32_t idx;
		std::cout << "Choose the type to add a plan: ";
		std::cin >> idx;

		clear = system("clear");
		DB::view_recipes();
		switch(idx) {
			case 1:
				add_daily_plans();
				break;
			case 2:
				add_weekly_plans();
				break;
			default:
				std::cerr << "No such plan type is currently available\n";
		}
	}

	void Plan::add_daily_plans() {
		std::string date;
		std::cout << "Enter today's date: ";
		std::cin >> date;
		std::cout << "Plan your breakfast for: " << date << "\n";
		plan_breakfast(date);
		std::cout << "Plan your lunch for: " << date << "\n";
		plan_lunch(date);
		std::cout << "Plan your dinner for: " << date << "\n";
		plan_dinner(date);
	}

	void Plan::add_weekly_plans() {

	}

	void plan_breakfast(std::string date) {
		char choice;
		std::string name;
		std::cout << "Would you like to have look at recipes (y/n): ";
		std::cin >> choice;
		if (choice == 'y') {
			DB::view_recipes();
		}

		while (true) {
			std::cout << "Enter the name of recipe for breakfast: ";
			std::cin >> name;
			if (DB::recipe_exists(name)) {

			} else {
				std::cerr << "Recipe \"" << name << "\" doesn't exist in the database.\n"
									<< "Would you like to add this recipe to database (y/n): ";
				std::cin >> choice;
				if (choice == 'y') {
					DB::add_recipes();
				}
			}
		}
	}

	void plan_lunch(std::string date) {

	}

	void plan_dinner(std::string date) {

	}

	void Plan::view_plans() {
		if (Plan::plan_count == 0) {
			std::cerr << "There are no plans currently available!\n"
					  		<< "Add new plans and proceed\n";
		} else {
			std::cout << "Following plans are available:\n";
			for (std::vector<std::string>::iterator itr = Plan::_plans.begin();
				itr != Plan::_plans.end(); ++itr) {
				std::cout << *itr << "\n";
			}
		}
	}

	void Plan::edit_plans() {
		if (Plan::plan_count == 0) {
			std::cerr << "There are no current plans available !\n"
					  		<< "Please consider adding plans.";
		} else {

		}
	}
}
