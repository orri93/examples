/*
 * OpenCV Face Detection example see
 * https://www.geeksforgeeks.org/opencv-c-program-face-detection
 * https://docs.opencv.org/3.4/db/d28/tutorial_cascade_classifier.html
 */

#include <cstdlib>

#include <iostream>
#include <vector>

#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#define DEVICE_ID 0
#define WINDOW_NAME "Live Face Detection"

 /* Extract Process name from argument */
static std::string epname(const char* a);
static int usage(const char* a);
static void detect(
  cv::Mat& image,
  cv::CascadeClassifier& cascade,
  cv::CascadeClassifier& nested,
  const double scale = 1.0);

int main(int argc, char** argv) {
  int wk;

  cv::Mat frame, image;

  cv::VideoCapture capture;

  cv::CascadeClassifier cascade, nested;

  if (argc < 3) {
    return usage(argv[0]);
  }

  if (cascade.load(argv[1])) {
    std::cout << "Successfully loaded " << argv[1]
      << " as main Cascade Classifier" << std::endl;
  } else {
    std::cerr << "Failed to load "
      << argv[1] << " as main Cascade Classifier" << std::endl;
    return EXIT_FAILURE;
  }

  if (nested.load(argv[2])) {
    std::cout << "Successfully loaded " << argv[2]
      << " as nested Cascade Classifier" << std::endl;
  } else {
    std::cerr << "Failed to load "
      << argv[2] << " as nested Cascade Classifier" << std::endl;
    return EXIT_FAILURE;
  }

  capture.open(DEVICE_ID);

  if (capture.isOpened()) {
    bool go = true;
    bool havewin = false;

    std::cout << "Face Detection Started..." << std::endl;
    std::cout << "Press 'Q' to terminate" << std::endl;

    while (go) {
      capture >> frame;

      if (!frame.empty()) {
        if (!havewin) {
          cv::namedWindow(WINDOW_NAME, cv::WINDOW_AUTOSIZE);
          havewin = true;
        }
        image = frame.clone();
        detect(image, cascade, nested);
        cv::imshow(WINDOW_NAME, image);
      } else {
        std::cerr << "Blank frame" << std::endl;
        return EXIT_FAILURE;
      }

      wk = cv::waitKey(5);
      if (wk == 27 || wk == 'q' || wk == 'Q' ) {
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

std::string epname(const char* a) {
  size_t f;
  std::string s(a);
#ifdef _WIN32
  f = s.rfind('\\');
#else
  f = s.rfind('/');
#endif
  if (f != std::string::npos) {
    s = s.substr(f + 1);
  }
  f = s.find('.');
  if (f != std::string::npos) {
    s = s.substr(0, f);
  }
  return s;
}

int usage(const char* a) {
  std::cerr << "usage: " << epname(a)
    << " <classifier> <nested classifier>" << std::endl;
  return EXIT_FAILURE;
}

void detect(
  cv::Mat& image,
  cv::CascadeClassifier& cascade,
  cv::CascadeClassifier& nested,
  const double scale) {
  double ratio;
  int radius;

  std::vector<cv::Rect> faces, eyes;
  cv::Mat gray, small, roi;

  double fx = 1.0 / scale;

  // Convert to Gray scale
  cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);

  // Resize the Gray scale Image
  cv::resize(gray, small, cv::Size(), fx, fx, cv::INTER_LINEAR);
  cv::equalizeHist(small, small);

  // Detect faces of different sizes using cascade classifier  
  cascade.detectMultiScale(
    small,                        // Image
    faces,                        // Objects
    1.1,                          // Scale factor
    2,                            // Minimum neighbors
    0 | cv::CASCADE_SCALE_IMAGE,  // Flags
    cv::Size(30, 30));            // Minimum size

  // Draw circles around the faces
  for (size_t i = 0; i < faces.size(); i++) {
    cv::Scalar color = cv::Scalar(255, 0, 0); // Color for Drawing
    cv::Rect rect = faces.at(i);
    cv::Point center;
    ratio = ((double)rect.width) / ((double)rect.height);
    if (ratio >= 0.75 && ratio < 1.3) {
      center.x = cvRound((rect.x + rect.width * 0.5) * scale);
      center.y = cvRound((rect.y + rect.height * 0.5) * scale);
      radius = cvRound((((double)rect.width) + ((double)rect.height))
        * 0.25 * scale);
      cv::circle(image, center, radius, color, 3, 8, 0);
    } else {
      cv::rectangle(
        image,
        cv::Point(cvRound(rect.x * scale), cvRound(rect.y * scale)),
        cv::Point(cvRound((((double)rect.x) + ((double)rect.width) - 1.0)
          * scale),
        cvRound((((double)rect.y) + ((double)rect.height) - 1.0) * scale)),
        color,
        3,
        8,
        0);
    }
    if (!nested.empty()) {
      roi = small(rect);
      nested.detectMultiScale(
        roi,                          // Image
        eyes,                         // Objects
        1.1,                          // Scale factor
        2,                            // Minimum neighbors
        0 | cv::CASCADE_SCALE_IMAGE,  // Flags
        cv::Size(30, 30));            // Minimum size

      // Draw circles around eyes
      for (size_t j = 0; j < eyes.size(); j++) {
        cv::Rect eye = eyes.at(i);
        center.x = cvRound((
          ((double)rect.x) +
          ((double)eye.x) +
          ((double)eye.width) * 0.5) * scale);
        center.y = cvRound((
          ((double)rect.y) +
          ((double)eye.y) +
          ((double)eye.height) * 0.5) * scale);
        radius = cvRound((
          ((double)eye.width) + ((double)eye.height)) * 0.25 * scale);
        cv::circle(image, center, radius, color, 3, 8, 0);
      }
    }
  }
}
