/*
 * Visual.cpp
 *
 *  Created on: Feb 25, 2015
 *      Author: elte
 */

#include <sdf_builder/shape/Visual.h>

namespace sdf_builder {

Visual::~Visual()
{}

Visual * Visual::clone() const {
	return new Visual(*this);
}

Visual & Visual::operator=(Visual other) {
	using std::swap;

	swap(*this, other);
	return *this;
}

std::string Visual::toXML() {
	std::stringstream out;

	out << "<visual name=\"" << name_ << "\">"
			<< pose_->toXML()
			<< geometry_->toXML()
			<< "</visual>";

	return out.str();
}

} /* namespace sdf_builder */
