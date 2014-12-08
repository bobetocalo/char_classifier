/** ****************************************************************************
 *  @file    RTClassifier.hpp
 *  @brief   Train or test a random trees classifier.
 *  @author  Roberto Valle Fernandez.
 *  @date    2012/01
 *  @copyright All rights reserved.
 *  Escuela Tecnica Superior de Ingenieria Informatica (Computer Science School)
 *  Universidad Rey Juan Carlos (Spain)
 ******************************************************************************/

#ifndef RTCLASSIFIER_HPP
#define RTCLASSIFIER_HPP

// ----------------------- INCLUDES --------------------------------------------
#include <opencv/cv.h>
#include <opencv/ml.h>

#include <string>
#include <vector>

namespace urjc {

/** ****************************************************************************
 * @class RTClassifier
 * @brief A class that allow us train or test a random trees classifier.
 ******************************************************************************/
class RTClassifier
{
public:

  // Constructor.
  RTClassifier
    () {};

  // Destroyer.
  ~RTClassifier
    () {};

  /**
   * @brief Compute the quality of a random trees multiclass classifier and
   * check how the results of an analysis will generalize to an independent
   * training data set.
   */
  float
  crossValidation
    (
    const int K_FOLD,
    cv::Mat data,
    cv::Mat label
    );

  /**
   * @brief Trains the random trees model and returns the train error.
   */
  float
  trainClassifier
    (
    cv::Mat data,
    cv::Mat labels
    );

  /**
   * @brief Predicts the output for an input sample.
   */
  float
  testClassifier
    (
    cv::Mat data
    );

  /**
   * @brief Loads the complete model state.
   */
  void
  loadClassifier
    (
    std::string name
    );

  /**
   * @brief Saves the complete model state to the specified XML.
   */
  void
  saveClassifier
    (
    std::string name
    );

private:

  cv::RandomTrees m_classifier;
};

}; // close namespace urjc

#endif /* RTCLASSIFIER_HPP */
