#pragma once

#include <stdexcept>

#include <logiql/simple.types.hpp>
#include <logiql/fixed.income/bonds/bond.hpp>
#include <logiql/policies/schedule.generation.policies.hpp>
#include <logiql/policies/businessday.policies.hpp>
#include <logiql/policies/daycount.policies.hpp>


namespace logiql {

  class ZeroCouponBond : public Bond {
  public:
    ZeroCouponBond(date issue_date, date maturity_date, double redeption_value, const Calendar& calendar):
      Bond(issue_date, maturity_date, redeption_value, calendar) {}
    virtual double accruedInterest(date settle_date) const override {
      checkValidSettle(settle_date);
      return 0;
    }
    virtual double cleanPrice(date settle_date, double yield) const override {
      checkValidSettle(settle_date);
      return redeption_value/pow(yield/100,yearsToMaturity(settle_date));
    }
    virtual double dirtyPrice(date settle_date, double yield) const override {
      checkValidSettle(settle_date);
      return cleanPrice(settle_date, yield);
    }
    virtual double yield(date settle_date, double clean_price) const override {
      checkValidSettle(settle_date);
      double ans = pow(redeption_value/clean_price,1/yearsToMaturity(settle_date)) - 1;
      return ans * 100;
    }
    virtual double macaulayDuration(date settle_date, double yield) const override {
      checkValidSettle(settle_date);
      return yearsToMaturity(settle_date);
    }
    virtual double modifiedDuration(date settle_date, double yield) const override {
      checkValidSettle(settle_date);
      return macaulayDuration(settle_date, yield)/(1.0 + yield/100.0);
    }
    virtual CashFlowsT cashflows() const override {
      return CashFlowsT { { maturity_date, redeption_value} };
    }
    virtual CashFlowsT cashflows(date settle_date) const override {
      checkValidSettle(settle_date);
      return CashFlowsT { { maturity_date, redeption_value} };
    }
  };

}  // end namespace logiql {
