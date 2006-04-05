

#include "odebase.h"

#include "runge_kutta_4.h"

#include <string>

template <class RHSC,class TY,class TS> 
adams_bashford_4<RHSC,TY,TS>::adams_bashford_4(RHSC & rhs__,
					   const TY & y0__,
					   const TS & t0__,
					   const TS & dt__):
  odebase<RHSC,TY,TS>(rhs__,y0__,t0__,dt__),
  fm1_(y0_),
  fm2_(y0_),
  fm3_(y0_)
{
  solvefirst();
}

template <class RHSC,class TY,class TS>
adams_bashford_4<RHSC,TY,TS>::~adams_bashford_4()
{
}

template <class RHSC,class TY,class TS>
void adams_bashford_4<RHSC,TY,TS>::iterate()
{
  double a(55.*dt_/24.);
  double b(59.*dt_/24.);
  double c(37.*dt_/24.);
  double d(9.*dt_/24.);
  TY f0_(rhs_(y0_,t0_));
  y_=y0_;
  TY aux=f0_;
  aux*=a;
  y_+=aux;
  aux=fm1_;
  aux*=b;
  y_-=aux;
  aux=fm2_;
  aux*=c;
  y_+=aux;
  aux=fm3_;
  aux*=d;
  y_-=aux;
  ++it_;
  t0_+=dt_;
  fm3_=fm2_;
  fm2_=fm1_;
  fm1_=f0_;
  y0_=y_;
}


template <class RHSC,class TY,class TS>
void adams_bashford_4<RHSC,TY,TS>::solvefirst()
{
  fm3_=rhs_(y0_,t0_);
  runge_kutta_4<RHSC,TY,TS> solverfirst(rhs_,y0_,t0_,dt_);
  ++solverfirst;
  fm2_=rhs_(solverfirst.y(),t0_);
  ++it_;
  t0_+=dt_;
  ++solverfirst;
  fm1_=rhs_(solverfirst.y(),t0_);
  ++it_;
  t0_+=dt_;
  ++solverfirst;
  y0_=solverfirst.y();
  ++it_;
  t0_+=dt_;
}
