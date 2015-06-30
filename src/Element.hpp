/**
 * uXML/src/Element.hpp
 *
 * Header file for ./Element.cpp
 *
 * Copyright 2015 Alexander Hoereth
 */

#ifndef __uXML_ELEMENT_INCLUDE__
#define __uXML_ELEMENT_INCLUDE__

#include <string>
#include <vector>
#include <cstdlib>
#include <iostream>
#include "boost/smart_ptr.hpp"
#include "Attribute.hpp"

namespace uXML {

/**
 * Class for constructing individual XML elements and complete XML document
 * trees. See local `main` function for example usage.
 */
class Element {
 private:
  std::string name;
  std::vector<Attribute> attributes;
  boost::shared_ptr<Element> child;
  boost::shared_ptr<Element> sibling;

 public:
  Element(void);
  explicit Element(const std::string& name);
  Element(const std::string& name, const std::string& attrName,
    const std::string& attrValue);
  Element(const std::string& name, const std::string& attrName, int attrValue);
  ~Element(void);
  void addAttribute(const Attribute& attribute);
  void addAttribute(const std::string& name, int value);
  void addAttribute(const std::string& name, const std::string& value);
  void addElement(const Element& elem);
  void addSibling(const Element& elem);
  bool hasChild();
  bool hasSibling();
  bool hasAttribute(const std::string& name);
  std::string getName() { return name; }
  std::string getAttributeValue(const std::string& name);
  std::string toString(int = 0);
};

}  // namespace uXML

#endif
