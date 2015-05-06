#include <stdexcept>
#include <logiql/calendar.hpp>

using namespace boost::gregorian;
using namespace logiql;

int main() {
  // use January as an example
  typedef nth_day_of_the_week_in_month ndw;
  Calendar jan({
    Saturday, Sunday, // weekends
    partial_date(1, Jan), // New Years Day
    ndw(ndw::third, Monday, Jan) // MLK day
  });

  // print business days
  std::vector<date> busDays = jan.businessDays(date(2015, 1, 1), date(2015, 1, 31));
  for ( auto d : busDays ) {
    std::cout << d.day_of_week() << " " << d << std::endl;
    if (!jan.isBusinessDay(d)) throw std::logic_error("Not a business day");
  }

  // test next/prev methods
  for (auto it = busDays.begin(); it < busDays.end(); ++it) {
    if (it > busDays.begin()) {
      if (jan.prevBusinessDay(*it) != *(it-1)) {
        throw std::logic_error("Prev business day doesn't match");
      }
    }
    if (it < busDays.end()-1) {
      if (jan.nextBusinessDay(*it) != *(it+1)) {
        throw std::logic_error("Next business day doesn't match");
      }
    }
  }

  return 0;
}
