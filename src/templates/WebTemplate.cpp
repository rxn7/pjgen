#include "WebTemplate.h"
#include "Pjgen.h"

bool WebTemplate::_Generate(std::string &projectName) const {
	bool flagJs = false;
	for(std::string_view flag : pjgen::flags) {
		if(flag == "js") {
			flagJs = true;
			break;
		}
	}

	std::string htmlContent = 
R"(<!DOCTYPE html>
<html>
<head>
	<link rel="stylesheet" href="style.css">
	<meta name="viewport" content="width=device-width, initial-scale=1.0, minimum-scale=1.0, user-scalable=no">
	<meta charset="UTF-8">
	<title>&TITLE&</title>
</head>
<body>

</body>&JS&
</html>)";

	std::string cssContent = 
R"(body {
	margin: 0;
})";

	std::string htmlPath = "index.html";
	pjgen::ReplaceAll(htmlContent, htmlContent, "&TITLE&", projectName);

	if(flagJs) {
		pjgen::ReplaceAll(htmlContent, htmlContent, "&JS&", "\n<script src=\"index.js\"></script>");
		pjgen::WriteToFile("index.js", "");
	} else {
		pjgen::ReplaceAll(htmlContent, htmlContent, "&JS&", "");
	}

	if(!pjgen::WriteToFile(htmlPath, htmlContent))
		return false;

	std::string cssPath = "style.css";
	if(!pjgen::WriteToFile(cssPath, cssContent))
		return false;

	return true;
}
