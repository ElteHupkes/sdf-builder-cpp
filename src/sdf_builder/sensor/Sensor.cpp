/*
 * Sensor.cpp
 *
 *  Created on: Mar 24, 2015
 *      Author: elte
 */

#include <sdf_builder/sensor/Sensor.h>

#include <sstream>

namespace sdf_builder {

Sensor::Sensor(std::string name, std::string type):
	Posable(name),
	type(type),
	alwaysOn(false),
	updateRate(0),
	visualize(false),
	topic("__default__")
{}

Sensor::~Sensor() {}

std::string Sensor::sensorXML() {
	return "";
}

Sensor * Sensor::clone() const {
	return new Sensor(*this);
}

std::string Sensor::toXML() {
	std::stringstream out;

	out << "<sensor name=\"" << name_ << "\" type=\"" << type << "\">";
	out << pose_->toXML();

	out << "<always_on>" << alwaysOn << "</always_on>";
	out << "<update_rate>" << updateRate << "</update_rate>";
	out << "<visualize>" << visualize << "</visualize>";

	if (topic != "__default__") {
		out << "<topic>" << topic << "</topic>";
	}

	out << this->sensorXML();
	out << ElementParent::toXML();
	out << "</sensor>";

	return out.str();
}

} /* namespace sdf_builder */
