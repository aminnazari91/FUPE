#ifndef _Utility_INFERENCE_ENGINE_
#define _Utility_INFERENCE_ENGINE_

#include <stdio.h>
#include <math.h>
#include "xfuzzy.hpp"
#include "Utility.hpp"

//+++++++++++++++++++++++++++++++++++++//
//  MembershipFunction MF_Utility_xfl_triangle  //
//+++++++++++++++++++++++++++++++++++++//

MF_Utility_xfl_triangle::MF_Utility_xfl_triangle(double min,double max,double step,double *param, int length) :
ParamMembershipFunction(min,max,step) {
 this->name = "MF_Utility_xfl_triangle";
 this->a = param[0];
 this->b = param[1];
 this->c = param[2];
}

MF_Utility_xfl_triangle * MF_Utility_xfl_triangle::dup() {
 double param[3] = {a,b,c};
 return new MF_Utility_xfl_triangle(min,max,step,param,3);
}

double MF_Utility_xfl_triangle::param(int _i) {
 switch(_i) {
  case 0: return a;
  case 1: return b;
  case 2: return c;
  default: return 0;
 }
}

double MF_Utility_xfl_triangle::compute_eq(double x) {
  return (a<x && x<=b? (x-a)/(b-a) : (b<x && x<c? (c-x)/(c-b) : 0)); 
}

double MF_Utility_xfl_triangle::compute_greq(double x) {
  return (x<a? 0 : (x>b? 1 : (x-a)/(b-a) )); 
}

double MF_Utility_xfl_triangle::compute_smeq(double x) {
  return (x<b? 1 : (x>c? 0 : (c-x)/(c-b) )); 
}

double MF_Utility_xfl_triangle::center() {
  return b; 
}

double MF_Utility_xfl_triangle::basis() {
  return (c-a); 
}

//+++++++++++++++++++++++++++++++++++++//
//  Operatorset OP_Utility_MySet //
//+++++++++++++++++++++++++++++++++++++//

double OP_Utility_MySet::and(double a, double b) {
  return (a<b? a : b); 
}
double OP_Utility_MySet::or(double a, double b) {
  return (a>b? a : b); 
}
double OP_Utility_MySet::also(double a, double b) {
  return (a>b? a : b); 
}
double OP_Utility_MySet::imp(double a, double b) {
  return (a<b? a : b); 
}
double OP_Utility_MySet::not(double a) {
  return 1-a; 
}

double OP_Utility_MySet::very(double a) {
 double w = 2.0;
  return pow(a,w); 
}

double OP_Utility_MySet::moreorless(double a) {
 double w = 0.5;
  return pow(a,w); 
}

double OP_Utility_MySet::slightly(double a) {
  return 4*a*(1-a); 
}

