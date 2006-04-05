

#include "odebase.h"

#include "runge_kutta_2.h"

#include <string>

template <class RHSC,class TY,class TS> 
adams_bashford_2<RHSC,TY,TS>::adams_bashford_2(RHSC & rhs__,
					   const TY & y0__,
					   const TS & t0__,
					   const TS & dt__):
  odebase<RHSC,TY,TS>(rhs__,y0__,t0__,dt__),
  ym1_(y0_)
{
  solvefirst();
}

template <class RHSC,class TY,class TS>
adams_bashford_2<RHSC,TY,TS>::~adams_bashford_2()
{
}

template <class RHSC,class TY,class TS>
void adams_bashford_2<RHSC,TY,TS>::iterate()
{
  TY aux(rhs_(y0_,t0_));
  aux*=(2.*dt_);
  y_=aux;
  y_+=ym1_;
  ++it_;
  t0_+=dt_;
  ym1_=y0_;
  y0_=y_; 
}


template <class RHSC,class TY,class TS>
void adams_bashford_2<RHSC,TY,TS>::solvefirst()
{
  ym1_=y0_;
  runge_kutta_2<RHSC,TY,TS> solverfirst(rhs_,y0_,t0_,dt_);
  ++solverfirst;
  y0_=solverfirst.y();
  ++it_;
  t0_+=dt_;
}
