#pragma once

#include <boost/date_time/gregorian/gregorian.hpp>
#include <logiql/types.hpp>

namespace logiql {
  using namespace boost::gregorian;

  double julianDiff(date accrual_start,date accrual_end) {
      return date_duration(accrual_end - accrual_start).days();
  }

  template<typename T, typename U>
  T vectorShift(const T& vec, const U shift) {
    T ans(vec);
    for(auto &v : ans) { v+= shift; }
    return ans;
  }

  bool dateMatch(const date& d1, const date& d2) { return d1 == d2; }

  bool dateMatch(const date& d, const year_based_generator& pd) { return d == pd.get_date(d.year()); }
  bool dateMatch(const year_based_generator& pd, const date& d) { return d == pd.get_date(d.year()); }

  bool dateMatch(const date& d, const greg_weekday& wd) { return d.day_of_week() == wd; }
  bool dateMatch(const greg_weekday& wd, const date& d) { return d.day_of_week() == wd; }

} // namespace logiql
