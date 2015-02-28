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
	 * Utility function to convert a local frame vector to the parent
	 * frame.
	 */
	static Vector3 toParentFrame(const Vector3 & vec, Posable* me);

	/**
	 * Utility function to convert a parent frame vector to the
	 * local frame.
	 */
	static Vector3 toLocalFrame(const Vector3 & vec, Posable* me);
private:
	// Singleton
	Util();
};

} /* namespace sdf_builder */

#endif /* SDF_BUILDER_UTIL_UTIL_H_ */
