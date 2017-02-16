#pragma once

#include <stdexcept>
#include <boost/math/tools/roots.hpp>
#include <logiql/types.hpp>
#include <logiql/instruments/bond.hpp>
#include <logiql/utils/yeild.root.functor.hpp>
#include <logiql/policies/schedule.generation.policies.hpp>
#include <logiql/policies/businessday.policies.hpp>
#include <logiql/policies/daycount.policies.hpp>

namespace logiql {
  using namespace boost::gregorian;
  using boost::math::tools::newton_raphson_iterate;

  template<class DayCounter,
           class BusinessDayConvention,
           template<typename> class ScheduleGeneration>
  class FixedCouponBond : public Bond {
  public:
    const double coupon;
    const PaymentFrequencyT payment_frequency;
    const std::vector<date> payment_dates;

    FixedCouponBond(date issue_date_, date maturity_date_, double coupon_, PaymentFrequencyT payment_frequency_, double redeption_value_, const Calendar& calendar):
      Bond(issue_date_, maturity_date_, redeption_value_, calendar), coupon(coupon_), payment_frequency(payment_frequency_),
      payment_dates(ScheduleGeneration<BusinessDayConvention>::paymentSchedule(issue_date, maturity_date, payment_frequency, calendar)) {}
    double payment() const {
      return redeption_value * coupon / 100 / static_cast<double>(paymentFrequencyPaymentsPerYear.at(payment_frequency));
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
      int digits = std::numeric_limits<double>::digits / 2;
      return newton_raphson_iterate(YeildRootFunctor<FixedCouponBond<DayCounter,BusinessDayConvention,ScheduleGeneration> >(*this,settle_date,clean_price),
                                    coupon, // initial guess
                                    std::numeric_limits<double>::min(), // min, bound at zero for testing
                                    std::numeric_limits<double>::max(), // max
                                    digits);
    }

    virtual double macaulayDuration(date settle_date, double yield) const override {
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
    virtual double modifiedDuration(date settle_date, double yield) const override {
      checkValidSettle(settle_date);
      double k = paymentFrequencyPaymentsPerYear.at(payment_frequency);
      return macaulayDuration(settle_date, yield)/(1.0 + yield/100.0/k);
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
}  // end namespace logiql {
