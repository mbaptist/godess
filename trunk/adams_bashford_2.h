// -*- C++ -*-

#ifndef ADAMS_BASHFORD_2_H
#define ADAMS_BASHFORD_2_H

#include <string>


//Forwarding de claration of template class odebase
template <class RHSC,class TY,class TS>
class odebase;

//Explicit Euler method
template <class RHSC,class TY,class TS> 
class adams_bashford_2: public odebase<RHSC,TY,TS>
{
private:
  using odebase<RHSC,TY,TS>::rhs_;
  using odebase<RHSC,TY,TS>::y_;
  using odebase<RHSC,TY,TS>::y0_;
  using odebase<RHSC,TY,TS>::t0_;
  using odebase<RHSC,TY,TS>::dt_;
  using odebase<RHSC,TY,TS>::it_;
  TY ym1_;
public:
  using odebase<RHSC,TY,TS>::y;
  using odebase<RHSC,TY,TS>::it;
  using odebase<RHSC,TY,TS>::iterate;
 public:
  //Constructors
  adams_bashford_2(RHSC & rhs__,
		 const TY & y0__,
		 const TS & t0__,
		 const TS & dt__);

  //Destructor
  ~adams_bashford_2();
  //Specific iteration function for this method
  void iterate();

private:
  void solvefirst();

};


#include "adams_bashford_2.C"

#endif
