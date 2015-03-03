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
	 * You can choose to specify the positions and orientations either in the parent
	 * frame or in the child frame using the final argument to this method.
	 * Be aware that representing orientation vectors in the parent frame
	 * merely means that they are already rotated with respect to their parent,
	 * not translated.
	 *
	 * @param Connection point at this posable
	 * @param Alignment vector of this posable normal to the connection point
	 * @param Alignment vector of this posable tangent to the connection point
	 * @param Connection point of other posable
	 * @param Alignment vector of other posable normal to the connection point
	 * @param Alignment vector of other posable tangent to the connection point
	 * @param other posable
	 * @param If false, all vectors are represented relative to the parent frame
	 * 		  rather than the child frame.
	 */
	void align(const Vector3 & my, const Vector3 & myNormal, const Vector3 & myTangent,
			const Vector3 & at, const Vector3 & atNormal, const Vector3 & atTangent,
			PosablePtr of, bool relativeToChildFrame = RELATIVE_TO_CHILD_FRAME);

	/**
	 * Rotates this posable such that the vector `my` aligns
	 * with the vector `other` in the other posable `of`.
	 * Note there are infinitely many ways of satisfying this constraint,
	 * use `align` with a normal and a tangent to specify a unique rotation.
	 * Posables should share a parent frame.
	 *
	 * @param Child vector to align
	 * @param Other vector to align
	 * @param Other object
	 * @param Whether vectors are relative to the child or parent frame
	 * @param Vector used for rotation if `my` and `other` are opposite vectors.
	 */
	void align(const Vector3 & my, const Vector3 & other, PosablePtr of,
			bool relativeToChildFrame = RELATIVE_TO_CHILD_FRAME,
			const Vector3 & fallback = Vector3(0, 0, 0));

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
