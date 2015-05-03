#pragma once

#include <stdexcept>
#include <boost/date_time/gregorian/gregorian.hpp>

namespace logiql {

  class NoAdjustment {
  public:
    // also needs the calendar as an object
    boost::gregorian::date adjust(boost::gregorian::date eventDate) {
      return eventDate;
    }
  };

} // namespace logiql
