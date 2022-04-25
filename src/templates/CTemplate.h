#pragma once

#include "Pjgen.h"
#include "ProjectTemplate.h"

class CTemplate : public ProjectTemplate {
public:
	CTemplate();
	virtual bool _Generate(std::string &projectName) override;
};
