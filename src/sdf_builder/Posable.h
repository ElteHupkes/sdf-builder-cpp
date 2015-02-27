/*
 * @TODO License
 */

#ifndef SDF_BUILDER_POSABLE_H_
#define SDF_BUILDER_POSABLE_H_

// sdfbuilder
#include <sdf_builder/Element.h>
#include <sdf_builder/Pose.h>

namespace sdf_builder {

/**
 * A class for posable elements with a name
 */
class Posable : public Element {
public:
	explicit Posable(std::string name);
	virtual ~Posable();

	/**
	 * Copy constructor, the pose of this element
	 * needs to be deep-copied.
	 */
	Posable(const Posable &p);

	/**
	 * Swap function for copy-and-swap behavior.
	 * See e.g. http://stackoverflow.com/questions/3279543/what-is-the-copy-and-swap-idiom
	 *
	 * Child classes will have to implement the operator= (Posable is not constructable)
	 */
	friend void swap(Posable & a, Posable & b);

	/**
	 * Need to define this so Posables can also be cloned without
	 * being cast to `Element`s.
	 */
	virtual Posable * clone() const = 0;

	/**
	 * @return Shared pointer to the Posable's pose
	 */
	PosePtr pose();

	/**
	 * @return Name of the posable
	 */
	const std::string & name();

	/**
	 * Set the name of the posable
	 */
	void name(std::string name);

	/**
	 * Sets this link's x/y/z position. Changes the link's
	 * pose object.
	 *
	 * @param 3D position
	 */
	void setPosition(const Vector3& pos);

	/**
	 * Sets this link's rotation using a quaternion. Changes the
	 * link's pose object.
	 *
	 * @param Orientation quaternion
	 */
	void setRotation(const Quaternion& rot);

protected:
	/**
	 * Name of the element
	 */
	std::string name_;

	/**
	 * Pose of the element
	 */
	PosePtr pose_;
};

} /* namespace sdf_builder */

#endif /* SDF_BUILDER_POSABLE_H_ */
