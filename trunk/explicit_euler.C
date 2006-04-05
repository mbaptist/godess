

#include "odebase.h"

#include <string>

template <class RHSC,class TY,class TS> 
explicit_euler<RHSC,TY,TS>::explicit_euler(RHSC & rhs__,
					   const TY & y0__,
					   const TS & t0__,
					   const TS & dt__):
  odebase<RHSC,TY,TS>(rhs__,y0__,t0__,dt__)
{
}

template <class RHSC,class TY,class TS>
explicit_euler<RHSC,TY,TS>::~explicit_euler()
{
}

template <class RHSC,class TY,class TS>
void explicit_euler<RHSC,TY,TS>::iterate()
{
  y_=rhs_(y0_,t0_);
  y_*=dt_;
  y_+=y0_;
  ++it_;
  t0_+=dt_;
  y0_=y_;
}
