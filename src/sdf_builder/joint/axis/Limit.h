/*
 * Limit.h
 *
 *  Created on: Feb 25, 2015
 *      Author: elte
 */

#ifndef TOL_SDF_JOINT_AXIS_LIMIT_H_
#define TOL_SDF_JOINT_AXIS_LIMIT_H_

#include <sdf_builder/Element.h>

namespace sdf_builder {

class Limit: public Element {
public:
	Limit();
	Limit(double lower, double upper);
	virtual ~Limit();

	double lower;
	double upper;
	double effort;
	double velocity;
	double dissipation;
	bool continuous;

	/**
	 * @return XML representation
	 */
	std::string toXML();

private:
	void init();
};

} /* namespace sdf_builder */

#endif /* TOL_SDF_JOINT_AXIS_LIMIT_H_ */
