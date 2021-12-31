/* Method optimize 3D road profile via 2 images */

#include <iostream>
#include <iomanip>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <utils/myimageprocessing.h>
#include <utils/mymath.h>

#include <libalglib/optimization.h>
#include <libalglib/stdafx.h>

using namespace std;
using namespace alglib;

cv::Mat img; /* bad disign */

const double f = 600;
const double cu = 320, cvv = 240;
const uint width = 640, height = 480;

/* Get u coordinate of left line corresponded to v coordinate */
int getU(int v) {
    for (int u = 0; u < img.cols; ++u) {
        if (img.at<cv::Vec3b>(v, u) != cv::Vec3b::zeros())
            return u;
    }

    return -1;
}

/* function to optimize */
void function1_func(const alglib::real_1d_array &x, double &func, void *ptr) {
    double res = 0;

    for (double z_ = 5; z_ < 30; z_ += 2) {
        double x_ = -1.6;
        double y_ = x[0] + z_ * x[1] + pow(z_, 2) * x[2] + pow(z_, 3) * x[3];

        int u = x_/z_ * f + cu;
        int v = -(y_ - 1.2) /z_ * f + cvv;

        if (v < 0 || v > height) // (?) choice optimization with constraints
            res += 10000;
        else {
            int real_u = getU(v);
            res += pow(u - real_u, 2);
        }
    }

    func = res;
}


int main(int argc, char** argv) {
    img = cv::imread("../mydataset/road1/0.png");

    real_1d_array x = "[0,0,0,0]";
    real_1d_array s = "[1,1,1,10]";
    double epsg = 0;
    double epsf = 0;
    double epsx = 0.0000000001;
    double diffstep = 1.0e-6;
    ae_int_t maxits = 0;
    mincgstate state;
    mincgcreatef(x, diffstep, state);
    mincgsetcond(state, epsg, epsf, epsx, maxits);
    mincgsetscale(state, s);

    mincgreport rep;
    alglib::mincgoptimize(state, function1_func);
    mincgresults(state, x, rep);

    /* draw */
    cv::Point2i prev;
    bool first_flag = true;
    for (double z_ = 0; z_ < 25; z_ += 0.5) {
        double x_ = -1.6;

        double y_ = x[0] + z_ * x[1] + z_ * z_ * x[2] + pow(z_, 3) * x[3];

        int u = x_/z_ * f + cu;
        int v = -(y_ - 1.2) /z_ * f + cvv;

        if (!first_flag)
            cv::line(img, cv::Point2i(u, v), prev, cv::Scalar(0, 0, 255));
        else
            first_flag = false;
        prev = cv::Point2i(u,v);
    }

    cv::imwrite("result.png", img);

    cout << x.tostring(10) << endl;

    cv::imshow("", img);
    cv::waitKey();

    return 0;
}
