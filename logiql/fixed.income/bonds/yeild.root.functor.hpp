#pragma once
#include <boost/math/tools/tuple.hpp>
#include <boost/date_time/gregorian/gregorian.hpp>

namespace logiql {
  using namespace boost::gregorian;
  using boost::math::make_tuple;

  template<class B>
  class YeildRootFunctor {
    const B& b_;
    date settle_date_;
    double p_;
  public:
    YeildRootFunctor(const B& b, date settle_date, double price) : b_(b), settle_date_(settle_date), p_(price) {}
    boost::math::tuple<double, double> operator()(double y) { // y is estimate so far.
      return boost::math::make_tuple(b_.cleanPrice(settle_date_,y) - p_, // return both f(x)
                                     -b_.duration(settle_date_,y));  // and f'(x)
    }
  };

} // namespace logiql
