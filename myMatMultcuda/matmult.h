/*
 * matmult.h
 *
 *  Created on: Jun 3, 2017
 *      Author: smher
 */

#ifndef MATMULT_H_
#define MATMULT_H_

#include <iostream>
#include <cassert>

using namespace std;

//const int blockPerGrid = 32;
//const int threadPerBlock = 256;

class matMult
{
public:
	float *A = NULL;
	float *A_d = NULL;
	void matMultF(matMult *A, matMult *B, matMult *C);

	int row = 0;
	int col = 0;
};

#endif /* MATMULT_H_ */
