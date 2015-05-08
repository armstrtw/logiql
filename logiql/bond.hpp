#pragma once

#include <stdexcept>

#include <logiql/simple.types.hpp>
#include <logiql/schedule.generation.hpp>
#include <logiql/businessday.policies.hpp>
#include <logiql/daycount.policies.hpp>

namespace logiql {
  using namespace boost::gregorian;

  class Investment {
  public:
    virtual CashFlowsT cashflows() const = 0;
    virtual CashFlowsT cashflows(date settle_date) const = 0;
  };

  class Bond : public Investment {
  public:
    // these are const.  it's fine for them to be public
    const date issue_date;
    const date maturity_date;
    const double redeption_value;

    Bond(date issue_date_, date maturity_date_, double redeption_value_):
      issue_date(issue_date_),maturity_date(maturity_date_), redeption_value(redeption_value_) {}

    virtual double accruedInterest(date settle_date) const = 0;
    virtual double cleanPrice(date settle_date, double yield) const = 0;
    virtual double dirtyPrice(date settle_date, double yield) const = 0;
    virtual double yield(date settle_date, double clean_price) const = 0;
    virtual double duration(date settle_date, double yield) const = 0;
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
