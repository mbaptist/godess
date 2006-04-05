//////////
//
//ODE.H
//Manuel Baptista, 26/06/2003
//
//Description:
// 
//Solves the 1st order ode d_t x(t) = f(x(t),t) by several methods
//
//Usage:
//
//1) Create a problem class (P). This class must have the following acessors:
//    double& get_dt()
//    double& get_tn()
//    T& get_ynp1()
//    T& get_yn()
//    T& get_ynm1()  //For Adams-Bashford only
//and an init() method to provide access to the initial condition.
//2) Declare a object of class odesolver<P,T,M>, where P is the problem class,
//T the type of ODE and M the method used. 
//3) Instatiate the problem, let's say problem_obj
//4) Instantiate the odesolver object, let's say odesolver_obj
//5) Use odesolver_obj.iterate(n_beg,n_end) as you please. 
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
//The latter classes provide the problem to the constructor.
template <class P,class T> class odesolver_data
{
 public:
  //constructor
  odesolver_data(P& problem_):
    problem(problem_),    
    dt(problem.get_dt()),
    tn(problem.get_tn()),
    ynp1(problem.get_ynp1()),
    yn(problem.get_yn()){};
  //destructor
  ~odesolver_data(){};
 protected:
  //Problem
  P& problem;
  //Data References
  double& dt;//time step
  double& tn;//current time
  T& ynp1;//next value
  T& yn;//current value
};



//ODESOLVER
//DECLARATION(IMPLEMENTATION INLINE) 
template <class P,class T,class M> class odesolver: public M
{
 public:
  //constructors
  odesolver(P& problem_):M(problem_){};
  //destructor
  ~odesolver(){};
  //Iterate
  void iterate(){
      method_iterate();
      tn += dt;
  };
  void iterate(int n){
    for (int i=0;i<n;i++){
      method_iterate();
      tn += dt;
    }
  };
  void iterate(int n_beg,int n_end){
    for (int i=n_beg;i<n_end;i++){
      method_iterate();
      tn += dt;
    }
  };
};



//ODESOLVER METHODS (M classes)
//DECLARATION
//These classes are inherited by the class ode_method, one at a time,
//as specified in the second template argument of ode_method.
//The last class provide the problem to the constructors.
//explicit euler method
template <class P,class T> class explicit_euler: public odesolver_data<P,T>
{
 public:
  explicit_euler(P& problem_):
    odesolver_data<P,T>(problem_){};
  ~explicit_euler(){};
  void method_iterate();
};
//Second order Runge-Kutta method
template <class P,class T> class runge_kutta_2: public odesolver_data<P,T>
{
 public:
  runge_kutta_2(P& problem_):
    odesolver_data<P,T>(problem_){};
  ~runge_kutta_2(){};
  void method_iterate(); 
};
//Fourth order Runge-Kutta method
template <class P,class T> class runge_kutta_4: public odesolver_data<P,T>
{
 public:
  runge_kutta_4(P& problem_):
    odesolver_data<P,T>(problem_){};
  ~runge_kutta_4(){};
  void method_iterate(); 
};
//Adams Bashford method
template <class P,class T> class adams_bashford: public odesolver_data<P,T>
{
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
  ynp1=yn+dt*problem.rhs(yn,tn);
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
  ynp1 += aux2;
}
//Fourth order Runge-Kutta method
template <class P,class T> void runge_kutta_4<P,T>::method_iterate()
{
  T aux1=problem.rhs(yn,tn);
  aux1 *= dt;
  double taux=tn+dt/2.;
  T aux2=yn+aux1/2.;
  aux2=problem.rhs(aux2,taux);
  aux2 *= dt;
  T aux3=yn+aux2/2.;
  aux3=problem.rhs(aux3,taux);
  aux3 *= dt;
  T aux4=yn+aux3;
  aux4=problem.rhs(aux4,taux);
  aux4 *= dt;
  aux4 += 2*aux3;
  aux4 += 2*aux2;
  aux4 += aux1;
  aux4 /= 6;
  ynp1 += aux4;
}
//Adams Bashford method
//constructor
template <class P,class T> adams_bashford<P,T>::adams_bashford(P& problem_):
    odesolver_data<P,T>(problem_),
    ynm1(yn),
    solverfirst(problem_)
{
  ynm1=yn;
  solverfirst.iterate();
}
//method_iterate
template <class P,class T> void adams_bashford<P,T>::method_iterate()
{
  T aux=yn;
  ynp1=problem.rhs(yn,tn);
  ynp1 *= 2;
  ynp1 *= dt;
  ynp1 += ynm1;
  ynm1=aux;
}



#endif
