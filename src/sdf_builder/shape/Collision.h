/*
 * Collision.h
 *
 *  Created on: Feb 25, 2015
 *      Author: elte
 */

#ifndef SDF_BUILDER_SHAPE_COLLISION_H_
#define SDF_BUILDER_SHAPE_COLLISION_H_

#include <sdf_builder/shape/Shape.h>

namespace sdf_builder {

class Collision: public Shape {
public:
	// Inherit constructors
	using Shape::Shape;
	virtual ~Collision();

	/**
	 * Virtual copy constructor
	 */
	virtual Collision * clone() const;

	/**
	 * Copy-swap assignment operator
	 */
	Collision & operator=(Collision other);

	/**
	 * @return XML representation
	 */
	virtual std::string toXML();
};

} /* namespace sdf_builder */

#endif /* SDF_BUILDER_SHAPE_COLLISION_H_ */
