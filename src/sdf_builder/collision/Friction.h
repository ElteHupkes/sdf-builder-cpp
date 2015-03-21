/*
 * Friction.h
 *
 *  Created on: Mar 21, 2015
 *      Author: elte
 */

#ifndef SDF_BUILDER_COLLISION_FRICTION_H_
#define SDF_BUILDER_COLLISION_FRICTION_H_

#include <sdf_builder/Element.h>

namespace sdf_builder {

class Friction: public Element {
public:
	Friction();
	virtual ~Friction();

	Friction * clone() const;

	double friction1;
	double friction2;
	Vector3 fdir1;
	double slip1;
	double slip2;
	double rollingFriction;

	virtual std::string toXML();
};

} /* namespace sdf_builder */

#endif /* SDF_BUILDER_COLLISION_FRICTION_H_ */
