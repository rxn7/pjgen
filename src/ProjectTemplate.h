#pragma once

#include "Pjgen.h"

class ProjectTemplate {
public:
	virtual ~ProjectTemplate();
	bool Generate(std::string &name);

protected:
	virtual bool _Generate(std::string &name);
	ProjectTemplate(std::string templateName);

	std::string m_TemplateName;
};
