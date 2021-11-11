#pragma once

#include "pjgen.h"

GEN_PROJECT(web) {
	#define INDEX_HTML \
		"<!DOCTYPE html>\n" \
		"<html>\n" \
		"<head>\n" \
		"	<link rel=\"stylesheet\" href=\"style.css\">\n" \
		"	<meta charset=\"UTF-8\">\n" \
		"	<title>%s</title>\n" \
		"</head>\n" \
		"<body>\n" \
		"	\n" \
		"</body>\n" \
		"</html>"

	char html_path[PATH_SIZE];
        strcpy(html_path, g_cwd);
        strcat(html_path, "/index.html");

	char css_path[PATH_SIZE];
        strcpy(css_path, g_cwd);
        strcat(css_path, "/style.css");

	char html_src[4096];
	sprintf(html_src, INDEX_HTML, _name);

	save_to_file(html_path, html_src);
	save_to_file(css_path, "");
}
