#ifndef _SDFB_TYPES_H_
#define _SDFB_TYPES_H_

// stdlib
#include <cmath>
#include <memory>

// eigen
#include <Eigen/Core>
#include <Eigen/Geometry>

namespace sdf_builder {

// Forward declarations
class Model;
class Link;
class PosableGroup;
class Shape;
class Geometry;
class Pose;
class Posable;
class Inertial;
class Box;
class Collision;
class Visual;
class Element;
class Axis;
class Limit;
class Joint;

// Typedefs
typedef Eigen::Vector3d Vector3;
typedef Eigen::Quaterniond Quaternion;
typedef Eigen::AngleAxisd AngleAxis;
typedef std::shared_ptr< Model > ModelPtr;
typedef std::shared_ptr< Link > LinkPtr;
typedef std::shared_ptr< PosableGroup > PosableGroupPtr;
typedef std::shared_ptr< Shape > ShapePtr;
typedef std::shared_ptr< Geometry > GeometryPtr;
typedef std::shared_ptr< Pose > PosePtr;
typedef std::shared_ptr< Posable > PosablePtr;
typedef std::shared_ptr< Inertial > InertialPtr;
typedef std::shared_ptr< Box > BoxPtr;
typedef std::shared_ptr< Collision > CollisionPtr;
typedef std::shared_ptr< Visual > VisualPtr;
typedef std::shared_ptr< Element > ElementPtr;
typedef std::shared_ptr< Axis > AxisPtr;
typedef std::shared_ptr< Limit > LimitPtr;
typedef std::shared_ptr< Joint > JointPtr;

}

#endif
