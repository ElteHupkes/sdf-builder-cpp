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

StringElement::StringElement(const StringElement & other):
	contents(other.contents)
{}

StringElement * StringElement::clone() const {
	return new StringElement(*this);
}

void swap(StringElement & a, StringElement & b) {
	using std::swap;
	swap(a.contents, b.contents);
}

StringElement & StringElement::operator=(StringElement other) {
	swap(*this, other);
	return *this;
}

std::string StringElement::toXML() {
	return contents;
}

} /* namespace sdf_builder */
