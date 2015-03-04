/*
 * TODO License
 */

#ifndef SDF_BUILDER_POSABLEPARENT_H_
#define SDF_BUILDER_POSABLEPARENT_H_

#include <sdf_builder/SdfBuilder.h>
#include <sdf_builder/Posable.h>

namespace sdf_builder {

class PosableParent {
public:
	PosableParent();
	virtual ~PosableParent();

	/**
	 * Copy constructor
	 */
	PosableParent(const PosableParent & other);

	/**
	 * Copy / swap pattern
	 */
	friend void swap(PosableParent & a, PosableParent & b);

	/**
	 * Adds a new posable element to this model
	 */
	void addPosable( PosablePtr element );

	/**
	 * @return Posable elements in this parent
	 */
	const std::vector< PosablePtr > & posables();

	/**
	 * Convenience method to output all posables in their
	 * XML form.
	 */
	virtual std::string toXML();
protected:
	/**
	 * List of posable elements in the model
	 */
	std::vector< PosablePtr > posables_;
};

} /* namespace sdf_builder */

#endif /* SDF_BUILDER_POSABLEPARENT_H_ */
