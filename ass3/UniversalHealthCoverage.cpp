/*
 * File: UniversalHealthCoverage.cpp
 * ----------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the UniversalHealthCoverage problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */
#include <iostream>
#include <string>
#include "set.h"
#include "vector.h"
#include "console.h"
using namespace std;

/* Function: canOfferUniversalCoverage(Set<string>& cities,
 *                                     Vector< Set<string> >& locations,
 *                                     int numHospitals,
 *                                     Vector< Set<string> >& result);
 * Usage: if (canOfferUniversalCoverage(cities, locations, 4, result)
 * ==================================================================
 * Given a set of cities, a list of what cities various hospitals can
 * cover, and a number of hospitals, returns whether or not it's
 * possible to provide coverage to all cities with the given number of
 * hospitals.  If so, one specific way to do this is handed back in the
 * result parameter.
 */
bool canOfferUniversalCoverage(Set<string>& cities,
                               Vector< Set<string> >& locations,
                               int numHospitals,
                               Vector< Set<string> >& result);

int main() {

    return 0;
}


bool canOfferUniversalCoverage(Set<string>& cities, Vector< Set<string> >& locations, 
							   int numHospitals, Vector< Set<string> >& result) {
	if (cities.isEmpty())
		return true;
	if (numHospitals == 0) {
		return false;
	}
	foreach(Set<string> coverage in locations) {
		//get set which have to be added to unmake decision
		Set<string> addBack = cities * coverage;
		if (canOfferUniversalCoverage(cities - coverage, locations, numHospitals - 1, result += coverage)) {
			return true;
		}
		//unmake
		result.remove(result.size() - 1);
		cities = cities + addBack;
	}
	return false;
}

