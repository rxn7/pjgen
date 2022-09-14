#include "RunScript.h"
#include "Pjgen.h"

#define RUN_SCRIPT_HEADER "#!/usr/bin/env bash\n\n"

#define RUN_SCRIPT_CONTENT \
        RUN_SCRIPT_HEADER \
	"./&OUT&\n" \

#define RUN_SCRIPT_CONTENT_PUSHD \
        RUN_SCRIPT_HEADER \
	"pushd bin > /dev/null 2>&1\n" \
	"./&OUT&\n" \
	"popd > /dev/null 2>&1\n"

void CreateRunScript(const std::string &out, bool pushd) {
	std::string content;
	pjgen::ReplaceAll(pushd ? RUN_SCRIPT_CONTENT_PUSHD : RUN_SCRIPT_CONTENT, content, "&OUT&", out);

	pjgen::WriteToFile("run.sh", content);
	system("chmod +x run.sh");
}
