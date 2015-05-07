#pragma once

#include <utility>
#include <vector>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <logiql/observed.partial.date.hpp>

// extend boost::gregorian to include observed_partial_date
namespace boost {
  namespace gregorian {
      typedef date_time::observed_partial_date<boost::gregorian::date> observed_partial_date;
  }
}

namespace logiql {
  typedef std::pair<boost::gregorian::date,double> CashFlowT;
  typedef std::vector<CashFlowT> CashFlowsT;
  enum class PaymentFrequencyT {Annual,SemiAnnual,Quarterly,Monthly};

} // namespace logiql
