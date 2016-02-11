#define Thread(function) CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)function, NULL, NULL, NULL)
#define OFFSET_GFX_ENDFRAME 0x004C5A40
#define	CG_OBITUARY 0x004D9ED0

extern  void		(*orig_CG_Obituary)			( );
void                HooK_CG_Obituary            ( );

extern DWORD			GFX_MODULE_Base;
extern cMenuManager		m;