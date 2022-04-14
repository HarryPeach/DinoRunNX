// Include the most common headers from the C standard library
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

// Include the main libnx system header, for Switch development
#include <switch.h>

// Exits the program, while also clearing up initialised resources and displaying any errors outputted during the run
int exit_program(int code, unsigned long long sleep_timer)
{
    consoleUpdate(NULL);
    svcSleepThread(sleep_timer);
    consoleExit(NULL);
    return code;
}

int exit_error()
{
    return exit_program(1, 5000000000ull);
}

int exit_graceful()
{
    return exit_program(0, 0ull);
}

// Main program entrypoint
int main(int argc, char *argv[])
{
    consoleInit(NULL);

    printf(CONSOLE_GREEN "Chromium Dino Run\n" CONSOLE_WHITE);
    printf("Ported by Harry Peach\n");
    printf("\nLicensed under the BSD3 license, found in the LICENSE file.\n\n");

    consoleUpdate(NULL);

    Result last_result = 0;
    WebCommonConfig config;
    WebCommonReply reply;
    WebExitReason exitReason = 0;

    if (appletGetAppletType() != AppletType_Application)
    {
        printf(CONSOLE_RED "ERROR: The applet cannot run if launched from the album menu, please launch by overriding a title!\n" CONSOLE_WHITE);
        return exit_error();
    }

    printf("\nDebug output:\n");
    consoleUpdate(NULL);

    last_result = webOfflineCreate(&config, WebDocumentKind_OfflineHtmlPage, 0, ".htdocs/dino_run/index.html");
    if (R_FAILED(last_result))
    {
        printf("webOfflineCreate() result: 0x%x\n", last_result);
        return exit_error();
    }

    last_result = webConfigSetFooterFixedKind(&config, WebFooterFixedKind_Hidden);
    if (R_FAILED(last_result))
    {
        printf("webConfigSetFooterFixedKind() result: 0x%x\n", last_result);
        return exit_error();
    }

    last_result = webConfigShow(&config, &reply);
    if (R_FAILED(last_result))
    {
        printf("webConfigShow(): 0x%x\n", last_result);
        return exit_error();
    }

    // Result rc = webReplyGetExitReason(&reply, &exitReason);
    // printf("webReplyGetExitReason(): 0x%x", rc);
    // if (R_SUCCEEDED(rc))
    //     printf(", 0x%x", exitReason);
    // printf("\n");

    return exit_graceful();
}
