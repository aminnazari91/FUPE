#ifndef _Security_INFERENCE_ENGINE_
#define _Security_INFERENCE_ENGINE_

#include <stdio.h>
#include <math.h>
#include "xfuzzy.hpp"
#include "Security.hpp"

//+++++++++++++++++++++++++++++++++++++//
//  MembershipFunction MF_Security_xfl_triangle  //
//+++++++++++++++++++++++++++++++++++++//

MF_Security_xfl_triangle::MF_Security_xfl_triangle(double min,double max,double step,double *param, int length) :
ParamMembershipFunction(min,max,step) {
 this->name = "MF_Security_xfl_triangle";
 this->a = param[0];
 this->b = param[1];
 this->c = param[2];
}

MF_Security_xfl_triangle * MF_Security_xfl_triangle::dup() {
 double param[3] = {a,b,c};
 return new MF_Security_xfl_triangle(min,max,step,param,3);
}

double MF_Security_xfl_triangle::param(int _i) {
 switch(_i) {
  case 0: return a;
  case 1: return b;
  case 2: return c;
  default: return 0;
 }
}

double MF_Security_xfl_triangle::compute_eq(double x) {
  return (a<x && x<=b? (x-a)/(b-a) : (b<x && x<c? (c-x)/(c-b) : 0)); 
}

double MF_Security_xfl_triangle::compute_greq(double x) {
  return (x<a? 0 : (x>b? 1 : (x-a)/(b-a) )); 
}

double MF_Security_xfl_triangle::compute_smeq(double x) {
  return (x<b? 1 : (x>c? 0 : (c-x)/(c-b) )); 
}

double MF_Security_xfl_triangle::center() {
  return b; 
}

double MF_Security_xfl_triangle::basis() {
  return (c-a); 
}

//+++++++++++++++++++++++++++++++++++++//
//  Operatorset OP_Security_MySet //
//+++++++++++++++++++++++++++++++++++++//

double OP_Security_MySet::and(double a, double b) {
  return (a<b? a : b); 
}
double OP_Security_MySet::or(double a, double b) {
  return (a>b? a : b); 
}
double OP_Security_MySet::also(double a, double b) {
  return (a>b? a : b); 
}
double OP_Security_MySet::imp(double a, double b) {
  return (a<b? a : b); 
}
double OP_Security_MySet::not(double a) {
  return 1-a; 
}

double OP_Security_MySet::very(double a) {
 double w = 2.0;
  return pow(a,w); 
}

double OP_Security_MySet::moreorless(double a) {
 double w = 0.5;
  return pow(a,w); 
}

double OP_Security_MySet::slightly(double a) {
  return 4*a*(1-a); 
}

double OP_Security_MySet::defuz(OutputMembershipFunction &mf) {
 double min = mf.min();
 double max = mf.max();
 double step = mf.step();
   double num=0, denom=0;
   for(double x=min; x<=max; x+=step) {
    double m = mf.compute(x);
    num += x*m;
    denom += m;
   }
   if(denom==0) return (min+max)/2;
   return num/denom;
}

//+++++++++++++++++++++++++++++++++++++//
//  Type TP_Security_MyType //
//+++++++++++++++++++++++++++++++++++++//

TP_Security_MyType::TP_Security_MyType() {
 min = 0.0;
 max = 1.0;
 step = 0.010101010101010102;
 double _p_L[3] = { 0.0,0.25,0.5 };
 double _p_M[3] = { 0.1,0.5,0.9 };
 double _p_H[3] = { 0.5,0.75,1.0 };
 L = MF_Security_xfl_triangle(min,max,step,_p_L,3);
 M = MF_Security_xfl_triangle(min,max,step,_p_M,3);
 H = MF_Security_xfl_triangle(min,max,step,_p_H,3);
}

//+++++++++++++++++++++++++++++++++++++//
//  Rulebase RL_MyRules //
//+++++++++++++++++++++++++++++++++++++//

