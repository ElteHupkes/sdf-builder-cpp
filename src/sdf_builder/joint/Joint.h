/*
 * Joint.h
 *
 *  Created on: Feb 24, 2015
 *      Author: elte
 */

#ifndef SDF_JOINT_H_
#define SDF_JOINT_H_

#include <sdf_builder/joint/axis/Axis.h>
#include <sdf_builder/Link.h>
#include <sdf_builder/Posable.h>

namespace sdf_builder {

class Joint: public Posable {
public:
	/**
	 * Initializes a joint without links
	 */
	explicit Joint(std::string name),

	/**
	 * Initializes a joint, composing name from parent and child
	 */
	Joint(PosablePtr parent, PosablePtr child);

	/**
	 * Initializes a joint with parent / child links
	 */
	Joint(std::string name, PosablePtr parent, PosablePtr child);

	/**
	 * Virtual constructor
	 */
	virtual Joint * create(std::string name, PosablePtr parent, PosablePtr child) = 0;

	/**
	 * Destructor
	 */
	virtual ~Joint();

	/**
	 * Copy constructor
	 */
	Joint(const Joint & joint);

	/**
	 * Copy-swap for joints
	 */
	friend void swap(Joint & a, Joint & b);

	/**
	 * Link parent. Note that this is defined as a posable
	 * rather than a link for generality and so we can avoid
	 * downcasting during a clone.
	 */
	PosablePtr parent;

	/**
	 * Link child
	 */
	PosablePtr child;

	/**
	 * Axis
	 */
	AxisPtr axis;

};

} /* namespace sdf_builder */

#endif /* SDF_JOINT_H_ */
