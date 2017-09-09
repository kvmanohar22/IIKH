#ifndef _IIKH_PLAN_HPP_
#define _IIKH_PLAN_HPP_

#include <vector>
#include <string>
#include <memory>

#include "recipe.hpp"
#include "database.hpp"

namespace IIKH {
	class Plan {
		private:
			std::vector<std::string> _plans;

		protected:
			void edit_breakfast(std::string date);
			void edit_lunch(std::string date);
			void edit_dinner(std::string date);

			void global_plan(std::string date, std::string time);

			void read_recipes(std::vector<uint32_t> *recipes, std::string time);

			void add_daily_plans();
			void view_daily_plan(std::string date);
			void edit_daily_plan(std::string date);

			void edit_meal(std::string date, std::vector<uint32_t> recipes,
				std::string time);
      void add_meal(std::string date, std::vector<uint32_t> recipes,
        std::string time);

			void parse_plans();
			void log_plans();

      int convert_time(std::string name);
      std::string convert_time_inv(int);
      size_t plan_exists(std::string date);

		public:
			static std::vector<std::pair<std::string, std::vector<std::pair<int, std::vector<uint32_t> > > > > _plans_db;
			static uint32_t plan_count;
			static const std::vector<std::string> plan_types;
			static const std::string plan_log_file;

			Plan();
			~Plan();

			void make_plans();
			void view_plans();
			void edit_plans();
	};
}

#endif
