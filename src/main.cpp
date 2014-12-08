/** ****************************************************************************
 *  @file    main.cpp
 *  @brief   Train a single character OCR classifier.
 *  @author  Roberto Valle Fernandez.
 *  @date    2012/01
 *  @copyright All rights reserved.
 *  Escuela Tecnica Superior de Ingenieria Informatica (Computer Science School)
 *  Universidad Rey Juan Carlos (Spain)
 ******************************************************************************/

// ----------------------- INCLUDES --------------------------------------------
#include <RTClassifier.hpp>
#include <Constants.hpp>
#include <utils.hpp>
#include <trace.hpp>

#include <string>
#include <vector>
#include <boost/filesystem.hpp>
#include <opencv/highgui.h>

namespace fs = boost::filesystem;

// -----------------------------------------------------------------------------
//
// Purpose and Method:
// Inputs:
// Outputs:
// Dependencies:
// Restrictions and Caveats:
//
// -----------------------------------------------------------------------------
void
loadImage
  (
  const std::string IMG_DIR,
  cv::Mat &img_row
  )
{
  // Input row feature vector extracted from the gray scale image
  cv::Size size = cv::Size(urjc::Constants::IMG_WIDTH, urjc::Constants::IMG_HEIGHT);
  cv::Mat img_grayscale = cv::imread(IMG_DIR, CV_LOAD_IMAGE_GRAYSCALE);
  cv::Mat img_resized;
  cv::resize(img_grayscale, img_resized, size);
  cv::threshold(img_resized, img_resized, 0, 255, cv::THRESH_OTSU);
  img_row = img_resized.reshape(0, 1);
  img_row.convertTo(img_row, CV_32FC1);
}

// -----------------------------------------------------------------------------
//
// Purpose and Method:
// Inputs:
// Outputs:
// Dependencies:
// Restrictions and Caveats:
//
// -----------------------------------------------------------------------------
void
loadDatabase
  (
  const std::string CHARS_DIR,
  cv::Mat &data,
  cv::Mat &label
  )
{
  // Open the characters database directory and read all the images
  fs::path chars_path(CHARS_DIR);
  if (fs::exists(chars_path) && fs::is_directory(chars_path))
  {
    fs::directory_iterator it1_end;
    for (fs::directory_iterator it1(chars_path) ; it1 != it1_end ; it1++)
    {
      if (fs::exists(*it1) && fs::is_directory(*it1))
      {
        int ascii = urjc::string2AsciiCode(it1->path().filename().string());
        fs::directory_iterator it2_end;
        for (fs::directory_iterator it2(*it1) ; it2 != it2_end ; it2++)
        {
          std::string ext = it2->path().extension().string();
          if ((ext.compare(".png")==0) || (ext.compare(".jpg")==0))
          {
            cv::Mat img_row;
            loadImage(it2->path().string(), img_row);
            data.push_back(img_row);
            label.push_back(ascii);
          }
        }
      }
    }
  }
  data.convertTo(data, CV_32FC1);
  label.convertTo(label, CV_32FC1);
}

// -----------------------------------------------------------------------------
//
// Purpose and Method:
// Inputs:
// Outputs:
// Dependencies:
// Restrictions and Caveats:
//
// -----------------------------------------------------------------------------
int
main
  (
  int argc,
  char **argv
  )
{
  PRINT("Allowed options");
  PRINT("  1) Test classifier performance");
  PRINT("  2) Train random trees classifier");
  PRINT("  3) Test random trees classifier");

  int option;
  std::cout << std::endl << "Enter the option: ";
  std::cin >> option;

  double ticks = static_cast<double>(cv::getTickCount());
  urjc::RTClassifier classifier;
  std::string current_dir = urjc::Constants::CHARS_DIR;
  cv::Mat data, label;
  float value;
  switch (option)
  {
    case 1:
      PRINT("Cross validation ...");
      loadDatabase(current_dir, data, label);
      value = classifier.crossValidation(5, data, label);
      PRINT("Average hit rate: " << value*100 << "%");
      break;
    case 2:
      PRINT("Train classifier ...");
      loadDatabase(current_dir, data, label);
      value = classifier.trainClassifier(data, label);
      classifier.saveClassifier("chars_classifier.xml");
      PRINT("Error estimated during the training: " << value);
      break;
    case 3:
      current_dir += argv[1]; // sample image
      PRINT("Test classifier with the input image: " << current_dir);
      loadImage(current_dir, data);
      classifier.loadClassifier("chars_classifier.xml");
      value = classifier.testClassifier(data);
      PRINT("Prediction: " << urjc::asciiCode2String(value));
      break;
    default:
      break;
  }
  ticks = static_cast<double>(cv::getTickCount() - ticks);
  PRINT("Elapsed time: " << (ticks/cv::getTickFrequency())*1000 << " ms");
  return EXIT_SUCCESS;
}
