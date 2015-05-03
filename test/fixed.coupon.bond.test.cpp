#include <boost/date_time/gregorian/gregorian.hpp>
#include <logiql/bonds.hpp>

using namespace logiql;
using namespace boost::gregorian;

int main() {
  FixedCouponBond<ActualActual,NoAdjustment,BackwardFromMaturity> b(date(2000,1,1),date(2015,12,31),
                                                                    5.25,PaymentFrequencyT::SemiAnnual,100);
  CashFlowsT b_cfs = b.cashflows();
  for ( auto cf : b_cfs) std::cout << cf.first << " " << cf.second << std::endl;
  return 0;
}
