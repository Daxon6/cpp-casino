#pragma once
#include "Error.h"
using namespace std;
class Error30 : public Error {
public:
	void write(ostream& output) {
		output << "Error. Game's name has more than 30 characters.";
	}
};