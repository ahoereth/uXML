/**
 * uXML/src/Attribute.hpp
 *
 * Header file for ./Attribute.cpp
 *
 * Copyright 2015 Alexander Hoereth
 */

#ifndef __uXML_ATTRIBUTE_INCLUDE__
#define __uXML_ATTRIBUTE_INCLUDE__

#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>
#include "boost/smart_ptr.hpp"

namespace uXML {

/**
 * Basic struct for XML tag attribute style key value pairs with a toString
 * function.
 *
 * Example:
 * `("key", "value")->toString() == "key=\"value\""``
 */
class Attribute {
 private:
  std::string name;
  std::string value;

 public:
  Attribute(const std::string& name, const std::string& value);
  Attribute(const std::string& name, int value);
  std::string toString();
  std::string getName() { return name; }
  std::string getValue() { return value; }
};

}  // namespace uXML

#endif
