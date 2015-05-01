#pragma once

#include "boost/date_time/gregorian/gregorian.hpp"

namespace logiql {

  using namespace boost::gregorian;

  typedef std::pair<boost::gregorian::date,double> CashFlowT;
  typedef std::vector<CashFlowT> CashFlowsT;
  enum class PaymentFrequencyT {Annual,SemiAnnual,Quarterly,Monthly};

} // namespace logiql
