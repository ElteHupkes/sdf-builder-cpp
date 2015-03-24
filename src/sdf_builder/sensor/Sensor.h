/*
 * Sensor.h
 *
 *  Created on: Mar 24, 2015
 *      Author: elte
 */

#ifndef SDF_BUILDER_SENSOR_SENSOR_H_
#define SDF_BUILDER_SENSOR_SENSOR_H_

#include <sdf_builder/ElementParent.h>
#include <sdf_builder/Posable.h>

namespace sdf_builder {

/**
 * SDF Sensor element. This is overridable with different
 * sensor types, but there doesn't seem to be much point
 * in doing so as writing direct XML for sensors generally
 * seems fine. I suggest using `StringElement`s to fill
 * the sensors.
 */
class Sensor: public ElementParent, public Posable {
public:
	Sensor(std::string name, std::string type);
	virtual ~Sensor();

	virtual std::string toXML();

	virtual Sensor * clone() const;

	/**
	 * Sensor type, by default this will be
	 * unspecified.
	 */
	std::string type;

	bool alwaysOn;
	double updateRate;
	bool visualize;
	std::string topic;

protected:
	/**
	 * The specific XML for this sensor, override in
	 * child class.
	 */
	virtual std::string sensorXML();
};

} /* namespace sdf_builder */

#endif /* SDF_BUILDER_SENSOR_SENSOR_H_ */
