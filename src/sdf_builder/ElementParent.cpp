/*
 * ElementParent.cpp
 *
 *  Created on: Mar 4, 2015
 *      Author: elte
 */

#include <sdf_builder/ElementParent.h>
#include <sdf_builder/Element.h>
#include <sdf_builder/StringElement.h>

namespace sdf_builder {

ElementParent::ElementParent() {}

ElementParent::~ElementParent() {}

ElementParent::ElementParent(const ElementParent & other):
	elements_(std::vector< ElementPtr >(other.elements_.size()))
{
	for (std::size_t i = 0; i < elements_.size(); ++i) {
		if (other.elements_[i]) {
			elements_[i].reset(other.elements_[i]->clone());
		}
	}
}

// Copy swap
void swap(ElementParent & a, ElementParent & b) {
	using std::swap;
	swap(a.elements_, b.elements_);
}

void ElementParent::addElement( ElementPtr element ) {
	elements_.push_back(element);
}

void ElementParent::addString(std::string contents) {
	ElementPtr elem(new StringElement(contents));
	this->addElement(elem);
}

const std::vector< ElementPtr > & ElementParent::elements() {
	return elements_;
}

std::string ElementParent::toXML() {
	std::stringstream out;

	auto it = elements_.begin();
	for (; it != elements_.end(); ++it) {
		out << (*it)->toXML() << '\n';
	}

	return out.str();
}

} /* namespace sdf_builder */
