/* NiuTrans.Tensor - an open-source tensor library
* Copyright (C) 2017, Natural Language Processing Lab, Northestern University.
* All rights reserved.
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*   http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

/*
* $Created by: Xu Chen (email: hello_master1954@163.com) 2018-07-31
*/

#include "../core/math/Unary.h"
#include "TSin.h"

namespace nts { // namespace nts(NiuTrans.Tensor)

/*
case 1: test Sin function.
Set every entry to its sine value.
*/
bool TestSin1()
{
	/* a tensor of size (3, 2) */
	int order = 2;
	int * dimSize = new int[order];
	dimSize[0] = 3;
	dimSize[1] = 2;

	int unitNum = 1;
	for (int i = 0; i < order; i++)
		unitNum *= dimSize[i];

	DTYPE aData[3][2] = { {1.0F, 2.0F}, 
	                      {-1.0F, -2.0F},
	                      {0.0F, 0.5F} };
	DTYPE answer[3][2] = { {0.8415F, 0.9093F},
	                       {-0.8415F, -0.9093F},
	                       {0.0F, 0.4794F} };

	/* CPU test */
	bool cpuTest = true;

	/* create tensors */
	XTensor * a = NewTensor(order, dimSize);
    XTensor * b = NewTensor(order, dimSize);
	XTensor * aMe = NewTensor(order, dimSize);
    XTensor bUser;

	/* initialize variables */
	a->SetData(aData, unitNum);
	aMe->SetData(aData, unitNum);

	/* call Sin function */
	_Sin(a, b);
	_SinMe(aMe);
    bUser = Sin(*a);

	/* check results */
	cpuTest = b->CheckData(answer, unitNum, 1e-4F) && aMe->CheckData(answer, unitNum, 1e-4F) && bUser.CheckData(answer, unitNum, 1e-4F);
    
#ifdef USE_CUDA
	/* GPU test */
	bool gpuTest = true;

	/* create tensor */
	XTensor * aGPU = NewTensor(order, dimSize, X_FLOAT, 1.0F, 0);
	XTensor * bGPU = NewTensor(order, dimSize, X_FLOAT, 1.0F, 0);
	XTensor * aMeGPU = NewTensor(order, dimSize, X_FLOAT, 1.0F, 0);
    XTensor bUserGPU;

	/* Initialize variables */
	aGPU->SetData(aData, unitNum);
	aMeGPU->SetData(aData, unitNum);

	/* call Sin function */
    _Sin(aGPU, bGPU);
	_SinMe(aMeGPU);
    bUserGPU = Sin(*aGPU);

	/* check results */
	gpuTest = bGPU->CheckData(answer, unitNum, 1e-4F) && aMeGPU->CheckData(answer, unitNum, 1e-4F) && bUserGPU.CheckData(answer, unitNum, 1e-4F);

	/* destroy variables */
	delete a;
	delete b;
	delete aMe;
    delete aGPU;
    delete bGPU;
    delete aMeGPU;
	delete[] dimSize;

	return cpuTest && gpuTest;
#else
	/* destroy variables */
	delete a;
	delete b;
	delete aMe;
	delete[] dimSize;

	return cpuTest;
#endif // USE_CUDA
}

/* other cases */
/*
TODO!!
*/

/* test for Sin Function */
bool TestSin()
{
	XPRINT(0, stdout, "[TEST Sin] set every entry to its sine value \n");
	bool returnFlag = true, caseFlag = true;

	/* case 1 test */
	caseFlag = TestSin1();

	if (!caseFlag) {
		returnFlag = false;
		XPRINT(0, stdout, ">> case 1 failed!\n");
	}
	else
		XPRINT(0, stdout, ">> case 1 passed!\n");

	/* other cases test */
	/*
	TODO!!
	*/

	if (returnFlag) {
		XPRINT(0, stdout, ">> All Passed!\n");
	}
	else
		XPRINT(0, stdout, ">> Failed!\n");

	XPRINT(0, stdout, "\n");

	return returnFlag;
}

} // namespace nts(NiuTrans.Tensor)