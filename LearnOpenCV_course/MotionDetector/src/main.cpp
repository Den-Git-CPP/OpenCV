#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

#include "camera.hpp"
#include "logger.hpp"

int main ()
{
    auto _logger = logger::Logger ("log.txt", 4, true);
    auto cam     = camera (0, _logger);
    if (cam.open ()) {
        for (;;) {
            auto frame = cam.get_frame ();
            cv::imshow ("Camera", frame);
            if (cv::waitKey (5) >= 0) break;
        }
    }
    return 0;
}
