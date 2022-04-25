#include "WebTemplate.h"
#include "Pjgen.h"

#define INDEX_HTML_CONTENT \
	"<!DOCTYPE html>\n" \
	"<html>\n" \
	"<head>\n" \
	"	<link rel=\"stylesheet\" href=\"style.css\">\n" \
	"	<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, minimum-scale=1.0, user-scalable=no\">\n" \
	"	<meta charset=\"UTF-8\">\n" \
	"	<title>&TITLE&</title>\n" \
	"</head>\n" \
	"<body>\n" \
	"	\n" \
	"</body>\n" \
	"</html>"

#define STYLE_CSS_CONTENT \
	"body {\n" \
	"	margin: 0;\n" \
	"}"

WebTemplate::WebTemplate() : ProjectTemplate("Web") { }

bool WebTemplate::_Generate(std::string &projectName) {
	std::string htmlPath = pjgen::rootDirPath + "/index.html";
	std::string htmlContent = INDEX_HTML_CONTENT;
	pjgen::ReplaceAll(htmlContent, "&TITLE&", projectName);
	if(!pjgen::WriteToFile(htmlPath, htmlContent)) {
		return false;
	}

	std::string cssPath = pjgen::rootDirPath + "/style.css";
	std::string cssContent = STYLE_CSS_CONTENT;
	if(!pjgen::WriteToFile(cssPath, cssContent)) {
		return false;
	}

	return true;
}
