#include "WebTemplate.h"

constexpr std::string_view WebTemplate::GetName() const {
	return "Web";
}

bool WebTemplate::_Generate(std::string &projectName) const {
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

</body>
</html>)";

	std::string cssContent = 
R"(body {
	margin: 0;
})";

	std::string htmlPath = pjgen::rootDirPath + "/index.html";
	pjgen::ReplaceAll(htmlContent, "&TITLE&", projectName);
	if(!pjgen::WriteToFile(htmlPath, htmlContent)) {
		return false;
	}

	std::string cssPath = pjgen::rootDirPath + "/style.css";
	if(!pjgen::WriteToFile(cssPath, cssContent)) {
		return false;
	}

	return true;
}
