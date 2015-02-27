/*
 * FixedJoint.h
 *
 *  Created on: Feb 25, 2015
 *      Author: elte
 */

#ifndef TOL_SDF_JOINT_REVOLUTEJOINT_H_
#define TOL_SDF_JOINT_REVOLUTEJOINT_H_

#include <sdf_builder/joint/Joint.h>

namespace sdf_builder {

class RevoluteJoint: public Joint {
public:
	// Inherit constructors (C++11)
	using Joint::Joint;
	virtual ~RevoluteJoint();

	virtual RevoluteJoint * clone() const;

	/**
	 * Assignment operator
	 */
	RevoluteJoint & operator=(RevoluteJoint other);

	/**
	 * @return XML representation
	 */
	virtual std::string toXML();
};

} /* namespace sdf_builder */

#endif /* TOL_SDF_JOINT_REVOLUTEJOINT_H_ */
