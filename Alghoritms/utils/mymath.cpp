#include "mymath.h"

vector<double> MyMath::getDDX(vector<double> Xs, uint n) {
    vector<double> res; /*res.reserve(Xs.size() - 2 * n);*/

    for (size_t i = n; i < Xs.size() - n; ++i)
        switch (n) {
        case 1:
            res.push_back(1. * Xs[i-1] +
                    -2. * Xs[i] +
                    1. * Xs[i+1]);
            break;
        case 2:
            res.push_back(-1./12 * Xs[i - 2] +
                    4./3 * Xs[i - 1] +
                    -5./2 * Xs[i] +
                    4./3 * Xs[i + 1] +
                    -1./12 * Xs[i + 2]);
            break;
        case 3:
            res.push_back(1./90 * Xs[i - 3] +
                    -3./20 * Xs[i - 2] +
                    3./2 * Xs[i - 1] +
                    -49./18 * Xs[i] +
                    3./2 * Xs[i + 1] +
                    -3./20 * Xs[i + 2] +
                    1./90 * Xs[i + 3]);
            break;
        }

    return res;
}

vector<uint> MyMath::getLocalMaximums(vector<double> a, uint area) {
    /* I find local maximum for each gap (gap is defined by point in center) */
    vector<double> local_maximums;
    for (uint i = 0; i < a.size(); ++i) {
        uint first = i > area ? i - area : 0;
        uint last = i + area < a.size()  ? i + area : a.size() - 1;

        double loc_max = a[first];
        for (uint j = first + 1; j <= last; ++j)
            loc_max = std::max(a[j], loc_max);

        local_maximums.push_back(loc_max);

    }

    /* II collect all local maximums */
    vector<uint> res;
    for (uint i = 0; i < a.size(); ++i) {
        if (std::abs(a[i] - local_maximums[i]) < 0.001)
            res.push_back(i);
    }

    return res;
}

vector<uint> MyMath::getStrongLocalMaximums(vector<double> a, uint area) {
    /* I find local maximum for each gap (gap is defined by point in center) and flag is found maximum is strong or not */
    vector<double> local_maximums;
    vector<int> strong_maximum_flags;

    for (uint i = 0; i < a.size(); ++i) {
        uint first = i > area ? i - area : 0;
        uint last = i + area < a.size()  ? i + area : a.size() - 1;

        double loc_max = a[first];
        bool strong_maximum_flag = true;

        for (uint j = first + 1; j <= last; ++j) {
            if (MyMath::compareDoubles(loc_max, a[j]))
                strong_maximum_flag = false;
            else
                if (loc_max < a[j]) {
                    loc_max = a[j];
                    strong_maximum_flag = true;
                }
        }

        local_maximums.push_back(loc_max);
        strong_maximum_flags.push_back(strong_maximum_flag ? 1 : 0);
    }

    /* II collect all local maximums, save only strongs */
    vector<uint> res;
    for (uint i = 0; i < a.size(); ++i) {
        if (MyMath::compareDoubles(a[i], local_maximums[i]) && strong_maximum_flags[i] == 1)
            res.push_back(i);
    }

    return res;
}

bool MyMath::compareDoubles(double a, double b, double epsilon) {
    return std::abs(a - b) < epsilon;
}
