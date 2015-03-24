/*
 * ElementParent.h
 *
 *  Created on: Mar 4, 2015
 *      Author: elte
 */

#ifndef SDF_BUILDER_ELEMENTPARENT_H_
#define SDF_BUILDER_ELEMENTPARENT_H_

#include <sdf_builder/SdfBuilder.h>

namespace sdf_builder {

class ElementParent {
public:
	ElementParent();
	virtual ~ElementParent();

	/**
	 * Copy constructor
	 */
	ElementParent(const ElementParent & other);

	/**
	 * Copy / swap pattern
	 */
	friend void swap(ElementParent & a, ElementParent & b);

	/**
	 * Adds a new posable element to this model
	 */
	virtual void addElement( ElementPtr element );

	/**
	 * Shortcut method to add a string element with the given
	 * contents.
	 */
	virtual void addString(std::string contents);

	/**
	 * @return Posable elements in this parent
	 */
	const std::vector< ElementPtr > & elements();

	/**
	 * Convenience method to output all posables in their
	 * XML form.
	 */
	virtual std::string toXML();
protected:
	/**
	 * List of posable elements in the model
	 */
	std::vector< ElementPtr > elements_;
};

} /* namespace sdf_builder */

#endif /* SDF_BUILDER_ELEMENTPARENT_H_ */
