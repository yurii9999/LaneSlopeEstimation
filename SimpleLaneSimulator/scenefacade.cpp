#include "scenefacade.h"


cv::Mat getPicture(Road::RoadBuilder &rb, sceneParameters sp) {
    Road roadNonConstWidth(rb, sp.delta_l, sp.lenght);
    roadNonConstWidth.setColor(cv::Scalar(255, 0, 0));

    cv::viz::Viz3d window;
    roadNonConstWidth.show(window);
    window.setBackgroundColor();

    cv::viz::Camera cam(sp.f, sp.f, sp.cx, sp.cy, cv::Size(sp.width, sp.height));
    window.setCamera(cam);

    cv::Point3d camPose(0, 1.2, sp.d);
    cv::Point3d cam_focal_point(0, 1.2, 1000);
    cv::Point3d cam_y_dir(0, -1, 0);
    cv::Affine3d cam_pose = cv::viz::makeCameraPose(camPose, cam_focal_point, cam_y_dir);
    window.setViewerPose(cam_pose);

    window.setOffScreenRendering();
    return window.getScreenshot();
}
