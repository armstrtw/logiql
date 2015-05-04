#include <boost/date_time/gregorian/gregorian.hpp>
#include <logiql/bonds.hpp>

using namespace logiql;
using namespace boost::gregorian;

void printCashflows(Investment& b) {
    CashFlowsT b_cfs = b.cashflows();
    for ( auto cf : b_cfs) {
      std::cout << cf.first << " " << cf.second << std::endl;
    }
}

int main() {
  FixedCouponBond<ActualActual,NoAdjustment,BackwardFromMaturity,RegularCoupon> actual_actual(date(2000,1,1),date(2015,12,31),5.25,PaymentFrequencyT::SemiAnnual,100);
  printCashflows(actual_actual);
  std::cout << "------------" << std::endl;

  FixedCouponBond<Actual365Fixed,NoAdjustment,BackwardFromMaturity,RegularCoupon> actual_365(date(2000,1,1),date(2015,12,31),5.25,PaymentFrequencyT::SemiAnnual,100);
  printCashflows(actual_365);
  std::cout << "------------" << std::endl;

  FixedCouponBond<Actual365Fixed,NoAdjustment,BackwardFromMaturity,CouponBasedOnCalendar> actual_365_calendarcoupon(date(2000,1,1),date(2015,12,31),5.25,PaymentFrequencyT::SemiAnnual,100);
  printCashflows(actual_365_calendarcoupon);
  std::cout << "------------" << std::endl;
  return 0;
}
