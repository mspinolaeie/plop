//---------------------------------------------------------------------------
#ifndef PlopExecH
#define PlopExecH
//---------------------------------------------------------------------------
#include <Classes.hpp>
//---------------------------------------------------------------------------

#include "global.h"

void run_plate (void);
void init_default_basis (void);

void plate_init ();

//---------------------------------------------------------------------------

class PlopExec : public TThread
{
private:
	int StatusPos;
protected:
	void __fastcall Execute();
public:
	__fastcall PlopExec(bool CreateSuspended);
	void __fastcall UpdateOptStatusSync(void);
    void __fastcall UpdateOptStatus(void);
    void __fastcall Finished (TObject *Sender);
    void __fastcall UpdateStatus (int n);
    void __fastcall UpdateStatusSync (void);
    void __fastcall UpdateMonte (void);
    void __fastcall UpdateMonteSync (void);
    void __fastcall UpdatePics (void);
    void __fastcall UpdatePicsSync (void);
    void __fastcall UpdateCellEditOptVars (void);
    void __fastcall UpdateCellEditOptVarsSync (void);

};
//---------------------------------------------------------------------------

typedef int plop_terminate;

#endif
