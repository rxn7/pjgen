#include "ProjectTemplate.h"
#include "Pjgen.h"

bool ProjectTemplate::Generate(std::string &name) const {
	ColoredPrintLine(WHITE, "Generating project '" << name << "' from " << GetName() << " template...");
	return _Generate(name);
}
