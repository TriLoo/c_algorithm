#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

int main(void)
{
	vector<double> dataIn(0);
	double d;

	while(cin >> d)
		dataIn.push_back(d);

	size_t siz = dataIn.size();

	double sum = 0.0;
	for(auto a : dataIn)
		sum += a;

	double mean = sum / siz;

	sum = 0.0f;
	for(auto a : dataIn)
		sum += (a - mean) * (a - mean);

	double std = sqrt(sum / (siz - 1));

	cout << "mean = " << mean << endl;
	cout << "std error = " << std << endl;

	for(auto a : dataIn)
		cout << "data = " << a << endl;

	return 0;
}
