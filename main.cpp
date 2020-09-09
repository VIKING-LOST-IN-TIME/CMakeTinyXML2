#include <iostream>
#include <tinyxml2.h>
#include <CMakeTinyXML2Config.h>

int main(int argc, char* argv[])
{
	std::cout << argv[0] << " Version " << CMakeTinyXML2_VERSION_MAJOR << "." << CMakeTinyXML2_VERSION_MINOR << std::endl;

    const char* filename = "resources/team.xml";

	tinyxml2::XMLDocument doc;
	doc.LoadFile(filename);

	// Load root element of xml
	tinyxml2::XMLElement* businessElement = doc.FirstChildElement("business");

	// Read from xml and log to console
	for (tinyxml2::XMLElement* child = businessElement->FirstChildElement("team")->FirstChildElement(); child != NULL; child = child->NextSiblingElement())
	{
		std::string firstname = child->FirstChildElement("firstname")->GetText();
		std::string lastname = child->FirstChildElement("lastname")->GetText();
		unsigned int age = atoi (child->FirstChildElement("age")->GetText());

		std::cout << firstname << " " << lastname << " is " << age << " years old." << std::endl;
	}

	// Update an element inside the xml
	time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	businessElement->FirstChildElement("last-update")->SetText(std::ctime(&now));
	doc.SaveFile(filename);
}