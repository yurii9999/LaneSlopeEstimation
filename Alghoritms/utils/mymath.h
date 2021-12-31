#pragma once

#include <vector>
#include <iostream>

using std::vector;

namespace MyMath {
/* some fuctions in some sense related to math */

/* get second derivatives of X
 * n is amount values for one side to estimate second derivative (== accuracy / 2)
 * https://en.wikipedia.org/wiki/Finite_difference_coefficient */
vector<double> getDDX(vector<double> X, uint n);

/* get indexes of local maximums in x
 * area defines the gap within the point sould be global maximum to considered as a local maximum */
vector<uint> getLocalMaximums(vector<double> x, uint area);

/* same as getLocalMaximums, but finds strong local maximums */
vector<uint> getStrongLocalMaximums(vector<double> a, uint area);

/* returns true, if |a - b| < epsilon */
bool compareDoubles(double a, double b, double epsilon = 0.0001);

}
