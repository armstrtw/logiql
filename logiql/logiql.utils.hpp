#pragma once

#include <boost/date_time/gregorian/gregorian.hpp>
#include <logiql/simple.types.hpp>

namespace logiql {
  using namespace boost::gregorian;

  double julianDiff(date accrual_start,date accrual_end) {
      return date_duration(accrual_end - accrual_start).days();
  }

  int paymentFrequencyToMonths(PaymentFrequencyT freq) {
    switch(freq) {
    case PaymentFrequencyT::Annual: return 12;
    case PaymentFrequencyT::SemiAnnual: return 6;
    case PaymentFrequencyT::Quarterly: return 3;
    case PaymentFrequencyT::Monthly: return 1;
    default:
      throw std::range_error("Payment frequency" + std::to_string(static_cast<int>(freq)) + " not found");
    }
    // never gets here
    return 0;
  }

  int paymentFrequencyToPaymentsPerYear(PaymentFrequencyT freq) {
    switch(freq) {
    case PaymentFrequencyT::Annual: return 1;
    case PaymentFrequencyT::SemiAnnual: return 2;
    case PaymentFrequencyT::Quarterly: return 4;
    case PaymentFrequencyT::Monthly: return 12;
    default:
      throw std::range_error("Payment frequency" + std::to_string(static_cast<int>(freq)) + " not found");
    }
    // never gets here
    return 0;
  }

  template<typename T, typename U>
  T vectorShift(const T& vec, const U shift) {
    T ans(vec);
    for(auto &v : ans) { v+= shift; }
    return ans;
  }

} // namespace logiql
