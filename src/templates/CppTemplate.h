#pragma once

#include "Pjgen.h"

class CppTemplate : public ProjectTemplate {
public:
	CppTemplate();
	virtual bool _Generate(std::string &projectName) override;
};
