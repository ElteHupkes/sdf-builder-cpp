/**
 * @TODO License
 */
#ifndef SDF_MODEL_H_
#define SDF_MODEL_H_

// stdlib libraries
#include <sdf_builder/Posable.h>
#include <sdf_builder/PosableParent.h>
#include <string>
#include <vector>

// SDF builder libraries

namespace sdf_builder {

/**
 * An SDF model
 */
class Model : public Posable, public PosableParent  {
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
	 * Return XML representation
	 */
	std::string toXML();
protected:
	/**
	 * Whether or not this model has the static
	 * property in the world.
	 */
	bool isStatic_;
};

} /* namespace sdf */

#endif /* SDF_MODEL_H */
