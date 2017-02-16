#pragma once

#include <utility>
#include <vector>
#include <boost/date_time/gregorian/gregorian.hpp>

namespace logiql {
  typedef std::pair<boost::gregorian::date,double> CashFlowT;
  typedef std::vector<CashFlowT> CashFlowsT;
  enum class PaymentFrequencyT {Annual,SemiAnnual,Quarterly,Monthly};

} // namespace logiql
