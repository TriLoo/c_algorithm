#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

int main(int argc, char  **argv)
{
	cout << "hello world " << endl;
	stack<string> ops;
	stack<double> vals;

	string s, op;
	while(cin >> s)
	{
		cout << s << endl;
		if(s == "(");
		else if( s == "+")
			ops.push(s);
		else if( s == "-")
			ops.push(s);
		else if( s == "*" )
			ops.push(s);
		else if(s == "/")
			ops.push(s);
		else if( s== ")")
		{
			op = ops.top();
			ops.pop();
			double v = 0;
			v = vals.top();
			vals.pop();
			if(op == "+")
			{
				cout << op << endl;
				v += vals.top();
				vals.pop();
			}
			else if(op == "-")
			{
				cout << op << endl;
				v = vals.top() - v;
				vals.pop();
			}
			else if(op == "*")
			{
				cout << op << endl;
				v = vals.top() * v;
				vals.pop();
			}
			else if(op == "/")
			{
				cout << op << endl;
				v = vals.top() / v;
				vals.pop();
			}
			vals.push(v);
		}
		else
		{
			vals.push(stod(s));
			cout << stod(s) << endl;
		}
	}

	//cout << "Result ..." << endl;
	//double res = vals.top
	cout << "Reuslt = " << vals.top() << endl;

	return 0;
}
