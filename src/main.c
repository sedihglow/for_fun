#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <stdbool.h>
#include <limits.h>
#include "utility.h"
#include "convNum.h"

/* Flag set by ‘--verbose’. */
static bool verbose_flag;

int main(int argc, char *argv[])
{
	int c;
	/* getopt_long stores the option index here. */
	int option_index = 0;

	compare_limits(_NANO_1SEC);
	compare_dbl_limits(DBL_MAX);
	exit(EXIT_SUCCESS);

	while (true) {
		static struct option long_options[] = {
			/* These options set a flag. */
			{"verbose", no_argument, (int*)&verbose_flag, true},
			{"brief",   no_argument, (int*)&verbose_flag, false},
			/* These options don’t set a flag.
			   We distinguish them by their indices. */
			{"add",     no_argument,       NULL, 'a'},
			{"append",  no_argument,       NULL, 'b'},
			{"delete",  required_argument, NULL, 'd'},
			{"create",  required_argument, NULL, 'c'},
			{"file",    required_argument, NULL, 'f'},
			{0, 0, 0, 0}
		};


		c = getopt_long(argc, argv, "abc:d:f:",
			       long_options, &option_index);

		/* Detect the end of the options. */
		if (c == -1)
			break;

		switch (c) {
		case 0:
			/* If this option set a flag, do nothing else now. */
			if (long_options[option_index].flag != 0)
				break;

			printf("option %s", long_options[option_index].name);

			if (optarg)
				printf(" with arg %s", optarg);
			printf("\n");
		break;
		case 'a':
			puts("option -a\n");
		break;
		case 'b':
			puts("option -b\n");
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
		puts ("verbose flag is set");

	/* Print any remaining command line arguments (not options). */
	if (optind < argc) {
		puts("non-option ARGV-elements: ");
		while (optind < argc)
			printf("%s ", argv[optind++]);
		putchar('\n');
	}



	exit(EXIT_SUCCESS);
}
