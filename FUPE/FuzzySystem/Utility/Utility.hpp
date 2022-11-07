#ifndef _Utility_INFERENCE_ENGINE_HPP
#define _Utility_INFERENCE_ENGINE_HPP

#include "xfuzzy.hpp"

//+++++++++++++++++++++++++++++++++++++//
//  MembershipFunction MF_Utility_xfl_triangle  //
//+++++++++++++++++++++++++++++++++++++//

class MF_Utility_xfl_triangle: public ParamMembershipFunction {
private:
 double a;
 double b;
 double c;

public:
 MF_Utility_xfl_triangle() {};
 virtual ~MF_Utility_xfl_triangle() {};
 MF_Utility_xfl_triangle(double min,double max,double step,double *param, int length);
 MF_Utility_xfl_triangle*dup();
 virtual double param(int _i);
 virtual double compute_eq(double x);
 virtual double compute_greq(double x);
 virtual double compute_smeq(double x);
 virtual double center();
 virtual double basis();
};

//+++++++++++++++++++++++++++++++++++++//
//  Operatorset OP_Utility_MySet //
//+++++++++++++++++++++++++++++++++++++//

class OP_Utility_MySet: public Operatorset {
public:
 virtual ~OP_Utility_MySet() {};
 virtual double and(double a, double b);
 virtual double or(double a, double b);
 virtual double also(double a, double b);
 virtual double imp(double a, double b);
 virtual double not(double a);
 virtual double very(double a);
 virtual double moreorless(double a);
 virtual double slightly(double a);
 virtual double defuz(OutputMembershipFunction &mf);
};

//+++++++++++++++++++++++++++++++++++++//
//  Type TP_Utility_MyType //
//+++++++++++++++++++++++++++++++++++++//

class TP_Utility_MyType {
private:
 double min;
 double max;
 double step;
public:
 MF_Utility_xfl_triangle L;
 MF_Utility_xfl_triangle M;
 MF_Utility_xfl_triangle H;
 TP_Utility_MyType();
};

//+++++++++++++++++++++++++++++++++++++//
//  Fuzzy Inference Engine Utility  //
//+++++++++++++++++++++++++++++++++++++//

class Utility: public FuzzyInferenceEngine {
public:
 Utility() {};
 virtual ~Utility() {};
 virtual double* crispInference(double* input);
 virtual double* crispInference(MembershipFunction* &input);
 virtual MembershipFunction** fuzzyInference(double* input);
 virtual MembershipFunction** fuzzyInference(MembershipFunction* &input);
 void inference( double _i_Credit, double _i_Rate, double _i_Bandwidth, double _i_TaskLength, double *_o_Utility );
private:
 void RL_MyRules(MembershipFunction &C, MembershipFunction &R, MembershipFunction &B, MembershipFunction &Len, MembershipFunction ** _o_U);
};

#endif /* _Utility_INFERENCE_ENGINE_HPP */