double OP_Utility_MySet::defuz(OutputMembershipFunction &mf) {
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
//  Type TP_Utility_MyType //
//+++++++++++++++++++++++++++++++++++++//

TP_Utility_MyType::TP_Utility_MyType() {
 min = 0.0;
 max = 1.0;
 step = 0.010101010101010102;
 double _p_L[3] = { 0.0,0.25,0.5 };
 double _p_M[3] = { 0.1,0.5,0.9 };
 double _p_H[3] = { 0.5,0.75,1.0 };
 L = MF_Utility_xfl_triangle(min,max,step,_p_L,3);
 M = MF_Utility_xfl_triangle(min,max,step,_p_M,3);
 H = MF_Utility_xfl_triangle(min,max,step,_p_H,3);
}

//+++++++++++++++++++++++++++++++++++++//
//  Rulebase RL_MyRules //
//+++++++++++++++++++++++++++++++++++++//

void Utility::RL_MyRules(MembershipFunction &C, MembershipFunction &R, MembershipFunction &B, MembershipFunction &Len, MembershipFunction ** _o_U) {
 OP_Utility_MySet _op;
 double _rl;
 int _i_U=0;
 double *_input = new double[4];
 _input[0] = C.getValue();
 _input[1] = R.getValue();
 _input[2] = B.getValue();
 _input[3] = Len.getValue();
 OutputMembershipFunction *U = new OutputMembershipFunction(new OP_Utility_MySet(),81,4,_input);
 TP_Utility_MyType _t_C;
 TP_Utility_MyType _t_R;
 TP_Utility_MyType _t_B;
 TP_Utility_MyType _t_Len;
 TP_Utility_MyType _t_U;
 _rl = _op.and(_op.and(_op.and(_t_C.L.isEqual(C),_t_R.L.isEqual(R)),_t_B.L.isEqual(B)),_t_Len.L.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.L.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.L.isEqual(C),_t_R.M.isEqual(R)),_t_B.L.isEqual(B)),_t_Len.L.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.L.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.L.isEqual(C),_t_R.H.isEqual(R)),_t_B.L.isEqual(B)),_t_Len.L.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.M.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.M.isEqual(C),_t_R.L.isEqual(R)),_t_B.L.isEqual(B)),_t_Len.L.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.L.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.M.isEqual(C),_t_R.M.isEqual(R)),_t_B.L.isEqual(B)),_t_Len.L.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.M.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.M.isEqual(C),_t_R.H.isEqual(R)),_t_B.L.isEqual(B)),_t_Len.L.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.M.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.H.isEqual(C),_t_R.L.isEqual(R)),_t_B.L.isEqual(B)),_t_Len.L.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.M.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.H.isEqual(C),_t_R.M.isEqual(R)),_t_B.L.isEqual(B)),_t_Len.L.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.M.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.H.isEqual(C),_t_R.H.isEqual(R)),_t_B.L.isEqual(B)),_t_Len.L.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.H.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.L.isEqual(C),_t_R.L.isEqual(R)),_t_B.L.isEqual(B)),_t_Len.M.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.L.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.L.isEqual(C),_t_R.M.isEqual(R)),_t_B.L.isEqual(B)),_t_Len.M.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.L.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.L.isEqual(C),_t_R.H.isEqual(R)),_t_B.L.isEqual(B)),_t_Len.M.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.L.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.M.isEqual(C),_t_R.L.isEqual(R)),_t_B.L.isEqual(B)),_t_Len.M.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.L.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.M.isEqual(C),_t_R.M.isEqual(R)),_t_B.L.isEqual(B)),_t_Len.M.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.L.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.M.isEqual(C),_t_R.H.isEqual(R)),_t_B.L.isEqual(B)),_t_Len.M.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.M.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.H.isEqual(C),_t_R.L.isEqual(R)),_t_B.L.isEqual(B)),_t_Len.M.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.L.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.H.isEqual(C),_t_R.M.isEqual(R)),_t_B.L.isEqual(B)),_t_Len.M.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.M.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.H.isEqual(C),_t_R.H.isEqual(R)),_t_B.L.isEqual(B)),_t_Len.M.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.M.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.L.isEqual(C),_t_R.L.isEqual(R)),_t_B.L.isEqual(B)),_t_Len.H.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.L.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.L.isEqual(C),_t_R.M.isEqual(R)),_t_B.L.isEqual(B)),_t_Len.H.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.L.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.L.isEqual(C),_t_R.H.isEqual(R)),_t_B.L.isEqual(B)),_t_Len.H.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.L.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.M.isEqual(C),_t_R.L.isEqual(R)),_t_B.L.isEqual(B)),_t_Len.H.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.L.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.M.isEqual(C),_t_R.M.isEqual(R)),_t_B.L.isEqual(B)),_t_Len.H.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.L.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.M.isEqual(C),_t_R.H.isEqual(R)),_t_B.L.isEqual(B)),_t_Len.H.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.L.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.H.isEqual(C),_t_R.L.isEqual(R)),_t_B.L.isEqual(B)),_t_Len.H.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.L.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.H.isEqual(C),_t_R.M.isEqual(R)),_t_B.L.isEqual(B)),_t_Len.H.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.L.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.H.isEqual(C),_t_R.H.isEqual(R)),_t_B.L.isEqual(B)),_t_Len.H.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.M.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.L.isEqual(C),_t_R.L.isEqual(R)),_t_B.M.isEqual(B)),_t_Len.L.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.L.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.L.isEqual(C),_t_R.M.isEqual(R)),_t_B.M.isEqual(B)),_t_Len.L.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.M.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.L.isEqual(C),_t_R.H.isEqual(R)),_t_B.M.isEqual(B)),_t_Len.L.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.H.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.M.isEqual(C),_t_R.L.isEqual(R)),_t_B.M.isEqual(B)),_t_Len.L.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.M.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.M.isEqual(C),_t_R.M.isEqual(R)),_t_B.M.isEqual(B)),_t_Len.L.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.H.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.M.isEqual(C),_t_R.H.isEqual(R)),_t_B.M.isEqual(B)),_t_Len.L.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.H.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.H.isEqual(C),_t_R.L.isEqual(R)),_t_B.M.isEqual(B)),_t_Len.L.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.H.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.H.isEqual(C),_t_R.M.isEqual(R)),_t_B.M.isEqual(B)),_t_Len.L.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.H.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.H.isEqual(C),_t_R.H.isEqual(R)),_t_B.M.isEqual(B)),_t_Len.L.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.H.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.L.isEqual(C),_t_R.L.isEqual(R)),_t_B.M.isEqual(B)),_t_Len.M.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.L.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.L.isEqual(C),_t_R.M.isEqual(R)),_t_B.M.isEqual(B)),_t_Len.M.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.L.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.L.isEqual(C),_t_R.H.isEqual(R)),_t_B.M.isEqual(B)),_t_Len.M.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.M.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.M.isEqual(C),_t_R.L.isEqual(R)),_t_B.M.isEqual(B)),_t_Len.M.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.L.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.M.isEqual(C),_t_R.M.isEqual(R)),_t_B.M.isEqual(B)),_t_Len.M.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.M.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.M.isEqual(C),_t_R.H.isEqual(R)),_t_B.M.isEqual(B)),_t_Len.M.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.H.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.H.isEqual(C),_t_R.L.isEqual(R)),_t_B.M.isEqual(B)),_t_Len.M.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.M.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.H.isEqual(C),_t_R.M.isEqual(R)),_t_B.M.isEqual(B)),_t_Len.M.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.H.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.H.isEqual(C),_t_R.H.isEqual(R)),_t_B.M.isEqual(B)),_t_Len.M.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.H.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.L.isEqual(C),_t_R.L.isEqual(R)),_t_B.M.isEqual(B)),_t_Len.H.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.L.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.L.isEqual(C),_t_R.M.isEqual(R)),_t_B.M.isEqual(B)),_t_Len.H.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.L.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.L.isEqual(C),_t_R.H.isEqual(R)),_t_B.M.isEqual(B)),_t_Len.H.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.L.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.M.isEqual(C),_t_R.L.isEqual(R)),_t_B.M.isEqual(B)),_t_Len.H.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.L.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.M.isEqual(C),_t_R.M.isEqual(R)),_t_B.M.isEqual(B)),_t_Len.H.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.L.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.M.isEqual(C),_t_R.H.isEqual(R)),_t_B.M.isEqual(B)),_t_Len.H.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.M.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.H.isEqual(C),_t_R.L.isEqual(R)),_t_B.M.isEqual(B)),_t_Len.H.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.L.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.H.isEqual(C),_t_R.M.isEqual(R)),_t_B.M.isEqual(B)),_t_Len.H.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.M.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.H.isEqual(C),_t_R.H.isEqual(R)),_t_B.M.isEqual(B)),_t_Len.H.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.H.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.L.isEqual(C),_t_R.L.isEqual(R)),_t_B.H.isEqual(B)),_t_Len.L.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.M.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.L.isEqual(C),_t_R.M.isEqual(R)),_t_B.H.isEqual(B)),_t_Len.L.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.H.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.L.isEqual(C),_t_R.H.isEqual(R)),_t_B.H.isEqual(B)),_t_Len.L.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.H.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.M.isEqual(C),_t_R.L.isEqual(R)),_t_B.H.isEqual(B)),_t_Len.L.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.H.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.M.isEqual(C),_t_R.M.isEqual(R)),_t_B.H.isEqual(B)),_t_Len.L.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.H.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.M.isEqual(C),_t_R.H.isEqual(R)),_t_B.H.isEqual(B)),_t_Len.L.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.H.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.H.isEqual(C),_t_R.L.isEqual(R)),_t_B.H.isEqual(B)),_t_Len.L.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.H.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.H.isEqual(C),_t_R.M.isEqual(R)),_t_B.H.isEqual(B)),_t_Len.L.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.H.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.H.isEqual(C),_t_R.H.isEqual(R)),_t_B.H.isEqual(B)),_t_Len.L.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.H.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.L.isEqual(C),_t_R.L.isEqual(R)),_t_B.H.isEqual(B)),_t_Len.M.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.L.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.L.isEqual(C),_t_R.M.isEqual(R)),_t_B.H.isEqual(B)),_t_Len.M.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.M.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.L.isEqual(C),_t_R.H.isEqual(R)),_t_B.H.isEqual(B)),_t_Len.M.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.M.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.M.isEqual(C),_t_R.L.isEqual(R)),_t_B.H.isEqual(B)),_t_Len.M.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.M.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.M.isEqual(C),_t_R.M.isEqual(R)),_t_B.H.isEqual(B)),_t_Len.M.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.M.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.M.isEqual(C),_t_R.H.isEqual(R)),_t_B.H.isEqual(B)),_t_Len.M.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.H.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.H.isEqual(C),_t_R.L.isEqual(R)),_t_B.H.isEqual(B)),_t_Len.M.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.M.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.H.isEqual(C),_t_R.M.isEqual(R)),_t_B.H.isEqual(B)),_t_Len.M.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.H.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.H.isEqual(C),_t_R.H.isEqual(R)),_t_B.H.isEqual(B)),_t_Len.M.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.H.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.L.isEqual(C),_t_R.L.isEqual(R)),_t_B.H.isEqual(B)),_t_Len.H.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.L.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.L.isEqual(C),_t_R.M.isEqual(R)),_t_B.H.isEqual(B)),_t_Len.H.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.L.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.L.isEqual(C),_t_R.H.isEqual(R)),_t_B.H.isEqual(B)),_t_Len.H.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.M.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.M.isEqual(C),_t_R.L.isEqual(R)),_t_B.H.isEqual(B)),_t_Len.H.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.L.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.M.isEqual(C),_t_R.M.isEqual(R)),_t_B.H.isEqual(B)),_t_Len.H.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.M.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.M.isEqual(C),_t_R.H.isEqual(R)),_t_B.H.isEqual(B)),_t_Len.H.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.M.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.H.isEqual(C),_t_R.L.isEqual(R)),_t_B.H.isEqual(B)),_t_Len.H.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.M.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.H.isEqual(C),_t_R.M.isEqual(R)),_t_B.H.isEqual(B)),_t_Len.H.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.M.dup()); _i_U++;
 _rl = _op.and(_op.and(_op.and(_t_C.H.isEqual(C),_t_R.H.isEqual(R)),_t_B.H.isEqual(B)),_t_Len.H.isEqual(Len));
 (*U).conc[_i_U] = new RuleConclusion(_rl, _t_U.H.dup()); _i_U++;
 *_o_U = U;
 delete _input;
}
//+++++++++++++++++++++++++++++++++++++//
//          Inference Engine           //
//+++++++++++++++++++++++++++++++++++++//

