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


  template<class DayCounter,
           class BusinessDayConvention,
           class CalendarGeneration>
  class FixedCouponBond : public Bond {
  public:
    const double coupon;
    const PaymentFrequencyT payment_frequency;
    const std::vector<date> payment_dates;

    FixedCouponBond(date issue_date_, date maturity_date_, double coupon_, PaymentFrequencyT payment_frequency_, double redeption_value_):
      Bond(issue_date_, maturity_date_, redeption_value_), coupon(coupon_), payment_frequency(payment_frequency_), payment_dates(CalendarGeneration::paymentSchedule(issue_date, maturity_date, payment_frequency)) {}
    double payment() const {
      return redeption_value * coupon / 100 / static_cast<double>(paymentFrequencyToPaymentsPerYear(payment_frequency));
    }
    double paymentsRemaining(date settle_date) const {
      checkValidSettle(settle_date);
      auto next_payment_date_itr = std::upper_bound(payment_dates.begin(), payment_dates.end(),settle_date);
      return std::distance(next_payment_date_itr,payment_dates.end());
    }
    date nextPaymentDate(date settle_date) const {
      checkValidSettle(settle_date);
      auto next_payment_date_itr = std::upper_bound(payment_dates.begin(), payment_dates.end(),settle_date);
      if(next_payment_date_itr == payment_dates.end()) {
        throw std::range_error("settle_date > (maurity_date-1).");
      }
      return *next_payment_date_itr;
    }
    date previousPaymentDate(date settle_date) const {
      if(settle_date <= *payment_dates.begin()) {
        throw std::range_error("no payments have occured before this settle_date");
      }
      auto next_payment_date_itr = std::upper_bound(payment_dates.begin(), payment_dates.end(),settle_date);
      return *--next_payment_date_itr;
    }

    virtual double accruedInterest(date settle_date) const override {
      checkValidSettle(settle_date);
      if(settle_date < issue_date) {
        return 0; // or throw
      }
      date accrual_start_date = settle_date <= *payment_dates.begin() ? issue_date : previousPaymentDate(settle_date);
      return coupon * DayCounter::yearFraction(accrual_start_date,settle_date);
    }
    virtual double cleanPrice(date settle_date, double yield) const override {
      checkValidSettle(settle_date);
      return dirtyPrice(settle_date, yield) - accruedInterest(settle_date);
    }
    virtual double dirtyPrice(date settle_date, double yield) const override {
      checkValidSettle(settle_date);
      double ans(0);
      CashFlowsT cfs(cashflows(settle_date));
      for (auto cf : cfs) {
        double years_from_settle = julianDiff(settle_date,cf.first)/365;
        ans += cf.second / pow((1 + yield/100),years_from_settle);
      }
      return ans;
    }
    virtual double yield(date settle_date, double clean_price) const override {
      checkValidSettle(settle_date);
      throw std::logic_error("not implemented.");
      return 0;
    }

    virtual double duration(date settle_date, double yield) const override {
      checkValidSettle(settle_date);
      CashFlowsT cfs = cashflows(settle_date);
      double days_in_year(365);
      double npv(0),macd(0);
      for(auto cf : cfs) {
        macd += julianDiff(settle_date,cf.first)/days_in_year * cf.second;
        npv += cf.second;
      }
      return macd/npv;
    }
    virtual CashFlowsT cashflows() const override {
      CashFlowsT ans(payment_dates.size());
      for(int i = 0; i < payment_dates.size(); ++i) {
        ans[i] = std::make_pair(payment_dates[i], payment());
      }
      // last date add in principal
      ans.back().second = ans.back().second + redeption_value;
      return ans;
    }

    virtual CashFlowsT cashflows(date settle_date) const override {
      checkValidSettle(settle_date);
      CashFlowsT ans;
      auto next_payment_date_itr = std::upper_bound(payment_dates.begin(), payment_dates.end(),settle_date);
      if(next_payment_date_itr == payment_dates.end()) { throw std::range_error("settle_date > (maurity_date-1)."); }
      for(;next_payment_date_itr != payment_dates.end(); ++next_payment_date_itr) {
        ans.push_back({*next_payment_date_itr, payment()});
      }
      // last date add in principal
      ans.back().second = ans.back().second + redeption_value;
      return ans;
    }

  };


  class ZeroCouponBond : public Bond {
  public:
    ZeroCouponBond(date issue_date, date maturity_date, double redeption_value):
      Bond(issue_date, maturity_date, redeption_value) {}
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
    virtual double duration(date settle_date, double yield) const override {
      checkValidSettle(settle_date);
      return daysToMaturity(settle_date)/365;
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
