#include "../interpreter.h"

//#define _WIN32_WINNT 0x0500
#include <windows.h>

#include "keyb.c"

/* Equivalent des #define NAME VALUE */
static int S_SW_FORCEMINIMIZE = SW_FORCEMINIMIZE ;
static int S_SW_HIDE = SW_HIDE ;
static int S_SW_MAXIMIZE = SW_MAXIMIZE ;
static int S_SW_MINIMIZE = SW_MINIMIZE ;
static int S_SW_RESTORE = SW_RESTORE ;
static int S_SW_SHOW = SW_SHOW ;
static int S_SW_SHOWDEFAULT = SW_SHOWDEFAULT ;
static int S_SW_SHOWMAXIMIZED = SW_SHOWMAXIMIZED ;
static int S_SW_SHOWMINIMIZED = SW_SHOWMINIMIZED ;
static int S_SW_SHOWMINNOACTIVE = SW_SHOWMINNOACTIVE ;
static int S_SW_SHOWNA = SW_SHOWNA ;
static int S_SW_SHOWNOACTIVATE = SW_SHOWNOACTIVATE ;
static int S_SW_SHOWNORMAL = SW_SHOWNORMAL ;

static int S_HWND_BOTTOM = 1 ;
static int S_HWND_NOTOPMOST = -2 ;
static int S_HWND_TOP = 0 ;
static int S_HWND_TOPMOST = -1 ;
static int S_SWP_ASYNCWINDOWPOS = SWP_ASYNCWINDOWPOS ;
static int S_SWP_DEFERERASE = SWP_DEFERERASE ;
static int S_SWP_DRAWFRAME = SWP_DRAWFRAME ;
static int S_SWP_FRAMECHANGED = SWP_FRAMECHANGED ;
static int S_SWP_HIDEWINDOW = SWP_HIDEWINDOW ;
static int S_SWP_NOACTIVATE = SWP_NOACTIVATE ;
static int S_SWP_NOCOPYBITS = SWP_NOCOPYBITS ;
static int S_SWP_NOMOVE = SWP_NOMOVE ;
static int S_SWP_NOOWNERZORDER = SWP_NOOWNERZORDER ;
static int S_SWP_NOREDRAW = SWP_NOREDRAW ;
static int S_SWP_NOREPOSITION = SWP_NOREPOSITION ;
static int S_SWP_NOSENDCHANGING = SWP_NOSENDCHANGING ;
static int S_SWP_NOSIZE = SWP_NOSIZE ;
static int S_SWP_NOZORDER = SWP_NOZORDER ;
static int S_SWP_SHOWWINDOW = SWP_SHOWWINDOW ;

static int S_WM_COMMAND = WM_COMMAND ;
static int S_WM_SYSCOMMAND = WM_SYSCOMMAND ;
static int S_SC_MAXIMIZE = SC_MAXIMIZE ;
static int S_SC_MINIMIZE = SC_MINIMIZE ;
static int S_SC_CLOSE = SC_CLOSE ;

/* handy structure definitions */
/*typedef struct hwnd { HWND * ptr ; } HWNDStruct ;*/
int matchpattern( const char * pattern, const char * st) ;

/* define definition */
const char WinDefs[] = "\
typedef struct __HWNDStruct HWND ;\n\
typedef char * LPCTSTR ;\n\
typedef int BOOL ;\n\
typedef unsigned int UINT ;\n\
typedef unsigned int WPARAM ;\n\
typedef long LPARAM ;\n\
typedef long LRESULT ;\n\
";

