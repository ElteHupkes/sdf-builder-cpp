/*
 * Box.cpp
 *
 *  Created on: Feb 25, 2015
 *      Author: elte
 */

#include <sdf_builder/geometry/Box.h>

namespace sdf_builder {

Box::Box(double x, double y, double z):
		x(x),
		y(y),
		z(z)
{}

Box::~Box() {}

Box * Box::clone() const {
	return new Box(*this);
}

std::string Box::toXML() {
	std::stringstream out;

	out << "<geometry>"
			<< "<box>"
			<< "<size>"
			<< nf(x) << ' ' << nf(y) << ' ' << nf(z)
			<< "</size>"
			<< "</box>"
			<< "</geometry>" << '\n';

	return out.str();
}

} /* namespace sdf_builder */
