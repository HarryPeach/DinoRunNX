// Include the most common headers from the C standard library
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

// Include the main libnx system header, for Switch development
#include <switch.h>

#include "exits.h"
#include "log.h"

// Main program entrypoint
int main(int argc, char *argv[])
{
    consoleInit(NULL);

    printf(CONSOLE_GREEN "Chromium Dino Run\n" CONSOLE_WHITE);
    printf("Ported by Harry Peach\n");
    printf("\nLicensed under the BSD3 license, found in the LICENSE file.\n\n");
    consoleUpdate(NULL);

    // Check if the applet is being run from the album
    if (appletGetAppletType() != AppletType_Application)
    {
        log_err(CONSOLE_RED "The applet cannot run if launched from the album menu, please launch by overriding a title!\n" CONSOLE_WHITE);
        return exit_error();
    }

    printf("\nDebug output:\n");
    consoleUpdate(NULL);

    log_dbg("Attempting to create an offline web session... ");
    WebCommonConfig config;
    Result res_create_web = webOfflineCreate(&config, WebDocumentKind_OfflineHtmlPage, 0, ".htdocs/dino_run/index.html");
    log_dbg("result: 0x%x\n", res_create_web);
    if (R_FAILED(res_create_web))
    {
        log_err("webOfflineCreate failed with code: 0x%x\n", res_create_web);
        return exit_error();
    }

    log_dbg("Setting footer to fixed kind...\n");
    webConfigSetFooterFixedKind(&config, WebFooterFixedKind_Hidden);
    log_dbg("Setting web audio...\n");
    webConfigSetWebAudio(&config, true);
    log_dbg("Setting touch enabled...\n");
    webConfigSetTouchEnabledOnContents(&config, true);

    log_dbg("Attempted to show web session...");
    WebCommonReply reply;
    Result res_config_show = webConfigShow(&config, &reply);
    log_dbg("result: 0x%x\n", res_config_show);
    if (R_FAILED(res_config_show))
    {
        log_err("webConfigShow failed with code: 0x%x\n", res_config_show);
        return exit_error();
    }

    return exit_graceful();
}
