/*
 * Surface.h
 *
 *  Created on: Mar 21, 2015
 *      Author: elte
 */

#ifndef SDF_BUILDER_COLLISION_SURFACE_H_
#define SDF_BUILDER_COLLISION_SURFACE_H_

#include <sdf_builder/Element.h>
#include <sdf_builder/ElementParent.h>

namespace sdf_builder {

class Surface: public Element, public ElementParent {
public:
	Surface();
	virtual ~Surface();

	Surface(const Surface & other);

	Surface & operator=(Surface other);

	// TODO copy constructors and such

	virtual std::string toXML();

	/**
	 * Create a clone of this surface element
	 */
	virtual Surface * clone() const;

	friend void swap(Surface & a, Surface & b);

	/**
	 * Friction element if applicable
	 */
	FrictionPtr friction;
};

} /* namespace sdf_builder */

#endif /* SDF_BUILDER_COLLISION_SURFACE_H_ */
