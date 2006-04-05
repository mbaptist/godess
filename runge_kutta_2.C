

#include "odebase.h"

#include <string>

template <class RHSC,class TY,class TS> 
runge_kutta_2<RHSC,TY,TS>::runge_kutta_2(RHSC & rhs__,
					 const TY & y0__,
					 const TS & t0__,
					 const TS & dt__):
  odebase<RHSC,TY,TS>(rhs__,y0__,t0__,dt__)
{
}

template <class RHSC,class TY,class TS>
runge_kutta_2<RHSC,TY,TS>::~runge_kutta_2()
{
}

template <class RHSC,class TY,class TS>
void runge_kutta_2<RHSC,TY,TS>::iterate()
{
  TY aux1(rhs_(y0_,t0_));
  aux1*=dt_;
  TY aux2(rhs_(y0_+aux1,t0_+dt_));
  aux2*=dt_;

  //  y_=y0_+.5*(aux1+aux2);

  y_=aux1;
  y_+=aux2;
  y_*=.5;
  y_+=y0_;

  ++it_;
  t0_+=dt_;
  y0_=y_;
}
