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

    WebCommonConfig config;
    WebCommonReply reply;

    // Check if the applet is being run from the album
    if (appletGetAppletType() != AppletType_Application)
    {
        printf(CONSOLE_RED "ERROR: The applet cannot run if launched from the album menu, please launch by overriding a title!\n" CONSOLE_WHITE);
        return exit_error();
    }

    printf("\nDebug output:\n");
    consoleUpdate(NULL);

    Result res_create_web = webOfflineCreate(&config, WebDocumentKind_OfflineHtmlPage, 0, ".htdocs/dino_run/index.html");
    if (R_FAILED(res_create_web))
    {
        printf("webOfflineCreate failed with code: 0x%x\n", res_create_web);
        return exit_error();
    }

    webConfigSetFooterFixedKind(&config, WebFooterFixedKind_Hidden);
    webConfigSetWebAudio(&config, true);
    webConfigSetTouchEnabledOnContents(&config, true);

    Result res_config_show = webConfigShow(&config, &reply);
    if (R_FAILED(res_config_show))
    {
        printf("webConfigShow failed with code: 0x%x\n", res_config_show);
        return exit_error();
    }

    return exit_graceful();
}
