/* ***********************************************************************
   * Project:
   * File: TrioPC_Linux_Test.c
   * Author: smartin
   ***********************************************************************

    Modifications
    0.00 4/12/2011 created
*/

/*---------------------------------------------------------------------
  -- macros
  ---------------------------------------------------------------------*/

/*---------------------------------------------------------------------
  -- standard includes
  ---------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

/*---------------------------------------------------------------------
  -- project includes (imports)
  ---------------------------------------------------------------------*/
#include "TrioPC_Linux.h"

/*---------------------------------------------------------------------
  -- project includes (exports)
  ---------------------------------------------------------------------*/

/*---------------------------------------------------------------------
  -- data types
  ---------------------------------------------------------------------*/

/*---------------------------------------------------------------------
  -- function prototypes
  ---------------------------------------------------------------------*/

/*---------------------------------------------------------------------
  -- global variables
  ---------------------------------------------------------------------*/

/*---------------------------------------------------------------------
  -- local variables
  ---------------------------------------------------------------------*/

/*---------------------------------------------------------------------
  -- implementation
  ---------------------------------------------------------------------*/

static unsigned int fire_event(fireEventClass_t fireEventClass, const int event, const long integerData, const char *message)
{
    switch (event)
    {
    case EVENT_WRITE_FAIL:
    case EVENT_READ_FAIL:
        break;
    case EVENT_MESSAGE:
        if (message)
            fprintf(stderr, "%s\n", (const char *)message);
        break;
    case EVENT_RECEIVE:
    case EVENT_BUFFER_OVERRUN:
    case EVENT_PROGRESS_CREATE:
        if (message)
            fprintf(stderr, "%s\n", (const char *)message);
        break;
    case EVENT_PROGRESS_DESTROY:
        if (message)
            fprintf(stderr, "%s\n", (const char *)message);
        fprintf(stderr, "\n");
        break;
    case EVENT_PROGRESS_SET_POS:
        if (message)
            fprintf(stderr, "%s", (const char *)message);
        break;
    case EVENT_GET_CONTROLLER_KEY:
        break;
    }
    return 1;
}

static int test_table(int points)
{
    double f[points];
    int i, rc = -1;

    for (i = 0; i < points; i++)
    {
        f[i] = points - i;
    }

    if (RemoteSetTable(0, points, f))
    {
        double g[points];
        printf("SetTable works!\n");
        if (RemoteGetTable(0, points, g))
        {
            printf("GetTable works!\n");
            if (!memcmp(f, g, sizeof(f)))
            {
                printf("GetTable/SetTable data checks!\n");
                rc = 0;
            }
        }
    }

    return rc;
}

static int test_vr()
{
    double f;
    int rc = -1;

    f = 9;
    if (RemoteSetVr(0, f))
    {
        double g = 0;
        printf("GetVr works!\n");
        if (RemoteGetVr(0, &g))
        {
            printf("SetVr works!\n");
            if (g == f)
            {
                printf("GetVr/SetVr data checks!\n");
                rc = 0;
            }
        }
    }

    return rc;
}

static int test_mpos()
{
    double f;
    int rc = -1;

    f = 9;
    if (RemoteGetVariable("MPOS", &f))
    {
        printf("GetMPOS works (%f)!\n", f);
        rc = 0;
    }

    return rc;
}

static int remote_test(const char *interface, const char *parameter)
{
    int rc = -1;

    // open remote
    int remote_open = 0;
    if (!strcasecmp(interface, "tcp"))
    {
        remote_open = RemoteOpenTCP(NULL, fire_event, parameter);
    }
    else if (!strcasecmp(interface, "pci"))
    {
        remote_open = RemoteOpenPCI(NULL, fire_event, atoi(parameter));
    }

    // if remote opened
    if (remote_open)
    {
        rc = test_table(100);
        if (!rc)
            rc = test_vr();
        if (!rc)
            rc = test_mpos();

        RemoteClose();
    }

    return rc;
}

static void load_firmware(const char *interface, const char *parameter, const char *firmware)
{
    // open Mpe
    int mpe_open = 0;
    if (!strcasecmp(interface, "tcp"))
    {
        mpe_open = MpeOpenTCP(NULL, fire_event, parameter);
    }
    else if (!strcasecmp(interface, "pci"))
    {
        mpe_open = MpeOpenPCI(NULL, fire_event, atoi(parameter));
    }

    // if Mpe opened
    if (mpe_open)
    {
        MpeLoadFirmware(firmware);
        MpeClose();
    }
}

int main (int argc, char *argv[])
{
    int rc = 0;

    // sanity check
    if ((argc < 3) || (argc > 4))
    {
        fprintf(stderr, "%s <interface> <parameter> [<firmware>]\n"
                "<interface> = tcp | pci\n"
                "<interface>=tcp -> <parameter>=ip\n"
                "<interface>=pci -> <parameter>=card number\n"
                "<firmare>=COFF .OUT file\n"
                , argv[0]);
        exit(1);
    }

    // load firmware
    if (argc == 4)
        load_firmware(argv[1], argv[2], argv[3]);
    else
        rc = remote_test(argv[1], argv[2]);

    return rc;
}

