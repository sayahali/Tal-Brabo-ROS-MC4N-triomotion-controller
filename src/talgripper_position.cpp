#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "TrioPC_Linux.h"
#include <iostream>
#include <string>
#include <unistd.h>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>
using namespace std;
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
static int get_pos1()
{   double f;
    int rc = -1;
  if (RemoteExecuteCommand("BASE(5)"))
{
RemoteGetVariable("MPOS",&f);
        printf("la pos du part 1 de la pince c'est (%f)!\n",f);
	rc=0;}
	return rc;}
static int get_pos2()
{   double g;
    int rc = -1;

  if (RemoteExecuteCommand("BASE(6)"))
{
RemoteGetVariable("MPOS",&g);
        printf("la pos du part 2 de la pince c'est (%f)!\n",g);
	rc=0;}
	return rc;}


static int remote_test(const char *interface, const char *parameter)
{
    int rc = -1;

    // open remote
    int remote_open = 0;
  interface="tcp";
  parameter="192.168.0.250";

    remote_open = RemoteOpenTCP(NULL, fire_event, parameter);


    // if remote opened
    if (remote_open)
    {   rc = test_table(1000);
        if (!rc)
        rc = get_pos1();
     	rc = get_pos2();


        RemoteClose();
    }
    return rc;
}
int main (int argc, char *argv[])
{
ros::init(argc, argv, "position");
ros::NodeHandle n;
    int rc = 0;
        rc = remote_test(argv[1], argv[2]);
    return rc;
ros::spin();
}










