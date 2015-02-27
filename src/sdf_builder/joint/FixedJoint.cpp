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

void FixedJoint::init() {
	this->axis->limit.reset(new Limit(0, 0));
}

FixedJoint::~FixedJoint() {}

} /* namespace sdf_builder */
