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
	LinkPtr link(new Link("my_link"));
	link->makeBox(1.0, 1, 2, 3, true, true);
	model.addPosable(link);

	std::cout << "<?xml version=\"1.0\"?>" << '\n';
	std::cout << "<sdf version=\"1.5\">" << '\n';
	std::cout << model.toXML();
	std::cout << "</sdf>" << std::endl;
}
