#include "boost/date_time/gregorian/gregorian.hpp"
#include <logiql/fixed.income/bonds/zero.coupon.bond.hpp>

using namespace logiql;
using std::cout;
using std::endl;


int main() {
  // 912820US4
  // Price	93-22	(93.6862237)
  // Settle	05/11/15
  // Street Convention	1.4510000
  // Treasury Convention	1.4509873
  // True Yield	1.4510000
  // Equiv	1	/Yr Compound	1.4562635
  cout << "cusip: " << "912820US4" << endl;

  typedef nth_day_of_the_week_in_month ndw;
  Calendar us_cal({Saturday, Sunday, partial_date(1, Jan),ndw(ndw::third, Monday, Jan)});

  date issue_date(2009,11,16);
  ZeroCouponBond zero(issue_date,date(2019,11,15),100,us_cal);
  date this_settle_date(2015,5,11);
  cout << "years to maturity:" << zero.yearsToMaturity(this_settle_date) << endl;
  cout << "yield to maturity:" << zero.yield(this_settle_date, 93.6862237) << endl;
  cout << "mod duration:" << zero.modifiedDuration(this_settle_date,2.1262576) << endl;

  CashFlowsT zero_cfs = zero.cashflows();
  cout << "Cashflows:" << endl;
  for ( auto cf : zero_cfs) cout << cf.first << " " << cf.second << endl;

  return 0;
}
