# Contributing Guidelines

To contribute your changes to the project, please follow the [GitHub how to](https://help.github.com/articles/using-pull-requests/) for pull requests

## Code Style

### Sources
    - Use `typedef struct`s instead of `struct`s unless absolutely neccesary
    - Include unit tests when you contribute new features to ensure that your feature is functional both now and in future builds
        Tests are to be placed in the `tests` folder and follow the same structure as the `src` folder
        A sample test can be found in `tests/sanity_check.c`

        NB. Ensure you add `extern int register_SUITENAME_suite();` and call it inside of the `cunit_test.c` main function
    - Use on-line opening brackets
    - Use bracketless statements where possible
    - Use varadic arguments instead of arrays for direct arguments where possible

### Headers
    - Use `#define` and `#ifndef` to implement one-time includes, DO NOT USE `#pragma once`
    - Define function pointer types where the type is to be implemented in a program
    - Use /**DOCUMENTATION*/ on all functions & types (Not neccesary for structs) in headers

## Scripts & Tools

NB. If it isn't reused internally or externally more than once, you dont need a script for it

Compilation targets only are to be placed in the Makefile, other scripts and tools go in the scripts folder

Scripts don't require tests, but please ensure they function properly for their purpose before adding them

### Makefile
    - Document all callable targets using ### (Documentation is self-generating)
    - Avoid requiring `$(exec)` in targets as it messes up the documentation output, run make inside the target instead

### Other tools
    - Avoid fetching external resources from webpages and the like
    - Place implementations of 3rd-party tools in the top level scripts directory, only the tools themselves need to be placed in `scripts/vendor`
    - Try to stick to Bash/Python where possible, though ruby is also acceptable
    - Try to use GNU versions of Bash programs
    - Add a shebang to all scripts
    - Ensure that the script provides usage information when used incorrectly
