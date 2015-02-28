/*
 * LinkGroup.h
 *
 *  Created on: Feb 28, 2015
 *      Author: elte
 */

#ifndef SDF_BUILDER_POSABLEGROUP_H_
#define SDF_BUILDER_POSABLEGROUP_H_

#include <sdf_builder/Posable.h>
#include <sdf_builder/PosableParent.h>

namespace sdf_builder {

/**
 * A PosableGroup is a Posable collection of posables which share a parent frame,
 * but are not necessarily the entire set of posables within the frame.
 * When the PosableGroup is translated or rotated, all the elements within
 * it are moved separately. This allows you to maintain a related set of
 * posables within a parent.
 */
class PosableGroup: public Posable, public PosableParent {
public:
	// Inherit Posable constructors, we add no fields here
	using Posable::Posable;

	/**
	 * Copy constructor
	 */
	PosableGroup(const PosableGroup & other);

	/**
	 * Destructor
	 */
	virtual ~PosableGroup();

	/**
	 * Virtual copy pattern
	 */
	virtual PosableGroup * clone() const;

	/**
	 * Copy-swap helper
	 */
	friend void swap(PosableGroup & a, PosableGroup & b);

	/**
	 * Assignment operator
	 */
	PosableGroup & operator=(PosableGroup other);

	// Look up the non-overriden overloaded methods
	using Posable::rotation;
	using Posable::position;

	/**
	 * Set the position of the group
	 */
	virtual void position(const Vector3 & position);

	/**
	 * Set the rotation of the group
	 */
	virtual void rotation(const Quaternion & rotation);

	/**
	 * XML representation
	 */
	virtual std::string toXML();
};

} /* namespace sdf_builder */

#endif /* SDF_BUILDER_POSABLEGROUP_H_ */
