/*
 * Axis.cpp
 *
 *  Created on: Feb 25, 2015
 *      Author: elte
 */

#include <sdf_builder/joint/axis/Axis.h>

namespace sdf_builder {

Axis::Axis():
	useParentModelFrame(false),
	tagName("axis"),
	xyz_(Vector3(0, 0, 1))
{}

Axis::~Axis()
{}

Axis::Axis(const Axis & other):
	Element(other),
	useParentModelFrame(other.useParentModelFrame),
	tagName(other.tagName),
	limit(LimitPtr(other.limit ? other.limit->clone() : nullptr)),
	xyz_(other.xyz_),
	elements_(std::vector< ElementPtr >(other.elements_.size()))
{
	for (std::size_t i = 0; i < elements_.size(); ++i) {
		if (other.elements_[i]) {
			elements_[i].reset(other.elements_[i]->clone());
		}
	}
}

Axis & Axis::operator=(Axis other) {
	swap(*this, other);
	return *this;
}

// Swap for copy-and-swap
void swap(Axis & a, Axis & b) {
	using std::swap;

	swap(a.useParentModelFrame, b.useParentModelFrame);
	swap(a.tagName, b.tagName);
	swap(a.limit, b.limit);
	swap(a.xyz_, b.xyz_);
	swap(a.elements_, b.elements_);
}

Axis *  Axis::clone() const {
	return new Axis(*this);
}

const Vector3& Axis::xyz() {
	return xyz_;
}

void Axis::xyz(const Vector3& vec) {
	xyz_[0] = vec[0];
	xyz_[1] = vec[1];
	xyz_[2] = vec[2];
}

std::string Axis::toXML() {
	std::stringstream out;

	out << "<" << tagName << ">"
			<< "<xyz>"
			<< nf(xyz_[0]) << ' '
			<< nf(xyz_[1]) << ' '
			<< nf(xyz_[2]) << ' '
			<< "</xyz>"
		<< "<use_parent_model_frame>"
		<< (useParentModelFrame ? "1" : "0")
		<< "</use_parent_model_frame>";

	std::vector< ElementPtr >::iterator it = elements_.begin();
	for (; it != elements_.end(); ++it) {
		out << it->get()->toXML() << '\n';
	}

	if (limit) {
		out << limit->toXML() << '\n';
	}

	out << "</" << tagName << ">";
	return out.str();
}

} /* namespace sdf_builder */
