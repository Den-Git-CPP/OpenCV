#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

#include "logger.hpp"


class camera
{
private:
    int m_id;
    cv::VideoCapture m_cam;
    logger::Logger m_logger;

public:
    camera(int id, logger::Logger logger);
    ~camera();

    bool open();
    cv::Mat get_frame();
};

#endif /* !CAMERA_HPP */