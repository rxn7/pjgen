#pragma once

#include "Pjgen.h"

class ProjectTemplate {
public:
	virtual inline constexpr std::string_view GetName() const = 0;
	bool Generate(std::string &name) const;

protected:
	virtual bool _Generate(std::string &name) const = 0;
};
