#include <iostream>
#include "boost/date_time/gregorian/gregorian.hpp"

using namespace std;
using namespace boost::gregorian;

int main () {
  //date_period days_in_year(date(2008,1,1),date(2008,12,31));
  date_duration days_in_year = date(2008,12,31) - date(2008,1,1);
  //cout << days_in_year.length() << endl;
  cout << days_in_year.days() << endl;
  cout << static_cast<double>(days_in_year.days()) << endl;

  return 0;
}
