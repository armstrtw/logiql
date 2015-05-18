#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <logiql/calendar.hpp>

using namespace boost::gregorian;
using namespace logiql;

TEST_CASE("calendars can be constructed in many ways") {
  date d(2015,5,15);
  greg_weekday wd(Saturday);
  partial_date pd(1,Jan);

  SECTION("from an explicit date") {
    Calendar c({d});
    REQUIRE(c.isHoliday(d));
  }
  SECTION("from a weekday") {
    Calendar c({wd});
    REQUIRE(c.isHoliday(date(2015,5,16)));
  }
  SECTION("from a partial date") {
    Calendar c({pd});
    REQUIRE(c.isHoliday(date(2015,1,1)));
  }
  SECTION("from a heterogeneous combination of the above") {
    Calendar c({d, wd, pd});
    REQUIRE(c.isHoliday(d));
    REQUIRE(c.isHoliday(date(2015,5,16)));
    REQUIRE(c.isHoliday(date(2015,1,1)));
  }
}
TEST_CASE("business_day methods are consistent") {
  Calendar c({Saturday, Sunday});
  std::vector<date> bd = c.businessDays(date(2015,1,1),date(2015,1,31));
  SECTION("all are business days and not holidays") {
    for (auto d : bd) {
      REQUIRE(c.isBusinessDay(d));
      REQUIRE(!c.isHoliday(d));
    }
  }
  SECTION("next/prev methods work") {
    for (auto it = bd.begin(); it < bd.end()-1; ++it) {
      REQUIRE(c.nextBusinessDay(*it) == *(it+1));
      REQUIRE(c.prevBusinessDay(*(it+1)) == *it);
    }
  }
}
