#pragma once

#include "pjgen.h"

class WebTemplate : public ProjectTemplate {
public:
	inline constexpr std::string_view GetName() const override { return "Web"; }

protected:
	virtual bool _Generate(std::string &projectName) const override;
};
