// -*- C++ -*-

#ifndef EXPLICIT_EULER_H
#define EXPLICIT_EULER_H

#include <string>


//Forwarding de claration of template class odebase
template <class RHSC,class TY,class TS>
class odebase;

//Explicit Euler method
template <class RHSC,class TY,class TS> 
class explicit_euler: public odebase<RHSC,TY,TS>
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
  explicit_euler(RHSC & rhs__,
		 const TY & y0__,
		 const TS & t0__,
		 const TS & dt__);

  //Destructor
  ~explicit_euler();
  //Specific iteration function for this method
  void iterate();
};


#include "explicit_euler.C"

#endif
