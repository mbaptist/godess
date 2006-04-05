// -*- C++ -*-

#ifndef RUNGE_KUTTA_2_H
#define RUNGE_KUTTA_2_H

#include <string>


//Forwarding de claration of template class odebase
template <class RHSC,class TY,class TS>
class odebase;

//Explicit Euler method
template <class RHSC,class TY,class TS> 
class runge_kutta_2: public odebase<RHSC,TY,TS>
{
 private:
  using odebase<RHSC,TY,TS>::rhs_;
  using odebase<RHSC,TY,TS>::y0_;
  using odebase<RHSC,TY,TS>::t0_;
  using odebase<RHSC,TY,TS>::dt_;
  using odebase<RHSC,TY,TS>::y_;
  using odebase<RHSC,TY,TS>::it_;
public:
  using odebase<RHSC,TY,TS>::y;
  using odebase<RHSC,TY,TS>::it;
  using odebase<RHSC,TY,TS>::iterate;
 public:
  //Constructors
  runge_kutta_2(RHSC & rhs__,
		const TY & y0__,
		const TS & t0__,
		const TS & dt__);

  //Destructor
  ~runge_kutta_2();
  //Specific iteration function for this method
  void iterate();
};


#include "runge_kutta_2.C"

#endif
