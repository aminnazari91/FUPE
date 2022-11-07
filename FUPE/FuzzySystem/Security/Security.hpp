#ifndef _Security_INFERENCE_ENGINE_HPP
#define _Security_INFERENCE_ENGINE_HPP

#include "xfuzzy.hpp"

//+++++++++++++++++++++++++++++++++++++//
//  MembershipFunction MF_Security_xfl_triangle  //
//+++++++++++++++++++++++++++++++++++++//

class MF_Security_xfl_triangle: public ParamMembershipFunction {
private:
 double a;
 double b;
 double c;

public:
 MF_Security_xfl_triangle() {};
 virtual ~MF_Security_xfl_triangle() {};
 MF_Security_xfl_triangle(double min,double max,double step,double *param, int length);
 MF_Security_xfl_triangle*dup();
 virtual double param(int _i);
 virtual double compute_eq(double x);
 virtual double compute_greq(double x);
 virtual double compute_smeq(double x);
 virtual double center();
 virtual double basis();
};

//+++++++++++++++++++++++++++++++++++++//
//  Operatorset OP_Security_MySet //
//+++++++++++++++++++++++++++++++++++++//

class OP_Security_MySet: public Operatorset {
public:
 virtual ~OP_Security_MySet() {};
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
//  Type TP_Security_MyType //
//+++++++++++++++++++++++++++++++++++++//

class TP_Security_MyType {
private:
 double min;
 double max;
 double step;
public:
 MF_Security_xfl_triangle L;
 MF_Security_xfl_triangle M;
 MF_Security_xfl_triangle H;
 TP_Security_MyType();
};

//+++++++++++++++++++++++++++++++++++++//
//  Fuzzy Inference Engine Security  //
//+++++++++++++++++++++++++++++++++++++//

class Security: public FuzzyInferenceEngine {
public:
 Security() {};
 virtual ~Security() {};
 virtual double* crispInference(double* input);
 virtual double* crispInference(MembershipFunction* &input);
 virtual MembershipFunction** fuzzyInference(double* input);
 virtual MembershipFunction** fuzzyInference(MembershipFunction* &input);
 void inference( double _i_Credit, double _i_Rate, double *_o_Security );
private:
 void RL_MyRules(MembershipFunction &C, MembershipFunction &R, MembershipFunction ** _o_S);
};

#endif /* _Security_INFERENCE_ENGINE_HPP */
