/*
 * Collision.cpp
 *
 *  Created on: Feb 25, 2015
 *      Author: elte
 */

#include <sdf_builder/shape/Collision.h>

namespace sdf_builder {

Collision::~Collision()
{}

Collision * Collision::clone() const {
	return new Collision(*this);
}

Collision & Collision::operator=(Collision other) {
	using std::swap;

	swap(*this, other);
	return *this;
}

std::string Collision::toXML() {
	std::stringstream out;

	out << "<collision name=\"" << name_ << "\">"
			<< pose_->toXML()
			<< geometry_->toXML()
			<< "</collision>";

	return out.str();
}

} /* namespace sdf_builder */
