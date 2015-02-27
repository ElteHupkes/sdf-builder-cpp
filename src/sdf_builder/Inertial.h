/*
 * @TODO License
 */

#ifndef SDF_BUILDER_INERTIAL_H_
#define SDF_BUILDER_INERTIAL_H_

#include <sdf_builder/Element.h>

namespace sdf_builder {

class Inertial : public Element {
public:
	Inertial();
	virtual ~Inertial();

	/**
	 * Sets box inertia
	 */
	void setBox(double mass, double x, double y, double z);

	/**
	 * Set inertia for a cylinder.
	 */
	void setCylinder(double mass, double radius, double height);

	/**
	 * Virtual copy constructor pattern
	 */
	Inertial * clone() const;

	/**
	 * Return XML representation
	 */
	std::string toXML();

	double mass;
	double ixx;
	double ixy;
	double ixz;
	double iyy;
	double iyz;
	double izz;
};

} /* namespace sdf_builder */

#endif /* SDF_BUILDER_INERTIAL_H_ */
