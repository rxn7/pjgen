#include "RunScript.h"
#include "Pjgen.h"

#define RUN_SCRIPT_CONTENT \
	"#!/bin/sh\n\n" \
	"pushd bin > /dev/null 2>&1\n" \
	"./&OUT&\n" \
	"popd > /dev/null 2>&1\n"

void CreateRunScript(const std::string &out) {
	std::string content;
	pjgen::ReplaceAll(RUN_SCRIPT_CONTENT, content, "&OUT&", out);

	pjgen::WriteToFile("run.sh", content);
	system("chmod +x run.sh");
}
