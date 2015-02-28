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
//	Model model("temp_bot");
//	PosableGroupPtr group(new PosableGroup("my_group"));
//
//	LinkPtr link(new Link("my_link"));
//	LinkPtr link2(new Link("my_link_2"));
//	link->makeBox(1.0, 1, 2, 3, true, true);
//	link2->makeBox(10.0, 5, 5, 5, true, true);
//	group->addPosable(link);
//	group->addPosable(link2);
//
//	model.addPosable(group);
//

	Model model("temp_bot");
	LinkPtr link(new Link("my_link"));
	LinkPtr link2(new Link("my_link_2"));

	link->makeBox(1.0, 2, 2, 4);
	link2->makeBox(2.0, 4, 4, 4);

	link->align(
		Vector3(0, 0, 0),
		Vector3(0, 1, 0),
		Vector3(0, 0, 1),
		Vector3(0, 0, 0),
		Vector3(0, 0, 2),
		Vector3(1, 0, 0),
		link2
	);

	model.addPosable(link);
	model.addPosable(link2);

	std::cout << "<?xml version=\"1.0\"?>" << '\n';
	std::cout << "<sdf version=\"1.5\">" << '\n';
	std::cout << model.toXML();
	std::cout << "</sdf>" << std::endl;
}
