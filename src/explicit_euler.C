/*

Copyright 2004,2005,2006 Manuel Baptista

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
