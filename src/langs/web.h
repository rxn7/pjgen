#pragma once

#include "pjgen.h"

void gen_web() {
	#define INDEX_HTML \
		"<!DOCTYPE html>\n" \
		"<html>\n" \
		"<head>\n" \
		"	<link rel=\"stylesheet\" href=\"style.css\">\n" \
		"	<meta name=\"vierport\" content=\"width=device-width, initial-scale=1.0, minimum-scale=1.0, user-scalable=no\">\n" \
		"	<meta charset=\"UTF-8\">\n" \
		"	<title>%s</title>\n" \
		"	<script src=\"script.js\"></script>\n" \
		"</head>\n" \
		"<body>\n" \
		"	\n" \
		"</body>\n" \
		"</html>"

	char html_path[PATH_SIZE];
        strcpy(html_path, g_root_dir);
        strcat(html_path, "/index.html");

	char css_path[PATH_SIZE];
        strcpy(css_path, g_root_dir);
        strcat(css_path, "/style.css");

	char js_path[PATH_SIZE];
	strcpy(js_path, g_root_dir);
	strcat(js_path, "/script.js");

	char html_src[4096];
	sprintf(html_src, INDEX_HTML, g_proj_name);

	save_to_file(html_path, html_src);
	save_to_file(css_path, "");
	save_to_file(js_path, "");
}
