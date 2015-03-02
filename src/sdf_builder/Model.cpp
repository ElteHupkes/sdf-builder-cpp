/**
 * @TODO License
 */
#include <sdf_builder/Model.h>
#include <sdf_builder/joint/Joint.h>

#include <algorithm>

namespace sdf_builder {

Model::Model(std::string name):
	Posable(name),
	isStatic_(false)
	{}

Model::~Model() {}

Model::Model(const Model & other):
	Posable(other),
	PosableParent(other),
	isStatic_(other.isStatic_),
	joints_(std::vector< JointPtr >(other.joints_.size()))
{
	// Create joints for the copied links. Links for the copied model
	// will be at the same indices as their original counterparts, which
	// means we can create joints from these indices.
	for (std::size_t i = 0; i < joints_.size(); ++i) {
		auto joint = other.joints_[i];
		PosablePtr parent;
		PosablePtr child;

		// TODO errors below here if parent/child not found (which is possible if
		// they were not added to the parent's posables).
		if (joint->parent) {
			int pos = std::find(other.posables_.begin(), other.posables_.end(),
					joint->parent) - other.posables_.begin();
			parent = posables_[pos];
		}

		if (joint->child) {
			int pos = std::find(other.posables_.begin(), other.posables_.end(),
					joint->parent) - other.posables_.begin();
			child = posables_[pos];
		}

		joints_[i].reset(joint->create(joint->name(), parent, child));
	}
}

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

void Model::addJoint(JointPtr joint) {
	// TODO Check whether links are in model
	joints_.push_back(joint);
}

const std::vector<JointPtr> & Model::joints() {
	return joints_;
}

std::string Model::toXML() {
	std::stringstream out;

	out << "<model name=\"" << name_ << "\">"
			<< "<static>" << (isStatic_ ? "true" : "false") << "</static>"
			<< pose_->toXML();

	for (int i = 0, l = posables_.size(); i < l; ++i) {
		out << posables_[i]->toXML() << '\n';
	}

	for (int i = 0, l = joints_.size(); i < l; ++i) {
		out << joints_[i]->toXML() << '\n';
	}

	out << "</model>" << '\n';
	return out.str();
}

} /* namespace sdf_builder */
