#include <opencv2/highgui.hpp>
#include <opencv2/core.hpp>

#include "road.h"
#include "scenefacade.h"

const double pi = atan(1) * 4;

class myRoadBuilder : public Road::RoadBuilder {
public:
    virtual double alpha(double l) override { return 0; }
    virtual double beta(double l) override {
        return 0;
        if (l < 20)
            return 0;
        if (l < 22)
            return 0 + sin( (l - 20) / 2 * pi / 2) * 6. / 180 * pi;

        return 6. / 180 * pi;

        return 0;
    }
    virtual double theta(double l) override {
        if (l < 1500)
            return 0;

        return 0.002 * l;
    }
    virtual double width(double l) override {
        if (l < 20)
            return 3.2;
        return std::min(3.2 + (l - 20) * 0.1, 4.8);
    }
};

int main()
{
    myRoadBuilder mrb;

    sceneParameters sp;
    sp.lenght = 500;
    sp.d = 10;
    cv::Mat img = getPicture(mrb, sp);
    cv::imwrite("2.png", img);
    cv::imshow("", img);
    cv::waitKey();

    return 0;
}
