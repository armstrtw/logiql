#pragma once

#include <logiql/types.hpp>

namespace logiql {

class Investment {
public:
  virtual CashFlowsT cashflows() const                 = 0;
  virtual CashFlowsT cashflows(date settle_date) const = 0;
};

} // end namespace logiql
