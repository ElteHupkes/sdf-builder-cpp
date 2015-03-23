/*
 * Friction.cpp
 *
 *  Created on: Mar 21, 2015
 *      Author: elte
 */

#include <sdf_builder/collision/Friction.h>

#include <sstream>

namespace sdf_builder {

Friction::Friction():
	friction1(1),
	friction2(1),
	fdir1(Vector3(0, 0, 0)),
	slip1(0),
	slip2(0),
	rollingFriction(1)
{}

Friction::~Friction() {}

Friction * Friction::clone() const {
	return new Friction(*this);
}

std::string Friction::toXML() {
	std::stringstream out;

	out << "<friction>";

	out << "<ode>"
		<< "<mu>" << nf(friction1) << "</mu>"
		<< "<mu2>" << nf(friction2) << "</mu2>"
		<< "<fdir1>" << nf(fdir1[0]) << ' ' << nf(fdir1[1]) << ' ' << nf(fdir1[2])
			<< "</fdir1>"
		<< "<slip1>" << slip1 << "</slip1>"
		<< "<slip2>" << slip2 << "</slip2>"
		<< "</ode>";

	out << "<bullet>"
		<< "<friction>" << nf(friction1) << "</friction>"
		<< "<friction2>" << nf(friction2) << "</friction2>"
		<< "<fdir1>" << nf(fdir1[0]) << ' ' << nf(fdir1[1]) << ' ' << nf(fdir1[2])
					<< "</fdir1>"
		<< "<rolling_friction>" << nf(rollingFriction) << "</rolling_friction>"
		<< "</bullet>";

	out << "</friction>";

	return out.str();
}

} /* namespace sdf_builder */
