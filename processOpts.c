#include "catalog.h"

// construct the longopts for our command line options
struct option longopts[] = {
    { "usage",      no_argument,        NULL, 'u' },
    { "reverse",    no_argument,        NULL, 'r' },
    { "insensitive",no_argument,        NULL, 'i' },
    { NULL,         0,                  NULL,  0  }
};

// pass in parameters and process with getopt_long
void 
processOpts(int argc, char **argv, char *progName, int *rFlag, int *iFlag)
{
    char ch;
    while((ch = getopt_long( argc, argv, "uri", longopts, NULL )) != -1 ) {
        switch (ch){
            // reverse
            case 'r':
                *rFlag = TRUE;
                break;
            // insensitive
            case 'i':
                *iFlag = TRUE;
                break;
            // usage
            case 'u':
                // print usage to stdout
                usage(progName, stdout);
                break;
            // unknown 
            case '?':
                // print usage to stderr
                usage(progName, stderr);
                break;
            // default behavior
            default:
                // print usage to stderr
                usage(progName, stderr);    
                break;
        }
    }
}

// usage function that prints the usage specified in the spec to either 
// stderr or stdout
void 
usage(char *progName, FILE *file)
{
    fprintf(file, "Usage: %s [-r] [-i] file [file ...]\n", progName );
    fprintf(file, "  --usage           print this information and exit\n");
    fprintf(file, "  -r --reverse      reverse alphabetic order\n");
    fprintf(file, "  -i --insensitive  case insensitive order\n");
    fprintf(file, "Default is case-sensitive alphabetic ordering\n");
    // if the file is stdout, print with an exit status of 0,
    // no error
    if (file == stdout) {
        exit(0);
    }
    // if the file is stderr, print with an exit status of 1,
    // error has occurred
    else {
        exit(1);
    }
}
