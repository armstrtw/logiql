#pragma once

#include <boost/date_time/gregorian/gregorian.hpp>

namespace logiql {
  using namespace boost::gregorian;

  bool operator==(const date& d, const year_based_generator& pd) { return d == pd.get_date(d.year()); }
  bool operator==(const year_based_generator& pd, const date& d) { return d == pd.get_date(d.year()); }

  bool operator==(const date& d, const greg_weekday& wd) { return d.day_of_week() == wd; }
  bool operator==(const greg_weekday& wd, const date& d) { return d.day_of_week() == wd; }

  typedef std::function<bool (date)> HolidayImpl;
  class Holiday {
    HolidayImpl impl_;
  public:
    Holiday(HolidayImpl impl) : impl_(impl) {}
    Holiday(std::vector<date> x) : impl_([x](date day) { return x.end() != std::find(x.begin(), x.end(), day); }) {}
    template<typename T>
    Holiday(T x) : impl_([x](date day) { return day == x; }) {}

    bool match(date day) const { return impl_(day); }
  };

} // namespace logiql
