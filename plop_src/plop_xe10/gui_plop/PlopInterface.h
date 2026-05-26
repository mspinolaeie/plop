//---------------------------------------------------------------------------
#ifndef PlopInterfaceH
#define PlopInterfaceH
#include "NumEdit.h"
//---------------------------------------------------------------------------


/* Map the gui_plop data into the plop parm_name data and vice versa.
 * The map can handle either a single NumEdit, or a vector of NumEditStates
 * because if there is more than one element in the data set, it uses a
 * NumEditState array to maintain the actual values. NumEditStates are also
 * handy for initializing from Plop. Similarly, only scalars
 * can have a RadioGroup associated with them. This is used for cases in which
 * several Plop keywords can be used in a single NumEdit box.
 */

typedef struct {
    NumEdit *MyNumEdit;
    NumEditState *MyNumEditState;
    TEdit *MyEdit;
    int RadioIndex;
    TRadioGroup *MyRadioGroup;
    } PlopDataMap;

#endif


    