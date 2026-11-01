#ifdef __linux__
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#include "log/log.h"
#include "mainShared.h"

uint32_t partialElfCrc = 0;

/* The game's command run without a shell: split at its spaces (the loader's
 * paths cannot hold any) and executed directly, with system()'s exit status.
 * Under box64 on ARM (the libretro core's aarch64 build) a shell is a native
 * ARM program, which cannot start the 32-bit x86 game nor preload the 32-bit
 * linuxloader.so into it; box64 runs an x86 program the loader executes
 * itself, with the loader's LD_PRELOAD. */
static int runCommand(char *command)
{
    char *argv[64];
    int argc = 0;
    for (char *tok = strtok(command, " "); tok && argc < 63; tok = strtok(NULL, " "))
        argv[argc++] = tok;
    argv[argc] = NULL;
    if (argc == 0)
        return -1;
    pid_t pid = fork();
    if (pid < 0)
        return -1;
    if (pid == 0)
    {
        execvp(argv[0], argv);
        _exit(127);
    }
    int status = 0;
    while (waitpid(pid, &status, 0) < 0)
        if (errno != EINTR)
            return -1;
    return status;
}

int main(int argc, char *argv[])
{
    char command[MAX_PATH_LENGTH] = {0};
    char originalDir[MAX_PATH_LENGTH] = {0};
    char gameELF[MAX_PATH_LENGTH] = {0};
    char libraryPath[MAX_PATH_LENGTH] = {0};

    if (parseArgs(argc, argv, command, originalDir, gameELF, libraryPath) != PARSE_ARGS_SUCCESS)
        return EXIT_SUCCESS;

    log_info("Starting $ %s", command);

    int sysCmd = runCommand(command);

    if (chdir(originalDir) != 0)
    {
        log_error("Could not return to the original directory.");
        return EXIT_FAILURE;
    }

    return sysCmd;
}
#endif