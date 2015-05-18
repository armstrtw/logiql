#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include <logiql/logiql.utils.hpp>

using namespace boost::gregorian;
using namespace logiql;

TEST_CASE("julianDiff performs date arithmetic") {
  SECTION("the same date has 0 diff") {
    date d(2015, 5, 15);
    REQUIRE(julianDiff(d, d) == 0);
  }
  SECTION("forward dates have +ive diff") {
    date d1(2015, 5, 15);
    date d2(d1 + days(3));
    REQUIRE(julianDiff(d1, d2) == 3);
  }
  SECTION("forward dates have -ive diff") {
    date d1(2015, 5, 15);
    date d2(d1 - days(3));
    REQUIRE(julianDiff(d1, d2) == -3);
  }
}
TEST_CASE("payment frequencies are coherent") {
  SECTION("ToMonths and PerYear should multiply to 12") {
    REQUIRE((paymentFrequencyToMonths(PaymentFrequencyT::Annual) * paymentFrequencyToPaymentsPerYear(PaymentFrequencyT::Annual)) == 12);
    REQUIRE((paymentFrequencyToMonths(PaymentFrequencyT::SemiAnnual) * paymentFrequencyToPaymentsPerYear(PaymentFrequencyT::SemiAnnual)) == 12);
    REQUIRE((paymentFrequencyToMonths(PaymentFrequencyT::Quarterly) * paymentFrequencyToPaymentsPerYear(PaymentFrequencyT::Quarterly)) == 12);
    REQUIRE((paymentFrequencyToMonths(PaymentFrequencyT::Monthly) * paymentFrequencyToPaymentsPerYear(PaymentFrequencyT::Monthly)) == 12);
  }
}
TEST_CASE("date/partial matching works") {
  SECTION("vanilla dates behave like ==") {
    date d(2015, 5, 15);
    REQUIRE(dateMatch(d, d));
    date d2(d + days(1));
    REQUIRE(!dateMatch(d, d2));
    REQUIRE(!dateMatch(d2, d));
  }
  SECTION("year-based generators behave like get_date") {
    SECTION("last day of the week in month") {
      last_day_of_the_week_in_month lwdm(Monday,Jan);
      date d = lwdm.get_date(2002);
      REQUIRE(dateMatch(d, lwdm));
      REQUIRE(dateMatch(lwdm, d));
      d += days(1);
      REQUIRE(!dateMatch(d, lwdm));
      REQUIRE(!dateMatch(lwdm, d));
    }
    SECTION("first day of the week in month") {
      first_day_of_the_week_in_month fdm(Monday,Jan);
      date d = fdm.get_date(2002);
      REQUIRE(dateMatch(d, fdm));
      REQUIRE(dateMatch(fdm, d));
      d += days(1);
      REQUIRE(!dateMatch(d, fdm));
      REQUIRE(!dateMatch(fdm, d));
    }
    SECTION("nth day of the week in month") {
      typedef nth_day_of_the_week_in_month nth_dow;
      nth_dow ndm(nth_dow::third, Monday,Jan);
      date d = ndm.get_date(2002);
      REQUIRE(dateMatch(d, ndm));
      REQUIRE(dateMatch(ndm, d));
      d += days(1);
      REQUIRE(!dateMatch(d, ndm));
      REQUIRE(!dateMatch(ndm, d));
    }
    SECTION("partial date") {
      partial_date pd(1,Jan);
      date d = pd.get_date(2002);
      REQUIRE(dateMatch(d, pd));
      REQUIRE(dateMatch(pd, d));
      d += days(1);
      REQUIRE(!dateMatch(d, pd));
      REQUIRE(!dateMatch(pd, d));
    }
  }
  SECTION("weekday matching behaves like day_of_week") {
    date d(2002,Jan,10);
    greg_weekday wd(d.day_of_week());
    REQUIRE(dateMatch(d, wd));
    REQUIRE(dateMatch(wd, d));
    d += days(1);
    REQUIRE(!dateMatch(d, wd));
    REQUIRE(!dateMatch(wd, d));
  }
}
