/**
 * TODO License
 */
// stdlib
#include <sdf_builder/collision/Collision.h>
#include <sdf_builder/collision/Visual.h>
#include <sdf_builder/geometry/Box.h>
#include <sdf_builder/Link.h>
#include <sstream>

// sdfbuilder

namespace sdf_builder {

Link::Link(std::string nm) :
	Posable(nm),
	selfCollide(false),
	inertial_(InertialPtr(new Inertial))
{}

Link::~Link()
{}

Link::Link(const Link & other):
	Posable(other),
	PosableParent(other),
	ElementParent(other),
	selfCollide(other.selfCollide),
	inertial_(InertialPtr(other.inertial_ ? other.inertial_->clone() : nullptr))
{}

Link * Link::clone() const {
	return new Link(*this);
}

void swap(Link & a, Link & b) {
	using std::swap;

	swap(static_cast<Posable &>(a), static_cast<Posable &>(b));
	swap(static_cast<PosableParent &>(a), static_cast<PosableParent &>(b));
	swap(a.selfCollide, b.selfCollide);
	swap(a.inertial_, b.inertial_);
}

Link & Link::operator=(Link other) {
	swap(*this, other);
	return *this;
}

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
		VisualPtr vis(new Visual("visual", box));
		this->addPosable(vis);
	}
}

/**
 * @return XML representation of the link
 */
std::string Link::toXML() {
	std::stringstream out;

	out << "<link name=\"" << name_ << "\">";
	out << "<self_collide>" << selfCollide << "</self_collide>";
	out << pose_->toXML() << '\n';
	out << inertial_->toXML() << '\n';

	out << PosableParent::toXML() << '\n';
	out << ElementParent::toXML() << '\n';

	out << "</link>" << '\n';
	return out.str();
}

} /* namespace sdf_builder */
