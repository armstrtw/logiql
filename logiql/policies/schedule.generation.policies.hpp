#pragma once

#include <stdexcept>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <logiql/simple.types.hpp>
#include <logiql/logiql.utils.hpp>

namespace logiql {
  using namespace boost::gregorian;

  class BackwardFromMaturity {
  public:
    static std::vector<date> paymentSchedule(date issue_date, date maturity_date, PaymentFrequencyT freq) {

      std::vector<date> ans;
      int freq_in_months = paymentFrequencyToMonths(freq);
      date payment_date(maturity_date);
      int offset = 0;
      while ( (payment_date = maturity_date - months(freq_in_months * offset)) > issue_date) {
        //no push front        
        ans.push_back(payment_date);
        ++offset;
      }
      std::reverse(ans.begin(),ans.end());
      return ans;
    }
  };

} // namespace logiql
