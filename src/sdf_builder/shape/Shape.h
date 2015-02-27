/*
 * Shape.h
 *
 *  Created on: Feb 25, 2015
 *      Author: elte
 */

#ifndef SDF_BUILDER_SHAPE_SHAPE_H_
#define SDF_BUILDER_SHAPE_SHAPE_H_

#include <sdf_builder/geometry/Geometry.h>
#include <sdf_builder/Posable.h>

namespace sdf_builder {

/**
 * Shape is used by both visual and collision elements. A shape
 * should have a certain geometry.
 */
class Shape: public Posable {
public:
	/**
	 * Default constructor initializes the shape with
	 * a unit size box.
	 */
	explicit Shape(std::string name);
	Shape(std::string name, GeometryPtr geom);

	/**
	 * Copy constructor, copies the geometry
	 */
	Shape(const Shape& other);

	/**
	 * Destructor
	 */
	virtual ~Shape();

	/**
	 * Swap for copy-and-swap
	 */
	friend void swap(Shape& a, Shape& b);

	/**
	 * @return The geometry of this shape
	 */
	GeometryPtr geometry();

	/**
	 * Sets the geometry
	 */
	void geometry(GeometryPtr geom);

protected:
	/**
	 * The geometry of this shape
	 */
	GeometryPtr geometry_;
};

} /* namespace sdf_builder */

#endif /* SDF_BUILDER_SHAPE_SHAPE_H_ */
