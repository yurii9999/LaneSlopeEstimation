#include "myimageprocessing.h"

#include <algorithm>

MyImageProcessing::Lane MyImageProcessing::getLane(cv::Mat img, uint h) {
    MyImageProcessing::Lane res;

    for (int i = img.rows - 1; i >= 0; i -= h) {
        for (int j = 0; j < img.cols; ++j) {
            if (img.at<cv::Vec3b>(i, j) != cv::Vec3b::zeros()) {
                    res.left_line.push_back(cv::Point2i(j, i));
                    break;
                }
        }

        for (int j = img.cols - 1; j > 0; --j) {
            if (img.at<cv::Vec3b>(i, j) != cv::Vec3b::zeros()) {
                    res.right_line.push_back(cv::Point2i(j, i));
                    break;
                }
        }


        /* if we found left line and did not find right or vice versa */
        if (res.left_line.size() > res.right_line.size())
            res.left_line.pop_back();
        else
            if (res.right_line.size() < res.left_line.size())
                res.right_line.pop_back();
    }

    return res;
}
