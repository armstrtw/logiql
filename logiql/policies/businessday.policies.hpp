#pragma once

#include <boost/date_time/gregorian/gregorian.hpp>

namespace logiql {
  using namespace boost::gregorian;

  class NoAdjustment {
  public:
    static date adjust(date eventDate, const Calendar& cal) {
      return eventDate;
    }
  };

  class Following {
  public:
    static date adjust(date eventDate, const Calendar& cal) {
      return cal.nextBusinessDay(eventDate);
    }
  };

} // namespace logiql
