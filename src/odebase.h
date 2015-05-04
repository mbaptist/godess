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


// -*- C++ -*-

#ifndef ODEBASE_H
#define ODEBASE_H


#include <string>

template <class RHSC,class TY, class TS>
class odebase
{

  //Members
protected:
  RHSC & rhs_;
  TY y0_;
  TS t0_;
  TS dt_;
  TY y_;
  int it_;

  //Accessors
public:
  TY & y();
  int & it();
  
  //Constructors
protected:
  odebase(RHSC & rhs__,
	  const TY & y0__,
	  const TS & t0__,
	  const TS & dt__);

  //Destructor
  virtual ~odebase();

  //Forbidden Constructors
private:
  odebase();
  odebase(const odebase &);

  //Iteration functions
public:
  virtual void iterate()=0;
  void operator++();
  void iterate(const int & nit);
  void iterate(const int & nit,const int & nit_output);
  void iterate(const TS & ti);
  void iterate(const TS & ti,const TS & ti_output);

  //Output function
protected:
  void output();

};


#include "odebase.C"


#endif
