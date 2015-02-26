/**
 * TODO License
 */
// stdlib
#include <sdf_builder/geometry/Box.h>
#include <sdf_builder/Link.h>
#include <sdf_builder/shape/Collision.h>
#include <sdf_builder/shape/Visual.h>
#include <sstream>

// sdfbuilder

namespace sdf_builder {

Link::Link(std::string nm) :
	Posable(nm),
	selfCollide(true),
	inertial_(InertialPtr(new Inertial))
{}

Link::~Link()
{}

void Link::inertial(InertialPtr inert) {
	inertial_ = inert;
}

void Link::makeBox(double mass, double x, double y, double z,
		bool collision, bool visual) {
	// Give our inertial box properties
	inertial_->setBox(mass, x, y, z);

	if (collision) {
		// Create the collision box
		BoxPtr box(new Box(x, y, z));
		CollisionPtr col(new Collision("collision", box));
		this->addPosable(col);
	}

	if (visual) {
		// Create the collision box
		BoxPtr box(new Box(x, y, z));
		VisualPtr vis(new Visual("collision", box));
		this->addPosable(vis);
	}
}

/**
 * @return XML representation of the link
 */
std::string Link::toXML() {
	std::stringstream out;

	out << "<link name=\"" << name_ << "\">";
	out << pose_->toXML() << '\n';
	out << inertial_->toXML() << '\n';

	for (int i = 0, l = posables_.size(); i < l; ++i) {
		out << posables_[i]->toXML() << '\n';
	}

	out << "<self_collide>"
		<< (selfCollide ? "1" : "0")
		<< "</self_collide>";

	out << "</link>" << '\n';
	return out.str();
}

} /* namespace sdf_builder */
