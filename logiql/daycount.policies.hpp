#pragma once

#include <stdexcept>
#include <iostream>
#include <boost/date_time/gregorian/gregorian.hpp>

namespace logiql {

  class ActualActual {  
  public:
    static double yearFraction(boost::gregorian::date accrual_start, boost::gregorian::date accrual_end) {
      double accural_days = boost::gregorian::date_duration(accrual_end - accrual_start).days();
      double days_in_year = boost::gregorian::date_duration(boost::gregorian::date(accrual_start.year(),12,31) - boost::gregorian::date(accrual_start.year(),1,1)).days();
      return accural_days/days_in_year;
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
