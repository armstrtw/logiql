#pragma once

#include <stdexcept>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <logiql/types.hpp>
#include <logiql/data.hpp>
#include <logiql/utils/utils.hpp>


namespace logiql {
  using namespace boost::gregorian;

  template<typename BusinessDayConvention>
  class BackwardFromMaturity {
  public:
    static std::vector<date> paymentSchedule(date issue_date, date maturity_date, PaymentFrequencyT freq, const Calendar& calendar) {

      std::vector<date> ans;
      int freq_in_months = 12 / paymentFrequencyPaymentsPerYear.at(freq);
      date payment_date(maturity_date);
      int offset = 0;
      while ( (payment_date = maturity_date - months(freq_in_months * offset)) > issue_date) {
        //no push front
        ans.push_back(BusinessDayConvention::adjust(payment_date, calendar));
        ++offset;
      }
      std::reverse(ans.begin(),ans.end());
      return ans;
    }
  };

} // namespace logiql
