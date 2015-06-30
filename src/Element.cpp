/*
 * uXML/src/Element.cpp
 *
 * Copyright 2015 Alexander Hoereth
 */

#include <string>
#include <sstream>
#include <vector>
#include <cstdlib>
#include <iostream>
#include "Attribute.hpp"
#include "Element.hpp"
#include "boost/smart_ptr.hpp"

namespace uXML {


/**
 *
 */
Element::Element() {}


/**
* Construct an uXML object by only providing its name.
*
* @param  {std::string} name XML tag name.
*/
Element::Element(const std::string& name) : name(name) {}


/**
 * Construct an uXML object with name and a first attribute with `int` value.
 *
 * @param {std::string} name      XML tag name.
 * @param {std::string} attrName  Attribute name.
 * @param {int}         attrValue Attribute value.
 */
Element::Element(
  const std::string& name,
  const std::string& attrName,
  int attrValue
) : name(name) {
  addAttribute(attrName, attrValue);
}


/**
 * Construct an uXML element with name and a first attribute with `string
 * value.
 *
 * @param {std::string} name      XML tag name.
 * @param {std::string} attrName  Attribute name.
 * @param {std::string} attrValue Attribute value.
 */
Element::Element(
  const std::string& name,
  const std::string& attrName,
  const std::string& attrValue
) : name(name) {
  addAttribute(attrName, attrValue);
}


/** Destructor */
Element::~Element(void) {
//  delete child;
//  delete sibling;
}


/**
 * Add a new attribute to the element.
 *
 * @param {uXML::Attribute} attribute
 */
void Element::addAttribute(const Attribute& attribute) {
  attributes.insert(attributes.end(), attribute);
}


/**
 * Add a new attribute to the element from a key `int` value pair.
 *
 * @param {std::string} name  Attribute name.
 * @param {int}         value Attribute value.
 */
void Element::addAttribute(const std::string& name, int value) {
  addAttribute(Attribute(name, value));
}


/**
 * Add a new attribute to the element from a key `string` value pair.
 *
 * @param {std::string} name  Attribute name.
 * @param {std::string} value Attribute value.
 */
void Element::addAttribute(
  const std::string& name,
  const std::string& value
) {
  addAttribute(Attribute(name, value));
}


/**
 * Define a XML element to include in the current XML element's body. The
 * child element can have its own child and sibling. Using those a whole XML
 * tree can be constructed recursively.
 *
 * @param {Element*} child Child element.
 */
void Element::addElement(const Element& elem) {
  if (name.empty()) {
    addSibling(elem);
  } else if (hasChild()) {
    child->addSibling(elem);
  } else {
    child = boost::make_shared<Element>(elem);
  }
}


/**
 * Define a XML element to follow after the current XML element in the
 * XML document tree. The sibling element itself can have its own child and
 * sibling. Using those a whole XML tree can be constructed recursively.
 *
 * @param {Element*} next Sibling element.
 */
void Element::addSibling(const Element& elem) {
  if (!sibling) {
    sibling = boost::make_shared<Element>(elem);
  } else {
    sibling->addSibling(elem);
  }
}


/**
 * Check if the element has a sibling element.
 *
 * @return {bool}
 */
bool Element::hasSibling() {
  return (true == static_cast<bool>(sibling));
}


/**
 * Check if the element has a child element.
 *
 * @return {bool}
 */
bool Element::hasChild() {
  return (true == static_cast<bool>(child));
}


std::string Element::getAttributeValue(const std::string& name) {
  std::string value;
  for (std::vector<Attribute>::iterator it = attributes.begin();
       it != attributes.end(); ++it) {
    if (it->getName().compare(name) == 0) {
      value = it->getValue();
      break;
    }
  }

  return value;
}


/**
 *
 */
bool Element::hasAttribute(const std::string& name) {
  return (!getAttributeValue(name).empty());
}


/**
 * Create the XML document tree string recursively starting with the current
 * element.
 *
 * @param  {int} depth Indention level, default 0.
 * @return {std::string} Valid (hopefully) XML tree.
 */
std::string Element::toString(int depth) {
  std::string value;

  if (!name.empty()) {
    // Handle indention, 2 spaces per depth level.
    std::string indent = "";
    for (int i = 0; i < depth; i++) { indent += "  "; }

    // Start open element tag with name.
    value += indent + "<" + name;

    // Fill tag with attribute key value pairs.
    for (std::vector<Attribute>::iterator it = attributes.begin();
         it != attributes.end(); ++it) {
      value += " " + it->toString();
    }

    if (child) {
      // Close opening tag, parse children and add closing tag.
      value += ">\n" + child->toString(depth+1) + indent + "</" + name + ">\n";
    } else {
      // No children, close opening tag.
      value += "/>\n";
    }
  }

  if (sibling) {
    if (hasChild() || sibling->hasChild()) { value += "\n"; }
    value += sibling->toString(depth);
  }

  return value;
}


}  // namespace uXML
