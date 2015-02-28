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
		// TODO Check whether this is correct
		my = Util::toLocalFrame(my, this);;
		myNormal = Util::toLocalFrame(myNormal, this);
		myTangent = Util::toLocalFrame(myTangent, this);
		at = Util::toLocalFrame(at, ofptr);
		atNormal = Util::toLocalFrame(atNormal, ofptr);
		atTangent = Util::toLocalFrame(atTangent, ofptr);
	}

	// 1) Rotate to align myNormal with atNormal
	// - Find quaternion to rotate myNormal to align
	//   with the inverse of atNormal (pointing inwards)
	// Note that Eigen3 handles the case of anti-parallel
	// vectors for us!
	auto alignNormal = Quaternion::FromTwoVectors(
		Util::toParentFrame(myNormal, this),
		Util::toParentFrame(-atNormal, ofptr)
	);

//	std::cerr << "rotation: " << alignNormal.w() << ' '
//			<< alignNormal.x() << ' ' << alignNormal.y() << ' '
//			<< alignNormal.z() << std::endl;

	this->rotation(alignNormal);

//	auto mtp = Util::toParentFrame(myTangent, this);
//	std::cerr << "mtp " << mtp.x() << ' ' << mtp.y() << ' ' << mtp.z() << std::endl;

	// 2) Rotate to align `myTangent` with `atTangent` in
	//    a similar fashion as above.
	auto alignTangent = Quaternion::FromTwoVectors(
		Util::toParentFrame(myTangent, this),
		Util::toParentFrame(atTangent, ofptr)
	);

//	std::cerr << "rotation2: " << alignTangent.w() << ' '
//			<< alignTangent.x() << ' ' << alignTangent.y() << ' '
//			<< alignTangent.z() << std::endl;

	this->rotation(alignTangent);

	// 3) Translate so that `my` lands at `at`
	auto translation = Util::toParentFrame(at, ofptr)
						- Util::toParentFrame(my, this);
	position(position() + translation);

	// TODO Check axis are parallel
}

void Posable::rotateAround(Vector3 vector, double angle, bool relativeToChildFrame) {
	// TODO implement
}

/**
 * Swap behavior
 */
void swap(Posable & a, Posable & b) {
	using std::swap;
	swap(a.pose_, b.pose_);
}

} /* namespace sdf_builder */
