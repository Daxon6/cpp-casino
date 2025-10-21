#pragma once
#include <iostream>
using namespace std;
class Error {
public:
	virtual void write(ostream& output) = 0;
	friend ostream& operator <<(ostream& output, Error& g) {
		g.write(output);
		return output;
	}
};