/** ****************************************************************************
 *  @file    Constants.hpp
 *  @brief   Identifier whose associated value cannot be altered.
 *  @author  Roberto Valle Fernandez.
 *  @date    2012/01
 *  @copyright All rights reserved.
 *  Escuela Tecnica Superior de Ingenieria Informatica (Computer Science School)
 *  Universidad Rey Juan Carlos (Spain)
 ******************************************************************************/

// ------------------ RECURSION PROTECTION -------------------------------------
#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

namespace urjc {

/** ****************************************************************************
 * @class Constants
 * @brief Class identifiers used by the computer vision algorithms.
 ******************************************************************************/
class Constants
{
public:

  static const char *CHARS_DIR, *CLASSIFIERS_DIR;
  static const unsigned IMG_WIDTH, IMG_HEIGHT;
};

} // close namespace urjc

#endif /* CONSTANTS_HPP */
