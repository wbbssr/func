#pragma once
#include "EvaluationFunctor.hpp"
#include <cmath>
#define FUNC(x) (exp(x))
#define FUNCNAME "(exp(x))"

class MyFunction final : public EvaluationFunctor<double,double>
{
public:
  double operator()(double x) override { return FUNC(x); }
  double deriv(double x) override
  {
    return FUNC(x);
  }
  double deriv2(double x) override
  {
    return FUNC(x);
  }
  double deriv3(double x) override
  {
    return FUNC(x);
  }
};
