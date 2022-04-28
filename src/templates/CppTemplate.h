#pragma once

#include "Pjgen.h"

class CppTemplate : public ProjectTemplate {
public:
	inline virtual constexpr std::string_view GetName() const override { return "C++"; }

protected:
	virtual bool _Generate(std::string &projectName) const override;
};
