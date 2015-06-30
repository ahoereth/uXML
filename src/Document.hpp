/**
 * uXML/src/Document.hpp
 *
 * Header file for ./Document.cpp
 *
 * Copyright 2015 Alexander Hoereth
 */

#ifndef __uXML_DOCUMENT_INCLUDE__
#define __uXML_DOCUMENT_INCLUDE__

#include <string>
#include <vector>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include "boost/smart_ptr.hpp"
#include "Element.hpp"

namespace uXML {


/**
 * Class for creating XML documents with a single root element.
 */
class Document {
 private:
  std::string name;
  boost::shared_ptr<Element> root;

 public:
  Document(void);
  explicit Document(const std::string& name);
  Document(const std::string& name, const Element& root);
  ~Document(void);
  void setRoot(const Element& elem);
  bool hasRoot();
  std::string getName() { return name; }
  std::string toString();
  bool toFile(const std::string& filename = "");
};


}  // namespace uXML

#endif
