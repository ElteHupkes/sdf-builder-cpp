/*
 * Surface.cpp
 *
 *  Created on: Mar 21, 2015
 *      Author: elte
 */

#include <sdf_builder/collision/Surface.h>
#include <sdf_builder/collision/Friction.h>

#include <sstream>

namespace sdf_builder {

Surface::Surface() {}

Surface::~Surface() {}

Surface::Surface(const Surface & other):
	friction(other.friction ? FrictionPtr(other.friction->clone()) : FrictionPtr())
	{

}

Surface & Surface::operator=(Surface other) {
	using std::swap;

	swap(*this, other);
	return *this;
}

std::string Surface::toXML() {
	std::stringstream out;

	out << "<surface>";

	out << ElementParent::toXML();

	if (friction) {
		out << friction->toXML();
	}

	out << "</surface>";

	return out.str();
}

Surface * Surface::clone() const {
	return new Surface(*this);
}

void swap(Surface & a, Surface & b) {
	using std::swap;

	swap(static_cast<ElementParent &>(a), static_cast<ElementParent &>(b));
	swap(a.friction, b.friction);
}

} /* namespace sdf_builder */
