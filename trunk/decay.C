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

#include "godess.h"

#include <iostream>
#include <iomanip>

using namespace std;


class decay_rhs
{
public:
  decay_rhs(){};
  ~decay_rhs(){};
  double operator()(double y, double t){return -y;};
};


int main()
{
  cout << setprecision(20);
  decay_rhs decay;
  //explicit_euler<decay_rhs,double,double>
  //runge_kutta_2<decay_rhs,double,double>
  //runge_kutta_4<decay_rhs,double,double>
  //adams_bashford_2<decay_rhs,double,double>
  adams_bashford_4<decay_rhs,double,double>
    solver(decay,1.,0.,1e-4);

  solver.iterate(200,10);

}
