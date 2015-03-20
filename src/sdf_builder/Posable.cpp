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

// Use this:
//
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

	// This explains how we can do the alignment easily:
	// http://stackoverflow.com/questions/21828801/how-to-find-correct-rotation-from-one-vector-to-another

	// We define coordinate systems in which "normal", "tangent" and "normal x tangent" are
	// the x, y and z axis (normal x tangent is the cross product). We then determine two
	// rotation matrices, one for the rotation of the standard basis to "my" (R1):
	auto myXref = Util::toParentDirection(myNormalLocal, this).normalized();
	auto myYref = Util::toParentDirection(myTangentLocal, this).normalized();
	auto myZref = myXref.cross(myYref);

	// and one for the rotation of "at" (R2):
	auto atXref = Util::toParentDirection(-atNormalLocal, ofptr).normalized();
	auto atYref = Util::toParentDirection(atTangentLocal, ofptr).normalized();
	auto atZref = atXref.cross(atYref);

	// Note that, provided the input vectors were orthogonal, these matrices
	// are orthonormal. Now we want to provide the rotation matrix from
	// R1 to R2. The easiest way to visualize this is if we first perform
	// the inverse rotation from R1 back to the standard basis, and then
	// rotate to R2. Since R1/R2 are orthonormal, their inverse is their
	// transpose, so we initialize r1 by rows rather than columns:
	RotationMatrix r1;
	r1.row(0) = myXref;
	r1.row(1) = myYref;
	r1.row(2) = myZref;

	// R2 is just initialized by columns
	RotationMatrix r2;
	r2.col(0) = atXref;
	r2.col(1) = atYref;
	r2.col(2) = atZref;

	// Use R2 * R2 to produce the quaternion rotation
	Quaternion quat(r2 * r1);
	this->rotation(quat);

	// Verify the axes are correctly aligned
	auto myParentNormal = Util::toParentDirection(myNormalLocal, this);
	auto atParentNormal = Util::toParentDirection(-atNormalLocal, ofptr);
	auto normalsParallel = Util::vectorParallellism(myParentNormal, atParentNormal);

	if (Util::PARALLEL != normalsParallel) {
		std::cerr << "`Posable::align()`: Normal vectors failed to align! Were input vectors orthogonal?" << std::endl;
		std::cerr << "Cosine of angle: "
				  << myParentNormal.dot(atParentNormal)
				  << std::endl;
	}

	auto myParentTangent = Util::toParentDirection(myTangentLocal, this);
	auto atParentTangent = Util::toParentDirection(atTangentLocal, ofptr);
	auto tangentsParallel = Util::vectorParallellism(myParentTangent, atParentTangent);

	if (Util::PARALLEL != tangentsParallel) {
		std::cerr << "`Posable::align()`: Tangent vectors failed to align! Were input vectors orthogonal?" << std::endl;
		std::cerr << "Cosine of angle: "
				  << myParentTangent.dot(atParentTangent)
				  << std::endl;
	}

	// Finally, translate so that `my` lands at `at`
	auto myPosition = Util::toParentFrame(myLocal, this);
	auto atPosition = Util::toParentFrame(atLocal, ofptr);
	auto translation = atPosition - myPosition;

	position(position() + translation);
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
