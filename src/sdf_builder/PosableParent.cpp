/*
 * TODO license
 */

#include <sdf_builder/PosableParent.h>

namespace sdf_builder {

PosableParent::PosableParent() {}

PosableParent::~PosableParent() {}

PosableParent::PosableParent(const PosableParent & other):
	posables_(std::vector< PosablePtr >(other.posables_.size()))
{
	for (std::size_t i = 0; i < posables_.size(); ++i) {
		if (other.posables_[i]) {
			posables_[i].reset(other.posables_[i]->clone());
		}
	}
}

// Copy swap
void swap(PosableParent & a, PosableParent & b) {
	using std::swap;
	swap(a.posables_, b.posables_);
}

void PosableParent::addPosable( PosablePtr element ) {
	posables_.push_back(element);
}

const std::vector< PosablePtr > & PosableParent::posables() {
	return posables_;
}

} /* namespace sdf_builder */
