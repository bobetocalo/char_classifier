/** ****************************************************************************
 *  @file    RTClassifier.cpp
 *  @brief   Train or test a random trees classifier.
 *  @author  Roberto Valle Fernandez.
 *  @date    2012/01
 *  @copyright All rights reserved.
 *  Escuela Tecnica Superior de Ingenieria Informatica (Computer Science School)
 *  Universidad Rey Juan Carlos (Spain)
 ******************************************************************************/

// ----------------------- INCLUDES --------------------------------------------
#include <RTClassifier.hpp>
#include <Constants.hpp>

namespace urjc {

// -----------------------------------------------------------------------------
//
// Purpose and Method:
// Inputs:
// Outputs:
// Dependencies:
// Restrictions and Caveats:
//
// -----------------------------------------------------------------------------
float
RTClassifier::crossValidation
  (
  const int K_FOLD,
  cv::Mat data,
  cv::Mat label
  )
{
  std::vector<float> tags(label);
  tags.resize(std::distance(tags.begin(), std::unique(tags.begin(), tags.end())));
  cv::Mat confusion_matrix = cv::Mat::zeros(tags.size(), tags.size(), CV_8UC1);

  // Of the k subsamples, a single subsample is retained as the validation
  // data for testing the model, and the remaining k − 1 subsamples are used
  // as training data.
  for (int i=0; i < K_FOLD; i++)
  {
    cv::Mat train_data, train_label, test_data, test_label;
    for (int j=0; j < data.rows; j++)
    {
      if (((i+j) % K_FOLD) == 0)
      {
        test_data.push_back(data.row(j));
        test_label.push_back(label.row(j));
      }
      else
      {
        train_data.push_back(data.row(j));
        train_label.push_back(label.row(j));
      }
    }
    this->trainClassifier(train_data, train_label);

    for (int j=0; j < test_data.rows; j++)
    {
      float predicted = this->testClassifier(test_data.row(j));
      int tag_predicted = std::distance(tags.begin(), std::find(tags.begin(), tags.end(), predicted));
      float real = test_label.at<float>(j,0);
      int tag_real = std::distance(tags.begin(), std::find(tags.begin(), tags.end(), real));
      confusion_matrix.at<uchar>(tag_predicted, tag_real)++;
    }
  }

  // The k results from the folds can then be averaged (or otherwise combined)
  // to produce a single estimation.
  float average = cv::sum(confusion_matrix.diag(0)).val[0]/cv::sum(confusion_matrix).val[0];
  return average;
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
float
RTClassifier::trainClassifier
  (
  cv::Mat data,
  cv::Mat label
  )
{
  // Define all the attributes as numerical
  cv::Mat var_type = cv::Mat(data.cols+1, 1, CV_8UC1);
  var_type.setTo(cv::Scalar(CV_VAR_NUMERICAL));
  // This is a classification problem
  var_type.at<uchar>(data.cols, 0) = CV_VAR_CATEGORICAL;

  // Weights of each classification
  const int NUM_DATA = label.rows;
  float priors[NUM_DATA];
  for (int i=0; i < NUM_DATA; i++)
    priors[i] = 1;

  cv::RandomTreeParams params = cv::RandomTreeParams(
      25,     // max depth of the tree
      5,      // minimum samples required at a leaf node for it to be split
      0,      // regression accuracy
      false,  // compute surrogate split, no missing data
      15,     // max number of categories (use sub-optimal algorithm for larger numbers)
      priors, // the array of labels priors
      false,  // calculate variable importance
      4,      // number of variables randomly selected at node used to find the best split
      100,    // max number of trees in the forest
      0.01f,  // forest accuracy
      CV_TERMCRIT_ITER | CV_TERMCRIT_EPS); // termination criteria

  m_classifier.train(data, CV_ROW_SAMPLE, label, cv::Mat(), cv::Mat(),
                     var_type, cv::Mat(), params);

  return m_classifier.get_train_error();
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
float
RTClassifier::testClassifier
  (
  cv::Mat data
  )
{
  // This method returns the cumulative result from all the trees in the forest
  // (the class that receives the majority of voices)
  return m_classifier.predict(data, cv::Mat());
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
RTClassifier::loadClassifier
  (
  std::string name
  )
{
  std::string filename = urjc::Constants::CLASSIFIERS_DIR + name;
  m_classifier.load(filename.c_str());
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
RTClassifier::saveClassifier
  (
  std::string name
  )
{
  std::string filename = urjc::Constants::CLASSIFIERS_DIR + name;
  m_classifier.save(filename.c_str());
}

}; // close namespace urjc
