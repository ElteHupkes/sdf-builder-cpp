/*
 * FixedJoint.cpp
 *
 *  Created on: Feb 25, 2015
 *      Author: elte
 */

#include <sdf_builder/joint/axis/Limit.h>
#include <sdf_builder/joint/FixedJoint.h>

namespace sdf_builder {

// Constructors are all inherited

FixedJoint * FixedJoint::clone() {
	return new FixedJoint(*this);
}

FixedJoint * FixedJoint::create(std::string name, PosablePtr parent, PosablePtr child) {
	return new FixedJoint(name, parent, child);
}

FixedJoint::~FixedJoint() {}

/**
 * I don't feel much like overriding all the constructors just
 * to set the limit to zero; instead we'll just force it here.
 */
std::string FixedJoint::toXML() {
	axis->limit.reset(new Limit(0, 0));
	return RevoluteJoint::toXML();
}

} /* namespace sdf_builder */
