#pragma once

#include <algorithm>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <logiql/utils/utils.hpp>

namespace logiql {
  using namespace boost::gregorian;

  typedef std::function<bool (date)> HolidayImpl;
  class Holiday {
    HolidayImpl impl_;
  public:
    Holiday(HolidayImpl impl) : impl_(impl) {}
    Holiday(std::vector<date> x) : impl_([x](date day) { return x.end() != std::find(x.begin(), x.end(), day); }) {}
    Holiday(std::vector<date> x, date_duration shift) : Holiday(vectorShift(x,shift)) {}

    template<typename T>
    Holiday(T x) : impl_([x](date day) { return dateMatch(day, x); }) {}
    template<typename T>
    Holiday(T x, date start, date end) : impl_([x, start, end](date day) { return day >= start && day <= end && dateMatch(day, x); }) {}

    bool match(date day) const { return impl_(day); }
  };

} // namespace logiql
