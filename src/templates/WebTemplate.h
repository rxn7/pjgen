#pragma once

#include "Pjgen.h"

class WebTemplate : public ProjectTemplate {
public:
	virtual constexpr std::string_view GetName() const override;

protected:
	virtual bool _Generate(std::string &projectName) const override;
};
