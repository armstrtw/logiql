#pragma once

#include <stdexcept>
#include <boost/date_time/gregorian/gregorian.hpp>
#include <logiql/simple.types.hpp>

namespace logiql {

  
  int PaymentFrequencyToMonths(PaymentFrequencyT freq) {
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

  class BackwardFromMaturity {
  public:
    static std::vector<boost::gregorian::date> paymentSchedule(boost::gregorian::date issue_date, boost::gregorian::date maturity_date, PaymentFrequencyT freq) {

      std::vector<boost::gregorian::date> ans;
      int freq_in_months = PaymentFrequencyToMonths(freq);
      boost::gregorian::date payment_date(maturity_date);
      int offset = 0;
      while ( (payment_date = maturity_date - boost::gregorian::months(freq_in_months * offset)) > issue_date) {
        //no push front        
        ans.push_back(payment_date);
        ++offset;
      }
      std::reverse(ans.begin(),ans.end());
      return ans;
    }
  };

} // namespace logiql
