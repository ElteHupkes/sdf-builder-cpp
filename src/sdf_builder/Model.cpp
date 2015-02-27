/**
 * @TODO License
 */
#include <sdf_builder/Model.h>

namespace sdf_builder {

Model::Model(std::string name):
	Posable(name),
	isStatic_(false)
	{}

Model::~Model() {}

Model::Model(const Model & other):
	Posable(other),
	PosableParent(other),
	isStatic_(other.isStatic_)
{}

Model * Model::clone() const {
	return new Model(*this);
}

void swap(Model & a, Model & b) {
	using std::swap;

	// Call for all parent classes
	swap(static_cast<Posable &>(a), static_cast<Posable &>(b));
	swap(static_cast<PosableParent &>(a), static_cast<PosableParent &>(b));

	// Own properties
	swap(a.isStatic_, b.isStatic_);
}

Model & Model::operator=(Model other) {
	swap(*this, other);
	return *this;
}

std::string Model::toXML() {
	std::stringstream out;

	out << "<model name=\"" << name_ << "\">"
			<< "<static>" << (isStatic_ ? "true" : "false") << "</static>"
			<< pose_->toXML();

	for (int i = 0, l = posables_.size(); i < l; ++i) {
		out << posables_[i]->toXML() << '\n';
	}

	out << "</model>" << '\n';
	return out.str();
}

} /* namespace sdf_builder */
