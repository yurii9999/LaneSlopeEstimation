#pragma once

#include <vector>

#include <opencv2/core.hpp>

/* some fuctions in some sense related to image processing */

namespace MyImageProcessing {

struct Lane { /* dont like std::pair in these cases */
    std::vector<cv::Point2i> left_line;
    std::vector<cv::Point2i> right_line;
};

/* get points belonging to left and right lane correspondingly,
 * h -- step size */
Lane getLane(cv::Mat image, uint h);

}
