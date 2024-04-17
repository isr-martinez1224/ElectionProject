//Emmanuel Portillo
/* This class also use of CalculateResults functions
* and prints a visual report of the selected poll to the user
*/

#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "CalculateResults.h"

using namespace std;

class PollReport 
{
public:
	PollReport();

	void PrintReport();
private:
	Results results = Results();
};


//constructor
PollReport::PollReport() {

}

//calls caluclate results to perform operations and display the report to the user
void PollReport::PrintReport() {
	results.CalculateResults();
}
