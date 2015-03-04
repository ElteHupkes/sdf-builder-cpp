/**
 * @TODO License
 */
#ifndef SDF_MODEL_H_
#define SDF_MODEL_H_

// stdlib
#include <string>
#include <vector>

// sdfbuilder
#include <sdf_builder/Posable.h>
#include <sdf_builder/PosableParent.h>
#include <sdf_builder/ElementParent.h>

namespace sdf_builder {

/**
 * An SDF model
 */
class Model : public Posable, public PosableParent, public ElementParent  {
public:
	explicit Model(std::string name);
	virtual ~Model();

	/**
	 * Copy constructor
	 */
	Model(const Model & other);

	/**
	 * Virtual copy constructor
	 */
	virtual Model * clone() const;

	/**
	 * Copy-swap helper
	 */
	friend void swap(Model & a, Model & b);

	/**
	 * Assignment operator
	 */
	Model & operator=(Model other);

	/**
	 * Add a joint
	 */
	void addJoint(JointPtr joint);

	/**
	 * Returns the joints in this model
	 */
	const std::vector<JointPtr> & joints();

	/**
	 * Return XML representation
	 */
	std::string toXML();
protected:
	/**
	 * Whether or not this model has the static
	 * property in the world.
	 */
	bool isStatic_;

	/**
	 * List of joints in this model
	 */
	std::vector<JointPtr> joints_;
};

} /* namespace sdf */

#endif /* SDF_MODEL_H */
