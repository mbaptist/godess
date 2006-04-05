
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
