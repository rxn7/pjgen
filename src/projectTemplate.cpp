#include "projectTemplate.h"
#include "pjgen.h"

bool ProjectTemplate::Generate(std::string &name) const {
	ColoredPrintLine(WHITE, "Generating project '" << name << "' from " << GetName() << " template...");
	return _Generate(name);
}
