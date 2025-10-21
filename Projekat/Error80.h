#pragma once
#include <iostream>
#include "Error.h"
using namespace std;
class Error80 : public Error {
public:
	void write(ostream& output) {
		output << "Error. Input name exceeds the 80 character limit.";
	}
};