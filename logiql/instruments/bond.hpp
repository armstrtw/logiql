#pragma once

#include <stdexcept>
#include <logiql/utils/utils.hpp>
#include <logiql/calendar/calendar.hpp>
#include <logiql/instruments/instrument.hpp>

namespace logiql {
  using namespace boost::gregorian;

  class Bond : public Investment {
  public:
    // these are const.  it's fine for them to be public
    const date issue_date;
    const date maturity_date;
    const double redeption_value;
    const Calendar& calendar;

    Bond(date issue_date_, date maturity_date_, double redeption_value_, const Calendar& calendar_):
      issue_date(issue_date_),maturity_date(maturity_date_), redeption_value(redeption_value_), calendar(calendar_) {}

    virtual double accruedInterest(date settle_date) const = 0;
    virtual double cleanPrice(date settle_date, double yield) const = 0;
    virtual double dirtyPrice(date settle_date, double yield) const = 0;
    virtual double yield(date settle_date, double clean_price) const = 0;
    virtual double macaulayDuration(date settle_date, double yield) const = 0;
    virtual double modifiedDuration(date settle_date, double yield) const = 0;
    double daysToMaturity(date settle_date) const {
      return julianDiff(settle_date,maturity_date);
    }
    double yearsToMaturity(date settle_date) const {
      return daysToMaturity(settle_date)/365;
    }
    void checkValidSettle(date settle_date) const {
      if(settle_date > maturity_date) throw std::range_error("settle_date > maurity_date.");
    }
  };

}  // end namespace logiql {
