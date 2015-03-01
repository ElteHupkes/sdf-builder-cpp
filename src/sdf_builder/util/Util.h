/*
 * SdfBuilderUtil.h
 *
 *  Created on: Feb 28, 2015
 *      Author: elte
 */

#ifndef SDF_BUILDER_UTIL_UTIL_H_
#define SDF_BUILDER_UTIL_UTIL_H_

#include <sdf_builder/SdfBuilder.h>

namespace sdf_builder {

class Util {
public:
	virtual ~Util();

	/**
	 * Return values for `areVectorsParallel`
	 */
	static const short OPPOSITE = -1;
	static const short NOT_PARALLEL = 0;
	static const short PARALLEL = 1;

	/**
	 * Epsilon value to use for parallel checking
	 *
	 * *could use constexpr to initialize it here with C++11,
	 * but the epsilon is better placed close to the implementation
	 * anyway.
	 */
	static const double PARALLEL_EPSILON;

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
	 * Returns the direction of the given vector in the parent frame
	 * @param The vector
	 * @param The frame containing the vector
	 * @return Vector with the direction of `vec` in the parent frame
	 */
	static Vector3 toParentDirection(const Vector3 & vec, Posable* me);

	/**
	 * Returns the direction of the given vector in the local frame
	 * @param The vector in the parent frame
	 * @param The local
	 * @return Vector with the direction of `vec` in the local frame
	 */
	static Vector3 toLocalDirection(const Vector3 & vec, Posable* me);

	/**
	 * Returns whether vectors a and b are parallel, antiparallel or
	 * not parallel at all.
	 *
	 * @return One of `ANTIPARALLEL`, `NOT_PARALLEL` or `PARALLEL`
	 */
	static short vectorParallellism(const Vector3 & a, const Vector3 & b);
private:
	// Singleton
	Util();
};

} /* namespace sdf_builder */

#endif /* SDF_BUILDER_UTIL_UTIL_H_ */
