/* ***********************************************************************
   * Project:
   * File: TrioPC_Linux.h
   * Author: smartin
   ***********************************************************************

    Modifications
    0.00 4/11/2011 created
*/

#ifdef __cplusplus
extern "C" {
#endif

/*---------------------------------------------------------------------
  -- macros
  ---------------------------------------------------------------------*/
#define EVENT_WRITE_FAIL                    0
#define EVENT_READ_FAIL                     1
#define EVENT_MESSAGE                       2
#define EVENT_RECEIVE                       3
#define EVENT_BUFFER_OVERRUN                4
#define EVENT_PROGRESS_CREATE               5
#define EVENT_PROGRESS_DESTROY              6
#define EVENT_PROGRESS_SET_POS              7
#define EVENT_GET_CONTROLLER_KEY            8

/*---------------------------------------------------------------------
  -- standard includes
  ---------------------------------------------------------------------*/

/*---------------------------------------------------------------------
  -- project includes (imports)
  ---------------------------------------------------------------------*/

/*---------------------------------------------------------------------
  -- project includes (exports)
  ---------------------------------------------------------------------*/

/*---------------------------------------------------------------------
  -- data types
  ---------------------------------------------------------------------*/
typedef void * fireEventClass_t;
typedef unsigned int (*fireEventFunction_t)(fireEventClass_t fireEventClass, const int event, const long integerData, const char * message);

/*---------------------------------------------------------------------
  -- function prototypes
  ---------------------------------------------------------------------*/

/*---------------------------------------------------------------------
  -- REMOTE
  ---------------------------------------------------------------------*/
// constructors
unsigned int RemoteOpenTCP(fireEventClass_t fire_event_class, fireEventFunction_t fire_event, const char *address);
unsigned int RemoteOpenPCI(fireEventClass_t fireEventClass, fireEventFunction_t fireEvent, int card);
void RemoteClose();

//-- methods
unsigned int RemoteSetControllerVersion(double controller_version);
unsigned int RemoteSetControllerType(int controller_type);
unsigned int RemoteGetTable(long start_position, long elements, double *values);
unsigned int RemoteGetSelected(const char * selected_program);
unsigned int RemoteInsertLine(const char * program,short line_number, const char * line);
unsigned int RemoteSelect(const char * program);
unsigned int RemoteDir(const char * dir);
unsigned int RemoteNew(const char * program);
unsigned int RemoteSetTable(long start_position, long elements, double values[]);
unsigned int RemoteGetNamedVariable(int variable,int process, double *return_value);
unsigned int RemoteExecuteCommand(const char * command);
unsigned int RemoteLinputCommand(short channel, short start_vr);
unsigned int RemoteKeyCommand(short channel, short *Value);
unsigned int RemoteInputCommand(short channel,double *Value);
unsigned int RemoteGetCommand(short channel,short *value);
unsigned int RemoteProcessCommand(const char * command,const char * program, double process, double *return_value); // run a process command
unsigned int RemoteCommand(const char * command);
unsigned int RemoteMotionCommand(const char * command,int Elements, double Array[], int Base, double *return_value); // run a motion command
unsigned int RemoteArrayCommand(const char * command,int Elements, double Array[], double *return_value); // run a standard command
unsigned int RemoteGetVariable(const char * Variable, double *Value);    // get the variable value
unsigned int RemoteSetVariable(const char * Variable,double Value);                     // set the variable to value
unsigned int RemoteGetVr(int nVr, double *Value);    // get the variable value
unsigned int RemoteSetVr(int nVr, double Value);    // set the variable value
unsigned int RemoteGetTokenTable(void);                                           // get the token table
unsigned int RemoteMarkCommand(short Axis, short *Value, short MarkNumber);
unsigned int RemoteScope5(unsigned int On, long SamplePeriod, long TableStart, long TableEnd, const char * ParamList[]);
unsigned int RemoteScope1(unsigned int On);
unsigned int RemoteTrigger();
unsigned int RemoteMechatroLink(short Module, short Function, short NumberOfParameters, const double MLParameters[], double *Result);
unsigned int RemoteGetAxisVariable(const char * Variable, short Axis, double *Value);    // get the variable value with the AXIS modifier
unsigned int RemoteSetAxisVariable(const char * Variable, short Axis, double Value);      // set the variable to value with the AXIS modifier
unsigned int RemoteGetProcessVariable(const char * Variable, short Process, double *Value);    // get the variable value with the AXIS modifier
unsigned int RemoteSetProcessVariable(const char * Variable, short Process, double Value);      // set the variable to value with the AXIS modifier
unsigned int RemoteGetSlotVariable(const char * Variable, short Slot, double *Value);    // get the variable value with the AXIS modifier
unsigned int RemoteSetSlotVariable(const char * Variable, short Slot, double Value);      // set the variable to value with the AXIS modifier
unsigned int RemoteGetPortVariable(const char * Variable, short Port, double *Value);    // get the variable value with the AXIS modifier
unsigned int RemoteSetPortVariable(const char * Variable, short Port, double Value);      // set the variable to value with the AXIS modifier
unsigned int RemoteStepRatio(int Numerator, int Denominator, long Axis);      // set the variable to value with the AXIS modifier

/*---------------------------------------------------------------------
  -- MPE
  ---------------------------------------------------------------------*/
unsigned int MpeOpenTCP(fireEventClass_t fire_event_class, fireEventFunction_t fire_event, const char *address);
unsigned int MpeOpenPCI(fireEventClass_t fireEventClass, fireEventFunction_t fireEvent, int card);
void MpeClose();

unsigned int MpeLoadFirmware(const char *filename);

/*---------------------------------------------------------------------
  -- global variables
  ---------------------------------------------------------------------*/

/*---------------------------------------------------------------------
  -- local variables
  ---------------------------------------------------------------------*/

/*---------------------------------------------------------------------
  -- implementation
  ---------------------------------------------------------------------*/

#ifdef __cplusplus
}
#endif
