// Include the most common headers from the C standard library
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
// #include <pthread.h>

// Include the main libnx system header, for Switch development
#include <switch.h>
// #include <hello.h>

// See also libnx web.h.

// This example shows how to use the web LibraryApplets.

// Main program entrypoint
int main(int argc, char *argv[])
{
    Result rc = 0;
    consoleInit(NULL);

    printf(CONSOLE_GREEN "Chromium Dino Run\n" CONSOLE_WHITE);
    printf("Ported by Harry Peach\n");
    printf("\nLicensed under the BSD3 license, found in the LICENSE file.");

    consoleUpdate(NULL);

    // Main loop
    while (appletMainLoop())
    {
        // Scan all the inputs. This should be done once for each frame
        // hidScanInput();

        // u64 kDown = hidKeysDown(CONTROLLER_P1_AUTO);

        WebCommonConfig config;
        WebCommonReply reply;
        WebExitReason exitReason = 0;

        rc = webOfflineCreate(&config, WebDocumentKind_OfflineHtmlPage, 0, ".htdocs/dino_run/index.html");
        printf("webOfflineCreate(): 0x%x\n", rc);

        if (R_SUCCEEDED(rc))
        {
            rc = webConfigSetFooterFixedKind(&config, WebFooterFixedKind_Hidden);
            printf("webConfigSetFooterFixedKind(): 0x%x\n", rc);

            if (R_SUCCEEDED(rc))
            { // Launch the applet and wait for it to exit.
                printf("Running webConfigShow...\n");
                rc = webConfigShow(&config, &reply); // If you don't use reply you can pass NULL for it.
                printf("webConfigShow(): 0x%x\n", rc);
            }

            if (R_SUCCEEDED(rc))
            { // Normally you can ignore exitReason.
                rc = webReplyGetExitReason(&reply, &exitReason);
                printf("webReplyGetExitReason(): 0x%x", rc);
                if (R_SUCCEEDED(rc))
                    printf(", 0x%x", exitReason);
                printf("\n");
                break;
            }
        }

        // Update the console, sending a new frame to the display
        consoleUpdate(NULL);
    }

    // Deinitialize and clean up resources used by the console (important!)
    consoleExit(NULL);
    return 0;
}
