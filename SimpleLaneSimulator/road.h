#pragma once

#include <opencv2/viz.hpp>

#include <vector>

class Road {
private:
    std::vector<cv::Point3d> center;
    std::vector<cv::Point3d> left_border;
    std::vector<cv::Point3d> right_border;
    std::string name;
    uint n;
    double delta_l;

    // If we need to apply transformation to road, we apply to each line, or set color, or ...
    std::vector<cv::viz::WLine> lines;
    cv::viz::Color color;

    void appendPoint(double alpha, double beta, double theta, double width, double delta_l);
    void appendFirstPoint(double width);

public:
    /* Interfece for user-defined road builders */
    class RoadBuilder {
    public:
        virtual double alpha(double l) = 0;
        virtual double beta(double l) = 0;
        virtual double theta(double l) = 0;
        virtual double width(double l) = 0;

        virtual ~RoadBuilder();
    };

    /* RoadBuilder rb describes the road's properties
     * delta_l is frequency of discretization of the road in meters
     * length is lenght of the road
     * name should be specified if you use more than one road in scene */
    Road(RoadBuilder &rb, double delta_l, double lenght, std::string name="Default name");

    void setColor(cv::viz::Color color) { this->color = color; }
    void setName(std::string name) { this->name = name; }
    void show(cv::viz::Viz3d &window);
};
