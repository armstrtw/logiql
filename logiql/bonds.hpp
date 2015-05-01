#pragma once

namespace logiql {

  class Investment {
  public:
    virtual CashFlowsT cashflows() const = 0; // posibly with start date arg?
  };

  class Bond : public Investment {
    date issue_date_;
    const date maturity_date_;
    double coupon_;
    PaymentFrequencyT payment_frequency_;
    double redeption_value_;
  public:
    Bond(const date& issue_date,const date& maturity_date, double coupon, PaymentFrequencyT payment_frequency, double redeption_value): issue_date_(issue_date), maturity_date_(maturity_date), coupon_(coupon), payment_frequency_(payment_frequency), redeption_value_(redeption_value) {}
    virtual CashFlowsT cashflows() const override;
  };

  class ZeroCouponBond : public Investment {
    date issue_date_;
    date maturity_date_;
    double redeption_value_;
  public:
    ZeroCouponBond(const date& issue_date,const date& maturity_date, double redeption_value): issue_date_(issue_date),maturity_date_(maturity_date), redeption_value_(redeption_value) {}
    virtual CashFlowsT cashflows() const override {
      return CashFlowsT { { maturity_date_, redeption_value_} };
    }
  };

}  // end namespace logiql {
