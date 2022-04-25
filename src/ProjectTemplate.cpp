#include "ProjectTemplate.h"

ProjectTemplate::ProjectTemplate(std::string templateName) 
: m_TemplateName(templateName) { }

ProjectTemplate::~ProjectTemplate() { }

bool ProjectTemplate::Generate(std::string &name) {
	ColoredPrintLine(WHITE, "Generating project '" << name << "' from " << m_TemplateName << " template...");
	return _Generate(name);
}

bool ProjectTemplate::_Generate(std::string &name) {
	return true;
}
