#pragma once

#include <opencv2/viz.hpp>
#include <opencv2/core.hpp>

#include "road.h"

/* facade for more conveniece usage of cv::viz (not sure I need it) */

struct sceneParameters {
    double lenght = 60;
    double delta_l = 0.2;

    double f = 600;
    uint width = 640;
    uint height = 480;
    uint cx = 320;
    uint cy = 240;

    double d = 0;
    /* d is distance in meters that camera moved forward along the road (now presentd poor implementation,
     * but TODO: make good implementation that move camera along the road, not just set Z coordinate) */
};

cv::Mat getPicture(Road::RoadBuilder &rb, sceneParameters sp);
// void showScene(Road::RoadBuilder &rb, sceneParameters sp);


