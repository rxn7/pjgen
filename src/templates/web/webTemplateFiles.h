#pragma once

#define WEB_TEMPLATE_HTML_CONTENT \
    "<!DOCTYPE html>\n" \
    "<html>\n" \
    "<head>\n" \
    "\t<link rel=\"stylesheet\" href=\"style.css\">\n" \
    "\t<meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, minimum-scale=1.0, user-scalable=no\">\n" \
    "\t<meta charset=\"UTF-8\">\n" \
    "\t<title>&TITLE&</title>\n" \
    "</head>\n" \
    "<body>\n" \
    "</body>&JS&\n" \
    "</html>"

#define WEB_TEMPLATE_CSS_CONTENT \
    "body {\n" \
    "\tmargin: 0;\n" \
    "}"

#define WEB_TEMPLATE_TSCONFIG_CONTENT \
    "{\n" \
        "\"compilerOptions\": {\n" \
            "\"target\": \"es2020\",\n" \
            "\"module\": \"es2020\",\n" \
            "\"rootDir\": \"./src\",\n" \
            "\"allowJs\": false,\n" \
            "\"declaration\": false,\n" \
            "\"declarationMap\": false,\n" \
            "\"sourceMap\": false,\n" \
            "\"outDir\": \"build\",\n" \
            "\"removeComments\": true,\n" \
            "\"inlineSourceMap\": false,\n" \
            "\"inlineSources\": false,\n" \
            "\"noEmitOnError\": true,\n" \
            "\"esModuleInterop\": true,\n" \
            "\"forceConsistentCasingInFileNames\": true,\n" \
            "\"strict\": true,\n" \
            "\"noImplicitAny\": true,\n" \
            "\"strictNullChecks\": true,\n" \
            "\"strictFunctionTypes\": true,\n" \
            "\"strictBindCallApply\": true,\n" \
            "\"strictPropertyInitialization\": true,\n" \
            "\"noImplicitThis\": true,\n" \
            "\"noUnusedLocals\": false,\n" \
            "\"noImplicitReturns\": true,\n" \
            "\"noImplicitOverride\": true,\n" \
            "\"skipLibCheck\": true\n" \
        "}\n" \
    "}"