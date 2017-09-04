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
			void edit_plan(uint32_t index);

			void plan_breakfast(std::string date);
			void plan_lunch(std::string date);
			void plan_dinner(std::string date);

			void add_daily_plans();
			void add_weekly_plans();

			void view_daily_plans();
			void view_weekly_plans();

			void edit_daily_plans();
			void edit_weekly_plans();

			void parse_plans();
			void log_plans();
		public:
			static std::vector<std::pair<std::string, std::vector<std::pair<int, std::shared_ptr<Recipe> > > > > _plans_db;
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
