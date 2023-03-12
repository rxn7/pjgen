#pragma once

#include "Pjgen.h"

class CTemplate : public ProjectTemplate {
public:
	inline constexpr std::string_view GetName() const override { return "C"; }

protected:
	virtual bool _Generate(std::string &projectName) const override;
};
