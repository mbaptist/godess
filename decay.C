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
