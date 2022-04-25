#pragma once

#include "Pjgen.h"

class PythonTemplate : public ProjectTemplate {
public:
	PythonTemplate();
	virtual bool _Generate(std::string &projectName) override;
};
