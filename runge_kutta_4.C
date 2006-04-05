

#include "odebase.h"

#include <string>

template <class RHSC,class TY,class TS> 
runge_kutta_4<RHSC,TY,TS>::runge_kutta_4(RHSC & rhs__,
					 const TY & y0__,
					 const TS & t0__,
					 const TS & dt__):
  odebase<RHSC,TY,TS>(rhs__,y0__,t0__,dt__)
{
}

template <class RHSC,class TY,class TS>
runge_kutta_4<RHSC,TY,TS>::~runge_kutta_4()
{
}

template <class RHSC,class TY,class TS>
void runge_kutta_4<RHSC,TY,TS>::iterate()
{ 
  TY aux1(rhs_(y0_,t0_));
  aux1*=dt_;
  TY aux2(rhs_(y0_+aux1*.5,t0_+.5*dt_));
  aux2*=dt_;
  TY aux3(rhs_(y0_+aux2*.5,t0_+.5*dt_));
  aux3*=dt_;
  TY aux4(rhs_(y0_+aux3,t0_+dt_));
  aux4*=dt_;
  y_=y0_+(aux1+aux2*2.+aux3*2.+aux4)/6.;
  ++it_;
  t0_+=dt_;
  y0_=y_;
}
