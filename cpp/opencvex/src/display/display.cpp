/*
 * Display an image with OpenCV see
 * https://docs.opencv.org/master/db/df5/tutorial_linux_gcc_cmake.html
 */

#include <cstdlib>

#include <iostream>
#include <string>

#include <opencv2/opencv.hpp>

#define WINDOW_NAME "Display Image"

/* Extract Process name from argument */
static std::string epname(const char* a);

int main(int argc, char** argv) {
  cv::Mat image;

  if (argc < 2) {
    std::cerr << "usage: " << epname(argv[0]) << " <Image_Path>" << std::endl;
    return EXIT_FAILURE;
  }

  printf("Reading image file %s\n", argv[1]);
  image = cv::imread(argv[1]);

  if (image.data) {
    cv::namedWindow(WINDOW_NAME, cv::WINDOW_AUTOSIZE);
    cv::imshow(WINDOW_NAME, image);
    cv::waitKey();
  } else {
    fprintf(stderr, "Image file '%s' doesn't contain image data\n", argv[1]);
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
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
