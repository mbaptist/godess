// -*- C++ -*-
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



//////////
//
//ODE.H
//Manuel Baptista, 26/06/2003
//Last modified, 31/01/2004
//
//Description:
// 
//Solves the 1st order ode d_t x(t) = f(x(t),t) by several methods
//
//Usage:
//
//1) Create a problem class (P). This class must have the following acessors:
//    double& get_dt() - 
//    double& get_tn()
//    int& get_it()
//    T& get_yn()
//    T rhs(cdVecArray3d& y,double& t)
//and a private method to provide the initial condition.
//2) Declare a object of class odesolver<P,T,M>, where P is the problem class,
//T the type used in ODE and M the method used. 
//3) Instatiate the problem, let's say problem_obj
//4) Instantiate the odesolver object, let's say odesolver_obj
//5) Use odesolver_obj.iterate() as you please. 
//
//////////

#ifndef ODE_H
#define ODE_H

#include<iostream>

#include<string>

using std::string;

//ODESOLVER_DATA
//DECLARATION (IMPLEMENTATION INLINE)
//This class is inherited by the methods' classes below.
//The latter classes provide the problem to the constructor of
//the present class.
template <class P,class T> class odesolver_data
{
 public:
  //constructor
  odesolver_data(P & problem_):
    problem(problem_),    
    dt(problem.get_dt()),
    tn(problem.get_tn()),
    it(problem.get_it()),
    yn(problem.get_yn()){};
  //destructor
  ~odesolver_data(){};
 protected:
  //Problem
  P& problem;
 protected:
  //Data References
  double & dt;//time dt
  double & tn;//current time
  int & it;//current iteration
  T & yn;//current value
};


//ODESOLVER
//DECLARATION(IMPLEMENTATION INLINE) 
template <class P,class T,class M> class odesolver: public M
{
  using M::tn;
  using M::dt;
  using M::it;
  using M::method_iterate;
 public:
  //constructors
  odesolver(P & problem_):M(problem_){};
  //destructor
  ~odesolver(){};
  //Iterate
  void iterate()
    {
      method_iterate();
      tn += dt;
      ++it;
    };
};


//ODESOLVER METHODS (M classes)
//DECLARATION
//These classes are inherited by the class odesolver, one at a time,
//as specified in the third template argument of odesolver.

//Explicit euler method
template <class P,class T> class explicit_euler: public odesolver_data<P,T>
{
 protected:
  using odesolver_data<P,T>::tn;
  using odesolver_data<P,T>::dt;
  using odesolver_data<P,T>::it;
  using odesolver_data<P,T>::problem;
 public:
  explicit_euler(P& problem_):
    odesolver_data<P,T>(problem_){};
  ~explicit_euler(){};
  void method_iterate();
};
//Second order Runge-Kutta method
template <class P,class T> class runge_kutta_2: public odesolver_data<P,T>
{
 protected:
  using odesolver_data<P,T>::tn;
  using odesolver_data<P,T>::dt;
  using odesolver_data<P,T>::it;
  using odesolver_data<P,T>::problem;
 public:
  runge_kutta_2(P& problem_):
    odesolver_data<P,T>(problem_){};
  ~runge_kutta_2(){};
  void method_iterate(); 
};
//Fourth order Runge-Kutta method
template <class P,class T> class runge_kutta_4: public odesolver_data<P,T>
{
 protected:
  using odesolver_data<P,T>::tn;
  using odesolver_data<P,T>::dt;
  using odesolver_data<P,T>::it;
  using odesolver_data<P,T>::problem;
 public:
  runge_kutta_4(P& problem_):
    odesolver_data<P,T>(problem_){};
  ~runge_kutta_4(){};
  void method_iterate(); 
};
//Adams Bashford method
template <class P,class T> class adams_bashford: public odesolver_data<P,T>
{
 protected:
  using odesolver_data<P,T>::tn;
  using odesolver_data<P,T>::dt;
  using odesolver_data<P,T>::it;
  using odesolver_data<P,T>::problem;
 public:
  adams_bashford(P& problem_);
  ~adams_bashford(){};
  void method_iterate();
  T ynm1;
 protected:
  odesolver<P,T,runge_kutta_2<P,T> > solverfirst;
};

//ODE_METHOD METHODS
//IMPLEMENTATION
//Explicit euler method
template <class P,class T> void explicit_euler<P,T>::method_iterate()
{
  T aux=problem.rhs(yn,tn);
  aux *= dt;
  aux += yn;
  yn=aux;
}
//Second order Runge-Kutta method
template <class P,class T> void runge_kutta_2<P,T>::method_iterate()
{
  T aux1=problem.rhs(yn,tn);
  aux1*=dt;
  T aux2=yn;
  aux2 += aux1;
  double taux=tn+dt;
  aux2=problem.rhs(aux2,taux);
  aux2 *= dt;
  aux2 += aux1;
  aux2 *=.5;
  yn += aux2;
}
//Fourth order Runge-Kutta method
template <class P,class T> void runge_kutta_4<P,T>::method_iterate()
{
  T aux1=problem.rhs(yn,tn);
  aux1 *= dt;
  double taux=tn+dt/2.;
  T aux2=yn;
  aux1 /= 2;
  aux2 += aux1;
  aux2=problem.rhs(aux2,taux);
  aux2 *= dt;
  T aux3=yn;
  aux2 /= 2;
  aux3 += aux2;
  aux2 *= 2;
  aux3=problem.rhs(aux3,taux);
  aux3 *= dt;
  T aux4=yn;
  aux4 += aux3;
  aux4=problem.rhs(aux4,taux);
  aux4 *= dt;
  aux3 *= 2;
  aux4 += aux3;
  aux2 *= 2;
  aux4 += aux2;
  aux4 += aux1;
  aux4 /= 6;
  yn += aux4;
}
//Adams Bashford method
//constructor
template <class P,class T> adams_bashford<P,T>::adams_bashford(P& problem_):
    odesolver_data<P,T>(problem_),
    ynm1(yn),
    solverfirst(problem_)
{
  solverfirst.iterate();
}
//method_iterate
template <class P,class T> void adams_bashford<P,T>::method_iterate()
{
  T aux;
  aux=yn;
  yn=problem.rhs(yn,tn);
  yn *= 2;
  yn *= dt;
  yn += ynm1;
  ynm1=aux;
}



#endif
