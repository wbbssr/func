#pragma once
#include "EvaluationFunctor.hpp"
#include <cmath>
#define FUNC(x) (1/(1+exp(-x)))
#define FUNCNAME "(1/(1+exp(-x)))"

class MyFunction final : public EvaluationFunctor<double,double>
{
public:
  double operator()(double x) override { return FUNC(x); }
  double deriv(double x) override
  {
    return FUNC(x)*(1-FUNC(x));
  }
  double deriv2(double x) override
  {
    return FUNC(x)*(1-FUNC(x))*(1-2*FUNC(x));
  }
  double deriv3(double x) override
  {
    return FUNC(x)*(1-FUNC(x))*(6*FUNC(x)*FUNC(x)-6*FUNC(x)+1);
  }
};
