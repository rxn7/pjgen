#pragma once

#include "../pjgen.hh"

void gen_web() {
	#define INDEX_HTML \
		"<!DOCTYPE html>\n" \
		"<html>\n" \
		"<head>\n" \
		"	<link rel=\"stylesheet\" href=\"style.css\">\n" \
		"	<meta name=\"vierport\" content=\"width=device-width, initial-scale=1.0, minimum-scale=1.0, user-scalable=no\">\n" \
		"	<meta charset=\"UTF-8\">\n" \
		"	<title>&TITLE&</title>\n" \
		"	<script src=\"script.js\"></script>\n" \
		"</head>\n" \
		"<body>\n" \
		"	\n" \
		"</body>\n" \
		"</html>"

	std::string html_path = g_root_dir + "/index.html";
	std::string css_path = g_root_dir + "/style.css";
	std::string js_path = g_root_dir + "/script.js";

	std::string html_content = INDEX_HTML;
	replace_all(html_content, "&TITLE&", g_proj_name);
	save_to_file(html_path, html_content);

	std::string blank = "\n";
	save_to_file(css_path, blank);
	save_to_file(js_path, blank);
}
