#include "WebTemplate.h"
#include "ColoredPrint.h"
#include "Pjgen.h"
#include "templates/web/WebTemplateFiles.h"

bool WebTemplate::_Generate(std::string &projectName) const {
	enum : std::uint8_t {
		NoScript = 0,
		JavaScript,
		TypeScript,
	} scriptType = NoScript;

	for(std::string_view flag : pjgen::flags) {
		if(flag == "js") {
			scriptType = JavaScript;
		} else if(flag == "ts") {
			scriptType = TypeScript;
		}
	}

	std::string htmlContent;
	pjgen::ReplaceAll(WEB_TEMPLATE_HTML_CONTENT, htmlContent, "&TITLE&", projectName);

	if(scriptType != NoScript) {
		if(!std::filesystem::create_directory("src")) {
			ColoredPrintLine(RED, "Failed to create src directory");
			return false;
		}
	} else {
		pjgen::ReplaceAll(htmlContent, htmlContent, "&JS&", "");
	}

	if(scriptType == JavaScript) {
		pjgen::WriteToFile("src/index.js", "");
		pjgen::ReplaceAll(htmlContent, htmlContent, "&JS&", "\n<script src=\"src/index.js\"></script>");
	} else if(scriptType == TypeScript) {
		pjgen::WriteToFile("src/index.ts", "");
		pjgen::WriteToFile("tsconfig.json", WEB_TEMPLATE_TSCONFIG_CONTENT);
		pjgen::ReplaceAll(htmlContent, htmlContent, "&JS&", "\n<script src=\"build/index.js\"></script>");
	}

	if(!pjgen::WriteToFile("index.html", htmlContent))
		return false;

	if(!pjgen::WriteToFile("style.css", WEB_TEMPLATE_CSS_CONTENT))
		return false;

	return true;
}