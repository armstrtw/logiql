#pragma once

#include <stdexcept>
#include <iostream>
#include <boost/date_time/gregorian/gregorian.hpp>

namespace logiql {
  using namespace boost::gregorian;

  class DayCounter {
  public:
    static double julianDiff(date accrual_start,date accrual_end) {
      return date_duration(accrual_end - accrual_start).days();
    }

    static int daysInYear(greg_year y) {
      return gregorian_calendar::is_leap_year(y) ? 366 : 365;
    }

    static void checkAccrualDates(date accrual_start,date accrual_end) {
      if(accrual_start > accrual_end) {
        throw std::range_error("Accrual Start date > Accrual End Date.");
      }
    }
  };

  class ActualActual : DayCounter {
  public:
    static double yearFraction(date accrual_start, date accrual_end) {
      checkAccrualDates(accrual_start,accrual_end);

      if(accrual_end.year() - accrual_start.year() > 1) {
        throw std::range_error("Need special Accrual method for coupons spanning more than 1 year.");
      }

      // can use same year basis if:
      // start and end in same period
      // both years have same number of days
      // if dates cross a leap year / non leap year or non leap year/ leap year
      // then we need two periods each with different year basis
      if(accrual_start.year() == accrual_end.year() || daysInYear(accrual_start.year())==daysInYear(accrual_end.year())) {
        double accural_days = julianDiff(accrual_start,accrual_end);
        double days_in_year = daysInYear(accrual_start.year());
        return accural_days/days_in_year;
      } else {
        date p1_end(accrual_start.year(),12,31);
        double accural_days_p1 = julianDiff(accrual_start,p1_end);
        double accural_days_p2 = julianDiff(p1_end,accrual_end);

        double days_in_year_p1 = daysInYear(accrual_start.year());
        double days_in_year_p2 = daysInYear(accrual_end.year());

        return accural_days_p1 / days_in_year_p1 + accural_days_p2 / days_in_year_p2;
      }
    }
  };


  template<int N>
  class ActualFixed : DayCounter {
  public:
    static double yearFraction(date accrual_start, date accrual_end) {
      checkAccrualDates(accrual_start,accrual_end);
      return julianDiff(accrual_start,accrual_end)/static_cast<double>(N);
    }
  };

  typedef ActualFixed<365> Actual365Fixed;
  typedef ActualFixed<364> Actual364Fixed;
  typedef ActualFixed<360> Actual360Fixed;

} // namespace logiql
