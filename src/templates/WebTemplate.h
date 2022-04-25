#pragma once

#include "Pjgen.h"
#include "ProjectTemplate.h"

class WebTemplate : public ProjectTemplate {
public:
	WebTemplate();
	virtual bool _Generate(std::string &projectName) override;
};
