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


#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

//Accessors

template <class RHSC,class TY, class TS>
TY & odebase<RHSC,TY,TS>::y()
{
  return y_;
}

template <class RHSC,class TY, class TS>
int & odebase<RHSC,TY,TS>::it()
{
  return it_;
}

//Constructor
template <class RHSC,class TY, class TS>
odebase<RHSC,TY,TS>::odebase(RHSC & rhs__,
			     const TY & y0__,
			     const TS & t0__,
			     const TS & dt__):
  rhs_(rhs__),
  y0_(y0__),
  t0_(t0__),
  dt_(dt__),  
  y_(y0_),
  it_(static_cast<int>(t0_/dt_))
{
}

//Destructor
template <class RHSC,class TY, class TS>
odebase<RHSC,TY,TS>::~odebase()
{
}


//Iteration functions

//void iterate() is defined in the derived method classes

template <class RHSC,class TY, class TS>
void odebase<RHSC,TY,TS>::operator++()
{
  iterate();
}

template <class RHSC,class TY, class TS>
void odebase<RHSC,TY,TS>::iterate(const int & nit)
{
  for (int i=0;i<nit;++i)
    iterate();
}

template <class RHSC,class TY, class TS>
void odebase<RHSC,TY,TS>::iterate(const int & nit,const int & nit_output)
{
  for (int i=0;i<nit;++i)
    {
      iterate();
      if(it_%nit_output==0)
	output();
    }
}

template <class RHSC,class TY, class TS>
void odebase<RHSC,TY,TS>::iterate(const TS & ti)
{
  int nit=ti/dt_;
  iterate(nit);
} 

template <class RHSC,class TY, class TS>
void odebase<RHSC,TY,TS>::iterate(const TS & ti,const TS & ti_output)
{
  int nit=ti/dt_;
  int nit_output=ti_output/dt_;
  iterate(nit,nit_output);
}

//Output function
template <class RHSC,class TY, class TS>
void odebase<RHSC,TY,TS>::output()
{
  cout << y_ << endl;
}

