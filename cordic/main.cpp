#include <iostream>
#include <vector>

using namespace std;

// 1 bit sign bit, 1 bit integer, for example = 1
vector<long int> Atan = {0x3243F6A9, 0x1dac6705, 0x0fadbafd, 0x07f56ea7, 0x03feab77, 0x01ffd55c, 0x00fffaab, 0x007fff55, 0x003fffeb, 0x001ffffd, 0x00100000, 0x00080000, 0x00040000, 0x00020000, 0x00010000, 0x00008000, 0x00004000, 0x00002000, 0x00001000, 0x00000800, 0x00000400, 0x00000200, 0x00000100, 0x00000080, 0x00000040, 0x00000020, 0x00000010, 0x00000008, 0x00000004, 0x00000002, 0x00000001, 0x00000000};

int main(int argc, char **argv)
{
	long int c = 0x26DD3B6A;    // = 0.6072529350088814
	long int s = 0;

	long int c_next = c;
	long int s_next = s;

	// get the input angle 
	//long int angle = 0x3243F6A9;   // input : Pi / 4 
	long int angle = 0x2182A470;   // input : Pi / 4
	long int theta = angle;
	long int direction = 1;

	for(int i = 0; i < 32; ++i)
	{
		if(theta > 0)
			direction = 1;
		else
			direction = -1;
		c_next = c - direction * (s >> i);
		s_next = s + direction * (c >> i);

		c = c_next;
		s = s_next;

		theta -= direction * Atan[i];
	}

	cout << "cos : " << c << endl;
	cout << "sin : " << s << endl;

	return 0;
}

