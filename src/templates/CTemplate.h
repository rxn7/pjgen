#pragma once

#include "Pjgen.h"

class CTemplate : public ProjectTemplate {
public:
	CTemplate();
	virtual bool _Generate(std::string &projectName) override;
};
