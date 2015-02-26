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
	Joint(LinkPtr parent, LinkPtr child);

	/**
	 * Initializes a joint with parent / child links
	 */
	Joint(std::string name, LinkPtr parent, LinkPtr child);
	virtual ~Joint();

	/**
	 * Link parent
	 */
	boost::shared_ptr< Link > parent;

	/**
	 * Link child
	 */
	boost::shared_ptr< Link > child;

	/**
	 * Axis
	 */
	boost::shared_ptr< Axis > axis;

};

} /* namespace sdf_builder */

#endif /* SDF_JOINT_H_ */
