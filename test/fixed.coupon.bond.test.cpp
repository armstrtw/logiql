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
  FixedCouponBond<ActualActual,NoAdjustment,BackwardFromMaturity> actual_actual(date(2000,1,1),date(2015,12,31),5.25,PaymentFrequencyT::SemiAnnual,100);
  printCashflows(actual_actual);

  FixedCouponBond<Actual365Fixed,NoAdjustment,BackwardFromMaturity> actual_365(date(2000,1,1),date(2015,12,31),5.25,PaymentFrequencyT::SemiAnnual,100);
  printCashflows(actual_365);
  return 0;
}
