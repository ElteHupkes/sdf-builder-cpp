/*
 * Shape.cpp
 *
 *  Created on: Feb 25, 2015
 *      Author: elte
 */

#include <sdf_builder/geometry/Box.h>
#include <sdf_builder/shape/Shape.h>

namespace sdf_builder {

Shape::Shape(std::string name, GeometryPtr geom):
	Posable(name),
	geometry_(geom)
{}

Shape::Shape(std::string name):
	Shape(name, GeometryPtr(new Box))
{}

Shape::~Shape() {}

GeometryPtr Shape::geometry() {
	return geometry_;
}

void Shape::geometry(GeometryPtr geom) {
	geometry_ = geom;
}

} /* namespace sdf_builder */
