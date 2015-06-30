/**
 * uXML/test/tests.cpp
 *
 * Tests for uXML::Element and uXML::Attribute.
 *
 * Copyright 2015 Alexander Hoereth
 */

// TODO: Seperate into 2 individual test files.

#define BOOST_TEST_MODULE uXML tests
#include "../src/Element.hpp"
#include "../src/Attribute.hpp"
#include "boost/test/included/unit_test.hpp"


BOOST_AUTO_TEST_CASE(uXML_Attribute_test) {
  uXML::Attribute attribute = uXML::Attribute("name", "value");

  BOOST_CHECK_EQUAL(attribute.getName(), "name");
  BOOST_CHECK_EQUAL(attribute.getValue(), "value");
  BOOST_CHECK_EQUAL(attribute.toString(), "name=\"value\"");
}


BOOST_AUTO_TEST_CASE(uXML_Element_test) {
  // #1
  // Single self-enclosed element.
  uXML::Element parent = uXML::Element("papa");
  BOOST_CHECK_EQUAL(parent.toString(), "<papa/>\n");

  // #2
  // Single self-enclosed element with attribute.
  parent.addAttribute("key", "value");
  BOOST_CHECK_EQUAL(parent.toString(), "<papa key=\"value\"/>\n");

  // #3
  // Single element with attribute and child element with attribute.
  uXML::Element child =
    uXML::Element("lilfoot", "childkey", "childvalue");
  parent.addElement(child);
  BOOST_CHECK_EQUAL(parent.toString(),
    "<papa key=\"value\">\n  <lilfoot childkey=\"childvalue\"/>\n</papa>\n");

  // #4
  // Element with attribute, child element and self-enclosed sibling element.
  uXML::Element sibling = uXML::Element("bro");
  parent.addSibling(sibling);
  BOOST_CHECK_EQUAL(parent.toString(), "<papa key=\"value\">\n  "
    "<lilfoot childkey=\"childvalue\"/>\n</papa>\n\n<bro/>\n");

  // #5
  // Container with two elements.
  uXML::Element container = uXML::Element();
  container.addElement(sibling);
  container.addElement(child);
  BOOST_CHECK_EQUAL(container.toString(),
    "<bro/>\n<lilfoot childkey=\"childvalue\"/>\n");

  // #6
  // Test getters.
  BOOST_CHECK_EQUAL(parent.getName(), "papa");

  // #7
  // Checking attribute existence.
  BOOST_CHECK_EQUAL(parent.hasAttribute("key"), true);
  BOOST_CHECK_EQUAL(parent.hasAttribute("woop"), false);

  // #8
  // Getting attribute value by name.
  BOOST_CHECK_EQUAL(child.getAttributeValue("childkey"), "childvalue");
}