void WinMsgBox(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	MessageBox( NULL, Param[1]->Val->Pointer, Param[0]->Val->Pointer, MB_OK ) ;
}
void WinGetForegroundWindow(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Pointer = GetForegroundWindow() ;
}
void WinGetWindowText(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	GetWindowText( Param[0]->Val->Pointer, Param[1]->Val->Pointer, Param[2]->Val->Integer ) ; 
}
void WinShowWindow(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = ShowWindow( Param[0]->Val->Pointer, Param[1]->Val->Integer ) ;
}
void WinFindWindow(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Pointer = FindWindow( Param[0]->Val->Pointer, Param[1]->Val->Pointer ) ;
}
void WindowActive( HWND hwnd ) {
	if ( hwnd!=0 ) {
		if( IsIconic( hwnd ) ) ShowWindow( hwnd, SW_RESTORE ) ;
		else ShowWindow(hwnd, SW_SHOW);
		SetForegroundWindow( hwnd ) ;
		SetActiveWindow( hwnd ) ;
		SetCapture( hwnd ) ;
		}	
	}
void WinActiveWindow(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	WindowActive( Param[0]->Val->Pointer ) ;
}

BOOL CALLBACK EnumWndProcActive( HWND hwnd, LPARAM pPattern ) {
	char title[1024] ;
	if( hwnd != 0 ) if( IsWindow( hwnd ) ) {
		if( GetWindowText( hwnd, title, 1024 ) ) {
			if( strlen( title ) > 0 ) 
			if( matchpattern( (char*)pPattern, title ) ) {
				if( IsIconic( hwnd ) ) ShowWindow( hwnd, SW_RESTORE ) ;
				else ShowWindow(hwnd, SW_SHOW);
				SetActiveWindow( hwnd );
				SetForegroundWindow ( hwnd );
				return FALSE ;
				}
			}
		}
	return TRUE ;
	}
int WindowActivePattern(LPCTSTR Name) {
	EnumWindows(EnumWndProcActive,(LPARAM)Name) ;
	return 0 ;
	}
void WinActiveWindowWithPattern(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = WindowActivePattern( Param[0]->Val->Pointer ) ;
}
void WinCloseWindow(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	SendMessage( Param[0]->Val->Pointer, WM_SYSCOMMAND, SC_CLOSE, (LPARAM)NULL );
	}
	
void WinBringWindowToTop(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = BringWindowToTop( Param[0]->Val->Pointer ) ;
}

void WinSetWindowPos(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	HWND hWndInsertAfter ;
	switch((int)Param[1]->Val->Pointer) {
		case 1: hWndInsertAfter = HWND_BOTTOM ; break ;
		case -2: hWndInsertAfter = HWND_NOTOPMOST ; break ;
		case 0: hWndInsertAfter = HWND_TOP ; break ;
		case -1: hWndInsertAfter = HWND_TOPMOST ; break ;
		default: hWndInsertAfter = Param[1]->Val->Pointer ; break ;
	}
	ReturnValue->Val->Integer = SetWindowPos( Param[0]->Val->Pointer, hWndInsertAfter, Param[2]->Val->Integer, Param[3]->Val->Integer, Param[4]->Val->Integer, Param[5]->Val->Integer, Param[6]->Val->Integer ) ;
}
void WinSendMessage(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = SendMessage( Param[0]->Val->Pointer, Param[1]->Val->Integer, Param[2]->Val->Integer, Param[3]->Val->Integer ) ;
}
void WinSleep(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	Sleep( Param[0]->Val->Integer ) ;
}

void WinWindowMaximize(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs)  {
	SendMessage( Param[0]->Val->Pointer, WM_SYSCOMMAND, SC_MAXIMIZE, (LPARAM)NULL );
}
void WinWindowMinimize(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	SendMessage( Param[0]->Val->Pointer, WM_SYSCOMMAND, SC_MINIMIZE, (LPARAM)NULL );
}

BOOL CALLBACK EnumWndProcMinimizeAll(HWND hFen,LPARAM pLstWnd) {
	if( IsWindowVisible( hFen ) )
	if( !IsIconic( hFen ) )
		SendMessage( hFen, WM_SYSCOMMAND, SC_MINIMIZE, (LPARAM)NULL );	
	return TRUE;
	}
