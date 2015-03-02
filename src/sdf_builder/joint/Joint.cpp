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

Joint::Joint(PosablePtr parent, PosablePtr child):
	Posable("joint_"+parent->name()+"_"+child->name()),
	parent(parent),
	child(child),
	axis(AxisPtr(new Axis))
{}

Joint::Joint(std::string nm, PosablePtr parent, PosablePtr child):
	Posable(nm),
	parent(parent),
	child(child),
	axis(AxisPtr(new Axis))
{}

Joint::Joint(const Joint & joint):
	Posable(joint),
	axis(AxisPtr(joint.axis ? joint.axis->clone() : nullptr)),
	child(PosablePtr(joint.child ? joint.child->clone() : nullptr)),
	parent(PosablePtr(joint.parent ? joint.parent->clone() : nullptr))
{}

Joint::~Joint()
{}

void swap(Joint & a, Joint & b) {
	using std::swap;

	swap(static_cast<Posable &>(a), static_cast<Posable &>(b));
	swap(a.axis, b.axis);
	swap(a.child, b.child);
	swap(a.parent, b.parent);
}

} /* namespace sdf_builder */
