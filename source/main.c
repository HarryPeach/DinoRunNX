// Include the most common headers from the C standard library
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

// Include the main libnx system header, for Switch development
#include <switch.h>

// Main program entrypoint
int main(int argc, char *argv[])
{
    Result rc = 0;
    consoleInit(NULL);

    printf(CONSOLE_GREEN "Chromium Dino Run\n" CONSOLE_WHITE);
    printf("Ported by Harry Peach\n");
    printf("\nLicensed under the BSD3 license, found in the LICENSE file.\n");
    printf("\n Debug output:\n");

    // Configure our supported input layout: a single player with standard controller styles
    padConfigureInput(1, HidNpadStyleSet_NpadStandard);

    // Init default gamepad
    PadState pad;
    padInitializeDefault(&pad);

    consoleUpdate(NULL);

    // Main loop
    while (appletMainLoop())
    {
        // Scan all the inputs. This should be done once for each frame
        padUpdate(&pad);

        u64 kDown = padGetButtonsDown(&pad);

        WebCommonConfig config;
        WebCommonReply reply;
        WebExitReason exitReason = 0;

        rc = webOfflineCreate(&config, WebDocumentKind_OfflineHtmlPage, 0, ".htdocs/dino_run/index.html");
        printf("webOfflineCreate() result: 0x%x\n", rc);

        if (R_SUCCEEDED(rc))
        {
            rc = webConfigSetFooterFixedKind(&config, WebFooterFixedKind_Hidden);
            printf("webConfigSetFooterFixedKind() result: 0x%x\n", rc);

            if (R_SUCCEEDED(rc))
            { // Launch the applet and wait for it to exit.
                rc = webConfigShow(&config, &reply);
                printf("webConfigShow(): 0x%x\n", rc);
                if (rc == 0x5d59)
                { // Warn the user when it appear they havent overridden a title to run the game
                    printf(CONSOLE_RED "!!! There was an issue showing the browser window. Make sure you're running the game through an overridden title and not the album. Hold KEY_PLUS to exit.\n" CONSOLE_WHITE);
                }

                rc = webReplyGetExitReason(&reply, &exitReason);
                printf("webReplyGetExitReason(): 0x%x", rc);
                if (R_SUCCEEDED(rc))
                    printf(", 0x%x", exitReason);
                printf("\n");
                consoleUpdate(NULL);
                svcSleepThread(1000000000ull);
                break;
                // continue;
            }
        }

        if (kDown & HidNpadButton_Plus)
            break;

        // Update the console, sending a new frame to the display
        consoleUpdate(NULL);
    }

    // Deinitialize and clean up resources used by the console (important!)
    consoleExit(NULL);
    return 0;
}
