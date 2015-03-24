/*
 * StringElement.cpp
 *
 *  Created on: Mar 4, 2015
 *      Author: elte
 */

#include <sdf_builder/StringElement.h>

namespace sdf_builder {

StringElement::StringElement()
{}

StringElement::~StringElement()
{}

StringElement::StringElement(const std::string & contents):
	contents(contents)
{}

StringElement * StringElement::clone() const {
	return new StringElement(*this);
}

std::string StringElement::toXML() {
	return contents;
}

} /* namespace sdf_builder */
