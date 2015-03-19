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
	auto myLocal = relativeToChildFrame ? my : Util::toLocalFrame(my, this);
	auto atLocal = relativeToChildFrame ? at : Util::toLocalFrame(at, ofptr);
	auto myTangentLocal = relativeToChildFrame ? myTangent : Util::toLocalDirection(myTangent, this);
	auto atTangentLocal = relativeToChildFrame ? atTangent : Util::toLocalDirection(atTangent, ofptr);
	auto myNormalLocal = relativeToChildFrame ? myNormal : Util::toLocalDirection(myNormal, this);
	auto atNormalLocal = relativeToChildFrame ? atNormal : Util::toLocalDirection(atNormal, ofptr);

	// 1) Rotate to align myNormal with atNormal
	align(myNormal, -atNormal, of, relativeToChildFrame);

	// 2) The normals now aligned, and the tangent vectors should be orthonormal
	//    to these vectors. That means that in order to match up the tangent vectors,
	//    we only need to rotate around the tangent vector. First, calculate the
	//    correct angle to do so:
	auto myTangentParent = Util::toParentDirection(myTangentLocal, this).normalized();
	auto atTangentParent = Util::toParentDirection(atTangentLocal, ofptr).normalized();
	double angle = acos(myTangentParent.dot(atTangentParent));

	// perform the rotation only if necessary
	if (fabs(angle) > Util::PARALLEL_EPSILON) {
		this->rotateAround(myNormalLocal, -angle, Posable::RELATIVE_TO_CHILD_FRAME);
	}

	// 3) Translate so that `my` lands at `at`
	auto myPosition = Util::toParentFrame(myLocal, this);
	auto atPosition = Util::toParentFrame(atLocal, ofptr);
	auto translation = atPosition - myPosition;

	position(position() + translation);

	// Verify the axes are correctly aligned
	auto normalsParallel = Util::vectorParallellism(
		Util::toParentDirection(myNormalLocal, this),
		Util::toParentDirection(-atNormalLocal, ofptr)
	);

	auto tangentsParallel = Util::vectorParallellism(
		Util::toParentDirection(myTangentLocal, this),
		Util::toParentDirection(atTangentLocal, ofptr)
	);

	if (Util::PARALLEL != normalsParallel) {
		std::cerr << "`Posable::align()`: Normal vectors failed to align! Were input vectors orthonormal?" << std::endl;
	}

	if (Util::PARALLEL != tangentsParallel) {
		std::cerr << "`Posable::align()`: Tangent vectors failed to align! Were input vectors orthonormal?" << std::endl;
	}
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