double* Utility::crispInference(double *_input) {
 FuzzySingleton Credit(_input[0]);
 FuzzySingleton Rate(_input[1]);
 FuzzySingleton Bandwidth(_input[2]);
 FuzzySingleton TaskLength(_input[3]);
 MembershipFunction *Utility;
 RL_MyRules(Credit, Rate, Bandwidth, TaskLength, &Utility);
 double *_output = new double[1];
 if(Utility->getType() == MembershipFunction::CRISP) _output[0] = ((FuzzySingleton *) Utility)->getValue();
 else _output[0] = ((OutputMembershipFunction *) Utility)->defuzzify();
 delete Utility;
 return _output;
}

double* Utility::crispInference(MembershipFunction* &_input) {
 MembershipFunction & Credit = _input[0];
 MembershipFunction & Rate = _input[1];
 MembershipFunction & Bandwidth = _input[2];
 MembershipFunction & TaskLength = _input[3];
 MembershipFunction *Utility;
 RL_MyRules(Credit, Rate, Bandwidth, TaskLength, &Utility);
 double *_output = new double[1];
 if(Utility->getType() == MembershipFunction::CRISP) _output[0] = ((FuzzySingleton *) Utility)->getValue();
 else _output[0] = ((OutputMembershipFunction *) Utility)->defuzzify();
 delete Utility;
 return _output;
}

