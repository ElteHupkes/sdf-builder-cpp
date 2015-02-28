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
	Model model("temp_bot");
	PosableGroupPtr group(new PosableGroup("my_group"));

	LinkPtr link(new Link("my_link"));
	LinkPtr link2(new Link("my_link_2"));
	link->makeBox(1.0, 1, 2, 3, true, true);
	link2->makeBox(10.0, 5, 5, 5, true, true);
	group->addPosable(link);
	group->addPosable(link2);

	model.addPosable(group);

	std::cout << "<?xml version=\"1.0\"?>" << '\n';
	std::cout << "<sdf version=\"1.5\">" << '\n';
	std::cout << model.toXML();
	std::cout << "</sdf>" << std::endl;
}
