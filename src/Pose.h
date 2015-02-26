/**
 * @TODO License
 */
#ifndef SDF_BUILDER_POSE_H_
#define SDF_BUILDER_POSE_H_

#include <sdf_builder/Element.h>

namespace sdf_builder {

/**
 * A pose, used all over
 */
class Pose : public Element  {
public:
	Pose();
	~Pose();

	/**
	 * Returns a copy of the current position
	 */
	Vector3 position();

	/**
	 * Returns a copy of the current rotation
	 */
	Quaternion rotation();

	/**
	 * Sets x / y / z
	 */
	void setPosition(const Vector3& pos);

	/**
	 * Set rotation using a quaternion
	 */
	void setRotation(const Quaternion& rot);

	/**
	 * Set rotation using roll / pitch / yaw
	 */
	//void setRotation(double roll, double pitch, double yaw);

	/**
	 * Converts the current quaternion rotation to
	 * roll / pitch / yaw angles.
	 */
	Vector3 rotationToEuler();

	/**
	 * Converts to XML
	 */
	std::string toXML();

protected:
	/**
	 * Position vector
	 */
	Vector3 pos_;

	/**
	 * Rotation quaternion, easier to work
	 * with when doing actual rotations.
	 */
	Quaternion rot_;
};

} /* namespace sdf_builder */

#endif /* SDF_BUILDER_POSE_H_ */
