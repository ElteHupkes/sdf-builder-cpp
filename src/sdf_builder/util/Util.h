/*
 * SdfBuilderUtil.h
 *
 *  Created on: Feb 28, 2015
 *      Author: elte
 */

#ifndef SDF_BUILDER_UTIL_UTIL_H_
#define SDF_BUILDER_UTIL_UTIL_H_

#include <sdf_builder/SdfBuilder.h>

#define SDFUTIL_PARALLEL_EPSILON 1e-4

namespace sdf_builder {

class Util {
public:
	virtual ~Util();

	/**
	 * Utility function to convert a local frame vector to the parent
	 * frame.
	 */
	static Vector3 toParentFrame(const Vector3 & vec, Posable* me);

	/**
	 * Utility function to convert a parent frame vector to the
	 * local frame.
	 */
	static Vector3 toLocalFrame(const Vector3 & vec, Posable* me);

	/**
	 * Returns whether the given vectors are parallel up to epsilon
	 * precision, and point in the same direction.
	 */
	static bool areVectorsParallel(const Vector3 & a, const Vector3 & b);
private:
	// Singleton
	Util();
};

} /* namespace sdf_builder */

#endif /* SDF_BUILDER_UTIL_UTIL_H_ */
