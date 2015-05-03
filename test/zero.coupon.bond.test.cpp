#include "boost/date_time/gregorian/gregorian.hpp"
#include <logiql/bonds.hpp>

using namespace logiql;


int main() {
  ZeroCouponBond zero(date(2000,1,1),date(2015,12,31),100);
  CashFlowsT zero_cfs = zero.cashflows();
  for ( auto cf : zero_cfs) std::cout << cf.first << " " << cf.second << std::endl;
  return 0;
}
