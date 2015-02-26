/*
 * FixedJoint.cpp
 *
 *  Created on: Feb 25, 2015
 *      Author: elte
 */

#include <sdf_builder/joint/axis/Limit.h>
#include <sdf_builder/joint/FixedJoint.h>

namespace sdf_builder {

FixedJoint::FixedJoint(std::string name):
	RevoluteJoint(name)
{
	init();
}

FixedJoint::FixedJoint(LinkPtr parent, LinkPtr child):
	RevoluteJoint(parent, child)
{
	init();
}

FixedJoint::FixedJoint(std::string name, LinkPtr parent, LinkPtr child):
	RevoluteJoint(name, parent, child)
{
	init();
}

void FixedJoint::init() {
	this->axis->limit.reset(new Limit(0, 0));
}

FixedJoint::~FixedJoint() {}

} /* namespace sdf_builder */
