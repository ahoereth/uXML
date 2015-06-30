/**
 * uXML/src/Attribute.cpp
 *
 * Copyright 2015 Alexander Hoereth
 */

#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <iostream>
#include "Attribute.hpp"
#include "boost/smart_ptr.hpp"

namespace uXML {

/**
 * Construct a XML attribute with its name and a string value.
 *
 * @param {std::string} name  Attribute name.
 * @param {std::string} value Attribute value.
 */
Attribute::Attribute(const std::string& name, const std::string& value)
  : name(name), value(value) {}



/**
 * Construct a XML attribute with name and an int value.
 *
 * @param {std::string} name  Attribute name.
 * @param {int}         value Attribute value.
 */
Attribute::Attribute(const std::string& name, int intValue) : name(name) {
  std::stringstream ss;
  ss << intValue;
  value = ss.str();
}


/**
 * Parses the name and value into a `key="value"`` style string ready to use
 * as part of a XML element.
 *
 * @return {std::string}
 */
std::string Attribute::toString() {
  return getName() + "=\"" + getValue() + "\"";
}


}  // namespace uXML
