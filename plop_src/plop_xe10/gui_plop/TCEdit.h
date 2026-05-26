//---------------------------------------------------------------------------
#ifndef TCEditH
#define TCEditH

class TCEdit:public TEdit
{
public:
        int *IdPtr;
        __fastcall TCEdit (TComponent *AOwner);
        void __fastcall Entered (TObject *Sender);
        void __fastcall Exited (TObject *Sender);
};

//---------------------------------------------------------------------------
#endif
