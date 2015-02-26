/*
 * Joint.cpp
 *
 *  Created on: Feb 24, 2015
 *      Author: elte
 */

#include <sdf_builder/joint/axis/Axis.h>
#include <sdf_builder/joint/Joint.h>

namespace sdf_builder {

Joint::Joint(std::string nm):
	Posable(nm)
{}

Joint::Joint(LinkPtr parent, LinkPtr child):
	Posable("joint_"+parent->name()+"_"+child->name()),
	parent(parent),
	child(child),
	axis(AxisPtr(new Axis))
{}

Joint::Joint(std::string nm, LinkPtr parent, LinkPtr child):
	Posable(nm),
	parent(parent),
	child(child),
	axis(AxisPtr(new Axis))
{}

Joint::~Joint()
{}

} /* namespace sdf_builder */
