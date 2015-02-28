/*
 * Posable.cpp
 *
 *  Created on: Feb 24, 2015
 *      Author: elte
 */

#include <sdf_builder/Posable.h>
#include <sdf_builder/util/Util.h>

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


// This code is very much thanks to Robogen
void Posable::align(Vector3 my, Vector3 myNormal, Vector3 myTangent,
		Vector3 at, Vector3 atNormal, Vector3 atTangent,
		PosablePtr of, double angle, bool relativeToChildFrame) {

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

	// 1) Mirror atAxis to obtain axis pointing inward
	auto invAtNormal = -atNormal;

	// 2) Find quaternion to rotate myNormal to align with atNormal
	auto rotAxisQuat = Quaternion::FromTwoVectors(
			Util::toParentFrame(myNormal, this),
			Util::toParentFrame(invAtNormal, ofptr)
	);
	this->rotation(rotAxisQuat);

	// 3) `my` has been rotated, find the new position and calculate
	//    the translation to align with `at`.
	Vector3 rotatedMy = rotAxisQuat * my;
	auto translation = Util::toParentFrame(at, ofptr) -
			Util::toParentFrame(rotatedMy, this);
	this->position(this->position() + translation);

	// TODO check axis are parallel

	// 4) Now we need to align with respect to the tangent vector
	auto alignRot = Quaternion::FromTwoVectors(
		Util::toParentFrame(myTangent, this),
		Util::toParentFrame(atTangent, ofptr)
	);

	auto myNormalParent = Util::toParentFrame(myNormal, this);

	alignRot.normalize();
	AngleAxis aa(alignRot);

	// Check if the rotation angle is parallel to the normal;
	// in which case we invert the rotation.
	if (Util::areVectorsParallel(myNormalParent, -aa.axis())) {
		aa = aa.inverse();
	}

	Quaternion tangentAlignRotation(aa);

	if (abs(angle) > 1e-6) {
		// Apply orientation w.r.t. the tangent
		Quaternion rotOrientationQuat(AngleAxis(angle, myNormalParent));
		this->rotation(tangentAlignRotation * rotOrientationQuat);
	} else {
		this->rotation(tangentAlignRotation);
	}

	// TODO Check axis are parallel
}

/**
 * Swap behavior
 */
void swap(Posable & a, Posable & b) {
	using std::swap;
	swap(a.pose_, b.pose_);
}

} /* namespace sdf_builder */
