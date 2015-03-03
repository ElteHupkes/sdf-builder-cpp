/*
 * LinkGroup.cpp
 *
 *  Created on: Feb 28, 2015
 *      Author: elte
 */

#include <sdf_builder/PosableGroup.h>
#include <iostream>

namespace sdf_builder {

PosableGroup::PosableGroup(const PosableGroup & other):
	Posable(other),
	PosableParent(other)
{}

PosableGroup::~PosableGroup()
{}

void swap(PosableGroup & a, PosableGroup & b) {
	using std::swap;

	// Call for all parent classes
	swap(static_cast<Posable &>(a), static_cast<Posable &>(b));
	swap(static_cast<PosableParent &>(a), static_cast<PosableParent &>(b));
}

PosableGroup * PosableGroup::clone() const {
	return new PosableGroup(*this);
}

PosableGroup & PosableGroup::operator=(PosableGroup other) {
	swap(*this, other);
	return *this;
}

void PosableGroup::position(const Vector3 & position) {
	Vector3 translation = position - this->position();

	// Reposition children
	std::vector<PosablePtr>::iterator it = this->posables_.begin();
	for (; it != this->posables_.end(); ++it) {
		PosablePtr child = (*it);
		Vector3 newPos = child->position() + translation;
		child->position(newPos);
	}

	// Store new position in pose
	this->pose_->position(position);
}

// TODO Change this, this is not correct
void PosableGroup::rotation(const Quaternion & rot) {
	Vector3 rootPosition = this->position();
	Quaternion rootRotation = this->rotation();
	Quaternion invRotation = rootRotation.conjugate();

	// Rotate children
	std::vector<PosablePtr>::iterator it = this->posables_.begin();
	for (; it != this->posables_.end(); ++it) {
		PosablePtr child = *it;

		// Get the position and rotation of the child relative
		// to this posable (i.e. as if the posable was in [0, 0]
		// with zero rotation).
		// Original position
		Vector3 origPosition = invRotation * (child->position() - rootPosition);

		// New position means rotating the original point according
		// to the new rotation.
		Vector3 newPosition = rot * origPosition;

		// Original rotation
		Quaternion origRotation = invRotation * child->rotation();

		// New rotation is rotating by the new rotation over the
		// existing rotation.
		Quaternion newRotation = rot * origRotation;

		// Set the new position and rotation
		child->position(newPosition);
		child->rotation(newRotation);
	}

	// Store new rotation in pose
	this->pose_->rotation(rot);
}


// XML conversion is just output of the posables
// Do not print the pose!
std::string PosableGroup::toXML() {
	std::stringstream out;

	for (int i = 0, l = posables_.size(); i < l; ++i) {
		out << posables_[i]->toXML() << '\n';
	}

	return out.str();
}

} /* namespace sdf_builder */
