/*
 * Posable.cpp
 *
 *  Created on: Feb 24, 2015
 *      Author: elte
 */

#include <sdf_builder/Posable.h>
#include <sdf_builder/util/Util.h>

#include <iostream>
#include <cmath>

namespace sdf_builder {

Posable::Posable(std::string name):
	name_(name),
	pose_(PosePtr(new Pose))
{}
Posable::~Posable() {}

// Copy constructor creates a new pose
Posable::Posable(const Posable &posable):
	name_(posable.name_),
	pose_(PosePtr(posable.pose_->clone()))
{}

PosePtr Posable::pose() {
	return pose_;
}

const std::string & Posable::name() {
	return name_;
}

void Posable::name(std::string nm) {
	name_ = nm;
}

void Posable::position(const Vector3& pos) {
	this->pose_->position(pos);
}

void Posable::rotation(const Quaternion &rot) {
	this->pose_->rotation(rot);
}

const Vector3 & Posable::position() {
	return this->pose_->position();
}

const Quaternion & Posable::rotation() {
	return this->pose_->rotation();
}


void Posable::align(Vector3 my, Vector3 myNormal, Vector3 myTangent,
		Vector3 at, Vector3 atNormal, Vector3 atTangent,
		PosablePtr of, bool relativeToChildFrame) {

	Posable* ofptr = of.get();
	if (relativeToChildFrame == RELATIVE_TO_PARENT_FRAME) {
		// Perform a one-time conversion of all the vectors
		// to the child frame for convenience.
		my = Util::toLocalFrame(my, this);
		myNormal = Util::toLocalFrame(myNormal, this);
		myTangent = Util::toLocalFrame(myTangent, this);
		at = Util::toLocalFrame(at, ofptr);
		atNormal = Util::toLocalFrame(atNormal, ofptr);
		atTangent = Util::toLocalFrame(atTangent, ofptr);
	}

	// 1) Rotate to align myNormal with atNormal
	// - Find quaternion to rotate myNormal to align
	//   with the inverse of atNormal (pointing inwards)
	align(myNormal, -atNormal, of);

	// 2) Rotate to align `myTangent` with `atTangent` in
	//    a similar fashion as above.
	align(myTangent, atTangent, of);

	// 3) Translate so that `my` lands at `at`
	auto myPosition = Util::toParentFrame(my, this);
	auto atPosition = Util::toParentFrame(at, ofptr);
	auto translation = atPosition - myPosition;
	position(position() + translation);
	// TODO Check axis are parallel
}

void Posable::align(const Vector3 & my, const Vector3 & other, PosablePtr of,
		bool relativeToChildFrame) {

	Posable* ofptr = of.get();
	auto myParentVec = relativeToChildFrame ?
			Util::toParentDirection(my, this) :
			Util::toParentDirection(Util::toLocalFrame(my, this), this);
	auto otherParentVec = relativeToChildFrame ?
				Util::toParentDirection(other, ofptr) :
				Util::toParentDirection(Util::toLocalFrame(other, ofptr), ofptr);

//	std::cerr << "Aligning:\n" << myParentVec
//					  << "\nWith:\n" << otherParentVec
//					  << std::endl;

	if (Util::PARALLEL == Util::vectorParallellism(myParentVec, otherParentVec)) {
		// Nothing needs to happen.
		return;
	}

	// Eigen3 handles the case of opposite vectors
	Quaternion rot = Quaternion::FromTwoVectors(myParentVec, otherParentVec);
//	std::cerr << "Rotation: "
//			<< rot.w() << ' '
//			<< rot.x() << ' '
//			<< rot.y() << ' '
//			<< rot.z() << std::endl;

	this->rotation(rot);
}

void Posable::rotateAround(Vector3 axis, double angle, bool relativeToChildFrame) {
	if (relativeToChildFrame) {
		axis = Util::toLocalFrame(axis, this);
	}

	Quaternion rot(AngleAxis(angle, axis));
	rotation(rotation() * rot);
}

/**
 * Swap behavior
 */
void swap(Posable & a, Posable & b) {
	using std::swap;
	swap(a.pose_, b.pose_);
}

} /* namespace sdf_builder */
