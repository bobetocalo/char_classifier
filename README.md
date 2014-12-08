char_classifier
===============

Multiclass random trees classifier for OCR using C++, [OpenCV](http://www.opencv.org) and [Boost](http://www.boost.org).

[Random trees](http://www.stat.berkeley.edu/~breiman/RandomForests/) classifier operate by constructing a multitude of decision trees at training time and outputting the class that is the mode of the classes output by individual trees. We are capable of train and test this classifier using the [generate_bd](https://github.com/bobetocalo/generate_db/blob/master/README.md) synthetic images. The cross validation technique estimates how accurately a predictive model will perform in practice (training set independence).
```
Allowed options
  1) Test classifier performance
  2) Train random trees classifier
  3) Test random trees classifier

Enter the option: 1
Cross validation ...
Average hit rate: 98.6443%
```
