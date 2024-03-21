#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdbool.h>
#include <limits.h>
#include "err_handle.h"
#include "convNum.h"

/* Flag set by ‘--verbose’. */
static bool verbose_flag = false;

int main(int argc, char *argv[])
{
	int c;
	/* getopt_long stores the option index here. */
	int option_index = 0;

	while (true) {
		static struct option long_options[] = {
			/* These options set a flag. */
			{"verbose", no_argument, (int*)&verbose_flag, true},
			{"brief",   no_argument, (int*)&verbose_flag, false},
			/* These options don’t set a flag.
			   We distinguish them by their indices. */
			{"insert",  no_argument,       NULL, 'i'},
			{"append",  no_argument,       NULL, 'a'},
			{"delete",  required_argument, NULL, 'd'},
			{"create",  required_argument, NULL, 'c'},
			{"file",    required_argument, NULL, 'f'},
			{"help",    no_argument,       NULL, 'h'},
			{0, 0, 0, 0}
		};


		c = getopt_long(argc, argv, "iad:c:f:h",
			       long_options, &option_index);

		/* Detect the end of the options. */
		if (c == -1)
			break;

		switch (c) {
		case 0: /* TODO: Test case 0 option in long option */
			/* If this option set a flag, do nothing else now. */
			if (long_options[option_index].flag != 0)
				break;

			printf("option %s", long_options[option_index].name);

			if (optarg)
				printf(" with arg %s", optarg);
			printf("\n");
		break;
		case 'i':
			puts("option -i\n");
		break;
		case 'a':
			puts("option -a\n");
		break;
		case 'c':
			printf("option -c with value `%s'\n", optarg);
		break;
		case 'd':
			printf("option -d with value `%s'\n", optarg);
		break;
		case 'f':
			printf("option -f with value `%s'\n", optarg);
		break;
		case 'h':
			printf("-- Progam: for_fun --\n"
			       "--help, -h: Print this help menu and exit\n"
			       "--insert, -i\n"
			       "--add,    -a\n"
			       "--create, -c\n"
			       "--delete, -d\n"
			       "--file,   -f\n");
		break;
		case '?':
			/* getopt_long already printed an error message. */
		break;
		default:
			abort();
		}
	}

	/* Instead of reporting ‘--verbose’
	   and ‘--brief’ as they are encountered,
	   we report the final status resulting from them. */
	if (verbose_flag)
		puts("verbose flag is set");

	/* Print any remaining command line arguments (not options). */
	if (optind < argc) {
		puts("non-option ARGV-elements: ");
		while (optind < argc)
			printf("%s ", argv[optind++]);
		putchar('\n');
	}

	exit(EXIT_SUCCESS);
}
