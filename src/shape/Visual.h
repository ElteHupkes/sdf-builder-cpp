/*
 * Visual.h
 *
 *  Created on: Feb 25, 2015
 *      Author: elte
 */

#ifndef TOL_SDF_SHAPE_VISUAL_H_
#define TOL_SDF_SHAPE_VISUAL_H_

#include <sdf_builder/shape/Shape.h>

namespace sdf_builder {

class Visual: public Shape {
public:
	explicit Visual(std::string name);
	Visual(std::string name, GeometryPtr geom);
	virtual ~Visual();

	/**
	 * @return XML representation
	 */
	virtual std::string toXML();
};

} /* namespace sdf_builder */

#endif /* TOL_SDF_SHAPE_VISUAL_H_ */
