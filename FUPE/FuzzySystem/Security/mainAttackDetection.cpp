#include <stdio.h>
#include <math.h>
#include "xfuzzy.hpp"
#include "Security.hpp"
#include <iostream>
#include "mex.h"

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    double credit;
    double rate;
	
    double *q;
    
    if(nrhs!=2) {
        mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nrhs","Two inputs required.");
    }
    if(nlhs!=1) {
        mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nlhs","One output required.");
    }
    credit=mxGetScalar(prhs[0]);
    rate=mxGetScalar(prhs[1]);
    
    plhs[0] = mxCreateDoubleScalar(mxREAL);

    q=mxGetPr(plhs[0]);
    Security f;
    f.inference(credit,rate,q);  
    
}