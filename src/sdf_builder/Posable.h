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
	 * Sets this Posable's x/y/z position. Changes the Pose object.
	 *
	 * @param 3D position
	 */
	virtual void position(const Vector3& pos);

	/**
	 * Sets this link's rotation using a quaternion. Changes the
	 * link's pose object.
	 *
	 * @param Orientation quaternion
	 */
	virtual void rotation(const Quaternion& rot);

	/**
	 * Shortcut to the Pose's position
	 */
	const Vector3 & position();

	/**
	 * Shortcut to the Pose's rotation
	 */
	const Quaternion & rotation();

	/**
	 * Rotates and translates this posable, such that the
	 * ends of the vectors `my` and `at` touch, and the
	 * vectors `myAxis` and `atAxis` align. See the
	 * parameter description for the respective parameters'
	 * frames.
	 *
	 * The two posables need to be in the same parent frame
	 * for this to work.
	 *
	 * @param Connection point at this posable, relative to the parent frame
	 * @param Alignment vector of this posable, relative to the posable
	 * @param Connection point of other posable, relative to the parent frame
	 * @param Alignment vector of other posable, relative to the posable
	 * @param other posable
	 */
	void align(const Vector3& my, const Vector3& myAxis,
			const Vector3& at, const Vector3& atAxis, PosablePtr of);

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
