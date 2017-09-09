#include <stdlib.h>

#include "plan.hpp"

namespace IIKH {

	uint32_t Plan::plan_count = 0;
	const std::vector<std::string> Plan::plan_types({"daily"});
	const std::string plan_log_file = "../data/plans.log";
	std::vector<std::pair<std::string, std::vector<
		std::pair<int, std::vector<uint32_t> > > > > Plan::_plans_db = {};

	Plan::Plan() {}
	Plan::~Plan() {}

	void Plan::make_plans() {
		int clear = system("clear");
		std::cout << "These are the available type of plans:\n";
		for (size_t i = 0; i < Plan::plan_types.size(); ++i) {
			std::cout << i+1 << ": " << Plan::plan_types[i] << "\n";
		}

		uint32_t idx;
		std::cout << "Choose the type to add a plan (Enter index): ";
		std::cin >> idx;

		clear = system("clear");
		DB::view_recipes();
    std::cout << "-----------\n";
		switch(idx) {
			case 1:
				add_daily_plans();
				break;
			default:
				std::cerr << "No such plan type is currently available\n";
		}
	}

	void Plan::add_daily_plans() {
		std::string date;
		std::cout << "Enter date of plan (dd-mm-yy): ";
		std::cin >> date;
		std::cout << "Plan your breakfast for: " << date << "\n";
		global_plan(date, "breakfast");
		std::cout << "Plan your lunch for: " << date << "\n";
		global_plan(date, "lunch");
		std::cout << "Plan your dinner for: " << date << "\n";
		global_plan(date, "dinner");
		int clear = system("clear");
		std::cout << "Reply: Your changes are incorporated in the database !\n\n";
	}

	void Plan::view_daily_plan(std::string date) {
    bool flag = false;
    for (size_t i = 0; i < Plan::plan_count; ++i) {
      if (date == Plan::_plans_db[i].first) {
        flag = true;
        std::cout << "Date: " << date << "\n";
        std::vector<std::pair<int, std::vector<uint32_t> > > dummy = Plan::_plans_db[i].second;
        for (size_t j = 0; j < dummy.size(); ++j) {
          std::cout << "\t" << this->convert_time_inv(dummy[j].first) << ": ";
          for (size_t k = 0; k < dummy[j].second.size(); ++k) {
            std::cout << DB::get_recipe_name(dummy[j].second[k]) << " ";
          }
          std::cout << "\n";
        }
      }
    }
    if (!flag) {
      std::cerr << "There are no plans for the day : " << date << "\n";
	 }
  }

	void Plan::edit_daily_plan(std::string date) {
		view_plans();
		int choice;
		std::cout << "Available options are: \n"
							<< "1. Make changes to breakfast\n"
							<< "2. Make changes to lunch\n"
							<< "3. Make changes to dinner\n"
							<< "Enter your choice (index): ";
		std::cin >> choice;
		switch(choice) {
			case 1:
				edit_breakfast(date);
				break;
			case 2:
				edit_lunch(date);
				break;
			case 3:
				edit_dinner(date);
				break;
		}
		int clear = system("clear");
		std::cout << "Reply: Your changes are incorporated in the database !\n\n";
	}

	void Plan::edit_breakfast(std::string date) {
		std::cout << "Enter new set of breakfast items:\n";
		std::vector<uint32_t> new_recipes;
		read_recipes(&new_recipes, "breakfast");
		edit_meal(date, new_recipes, "breakfast");
	}

	void Plan::edit_lunch(std::string date) {
		std::cout << "Enter new set of lunch items:\n";
		std::vector<uint32_t> new_recipes;
		read_recipes(&new_recipes, "lunch");
		edit_meal(date, new_recipes, "lunch");
	}

	void Plan::edit_dinner(std::string date) {
		std::cout << "Enter new set of dinner items:\n";
		std::vector<uint32_t> new_recipes;
		read_recipes(&new_recipes, "dinner");
		edit_meal(date, new_recipes, "dinner");
	}

	void Plan::global_plan(std::string date, std::string time) {
    std::vector<uint32_t> recipe_idx;
		read_recipes(&recipe_idx, time);
    add_meal(date, recipe_idx, time);
  }

