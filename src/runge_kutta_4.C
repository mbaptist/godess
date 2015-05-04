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
