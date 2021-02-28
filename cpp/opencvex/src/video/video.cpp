/*
 * Video capturing example see
 * https://docs.opencv.org/master/d8/dfe/classcv_1_1VideoCapture.html
 */

#include <cstdlib>

#include <iostream>

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>

#define DEVICE_ID 0
#define WINDOW_NAME "Live"

int main(int argc, char** argv) {
  int wk;

  cv::Mat frame;

  cv::VideoCapture capture;

  capture.open(DEVICE_ID, cv::CAP_ANY);

  if (capture.isOpened()) {
    bool go = true;
    bool havewin = false;

    std::cout << "Start grabbing" << std::endl;
    std::cout << "Press any key to terminate" << std::endl;

    while (go) {
      capture.read(frame);

      if (!frame.empty()) {
        if (!havewin) {
          cv::namedWindow(WINDOW_NAME, cv::WINDOW_AUTOSIZE);
          havewin = true;
        }
        cv::imshow(WINDOW_NAME, frame);
      } else {
        std::cerr << "Blank frame" << std::endl;
        return EXIT_FAILURE;
      }

      wk = cv::waitKey(5);
      if (wk >= 0) {
        std::cout << "Ending the loop" << std::endl;
        go = false;
      }
    }

    return EXIT_SUCCESS;
  } else {
    std::cerr << "Failed to open default camera" << std::endl;
    return EXIT_FAILURE;
  }
}
