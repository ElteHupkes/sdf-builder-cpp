/*
 * Geometry.h
 *
 *  Created on: Feb 23, 2015
 *      Author: elte
 */

#ifndef SDF_GEOMETRY_H_
#define SDF_GEOMETRY_H_

#include <sdf_builder/Element.h>

namespace sdf_builder {

class Geometry: public Element {
public:
	Geometry();
	virtual ~Geometry();

	/**
	 * Need to define this so Geometries can also be cloned without
	 * being cast to `Element`s.
	 */
	virtual Geometry * clone() const = 0;

	/**
	 * @return XML representation
	 */
	virtual std::string toXML() = 0;
};

} /* namespace sdf_builder */

#endif /* SDF_GEOMETRY_H_ */
