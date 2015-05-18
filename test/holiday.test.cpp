#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <logiql/holiday.hpp>

using namespace boost::gregorian;
using namespace logiql;

TEST_CASE("holidays can be constructed in many ways") {
  SECTION("from a functor") {
    HolidayImpl func([](date d) -> bool { return d == date(2015, 5, 15); });
    Holiday h(func);
    REQUIRE(h.match(date(2015, 5, 15)));
    REQUIRE(!h.match(date(2015, 5, 16)));
  }
  SECTION("from a vector of dates") {
    std::vector<date> dd({date(2015, 5, 15), date(2015, 4, 15)});
    Holiday h(dd);
    REQUIRE(h.match(date(2015, 5, 15)));
    REQUIRE(h.match(date(2015, 4, 15)));
    REQUIRE(!h.match(date(2015, 4, 20)));

    SECTION("plus a positive shift") {
      Holiday h(dd, days(2));
      REQUIRE(h.match(date(2015, 5, 17)));
      REQUIRE(h.match(date(2015, 4, 17)));
      REQUIRE(!h.match(date(2015, 5, 15)));
      REQUIRE(!h.match(date(2015, 4, 15)));
    }
    SECTION("plus a negative shift") {
      Holiday h(dd, days(-2));
      REQUIRE(h.match(date(2015, 5, 13)));
      REQUIRE(h.match(date(2015, 4, 13)));
      REQUIRE(!h.match(date(2015, 5, 15)));
      REQUIRE(!h.match(date(2015, 4, 15)));
    }
  }
  SECTION("from anything where dateMatch is defined") {
    SECTION("partial date") {
      Holiday h(partial_date(1,Jan));
      REQUIRE(h.match(date(2002,Jan,1)));
      REQUIRE(!h.match(date(2002,Jan,2)));
    }
    SECTION("weekday matching behaves like day_of_week") {
      Holiday h(Thursday);
      REQUIRE(h.match(date(2002,Jan,10)));
      REQUIRE(!h.match(date(2002,Jan,11)));
    }
    SECTION("plus a range") {
      SECTION("partial date") {
        Holiday h(partial_date(1,Jan), date(2002,Jan,1), date(2002,Jan,31));
        REQUIRE(h.match(date(2002,Jan,1)));
        REQUIRE(!h.match(date(2002,Jan,2)));
        REQUIRE(!h.match(date(2003,Jan,1)));
        REQUIRE(!h.match(date(2003,Jan,2)));
      }
      SECTION("weekday matching behaves like day_of_week") {
        Holiday h(Thursday, date(2002,Jan,1), date(2002,Jan,31));
        REQUIRE(h.match(date(2002,Jan,10)));
        REQUIRE(!h.match(date(2002,Jan,11)));
        REQUIRE(!h.match(date(2002,Feb,7)));
        REQUIRE(!h.match(date(2002,Feb,8)));
      }
    }
  }
}
