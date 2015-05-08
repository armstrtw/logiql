#pragma once

#include <stdexcept>
#include <logiql/simple.types.hpp>
#include <logiql/schedule.generation.hpp>
#include <logiql/businessday.policies.hpp>
#include <logiql/daycount.policies.hpp>
#include <logiql/logiql.utils.hpp>

namespace logiql {
  using namespace boost::gregorian;

  template<class DayCounter>
  class RegularCoupon {
  public:
    static double paymentCalculation(double face_value, double coupon, PaymentFrequencyT freq, date accrual_start, date accrual_end) {
      return face_value * coupon / 100 / static_cast<double>(paymentFrequencyToPaymentsPerYear(freq));
    }
  };

  template<class DayCounter>
  class CouponBasedOnCalendar {
  public:
    static double paymentCalculation(double face_value, double coupon, PaymentFrequencyT freq, date accrual_start, date accrual_end) {
      return face_value * coupon / 100 * DayCounter::yearFraction(accrual_start,accrual_end);
    }
  };
} // namespace logiql