	void Plan::read_recipes(std::vector<uint32_t> *recipe_idx, std::string time) {
		std::string name;
		char choice, one_more;
		recipe_idx->clear();
		while (true) {
			std::cout << "Enter the name of recipe: ";
			std::cin >> name;
			if (DB::recipe_exists(name)) {
				recipe_idx->push_back(DB::get_recipe_idx(name));
				std::cout << "Would you like to add one more recipe to " << time << " (y/n): ";
				std::cin >> one_more;
				if (one_more != 'y') {
					break;
				}
			} else {
				std::cerr << "Recipe \"" << name << "\" doesn't exist in the database.\n"
									<< "Would you like to add this recipe to database (y/n): ";
				std::cin >> choice;
				if (choice == 'y') {
					DB::add_recipes();
				} else {
					std::cout << "New recipe is not added, choose from the existing recipes\n";
				}
			}
		}
	}

  void Plan::add_meal(std::string date, std::vector<uint32_t> recipes, std::string time) {
    size_t plan_idx = this->plan_exists(date);
    if (plan_idx != -1) {
      Plan::_plans_db[plan_idx].second.push_back(std::make_pair(convert_time(time), recipes));
    } else {
      std::vector<std::pair<int, std::vector<uint32_t> > > dummy;
      dummy.push_back(std::make_pair(convert_time(time), recipes));
      Plan::_plans_db.push_back(std::make_pair(date, dummy));
      Plan::plan_count += 1;
    }
  }

	void Plan::edit_meal(std::string date, std::vector<uint32_t> recipes, std::string time) {
		size_t plan_idx = this->plan_exists(date);
		if (plan_idx != -1) {
			Plan::_plans_db[plan_idx].second.erase(
				Plan::_plans_db[plan_idx].second.begin()+convert_time(time));
			Plan::_plans_db[plan_idx].second.insert(
				Plan::_plans_db[plan_idx].second.begin()+convert_time(time),
				std::make_pair(convert_time(time), recipes));
		} else {
			std::cerr << "Plan for date \"" << date << "\" doesn't' exist !\n";
		}
	}

  size_t Plan::plan_exists(std::string date) {
    for (size_t i = 0; i < Plan::plan_count; ++i) {
      if (Plan::_plans_db[i].first == date) {
        return i;
      }
    }
    return -1;
  }

	void Plan::view_plans() {
		if (Plan::plan_count == 0) {
			std::cerr << "There are no plans currently available !\n"
					      << "Please consider adding plans\n";
    } else {
      std::cout << "Following plans are available:\n";
      for (size_t i = 0; i < Plan::plan_count; ++i) {
        this->view_daily_plan(Plan::_plans_db[i].first);
      }
    }
  }

  void Plan::edit_plans() {
		std::string plan_date;
		char choice;
    if (Plan::plan_count == 0) {
      std::cerr << "There are no plans currently available !\n"
                << "Please consider adding plans\n";
		} else {
			view_plans();
			std::cout << "Enter the date of the plan to make changes: ";
			std::cin >> plan_date;
			if (plan_exists(plan_date) != -1) {
				int clear = system("clear");
				edit_daily_plan(plan_date);
			} else {
				std::cerr << "Plan for the date \"" << plan_date << "\" doesn't exist !\n"
									<< "Would you like to make plan for this date (y/n): ";
				std::cin >> choice;
				if (choice == 'y') {
					int clear = system("clear");
					make_plans();
				} else {
					int clear = system("clear");
					std::cout << "Reply: Please select valid date to make changes !\n";
				}
			}
		}
	}

  int Plan::convert_time(std::string name) {
    if (name == "breakfast") {
      return 0;
    } else if (name == "lunch") {
      return 1;
    } else {
      return 2;
    }
  }

  std::string Plan::convert_time_inv(int time) {
    switch(time) {
      case 0:
        return "Breakfast";
      case 1:
        return "Lunch";
      case 2:
        return "Dinner";
      default:
        std::cerr << "No such type exists !\n";
    }
  }

}
