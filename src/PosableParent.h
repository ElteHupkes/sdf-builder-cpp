/*
 * TODO License
 */

#ifndef SDF_BUILDER_POSABLEPARENT_H_
#define SDF_BUILDER_POSABLEPARENT_H_

#include <sdf_builder/Posable.h>
#include <tol/SdfBuilder.h>

namespace sdf_builder {

class PosableParent {
public:
	PosableParent();
	virtual ~PosableParent();

	/**
	 * Adds a new posable element to this model
	 */
	void addPosable( PosablePtr element );

	/**
	 * @return Posable elements in this parent
	 */
	const std::vector< PosablePtr > & posables();
protected:
	/**
	 * List of posable elements in the model
	 */
	std::vector< PosablePtr > posables_;
};

} /* namespace sdf_builder */

#endif /* SDF_BUILDER_POSABLEPARENT_H_ */
