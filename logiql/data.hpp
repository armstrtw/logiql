#pragma once

#include <map>
#include <logiql/types.hpp>

namespace logiql {

  const std::map<PaymentFrequencyT, int> paymentFrequencyPaymentsPerYear {
    {PaymentFrequencyT::Annual, 1},
    {PaymentFrequencyT::SemiAnnual, 2},
    {PaymentFrequencyT::Quarterly, 4},
    {PaymentFrequencyT::Monthly, 12}
  };

} // namespace logiql
