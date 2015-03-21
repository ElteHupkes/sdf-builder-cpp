/*
 * Shape.cpp
 *
 *  Created on: Feb 25, 2015
 *      Author: elte
 */

#include <sdf_builder/collision/Shape.h>
#include <sdf_builder/geometry/Box.h>

namespace sdf_builder {

Shape::Shape(std::string name, GeometryPtr geom):
	Posable(name),
	geometry_(geom)
{}

Shape::Shape(std::string name):
	Shape(name, GeometryPtr(new Box))
{}

Shape::Shape(const Shape& other):
	ElementParent(other),
	Posable(other),
	geometry_(GeometryPtr(geometry_->clone()))
{}

Shape::~Shape() {}

GeometryPtr Shape::geometry() {
	return geometry_;
}

void Shape::geometry(GeometryPtr geom) {
	geometry_ = geom;
}

void swap(Shape & a, Shape & b) {
	using std::swap;

	// Call posable swap function
	swap(static_cast< Posable& >(a), static_cast< Posable & >(b));

	// Swap own fields
	swap(a.geometry_, b.geometry_);
}

} /* namespace sdf_builder */
