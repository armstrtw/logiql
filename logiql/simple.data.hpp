#pragma once

#include <map>
#include <logiql/simple.types.hpp>

namespace logiql {
  /*
  const std::map<PaymentFrequencyT, int> paymentFrequencyMonths {
    {PaymentFrequencyT::Annual, 12},
    {PaymentFrequencyT::SemiAnnual, 6},
    {PaymentFrequencyT::Quarterly, 3},
    {PaymentFrequencyT::Monthly, 1}
  };
  */

  const std::map<PaymentFrequencyT, int> paymentFrequencyPaymentsPerYear {
    {PaymentFrequencyT::Annual, 1},
    {PaymentFrequencyT::SemiAnnual, 2},
    {PaymentFrequencyT::Quarterly, 4},
    {PaymentFrequencyT::Monthly, 12}
  };

} // namespace logiql
