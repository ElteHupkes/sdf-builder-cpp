/*
 * FixedJoint.h
 *
 *  Created on: Feb 25, 2015
 *      Author: elte
 */

#ifndef TOL_SDF_JOINT_FIXEDJOINT_H_
#define TOL_SDF_JOINT_FIXEDJOINT_H_

#include <sdf_builder/joint/RevoluteJoint.h>

namespace sdf_builder {

/**
 * Fixed Joint to connect links. Fixed joints do not actually
 * exist within Gazebo, so for now this is implemented using
 * a RevoluteJoint with zero limits.
 */
class FixedJoint: public RevoluteJoint {
public:
	// Inherit constructors (C++11)
	using RevoluteJoint::RevoluteJoint;
	virtual ~FixedJoint();

	// Virtual copy / create need to be overridden
	virtual FixedJoint * clone();
	virtual FixedJoint * create(std::string name, PosablePtr parent, PosablePtr child);

	// Do not override copy constructor / operator=,
	// no fields are added to RevoluteJoint

	/**
	 * XML representation is overridden to force
	 * the zero limit.
	 */
	virtual std::string toXML();
};

} /* namespace sdf_builder */

#endif /* TOL_SDF_JOINT_FIXEDJOINT_H_ */
