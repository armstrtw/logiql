#include <boost/date_time/gregorian/gregorian.hpp>
#include <logiql/instruments/fixed.coupon.bond.hpp>

using namespace logiql;
using std::cout;
using std::endl;

void printCashflows(Investment& b, date settle_date) {
  cout << "Cashflows:" << endl;
  CashFlowsT b_cfs = b.cashflows(settle_date);
  for ( auto cf : b_cfs) {
    std::cout << cf.first << " " << cf.second << std::endl;
  }
}

int main() {
  // 912828J27
  // Issue Date 02/17/15
  // Maturity Date 02/15/25
  // Coupon 2.000
  // Cpn Frequency S/A
  // Day Count ACT/ACT
  // Price 98-28+	(98.890625)
  // Settle 05/11/15
  // Street Convention	2.1262576
  // US Government Equivalent	2.1260990
  // True Yield	2.1245324
  // Equiv	1	/Yr Compound	2.1375600
  // Duration 8.872
  // Modified Duration 8.779
  // Risk 8.722
  // Convexity 0.864


  typedef nth_day_of_the_week_in_month ndw;
  Calendar us_cal({Saturday, Sunday, partial_date(1, Jan),ndw(ndw::third, Monday, Jan)});

  date issue_date(2015,2,17);
  FixedCouponBond<ActualActual,Following,BackwardFromMaturity> actual_actual(issue_date,date(2025,02,15),2.0,PaymentFrequencyT::SemiAnnual,100,us_cal);

  date this_settle_date(2015,5,11);
  cout << "years to maturity:" << actual_actual.yearsToMaturity(this_settle_date) << endl;
  cout << "accrued:" << actual_actual.accruedInterest(this_settle_date) << endl;
  //cout << "dirty price:" << actual_actual.dirtyPrice(this_settle_date,2.1262576) << endl;
  //cout << "clean price:" << actual_actual.cleanPrice(this_settle_date,2.1262576) << endl;

  cout << "mod duration:" << actual_actual.modifiedDuration(this_settle_date,2.1262576) << endl;
  cout << "yield from price: " << actual_actual.yield(this_settle_date, 98.890625) << endl;
  //cout << "yield to maturity:" << actual_actual.yield(this_settle_date, 93.6862237) << endl;
  //cout << ActualActual::yearFraction(date(2015,Feb,15),this_settle_date) << endl;

  printCashflows(actual_actual,this_settle_date);
  std::cout << "------------" << std::endl;


  return 0;
}
