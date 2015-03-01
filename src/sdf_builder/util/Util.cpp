/*
 * SdfBuilderUtil.cpp
 *
 *  Created on: Feb 28, 2015
 *      Author: elte
 */

#include <sdf_builder/util/Util.h>
#include <sdf_builder/Posable.h>

#include <cmath>

namespace sdf_builder {

Util::Util() {}

Util::~Util() {}

// TODO Check these methods for correctness
Vector3 Util::toParentFrame(const Vector3 & vec, Posable* me) {
	auto rot = me->rotation();
	auto pos = me->position();
	return (rot * vec) + pos;
}

Vector3 Util::toLocalFrame(const Vector3 & vec, Posable* me) {
	auto rot = me->rotation().conjugate();
	auto pos = me->position();
	return rot * (vec - pos);
}

// This simply amounts to rotating the vector to the parent frame
Vector3 Util::toParentDirection(const Vector3 & vec, Posable* me) {
	return me->rotation() * vec;
}

// Initialize the epsilon
const double Util::PARALLEL_EPSILON = 1e-4;

short Util::vectorParallellism(const Vector3 & a, const Vector3 & b) {
	double dot = a.normalized().dot(b.normalized());
	if (dot <= (-1 + PARALLEL_EPSILON)) {
		return OPPOSITE;
	} else if (dot >= (1 - PARALLEL_EPSILON)) {
		return PARALLEL;
	} else {
		return NOT_PARALLEL;
	}
}

} /* namespace sdf_builder */
