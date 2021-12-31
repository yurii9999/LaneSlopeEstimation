#include <iostream>
#include <iomanip>

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <utils/myimageprocessing.h>
#include <utils/mymath.h>

using namespace std;

vector<double> getXs(vector<cv::Point2i> points) {
    vector<double> res; res.reserve(points.size());
    for (auto &p : points)
        res.push_back(static_cast<double>(p.x));

    return res;
}


/* img : image with lane
 * h -- frequency of descretization of the lane
 * n -- accuracy of second derivative formula
 * area -- area for local maximum search */
vector<cv::Point2i> getInterestingPoints(cv::Mat img, uint h, uint n, uint area) {
    /* find points corresponded to left and right lines II */
    MyImageProcessing::Lane lane = MyImageProcessing::getLane(img, h);

    /* search some distinguish points III */
    vector<double> Xs = getXs(lane.left_line);
    vector<double> left_DDXs = MyMath::getDDX(Xs, n);
    for (auto &a : left_DDXs) {
        a = std::abs(a);
    }

    vector<uint> interesting_points = MyMath::getStrongLocalMaximums(left_DDXs, area);

    vector<cv::Point2i> result;
    for (uint i : interesting_points) {
        result.push_back(lane.left_line[i + n]);
    }

    return result;
}

/* Get u coordinate of left line corresponded to v coordinate */
int getU(cv::Mat img, int v) {
    for (int u = 0; u < img.cols; ++u) {
        if (img.at<cv::Vec3b>(v, u) != cv::Vec3b::zeros())
            return u;
    }

    return -1;
}

/* Method with second derivative uses the fact that in points where slope changes there is sharp angels
 * whereas in regular point is almost straight line */
int main(int argc, char** argv) {
    /* load image I */
    string filename = argc == 1 ? "../mydataset/road1/1.png" : argv[1];
    cv::Mat img = cv::imread(filename, cv::IMREAD_COLOR);

    /* Set some regions of interest to process them with different parameters,
     * eg part that is far away better process with smaller h, and close parts with higher */
    uint b1 = 290;
    uint b2 = 360;
    cv::Rect upper_roi(0, 0, img.cols, b1);
    cv::Rect middle_roi(0, b1, img.cols, b2 - b1);
    cv::Rect lower_roi(0, b2, img.cols, img.rows - b2);

    vector<cv::Point2i> features = getInterestingPoints(img, 7, 3, 15);
    int border = 0;
    /* Merge results IV */
    for (auto p : features) {
        cv::line(img, cv::Point2i(0, p.y + border), cv::Point2i(img.cols - 1, p.y + border), cv::Scalar(255, 255, 255));
    }


    cv::imshow("dd", img);
    cv::imwrite("1.png", img);
    cv::waitKey();

    return 0;
}
