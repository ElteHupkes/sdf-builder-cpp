/*
 * StringElement.h
 *
 *  Created on: Mar 4, 2015
 *      Author: elte
 */

#ifndef SDF_BUILDER_STRINGELEMENT_H_
#define SDF_BUILDER_STRINGELEMENT_H_

#include <sdf_builder/Element.h>

namespace sdf_builder {

/**
 * An element that can contain anything, just rendered
 * as-is.
 */
class StringElement: public Element {
public:
	StringElement();
	StringElement(const std::string & contents);
	StringElement(const StringElement & other);
	virtual ~StringElement();
	virtual StringElement * clone() const;
	friend void swap(StringElement & a, StringElement & b);

	StringElement & operator=(StringElement other);

	virtual std::string toXML();
	std::string contents;
};

} /* namespace sdf_builder */

#endif /* SDF_BUILDER_STRINGELEMENT_H_ */
