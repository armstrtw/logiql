#pragma once

#include <vector>
#include <boost/date_time/gregorian/gregorian.hpp>

namespace logiql {
  namespace holidays {
    using namespace boost::gregorian;
    namespace US {

      const date reagans_funeral(2004,Jun,11);
      const date sep11_2001(2011,Sep,11);
      const date fords_funeral(2007,Jan,2);
      const date blackout_1977(1977,Jul,14);
      const date johnsons_funeral(1973,Jan,25);
      const date trumans_funeral(1972,Dec,28);
      const date lunar_exploration_day(1969,Jul,21);
      const date eisenhowers_funeral(1969,Mar,31);
      const date snow_storm1969(1969,Feb,10);
      const date day_after_independence_day(1968,Jul,5);
      const date nixons_funeral(1994,Apr,27);
    }

    namespace UK {
      const date golden_jubilee_bank_holiday_2002(2002,Jun,3);
      const date special_spring_bank_holiday_2002(2002,Jun,3);
      const date royal_wedding_bank_holiday_2011(2011,Apr,29);
      const date diamond_jubilee_bank_holiday_2012(2012,Jun,4);
      const date special_spring_bank_holiday_2012(2012,Jun,5);
      const date dec31_1999(1999,Dec,31);
    }

  } // namespace holidays
} // namespace logiql