void WinMinimizeAllWindows(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	EnumWindows(EnumWndProcMinimizeAll,(LPARAM)NULL) ;
}
BOOL CALLBACK EnumWndProcMaximizeAll(HWND hFen,LPARAM pLstWnd) {
	if( IsWindowVisible( hFen ) && IsWindow( hFen ) )
		ShowWindow( hFen, SW_RESTORE );
	return TRUE;
	}
void WinMaximizeAllWindows(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	EnumWindows(EnumWndProcMaximizeAll,(LPARAM)NULL) ;
}

void WinSendKeyboard(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	RunKeyboard( Param[0]->Val->Pointer ) ;
}

void WinSetCursorPos(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = SetCursorPos( Param[0]->Val->Integer, Param[1]->Val->Integer ) ;
}
void WinMouseLeftClick(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
}
void WinMouseRightClick(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	mouse_event(MOUSEEVENTF_RIGHTDOWN, 0, 0, 0, 0);
	mouse_event(MOUSEEVENTF_RIGHTUP, 0, 0, 0, 0);
}

void WinMouseDoubleClick(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
	mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
	ShowCursor( TRUE ) ;
}
void WinShowCursor(struct ParseState *Parser, struct Value *ReturnValue, struct Value **Param, int NumArgs) {
	ReturnValue->Val->Integer = ShowCursor( Param[0]->Val->Integer ) ;
}

/* all various.h functions */
struct LibraryFunction WinFunctions[] =
{
	{ WinMsgBox,			"void MsgBox( LPCTSTR title, LPCTSTR msg ) ;" },
	{ WinGetForegroundWindow,	"HWND GetForegroundWindow( void ) ;" },
	{ WinGetWindowText,		"void GetWindowText( HWND hWnd, LPCTSTR lpString, int nMaxCount ) ;" },
	{ WinShowWindow,		"BOOL ShowWindow( HWND hWnd, int nCmdShow ) ; " },
	{ WinFindWindow,		"HWND FindWindow( LPCTSTR lpClassName, LPCTSTR lpWindowName ) ;" },
	{ WinActiveWindow,		"void ActiveWindow( HWND hwnd ) ;" },
	{ WinActiveWindowWithPattern,	"int ActiveWindowWithPattern( LPCTSTR lpWindowName ) ;" },
	{ WinCloseWindow,		"void CloseWindow( HWND hwnd ) ;" },
	{ WinBringWindowToTop,		"BOOL BringWindowToTop( HWND hwnd ) ;" },
	{ WinSetWindowPos,		"BOOL SetWindowPos( HWND hWnd, void* hWndInsertAfter, int X, int Y, int cx, int cy, UINT uFlags ) ;" },
	{ WinSendMessage,		"LRESULT SendMessage( HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam ) ;" },
	{ WinSleep,			"void Sleep( long time ) ;" },
	{ WinWindowMaximize,		"void MaximizeWindow( HWND hwnd ) ;" },
	{ WinWindowMinimize,		"void MinimizeWindow( HWND hwnd ) ;" },
	{ WinMaximizeAllWindows,	"void MaximizeAllWindows( void ) ;" },
	{ WinMinimizeAllWindows,	"void MinimizeAllWindows( void ) ;" },
	{ WinSendKeyboard,		"void SendKeyboard( char * keys ) ;" },
	{ WinSetCursorPos,		"BOOL SetCursorPos( int X, int Y ) ;" },
	{ WinMouseLeftClick,		"void MouseLeftClick( void ) ;" },
	{ WinMouseRightClick,		"void MouseRightClick( void ) ;" },
	{ WinMouseDoubleClick,		"void MouseDoubleClick( void ) ;" },
	{ WinShowCursor,		"int ShowCursor( BOOL bShow ) ;" },
	{ NULL,			NULL }
};

