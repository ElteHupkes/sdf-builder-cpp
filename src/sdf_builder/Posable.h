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

	static const bool RELATIVE_TO_PARENT_FRAME = false;
	static const bool RELATIVE_TO_CHILD_FRAME = true;

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
	 * ends of the vectors `my` and `at` touch, aligning
	 * both `myNormal` to `atNormal` as well as `myTangent`
	 * to `atTangent`.
	 *
	 * The two posables need to be in the same parent frame
	 * for this to work.
	 *
	 * @param Connection point at this posable
	 * @param Alignment vector of this posable normal to the connection point
	 * @param Alignment vector of this posable tangent to the connection point
	 * @param Connection point of other posable
	 * @param Alignment vector of other posable normal to the connection point
	 * @param Alignment vector of other posable tangent to the connection point
	 * @param other posable
	 * @param If true, all vectors are represented relative to the child frame
	 * 		  rather than the parent frame.
	 */
	void align(Vector3 my, Vector3 myNormal, Vector3 myTangent,
			Vector3 at, Vector3 atNormal, Vector3 atTangent,
			PosablePtr of, bool relativeToChildFrame = RELATIVE_TO_CHILD_FRAME);

	/**
	 * Performs a rotation around the given axis with the given angle.
	 *
	 * @param The vector to rotate around
	 * @param The angle to rotate, in radians
	 * @param Whether the given axis is in the child or the parent frame
	 */
	void rotateAround(Vector3 vector, double angle,
			bool relativeToChildFrame = RELATIVE_TO_PARENT_FRAME);

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
