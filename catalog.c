#include "catalog.h"

int 
main( int argc, char *argv[] )
{
    // variable to hold our program name
    char *progName = argv[0];
    // varaible to hold our reverse flag
    int rFlag = FALSE;
    // varaible to hold our insensitive flag
    int iFlag = FALSE;
    // variable to hold our input file
    FILE *inputFile;
    // variable to hold our output file
    FILE *outputFile;
    // loop variable 
    int i;
    // hold the output file name
    char *outputFileName;
    // pass in the arguments, flag and program name to be processed
    processOpts( argc, argv, progName, &rFlag, &iFlag );

    // adjust the agrument count and position
    argc -= optind;
    argv += optind;

    // if the argument number is 0, we are missing the file name
    if (argc == 0) {
        fprintf(stderr, "Missing file name\n");
        usage(progName, stderr);
    }
    // else start to process the files
    else {
        for(i = 0; i < argc; i++) {
            // hold the string length
            int len = strlen(argv[i]);
            outputFileName = malloc(len + 7);
            memcpy(outputFileName, argv[i], len+1);
            // append (or concatenate) .save to the file name
            strcat(outputFileName, ".save");
            char *txt = malloc(len+6);
            memcpy(txt, argv[i], len+1);
            // append (or concatenate) .save to the file name
            strcat(txt, ".txt");
            char *command = malloc(len+11);
            memcpy(command, argv[i],len+1);
            // append (or concatenate) .save to the file name
            strcat(command,".commands");
            // set the command file variable
            FILE *cmdFile = fopen(command, "r");
            // set the output file variable
            outputFile = fopen(outputFileName, "w");
            // set the input file variable
            inputFile = fopen(txt, "r" );
            // if the input file is NULL, print error to stderr along with usage
            if (inputFile == NULL) {
                fprintf( stderr, "Unable to open %s for reading\n", argv[i] );
                usage( progName, stderr );
            }
            // process the given files and commands
            else { 
                printf("%s:\n\n",argv[i]);
                BSTNode root = processInputFile(inputFile, outputFile, rFlag, iFlag);
                root = processCommands(cmdFile, outputFile, rFlag, iFlag, root); 
                // after processing, free the file names
                free(outputFileName);
                free(txt);
                free(command);
                // close the files
                fclose(outputFile);
                fclose(cmdFile);
                fclose(inputFile);
                // delete the tree, freeing all the text and node references
                deleteTree(root);
            }
        }
    }
    return 0;
}
