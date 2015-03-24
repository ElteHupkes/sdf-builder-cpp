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
	virtual ~StringElement();
	virtual StringElement * clone() const;

	virtual std::string toXML();

	/**
	 * Element contents
	 */
	std::string contents;

	/**
	 * If you want, you can assign a value here to
	 * identify your element by. Not rendered in
	 * any way.
	 */
	std::string id;
};

} /* namespace sdf_builder */

#endif /* SDF_BUILDER_STRINGELEMENT_H_ */
