#include <stdio.h>
#include <math.h>
#include "xfuzzy.hpp"
#include "Utility.hpp"
#include <iostream>
#include "mex.h"

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    double CPU;
    double RAM;
	double Bandwidth;
    double Task_Len;
    
    double *q;
    
    if(nrhs!=4) {
        mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nrhs","Two inputs required.");
    }
    if(nlhs!=1) {
        mexErrMsgIdAndTxt("MyToolbox:arrayProduct:nlhs","One output required.");
    }
    CPU=mxGetScalar(prhs[0]);
    RAM=mxGetScalar(prhs[1]);
    Bandwidth=mxGetScalar(prhs[0]);
    Task_Len=mxGetScalar(prhs[1]);
    
    plhs[0] = mxCreateDoubleScalar(mxREAL);

    q=mxGetPr(plhs[0]);
    Utility f;
    f.inference(CPU,RAM,Bandwidth,Task_Len,q);  
    
}