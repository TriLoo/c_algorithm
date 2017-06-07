#include "matmult.h"

/*
 * Correct !!!!
 */

int main(void)
{
	float *L = new float [512 * 42];
	float *R = new float [42 * 512];

	float *SUM = new float [512 * 512]();

	for(int i = 0; i < 512 * 30; i++)
	{
		L[i] = 3;
		R[i] = 1;
	}

	matMult LA, RA, SA;
	LA.col = 30;
	LA.row = 512;
	RA.col = 512;
	RA.row = 30;
	SA.row = 512;
	SA.col = 512;

	LA.A = L;
	RA.A = R;
	SA.A = SUM;

	SA.matMultF(&LA, &RA, &SA);

	int count = 0;

	for(int i = 0; i < 512 * 512; i++)
	{
		if(SA.A[i] != 90)
			count++;
	}

	cout << "Not equal to 90 : " << count << endl;

	/*
	// for test
	for(int i = 0; i < 10; i++)
		cout << "Result = " << SA.A[i] << endl;
	*/

	delete [] L;
	delete [] R;
	delete [] SUM;


	return 0;
}
