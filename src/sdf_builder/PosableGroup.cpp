/*
 * LinkGroup.cpp
 *
 *  Created on: Feb 28, 2015
 *      Author: elte
 */

#include <sdf_builder/PosableGroup.h>

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

void PosableGroup::rotation(const Quaternion & rot) {
	Vector3 rootPosition = this->position();

	// Rotate children
	std::vector<PosablePtr>::iterator it = this->posables_.begin();
	for (; it != this->posables_.end(); ++it) {
		PosablePtr child = (*it);
		Vector3 curPosition = child->position();
		Vector3 relPosition = curPosition - rootPosition;

		// Rotate relPosition
		Vector3 newPosition = rot * relPosition;
		child->position(newPosition);

		Quaternion curRotation = child->rotation();
		child->rotation(rot * curRotation);
	}
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
