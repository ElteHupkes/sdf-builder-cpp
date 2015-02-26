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
	explicit FixedJoint(std::string name);
	FixedJoint(LinkPtr parent, LinkPtr child);
	FixedJoint(std::string name, LinkPtr parent, LinkPtr child);
	virtual ~FixedJoint();

private:
	/**
	 * Initializes the joint axis to zero movement
	 */
	void init();
};

} /* namespace sdf_builder */

#endif /* TOL_SDF_JOINT_FIXEDJOINT_H_ */
