#pragma once

#include <stdexcept>
#include <logiql/simple.types.hpp>
#include <logiql/schedule.generation.hpp>
#include <logiql/businessday.policies.hpp>
#include <logiql/daycount.policies.hpp>
#include <logiql/coupon.policies.hpp>

namespace logiql {
  using namespace boost::gregorian;

  class Investment {
  public:
    virtual CashFlowsT cashflows() const = 0; // posibly with start date arg?
  };

  template<class DayCounter,
           class BusinessDayConvention,
           class CalendarGeneration,
           template<class> class CouponCalculationPolicy>
  class FixedCouponBond : public Investment {
    const date issue_date_;
    const date maturity_date_;
    const double coupon_;
    const PaymentFrequencyT payment_frequency_;
    const double redeption_value_;
  public:
    FixedCouponBond(date issue_date, date maturity_date, double coupon, PaymentFrequencyT payment_frequency, double redeption_value):
      issue_date_(issue_date), maturity_date_(maturity_date), coupon_(coupon), payment_frequency_(payment_frequency), redeption_value_(redeption_value) {}
    virtual CashFlowsT cashflows() const override {
      std::vector<date> paymentDates = CalendarGeneration::paymentSchedule(issue_date_, maturity_date_, payment_frequency_);
      CashFlowsT ans;
      for(int i = 0; i < paymentDates.size(); ++i) {
        date accrual_start = i > 0 ? paymentDates[i - 1] : issue_date_;
        date accrual_end = paymentDates[i];
        double payment = CouponCalculationPolicy<DayCounter>::paymentCalculation(redeption_value_, coupon_, payment_frequency_, accrual_start, accrual_end);
        ans.push_back({ paymentDates[i], payment });
      }
      // last date add in principal
      ans.back().second = ans.back().second + redeption_value_;
      return ans;
    }
  };

  class ZeroCouponBond : public Investment {
    const date issue_date_;
    const date maturity_date_;
    const double redeption_value_;
  public:
    ZeroCouponBond(date issue_date, date maturity_date, double redeption_value):
      issue_date_(issue_date),maturity_date_(maturity_date), redeption_value_(redeption_value) {}
    virtual CashFlowsT cashflows() const override {
      return CashFlowsT { { maturity_date_, redeption_value_} };
    }
  };

}  // end namespace logiql {
