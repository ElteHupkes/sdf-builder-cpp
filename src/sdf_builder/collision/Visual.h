/*
 * Visual.h
 *
 *  Created on: Feb 25, 2015
 *      Author: elte
 */

#ifndef TOL_SDF_SHAPE_VISUAL_H_
#define TOL_SDF_SHAPE_VISUAL_H_

#include <sdf_builder/collision/Shape.h>

namespace sdf_builder {

class Visual: public Shape {
public:
	using Shape::Shape;
	virtual ~Visual();

	/**
	 * Virtual copy constructor
	 */
	virtual Visual * clone() const;

	/**
	 * Assignment operator
	 */
	Visual & operator=(Visual other);

	/**
	 * @return XML representation
	 */
	virtual std::string toXML();
};

} /* namespace sdf_builder */

#endif /* TOL_SDF_SHAPE_VISUAL_H_ */