void Security::RL_MyRules(MembershipFunction &C, MembershipFunction &R, MembershipFunction ** _o_S) {
 OP_Security_MySet _op;
 double _rl;
 int _i_S=0;
 double *_input = new double[2];
 _input[0] = C.getValue();
 _input[1] = R.getValue();
 OutputMembershipFunction *S = new OutputMembershipFunction(new OP_Security_MySet(),9,2,_input);
 TP_Security_MyType _t_C;
 TP_Security_MyType _t_R;
 TP_Security_MyType _t_S;
 _rl = _op.and(_t_C.L.isEqual(C),_t_R.L.isEqual(R));
 (*S).conc[_i_S] = new RuleConclusion(_rl, _t_S.M.dup()); _i_S++;
 _rl = _op.and(_t_C.L.isEqual(C),_t_R.M.isEqual(R));
 (*S).conc[_i_S] = new RuleConclusion(_rl, _t_S.L.dup()); _i_S++;
 _rl = _op.and(_t_C.L.isEqual(C),_t_R.H.isEqual(R));
 (*S).conc[_i_S] = new RuleConclusion(_rl, _t_S.L.dup()); _i_S++;
 _rl = _op.and(_t_C.M.isEqual(C),_t_R.L.isEqual(R));
 (*S).conc[_i_S] = new RuleConclusion(_rl, _t_S.H.dup()); _i_S++;
 _rl = _op.and(_t_C.M.isEqual(C),_t_R.M.isEqual(R));
 (*S).conc[_i_S] = new RuleConclusion(_rl, _t_S.M.dup()); _i_S++;
 _rl = _op.and(_t_C.M.isEqual(C),_t_R.H.isEqual(R));
 (*S).conc[_i_S] = new RuleConclusion(_rl, _t_S.L.dup()); _i_S++;
 _rl = _op.and(_t_C.H.isEqual(C),_t_R.L.isEqual(R));
 (*S).conc[_i_S] = new RuleConclusion(_rl, _t_S.H.dup()); _i_S++;
 _rl = _op.and(_t_C.H.isEqual(C),_t_R.M.isEqual(R));
 (*S).conc[_i_S] = new RuleConclusion(_rl, _t_S.H.dup()); _i_S++;
 _rl = _op.and(_t_C.H.isEqual(C),_t_R.H.isEqual(R));
 (*S).conc[_i_S] = new RuleConclusion(_rl, _t_S.M.dup()); _i_S++;
 *_o_S = S;
 delete _input;
}
//+++++++++++++++++++++++++++++++++++++//
//          Inference Engine           //
//+++++++++++++++++++++++++++++++++++++//

double* Security::crispInference(double *_input) {
 FuzzySingleton Credit(_input[0]);
 FuzzySingleton Rate(_input[1]);
 MembershipFunction *Security;
 RL_MyRules(Credit, Rate, &Security);
 double *_output = new double[1];
 if(Security->getType() == MembershipFunction::CRISP) _output[0] = ((FuzzySingleton *) Security)->getValue();
 else _output[0] = ((OutputMembershipFunction *) Security)->defuzzify();
 delete Security;
 return _output;
}

double* Security::crispInference(MembershipFunction* &_input) {
 MembershipFunction & Credit = _input[0];
 MembershipFunction & Rate = _input[1];
 MembershipFunction *Security;
 RL_MyRules(Credit, Rate, &Security);
 double *_output = new double[1];
 if(Security->getType() == MembershipFunction::CRISP) _output[0] = ((FuzzySingleton *) Security)->getValue();
 else _output[0] = ((OutputMembershipFunction *) Security)->defuzzify();
 delete Security;
 return _output;
}

MembershipFunction** Security::fuzzyInference(double *_input) {
 FuzzySingleton Credit(_input[0]);
 FuzzySingleton Rate(_input[1]);
 MembershipFunction *Security;
 RL_MyRules(Credit, Rate, &Security);
 MembershipFunction **_output = new MembershipFunction * [1];
 _output[0] = Security;
 return _output;
}

MembershipFunction** Security::fuzzyInference(MembershipFunction* &_input) {
 MembershipFunction & Credit = _input[0];
 MembershipFunction & Rate = _input[1];
 MembershipFunction *Security;
 RL_MyRules(Credit, Rate, &Security);
 MembershipFunction **_output = new MembershipFunction * [1];
 _output[0] = Security;
 return _output;
}

void Security::inference( double _i_Credit, double _i_Rate, double *_o_Security ) {
 FuzzySingleton Credit(_i_Credit);
 FuzzySingleton Rate(_i_Rate);
 MembershipFunction *Security;
 RL_MyRules(Credit, Rate, &Security);
 if(Security->getType() == MembershipFunction::CRISP) (*_o_Security) = ((FuzzySingleton *) Security)->getValue();
 else (*_o_Security) = ((OutputMembershipFunction *) Security)->defuzzify();
 delete Security;
}

#endif /* _Security_INFERENCE_ENGINE_ */
