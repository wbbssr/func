/* Implementation of a UniformPrecomputed Lookup table with linear interpolation */
#include "UniformCubicHermiteTable.hpp"

#define IMPL_NAME UniformCubicHermiteTable
REGISTER_ULUT_IMPL(IMPL_NAME);

UniformCubicHermiteTable::UniformCubicHermiteTable(EvaluationFunctor<double,double> *func, UniformLookupTableParameters par) : UniformLookupTable(func, par)
{

  /* Base class default variables */
  m_name = STR(IMPL_NAME);
  m_order = 4;
  m_numTableEntries = 4*(m_numIntervals+1);
  m_dataSize = (unsigned) sizeof(double) * m_numTableEntries;

  /* Allocate and set table */
  m_table.reset(new double[m_numTableEntries]);
  for (int ii=0; ii<m_numIntervals; ++ii) {
    const double x = m_minArg + ii*m_stepSize;
    m_grid[ii] = x;
    const double y0 = (*mp_func)(x);
    const double m0 = mp_func->deriv(x);
    const double y1 = (*mp_func)(x+m_stepSize);
    const double m1 = mp_func->deriv(x+m_stepSize);
    m_table[4*ii]   = y0;
    m_table[4*ii+1] = m_stepSize*m0;
    m_table[4*ii+2] = -3*y0+3*y1-(2*m0+m1)*m_stepSize;
    m_table[4*ii+3] = 2*y0-2*y1+(m0+m1)*m_stepSize;
  }
}

double UniformCubicHermiteTable::operator()(double x)
{
  // nondimensionalized x position, scaled by step size
  double   dx = m_stepSize_inv*(x-m_minArg);
  // index of previous table entry
  unsigned x0  = (unsigned) dx;
  dx -= x0;
  x0 *= 4;
  // linear interpolation
  return m_table[x0]+dx*(m_table[x0+1]+dx*(m_table[x0+2]+dx*m_table[x0+3]));
}
