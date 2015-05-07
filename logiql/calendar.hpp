#pragma once

#include <vector>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <logiql/holiday.hpp>

namespace logiql {
  using namespace boost::gregorian;

  class Calendar {
    std::vector<Holiday> holidays_;
  public:
    Calendar(std::vector<Holiday> holidays) : holidays_(holidays) {}

    bool isBusinessDay(const date& day) {
      for (auto h : holidays_) {
        if (h.match(day)) {
          return false;
        }
      }
      return true;
    }

    bool isHoliday(const date& day) {
      return !isBusinessDay(day);
    }

    date nextBusinessDay(const date& day) {
      day_iterator it(day);
      while (!isBusinessDay(*++it)) {}
      return *it;
    }

    date prevBusinessDay(const date& day) {
      day_iterator it(day);
      while (!isBusinessDay(*--it)) {}
      return *it;
    }

    std::vector<date> businessDays(const date& start_date, const date& end_date) {
      std::vector<date> ans;
      for (day_iterator it(start_date); it <= end_date; ++it) {
        if (isBusinessDay(*it)) {
          ans.push_back(*it);
        }
      }
      return ans;
    }

  };

} // namespace logiql
