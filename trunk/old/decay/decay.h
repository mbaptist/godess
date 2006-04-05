//decay problem definition

#include <iostream>

#include "ode.h"

class decay
{
 public:
  //Constructor
  decay():
    dt(1e-5){init();};
  //Destructor
  ~decay(){};
  //Accessors for ode
  double& get_dt(){return dt;}
  double& get_tn(){return tn;}
  double& get_ynp1(){return sol;}
  double& get_yn(){return sol;}
  double& get_ynm1(){return sol_old;}
  //RHS function
  double rhs(double& y,double& t);
 private:
  double dt;
  double tn;
  double sol,sol_old;
  void init();
};

class decay_exec
{
 public:
  //Constructor
  decay_exec():
    decay_obj(),
    solver(decay_obj),
    dt(decay_obj.get_dt()),
    tn(decay_obj.get_tn()),
    sol(decay_obj.get_yn()),
    sol_old(decay_obj.get_ynm1()),
    maxts(200000){};
  //Destructor
  ~decay_exec(){};
  void execute();
 private:
  decay decay_obj;
  double& dt;
  double& tn;
  double& sol,sol_old;
  int maxts;
#if 0
  odesolver<
    decay,
    double,
    //explicit_euler< decay , double >
    runge_kutta_2< decay , double >
    //runge_kutta_4< decay , double >
    //adams_bashford< decay , double >
    > solverfirst;
#endif
  odesolver<
    decay,
    double,
    //explicit_euler< decay , double >
    //runge_kutta_2< decay , double >
    adams_bashford< decay , double >
    > solver;
};
