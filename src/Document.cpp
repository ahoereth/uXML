/*
 * uXML/src/Element.cpp
 *
 * Copyright 2015 Alexander Hoereth
 */

#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include "Document.hpp"
#include "Element.hpp"
#include "boost/smart_ptr.hpp"

namespace uXML {

/**
 * Construct a uXML document container for holding uXML elements.
 */
Document::Document(void) {}


/**
* Construct an uXML document objectby only providing its name.
*
* @param {std::string} name XML document filename.
*/
Document::Document(const std::string& name) : name(name) {}


/**
 * Construct an uXML document object with name and its root element.
 *
 * @param {std::string}   name XML tag name.
 * @param {uXML::Element} elem Root element.
 */
Document::Document(
  const std::string& name,
  const Element& elem
) : name(name) {
  setRoot(elem);
}


/** Destructor */
Document::~Document(void) {
//  delete root;
}


/**
 * Define a root element for the future XML document.
 *
 * @param {uXML::Element} elem
 */
void Document::setRoot(const Element& elem) {
  root = boost::make_shared<Element>(elem);
}


/**
 * Check if the document has a root element.
 *
 * @return {bool}
 */
bool Document::hasRoot() {
  return (true == static_cast<bool>(root));
}


/**
 * Create the XML document tree as string starting from the defined
 * root element.
 *
 * @return {std::string} Valid XML document text.
 */
std::string Document::toString() {
  if (hasRoot()) {
    return root->toString();
  } else {
    return "";
  }
}


/**
 * Write the XML tree starting with the root element into a file.
 *
 * TODO: Stream into the file element by element for better performance.
 *
 * @param  {std::string} filename Target filename including path. Defaults to
 *                                the documents name + `.xml` extension or, if
 *                                no name defined, `uXML.xml`.
 * @return {bool}        Success/failure information.
 */
bool Document::toFile(const std::string& filename) {
  std::string fn = filename.c_str();

  // Default filename.
  if (fn.empty()) {
    fn = !getName().empty() ? getName() : "uXML";
  }

  // `.xml` filename extension.
  if (fn.find_last_of(".") == std::string::npos) {
    fn += ".xml";
  }

  // Write to file.
  std::ofstream file(fn.c_str());
  if (file.is_open()) {
    file << toString();
    file.close();
    return true;
  } else {
    return false;
  }
}


}  // namespace uXML
