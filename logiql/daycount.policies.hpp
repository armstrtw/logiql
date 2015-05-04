#pragma once

#include <stdexcept>
#include <iostream>
#include <boost/date_time/gregorian/gregorian.hpp>

namespace logiql {

  class ActualActual {
  public:
    static double yearFraction(boost::gregorian::date accrual_start, boost::gregorian::date accrual_end) {
      // can use same year basis if:
      // start and end in same period
      // both years are non leap years
      // if dates cross a leap year / non leap year or non leap year/ leap year
      // then we need two periods w/ different year basis
      if(accrual_start.year() == accrual_end.year() ||
         boost::gregorian::gregorian_calendar::is_leap_year(accrual_start.year()) == boost::gregorian::gregorian_calendar::is_leap_year(accrual_end.year())) {
        double accural_days = boost::gregorian::date_duration(accrual_end - accrual_start).days();
        double days_in_year = boost::gregorian::gregorian_calendar::is_leap_year(accrual_start.year()) ? 366 : 365;
        return accural_days/days_in_year;
      } else {
        // need two calculation periods
        if(accrual_end.year() - accrual_start.year() > 1) {
          throw std::range_error("Need special Accrual method for coupons spanning more than 1 year.");
        }

        boost::gregorian::date p1_end(accrual_start.year(),12,31);
        double accural_days_p1 = boost::gregorian::date_duration(p1_end - accrual_start).days();
        double accural_days_p2 = boost::gregorian::date_duration(accrual_end - p1_end).days();

        double days_in_year_p1 = boost::gregorian::gregorian_calendar::is_leap_year(accrual_start.year()) ? 366 : 365;
        double days_in_year_p2 = boost::gregorian::gregorian_calendar::is_leap_year(accrual_end.year()) ? 366 : 365;

        return accural_days_p1 / days_in_year_p1 + accural_days_p2/ days_in_year_p2;
      }
    }
  };

  /*
  class Actual365 {
  public:
    double yearFraction(date accrual_start, date accrual_end) {
      const double year_basis(365);
      if(accrual_start.year() != accrual_end.year()) {
        throw std::range_error("Accrual dates not in same year.");
      }
      
      double accural_days = date_period(accrual_start,accrual_end).length();
      return accural_days/year_basis;
    }
  };
  */

} // namespace logiql
