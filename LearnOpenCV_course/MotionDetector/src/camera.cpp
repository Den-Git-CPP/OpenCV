#include "camera.hpp"


camera::camera(int id, logger::Logger logger) : m_id(id), m_logger(logger)
{}

camera::~camera()
{}

bool camera::open() {
    m_cam.open(m_id, cv::CAP_ANY);
    if (!m_cam.isOpened()) {
        m_logger.add_log(0, "Failed to open Camera");
        return false;
    }
    m_logger.add_log(3, "Success to open the camera");
    return true;
}

cv::Mat camera::get_frame() {
    cv::Mat frame;
    m_cam.read(frame);
    if (frame.empty()) {
        m_logger.add_log(0, "Cannot get the last frame");
    }
    return frame;
}