# µXML
A lightweight C++ XML creation interface.



## Build
Run `make` from the projects root directory.



## Usage
Include the designated header file (`uXML/src/Element.hpp`) in your source code and link to the static library (`./bin/libuXML.a`) when building.

    // source
    #include uXML/src/Element.hpp

    // build
    g++ -L uXML/bin -luXML



## API
### uXML::Document
`uXML/src/Document.hpp`

* **Document(void)**;
* **Document(*string* name)**;
* **Document(*string* name, *Element* root)**
* **setRoot(const Element& elem)**
* *bool* **hasRoot()**
* *string* **getName()**
* *string* **toString()**
* *bool* **toFile(*string* filename = "")**


### uXML::Element
`uXML/src/Element.hpp`

* **Element(void)**
* **Element(*string* name)**
* **Element(*string* name, *string* attrName, *string* attrValue)**
* **Element(*string* name, *string* attrName, int attrValue)**
* **addAttribute(*string* name, int value)**
* **addAttribute(*string* name, *string* value)**
* **addElement(Element elem)**
* **addSibling(Element elem)**
* *bool* **hasChild()**
* *bool* **hasSibling()**
* *bool* **hasAttribute(*string* name)**
* *string* **getName()**
* *string* **getAttributeValue(*string* name)**
* *string* **toString(*int* = 0)**


### uXML::Attribute
`uXML/src/Attribute.hpp`

* **Attribute(*string* name, *string* value)**
* *string* **toString()**
* *string* **getName()**
* *string* **getValue()**
