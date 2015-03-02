/*
 * FixedJoint.cpp
 *
 *  Created on: Feb 25, 2015
 *      Author: elte
 */

#include <sdf_builder/joint/RevoluteJoint.h>
#include <iostream>

namespace sdf_builder {

// Constructors are all inherited

RevoluteJoint::~RevoluteJoint()
{}

RevoluteJoint * RevoluteJoint::clone() const {
	return new RevoluteJoint(*this);
}

RevoluteJoint * RevoluteJoint::create(std::string name, PosablePtr parent, PosablePtr child) {
	return new RevoluteJoint(name, parent, child);
}

RevoluteJoint & RevoluteJoint::operator=(RevoluteJoint other) {
	using std::swap;

	swap(*this, other);
	return *this;
}

std::string RevoluteJoint::toXML() {
	std::stringstream out;

	if (!parent || !child) {
		std::cerr << "Joint " << name_ <<
				" is missing parent or child links, skipping." << std::endl;
		return "";
	}

	out << "<joint type=\"revolute\" name=\"" << name_ << "\">"
			<< pose_->toXML()
			<< "<parent>" << parent->name() << "</parent>" << '\n'
			<< "<child>" << child->name() << "</child>" << '\n'
			<< axis->toXML() << '\n'
		<< "</joint>";

	return out.str();
}

} /* namespace sdf_builder */
