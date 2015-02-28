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

bool Util::areVectorsParallel(const Vector3 & a, const Vector3 & b) {
	double v = a.dot(b) - (a.norm() * b.norm());
	return abs(v) < SDFUTIL_PARALLEL_EPSILON;
}

} /* namespace sdf_builder */
