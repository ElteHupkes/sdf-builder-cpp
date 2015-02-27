/*
 * Posable.cpp
 *
 *  Created on: Feb 24, 2015
 *      Author: elte
 */

#include <sdf_builder/Posable.h>

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

void Posable::setPosition(const Vector3& pos) {
	this->pose_->setPosition(pos);
}

void Posable::setRotation(const Quaternion &rot) {
	this->pose_->setRotation(rot);
}

/**
 * Swap behavior
 */
void swap(Posable & a, Posable & b) {
	using std::swap;
	swap(a.pose_, b.pose_);
}

} /* namespace sdf_builder */
