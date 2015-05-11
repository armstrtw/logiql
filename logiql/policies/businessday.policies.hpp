#pragma once

#include <stdexcept>
#include <boost/date_time/gregorian/gregorian.hpp>

namespace logiql {
  using namespace boost::gregorian;

  class NoAdjustment {
  public:
    // also needs the calendar as an object
    date adjust(date eventDate) {
      return eventDate;
    }
  };

} // namespace logiql
