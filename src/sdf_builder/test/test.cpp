/**
 * Quick model creation test
 */
#include <sdf_builder/Parts.h>
#include <sdf_builder/Types.h>

// stdlib
#include <iostream>
#include <vector>

using namespace sdf_builder;

int main() {
	// The containing model
	Model model("temp_bot");

	LinkPtr link(new Link("my_link"));
	LinkPtr minibox(new Link("my_minibox"));

	// Link one is a vertical box
	link->makeBox(1.0, 2, 2, 4);

	// Minibox is... well, a mini box
	minibox->makeBox(0.1, 0.2, 0.2, 0.2);

	// Let's put minibox on the left-top of link 1 using our alignment
	// mechanism.
	minibox->align(
		// Bottom of minibox
		Vector3(0, 0, -0.1),

		// Normal vector
		Vector3(0, 0, -1),

		// Tangent vector
		Vector3(1, 0, 0),

		// Top left of link 1
		Vector3(-0.9, -0.9, 2),

		// Normal vector
		Vector3(0, 0, 1),

		// Tangent vector
		Vector3(1, 0, 0),

		// Link to align with
		link
	);

	// Add link and minibox to a posable group so we can
	// move them around together.
	PosableGroupPtr group(new PosableGroup("my_group"));
	group->addPosable(link);
	group->addPosable(minibox);

	//group->rotateAround(Vector3(0, 1, 0), 0.5);

	// Create a new, larger box called link2
	LinkPtr link2(new Link("my_link_2"));
	link2->makeBox(2.0, 4, 3, 3);

	// Now rotate this group so its right center
	// lands at the top center of link 2
	group->align(
		// Center of the right face of box 1
		Vector3(1, 0, 0),

		// Vector normal to box 2 right face
		Vector3(1, 0, 0),

		// Vector normal to box 2 top face should align with...(*)
		Vector3(0, 0, 1),

		// Center of the top face of box 2
		Vector3(0, 0, 1.5),

		// Vector normal to box 2 top face
		Vector3(0, 0, 1),

		// (*)...vector normal to box 2 right face
		Vector3(1, 0, 0),
		link2
	);

	model.addPosable(group);
	model.addPosable(link2);

	std::cout << "<?xml version=\"1.0\"?>" << '\n';
	std::cout << "<sdf version=\"1.5\">" << '\n';
	std::cout << model.toXML();
	std::cout << "</sdf>" << std::endl;
}
