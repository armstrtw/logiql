#include <logiql/simple.types.hpp>

using namespace boost::gregorian;
using namespace logiql;


int main() {
  for (int i = 2010; i <= 2016; ++i) {
    observed_partial_date xmas(25,Dec);
    std::cout << xmas.get_date(i) << std::endl;
  }
  return 0;
}
