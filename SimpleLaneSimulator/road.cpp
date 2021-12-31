#include "road.h"

#include <string>

void Road::appendPoint(double alpha, double beta, double theta, double width, double delta_l) {
    double width_half = width / 2;

    double cos_alpha = std::cos(alpha);
    double sin_alpha = std::sin(alpha);

    double sin_beta = std::sin(beta);
    double cos_beta = std::cos(beta);

    double sin_theta = std::sin(theta);
    double cos_theta = std::cos(theta);

    center.push_back(center.back() +
                       cv::Point3d(delta_l * sin_theta * cos_beta,
                                   delta_l * sin_beta,
                                   delta_l * cos_theta * cos_beta)
                       );

    left_border.push_back(center.back() +
                          cv::Point3d(width_half * cos_theta * cos_alpha,
                                      -width_half * sin_alpha,
                                      -width_half * sin_theta * cos_alpha)
                          );

    right_border.push_back(center.back() +
                          cv::Point3d(-width_half * cos_theta * cos_alpha, // could be replaced with -Point of left border
                                      width_half * sin_alpha,
                                      width_half * sin_theta * cos_alpha)
                           );
}

void Road::appendFirstPoint(double width)
{
    center.push_back(cv::Point3d(0, 0, 0));
    left_border.push_back(cv::Point3d(width / 2, 0, 0));
    right_border.push_back(cv::Point3d(-width / 2, 0, 0));
}

Road::Road(Road::RoadBuilder &rb, double delta_l, double lenght, std::string name) : name(name), delta_l(delta_l) {
    this->n = std::round(lenght / delta_l);

    center.reserve(n + 1);
    left_border.reserve(n + 1);
    right_border.reserve(n + 1);

    appendFirstPoint(rb.width(0));

    double l = delta_l;

    for (int i = 0; i < n; ++i) {
        appendPoint(rb.alpha(l), rb.beta(l), rb.theta(l), rb.width(l), delta_l);
        l += delta_l;
    }
}

void Road::show(cv::viz::Viz3d &window) {
    lines.reserve(n * 2);
    int j = 0;
    for (auto points_it : {left_border.begin(), right_border.begin()}) {
        for (int i = 0; i < n; ++i) {
            cv::viz::WLine line(*points_it, *(points_it + 1), color);
            ++points_it;
            window.showWidget(name +std::to_string(j) + std::to_string(i), line);
            lines.push_back(line);
        }
        ++j;
    }
}

Road::RoadBuilder::~RoadBuilder() {}
