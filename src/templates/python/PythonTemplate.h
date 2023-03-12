#pragma once

#include "Pjgen.h"

class PythonTemplate : public ProjectTemplate {
public:
	inline constexpr std::string_view GetName() const override { return "Python"; }

protected:
	virtual bool _Generate(std::string &projectName) const override;
};
