// -*- C++ -*-
/*

Copyright 2004-2015 Manuel Baptista

This file is part of GODESS

GODESS is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

GODESS is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

*/



#ifndef ADAMS_BASHFORD_4_H
#define ADAMS_BASHFORD_4_H

#include <string>


//Forwarding de claration of template class odebase
template <class RHSC,class TY,class TS>
class odebase;

//Explicit Euler method
template <class RHSC,class TY,class TS> 
class adams_bashford_4: public odebase<RHSC,TY,TS>
{
private:
  using odebase<RHSC,TY,TS>::rhs_;
  using odebase<RHSC,TY,TS>::y_;
  using odebase<RHSC,TY,TS>::y0_;
  using odebase<RHSC,TY,TS>::t0_;
  using odebase<RHSC,TY,TS>::dt_;
  using odebase<RHSC,TY,TS>::it_;
  TY fm1_;
  TY fm2_;
  TY fm3_;
public:
  using odebase<RHSC,TY,TS>::y;
  using odebase<RHSC,TY,TS>::it;
  using odebase<RHSC,TY,TS>::iterate;
 public:
  //Constructors
  adams_bashford_4(RHSC & rhs__,
		 const TY & y0__,
		 const TS & t0__,
		 const TS & dt__);

  //Destructor
  ~adams_bashford_4();
  //Specific iteration function for this method
  void iterate();

private:
  void solvefirst();

};


#include "adams_bashford_4.C"

#endif