/* creates various system-dependent definitions */
void WinSetupFunc(Picoc *pc)
{
	/* define definitions */
	TypeCreateOpaqueStruct(pc, NULL, TableStrRegister(pc, "__HWNDStruct"), sizeof(HWND));
	
	/* define definitions */
	VariableDefinePlatformVar(pc, NULL, "SW_FORCEMINIMIZE", &pc->IntType, (union AnyValue *)&S_SW_FORCEMINIMIZE, FALSE);
	VariableDefinePlatformVar(pc, NULL, "SW_HIDE", &pc->IntType, (union AnyValue *)&S_SW_HIDE, FALSE);
	VariableDefinePlatformVar(pc, NULL, "SW_MAXIMIZE", &pc->IntType, (union AnyValue *)&S_SW_MAXIMIZE, FALSE);
	VariableDefinePlatformVar(pc, NULL, "SW_MINIMIZE", &pc->IntType, (union AnyValue *)&S_SW_MINIMIZE, FALSE);
	VariableDefinePlatformVar(pc, NULL, "SW_RESTORE", &pc->IntType, (union AnyValue *)&S_SW_RESTORE, FALSE);
	VariableDefinePlatformVar(pc, NULL, "SW_SHOW", &pc->IntType, (union AnyValue *)&S_SW_SHOW, FALSE);
	VariableDefinePlatformVar(pc, NULL, "SW_SHOWDEFAULT", &pc->IntType, (union AnyValue *)&S_SW_SHOWDEFAULT, FALSE);
	VariableDefinePlatformVar(pc, NULL, "SW_SHOWMAXIMIZED", &pc->IntType, (union AnyValue *)&S_SW_SHOWMAXIMIZED, FALSE);
	VariableDefinePlatformVar(pc, NULL, "SW_SHOWMINIMIZED", &pc->IntType, (union AnyValue *)&S_SW_SHOWMINIMIZED, FALSE);
	VariableDefinePlatformVar(pc, NULL, "SW_SHOWMINNOACTIVE", &pc->IntType, (union AnyValue *)&S_SW_SHOWMINNOACTIVE, FALSE);
	VariableDefinePlatformVar(pc, NULL, "SW_SHOWNA", &pc->IntType, (union AnyValue *)&S_SW_SHOWNA, FALSE);
	VariableDefinePlatformVar(pc, NULL, "SW_SHOWNOACTIVATE", &pc->IntType, (union AnyValue *)&S_SW_SHOWNOACTIVATE, FALSE);
	VariableDefinePlatformVar(pc, NULL, "SW_SHOWNORMAL", &pc->IntType, (union AnyValue *)&S_SW_SHOWNORMAL, FALSE);
	
	VariableDefinePlatformVar(pc, NULL, "HWND_BOTTOM", &pc->IntType, (union AnyValue *)&S_HWND_BOTTOM, FALSE);
	VariableDefinePlatformVar(pc, NULL, "HWND_NOTOPMOST", &pc->IntType, (union AnyValue *)&S_HWND_NOTOPMOST, FALSE);
	VariableDefinePlatformVar(pc, NULL, "HWND_TOP", &pc->IntType, (union AnyValue *)&S_HWND_TOP, FALSE);
	VariableDefinePlatformVar(pc, NULL, "HWND_TOPMOST", &pc->IntType, (union AnyValue *)&S_HWND_TOPMOST, FALSE);
	VariableDefinePlatformVar(pc, NULL, "SWP_ASYNCWINDOWPOS", &pc->IntType, (union AnyValue *)&S_SWP_ASYNCWINDOWPOS, FALSE);
	VariableDefinePlatformVar(pc, NULL, "SWP_DEFERERASE", &pc->IntType, (union AnyValue *)&S_SWP_DEFERERASE, FALSE);
	VariableDefinePlatformVar(pc, NULL, "SWP_DRAWFRAME", &pc->IntType, (union AnyValue *)&S_SWP_DRAWFRAME, FALSE);
	VariableDefinePlatformVar(pc, NULL, "SWP_FRAMECHANGED", &pc->IntType, (union AnyValue *)&S_SWP_FRAMECHANGED, FALSE);
	VariableDefinePlatformVar(pc, NULL, "SWP_HIDEWINDOW", &pc->IntType, (union AnyValue *)&S_SWP_HIDEWINDOW, FALSE);
	VariableDefinePlatformVar(pc, NULL, "SWP_NOACTIVATE", &pc->IntType, (union AnyValue *)&S_SWP_NOACTIVATE, FALSE);
	VariableDefinePlatformVar(pc, NULL, "SWP_NOCOPYBITS", &pc->IntType, (union AnyValue *)&S_SWP_NOCOPYBITS, FALSE);
	VariableDefinePlatformVar(pc, NULL, "SWP_NOMOVE", &pc->IntType, (union AnyValue *)&S_SWP_NOMOVE, FALSE);
	VariableDefinePlatformVar(pc, NULL, "SWP_NOOWNERZORDER", &pc->IntType, (union AnyValue *)&S_SWP_NOOWNERZORDER, FALSE);
	VariableDefinePlatformVar(pc, NULL, "SWP_NOREDRAW", &pc->IntType, (union AnyValue *)&S_SWP_NOREDRAW, FALSE);
	VariableDefinePlatformVar(pc, NULL, "SWP_NOREPOSITION", &pc->IntType, (union AnyValue *)&S_SWP_NOREPOSITION, FALSE);
	VariableDefinePlatformVar(pc, NULL, "SWP_NOSENDCHANGING", &pc->IntType, (union AnyValue *)&S_SWP_NOSENDCHANGING, FALSE);
	VariableDefinePlatformVar(pc, NULL, "SWP_NOSIZE", &pc->IntType, (union AnyValue *)&S_SWP_NOSIZE, FALSE);
	VariableDefinePlatformVar(pc, NULL, "SWP_NOZORDER", &pc->IntType, (union AnyValue *)&S_SWP_NOZORDER, FALSE);
	VariableDefinePlatformVar(pc, NULL, "SWP_SHOWWINDOW", &pc->IntType, (union AnyValue *)&S_SWP_SHOWWINDOW, FALSE);
	
	VariableDefinePlatformVar(pc, NULL, "S_WM_COMMAND", &pc->IntType, (union AnyValue *)&S_WM_COMMAND, FALSE);
	VariableDefinePlatformVar(pc, NULL, "S_WM_SYSCOMMAND", &pc->IntType, (union AnyValue *)&S_WM_SYSCOMMAND, FALSE);
	VariableDefinePlatformVar(pc, NULL, "S_SC_MAXIMIZE", &pc->IntType, (union AnyValue *)&S_SC_MAXIMIZE, FALSE);
	VariableDefinePlatformVar(pc, NULL, "S_SC_MINIMIZE", &pc->IntType, (union AnyValue *)&S_SC_MINIMIZE, FALSE);
	VariableDefinePlatformVar(pc, NULL, "S_SC_CLOSE", &pc->IntType, (union AnyValue *)&S_SC_CLOSE, FALSE);
}


/*
HWND hwnd; hwnd=GetForegroundWindow() ;
ActiveWindowWithPattern( "*Bloc*" ); hwnd=GetForegroundWindow() ; SendKeyboard("Ceci est un test !!!" ); 
SetWindowPos(hwnd,HWND_TOP,10,10,0,0,SWP_NOSIZE|SWP_NOZORDER);
char buffer[1024];
GetWindowText(hwnd, buffer, 1024 );
GetWindowText(hwnd, buffer, 1024 );
printf("%s\n",buffer);
hwnd=FindWindow(NULL,"Sans titre - Bloc-notes");
WindowMaximize(hwnd);
WindowMinimize(hwnd);
*/
