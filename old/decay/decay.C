//decay implementation

#include <iostream>

#include <cmath>

#include "decay.h"

#include "ode.h"

using namespace std;

void decay::init()
{
  tn=0.;
  sol=1.;
  cout << "t=" << tn << "     sol=" << sol << endl;
}

double decay::rhs(double& y, double& t)
{
  return -y;
}

void decay_exec::execute()
{ 
  //sol_old=sol;
  //solverfirst.iterate();
  //double tsol=exp(-tn);
  //cout << "t=" << tn << "  sol=" << sol << "  tsol=" << tsol << endl;
  for(int i=2;i<=maxts;i++)
    {
      solver.iterate();
      double tsol=exp(-tn);
      cout << "t=" << tn << "  sol=" << sol << "  tsol=" << tsol << endl;
    }
}
