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

    bool isBusinessDay(const date& day) const {
      for (auto h : holidays_) {
        if (h.match(day)) {
          return false;
        }
      }
      return true;
    }

    bool isHoliday(const date& day) const {
      return !isBusinessDay(day);
    }

    date nextBusinessDay(const date& day) const {
      day_iterator it(day);
      while (!isBusinessDay(*++it)) {}
      return *it;
    }

    date prevBusinessDay(const date& day) const {
      day_iterator it(day);
      while (!isBusinessDay(*--it)) {}
      return *it;
    }

    std::vector<date> businessDays(const date& start_date, const date& end_date) const {
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
