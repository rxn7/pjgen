#pragma once

#include "Pjgen.h"
#include "ProjectTemplate.h"

class CppTemplate : public ProjectTemplate {
public:
	CppTemplate();
	virtual bool _Generate(std::string &projectName) override;
};
