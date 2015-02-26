/*
 * Element.h
 *
 *  Created on: Feb 23, 2015
 *      Author: elte
 */

#ifndef SDF_BUILDER_ELEMENT_H_
#define SDF_BUILDER_ELEMENT_H_

// stdlib classes
#include <tol/SdfBuilder.h>
#include <string>
#include <sstream> // Common to use for toXML

// sdfbuilder

namespace sdf_builder {

class Element {
public:
	Element();
	virtual ~Element();

	/**
	 * Returns the full XML string representation
	 * of this element.
	 */
	virtual std::string toXML() = 0;
};

} /* namespace sdf_builder */

#endif /* SDF_BUILDER_ELEMENT_H_ */
