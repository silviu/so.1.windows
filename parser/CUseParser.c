#include <stdio.h>
#include <stdlib.h>

#include "parser.h"

#ifdef UNICODE
#  error "Unicode not supported in this source file!"
#endif

#define PROMPT_STRING	"> "


void parse_error(const char * str, const int where)
{
	fprintf(stderr, "Parse error near %d: %s\n", where, str);
}


int main(void)
{
	char line[1000];
	command_t *root = NULL;

	printf(PROMPT_STRING); fflush(stdout);
	if (fgets(line, sizeof(line), stdin) == NULL)
	{
		fprintf(stderr, "End of file!\n");
		return EXIT_SUCCESS;
	}
	/* we might have not read the entire line... */
	if (parse_line(line, &root)) {
		printf("Command successfully read!\n");
		if (root == NULL) {
			printf("Command is empty!\n");
		}
		else {
			/* root points to a valid command tree that we can use */
		}
	}
	else {
		/* there was an error parsing the command */
	}

	free_parse_memory();
	
	return EXIT_SUCCESS;
}