MembershipFunction** Utility::fuzzyInference(double *_input) {
 FuzzySingleton Credit(_input[0]);
 FuzzySingleton Rate(_input[1]);
 FuzzySingleton Bandwidth(_input[2]);
 FuzzySingleton TaskLength(_input[3]);
 MembershipFunction *Utility;
 RL_MyRules(Credit, Rate, Bandwidth, TaskLength, &Utility);
 MembershipFunction **_output = new  MembershipFunction * [1];
 _output[0] = Utility;
 return _output;
}

MembershipFunction** Utility::fuzzyInference(MembershipFunction* &_input) {
 MembershipFunction & Credit = _input[0];
 MembershipFunction & Rate = _input[1];
 MembershipFunction & Bandwidth = _input[2];
 MembershipFunction & TaskLength = _input[3];
 MembershipFunction *Utility;
 RL_MyRules(Credit, Rate, Bandwidth, TaskLength, &Utility);
 MembershipFunction **_output = new  MembershipFunction * [1];
 _output[0] = Utility;
 return _output;
}

void Utility::inference( double _i_Credit, double _i_Rate, double _i_Bandwidth, double _i_TaskLength, double *_o_Utility ) {
 FuzzySingleton Credit(_i_Credit);
 FuzzySingleton Rate(_i_Rate);
 FuzzySingleton Bandwidth(_i_Bandwidth);
 FuzzySingleton TaskLength(_i_TaskLength);
 MembershipFunction *Utility;
 RL_MyRules(Credit, Rate, Bandwidth, TaskLength, &Utility);
 if(Utility->getType() == MembershipFunction::CRISP) (*_o_Utility) = ((FuzzySingleton *) Utility)->getValue();
 else (*_o_Utility) = ((OutputMembershipFunction *) Utility)->defuzzify();
 delete Utility;
}

#endif /* _Utility_INFERENCE_ENGINE_ */
