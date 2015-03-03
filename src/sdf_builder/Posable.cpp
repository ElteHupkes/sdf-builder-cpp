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


void Posable::align(const Vector3 & my, const Vector3 & myNormal, const Vector3 & myTangent,
		const Vector3 & at, const Vector3 & atNormal, const Vector3 & atTangent,
		PosablePtr of, bool relativeToChildFrame) {

	Posable* ofptr = of.get();

	// Convert my and at to local coordinates if not already so. This is
	// important, since we need to be able to retrieve their positions
	// later when some rotations have occurred.
	// The only exception are the normals, which are used before any
	// rotations.
	auto myLocal = relativeToChildFrame ? my : Util::toLocalFrame(my, this);
	auto atLocal = relativeToChildFrame ? at : Util::toLocalFrame(at, ofptr);
	auto myTangentLocal = relativeToChildFrame ? myTangent : Util::toLocalDirection(myTangent, this);
	auto atTangentLocal = relativeToChildFrame ? atTangent : Util::toLocalDirection(atTangent, ofptr);
	auto fallback = relativeToChildFrame ? myNormal : Util::toLocalDirection(myNormal, this);

	// 1) Rotate to align myNormal with atNormal
	align(myNormal, -atNormal, of, relativeToChildFrame);

	// 2) Rotate to align `myTangent` with `atTangent`
	align(myTangentLocal, atTangentLocal, of, RELATIVE_TO_CHILD_FRAME, fallback);

	// 3) Translate so that `my` lands at `at`
	auto myPosition = Util::toParentFrame(myLocal, this);
	auto atPosition = Util::toParentFrame(atLocal, ofptr);
	auto translation = atPosition - myPosition;

	position(position() + translation);
	// TODO Check axis are parallel
}

void Posable::align(const Vector3 & my, const Vector3 & other, PosablePtr of,
		bool relativeToChildFrame, const Vector3 & fallback) {

	Posable* ofptr = of.get();
	auto myParentVec = relativeToChildFrame ?
			Util::toParentDirection(my, this) :
			my;
	auto otherParentVec = relativeToChildFrame ?
				Util::toParentDirection(other, ofptr) :
				other;

	auto parallel = Util::vectorParallellism(myParentVec, otherParentVec);
	if (Util::PARALLEL == parallel) {
		// Nothing needs to happen.
		return;
	} else if (Util::OPPOSITE == parallel && fallback.norm() > 0.01) {
		// Opposite vectors with nonzero fallback vector; rotate
		// PI degrees along the fallback vector.
		this->rotateAround(fallback, M_PI, relativeToChildFrame);
	} else {
		// Eigen3 handles the case of opposite vectors
		Quaternion rot = Quaternion::FromTwoVectors(myParentVec, otherParentVec);
		this->rotation(rot);
	}
}

void Posable::rotateAround(Vector3 axis, double angle, bool relativeToChildFrame) {
	if (!relativeToChildFrame) {
		axis = Util::toLocalDirection(axis, this);
	}

	Quaternion rot(AngleAxis(angle, axis));
	rotation(rot * rotation());
}

/**
 * Swap behavior
 */
void swap(Posable & a, Posable & b) {
	using std::swap;
	swap(a.pose_, b.pose_);
}

} /* namespace sdf_builder */
