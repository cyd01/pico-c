#define MAXCORRESP 300

int pos( const char * , const char * ) ;
int del( char * , const int , const int ) ;

struct tabcorresp {
	unsigned int valint ;
	char valchar[11] ;
	} ;
/*	
struct tabcorresp TabCorresp[MAXCORRESP] = {
  0x10,"SHIFT", 0xa0,"SHIFT", 0xa1,"SHIFT",
  0x03,"CANCEL", 0x08,"BACKSPACE", 0x09,"TAB", 0x0c,"CLEAR", 0x0d,"RETURN",
  0x11,"CTRL", 0xa2,"CTRL", 0xa3,"CTRL",
  0x12,"ALT", 0xa4,"ALT", 0xa5,"ALTGR",
  0x13,"PAUSE", 0x14,"CAPS", 0x1b,"ESC", 0x20,"SPACE", 
  0x21,"PRIOR", 0x22,"NEXT", 0x23,"END", 0x24,"HOME", 0x25,"LEFT", 0x26,"UP", 0x27,"RIGHT", 0x28,"DOWN", // Touche flèches
  0x2a,"PRINT", 0x2d,"INS", 0x2e,"DEL", 0x2f,"HELP",
  0x30,"à", 0x31,"&", 0x32,"é", 0x33,"\"", 0x34,"\'", 0x35,"(", 0x36,"-", 0x37,"è", 0x38,"_", 0x39,"ç", 0xdb,")", 0xbb,"=", // Touches au dessus des lettres
  0x41,"a", 0x42,"b", 0x43,"c", 0x44,"d", 0x45,"e", 0x46,"f", 0x47,"g", 0x48,"h", 0x49,"i", 0x4a,"j",
  0x4b,"k", 0x4c,"l", 0x4d,"m", 0x4e,"n", 0x4f,"o", 0x50,"p", 0x51,"q", 0x52,"r", 0x53,"s", 0x54,"t",
  0x55,"u", 0x56,"v", 0x57,"w", 0x58,"x", 0x59,"y", 0x5a,"z",
  0x5b,"WIN", 0x5c,"WIN", 0x5d,"APPS",
  0x60,"0", 0x61,"1", 0x62,"2", 0x63,"3", 0x64,"4", 0x65,"5", 0x66,"6", 0x67,"7", 0x68,"8", 0x69,"9", 0x6e,".", 0x6b,"+", 0x6a,"*", 0x6f,"/", // Pavé numerique
  0x70,"F1", 0x71,"F2", 0x72,"F3", 0x73,"F4", 0x74,"F5", 0x75,"F6", 0x76,"F7", 0x77,"F8", 0x78,"F9", 0x79,"F10", 0x7a,"F11", 0x7b,"F12", 0x7c,"F13", 0x7d,"F14", 0x7e,"F15", 0x7f,"F16", 0x80,"F17", 0x81,"F18", 0x82,"F19", 0x83,"F20", 0x84,"F21", 0x85,"F22", 0x86,"F23", 0x87,"F24", // Touches de fonction
  0x90,"NUMLOCK", 0x91,"SCROLLLOCK",
  0xba,"$", 0xc0,"ù", 0xdc,"*", 0xbc,",", 0xbe,";", 0xdf,"!", 0xde,"²"
  } ;*/
struct tabcorresp TabCorresp[MAXCORRESP] = {
  {0x10,"SHIFT"}, {0xa0,"SHIFT"}, {0xa1,"SHIFT"},
  {0x03,"CANCEL"}, {0x08,"BACKSPACE"}, {0x09,"TAB"}, {0x0c,"CLEAR"}, {0x0d,"RETURN"},
  {0x11,"CTRL"}, {0xa2,"CTRL"}, {0xa3,"CTRL"},
  {0x12,"ALT"}, {0xa4,"ALT"}, {0xa5,"ALTGR"},
  {0x13,"PAUSE"}, {0x14,"CAPS"}, {0x1b,"ESC"}, {0x20,"SPACE"}, 
  {0x21,"PRIOR"}, {0x22,"NEXT"}, {0x23,"END"}, {0x24,"HOME"}, {0x25,"LEFT"}, {0x26,"UP"}, {0x27,"RIGHT"}, {0x28,"DOWN"}, /* Touche flèches */
  {0x2a,"PRINT"}, {0x2d,"INS"}, {0x2e,"DEL"}, {0x2f,"HELP"},
  {0x30,"à"}, {0x31,"&"}, {0x32,"é"}, {0x33,"\""}, {0x34,"\'"}, {0x35,"("}, {0x36,"-"}, {0x37,"è"}, {0x38,"_"}, {0x39,"ç"}, {0xdb,")"}, {0xbb,"="}, /* Touches au dessus des lettres */
  {0x41,"a"}, {0x42,"b"}, {0x43,"c"}, {0x44,"d"}, {0x45,"e"}, {0x46,"f"}, {0x47,"g"}, {0x48,"h"}, {0x49,"i"}, {0x4a,"j"},
  {0x4b,"k"}, {0x4c,"l"}, {0x4d,"m"}, {0x4e,"n"}, {0x4f,"o"}, {0x50,"p"}, {0x51,"q"}, {0x52,"r"}, {0x53,"s"}, {0x54,"t"},
  {0x55,"u"}, {0x56,"v"}, {0x57,"w"}, {0x58,"x"}, {0x59,"y"}, {0x5a,"z"},
  {0x5b,"WIN"}, {0x5c,"WIN"}, {0x5d,"APPS"},
  {0x60,"0"}, {0x61,"1"}, {0x62,"2"}, {0x63,"3"}, {0x64,"4"}, {0x65,"5"}, {0x66,"6"}, {0x67,"7"}, {0x68,"8"}, {0x69,"9"}, {0x6e,"."}, {0x6b,"+"}, {0x6a,"*"}, {0x6f,"/"}, /* Pavé numerique */
  {0x70,"F1"}, {0x71,"F2"}, {0x72,"F3"}, {0x73,"F4"}, {0x74,"F5"}, {0x75,"F6"}, {0x76,"F7"}, {0x77,"F8"}, {0x78,"F9"}, {0x79,"F10"}, {0x7a,"F11"}, {0x7b,"F12"}, {0x7c,"F13"}, {0x7d,"F14"}, {0x7e,"F15"}, {0x7f,"F16"}, {0x80,"F17"}, {0x81,"F18"}, {0x82,"F19"}, {0x83,"F20"}, {0x84,"F21"}, {0x85,"F22"}, {0x86,"F23"}, {0x87,"F24"}, /* Touches de fonction */
  {0x90,"NUMLOCK"}, {0x91,"SCROLLLOCK"},
  {0xba,"$"}, {0xc0,"ù"}, {0xdc,"*"}, {0xbc,","}, {0xbe,";"}, {0xdf,"!"}, {0xde,"²"}
  } ;

/* Envoi simple de suite de touches 'standard' de clavier */
void __stdcall KeyboardSimule(TCHAR *psz)
{
  INPUT npt;
  npt.ki.dwExtraInfo = npt.ki.time = 0;
  npt.type = INPUT_KEYBOARD;
  npt.ki.wVk = 0;
  while(*psz) {
#ifdef UNICODE
    npt.ki.wScan = (WORD) *psz;
#else
    npt.ki.wScan = (WORD) (BYTE) *psz;
#endif
    npt.ki.dwFlags = KEYEVENTF_UNICODE;
    SendInput(1, &npt, sizeof(INPUT));
    npt.ki.dwFlags =  KEYEVENTF_UNICODE| KEYEVENTF_KEYUP;
    SendInput(1, &npt, sizeof(INPUT));
    psz++;
  }
}

/* Envoi simple de suite de touches 'standard' de clavier avec un beep entre chaque */
void __stdcall KeyboardSimuleBeep(TCHAR *psz)
{
  INPUT npt;
  npt.ki.dwExtraInfo = npt.ki.time = 0;
  npt.type = INPUT_KEYBOARD;
  npt.ki.wVk = 0;
  while(*psz) {
#ifdef UNICODE
    npt.ki.wScan = (WORD) *psz;
#else
    npt.ki.wScan = (WORD) (BYTE) *psz;
#endif
    npt.ki.dwFlags = KEYEVENTF_UNICODE;
    SendInput(1, &npt, sizeof(INPUT));
    npt.ki.dwFlags =  KEYEVENTF_UNICODE| KEYEVENTF_KEYUP;
    SendInput(1, &npt, sizeof(INPUT));
    psz++;
   MessageBeep(0);
   Sleep(40);
  }
}


/* Envoi simple d'une touche 'standard' du clavier */
void __stdcall Keyboard1Simule(const char c) {
	char st[2];
	st[0]=c;st[1]='\0';
	KeyboardSimule((TCHAR*)st);
	}

void GetKeyName( DWORD x, char * buf ) {
	unsigned int i;
	for( i=0 ; i<MAXCORRESP ; i++ ) 
		if( TabCorresp[i].valint == x ) {strcpy(buf,TabCorresp[i].valchar);break;}
	}

/* Récupération du code virtuel d'une touche "normal" du clavier */
int GetVirtualNumber(const int c) {
	int x;
	switch(c) { 
      		/* Lettres */
		case 'a': x = 0x41; break; 
		case 'b': x = 0x42; break; 
		case 'c': x = 0x43; break; 
		case 'd': x = 0x44; break; 
		case 'e': x = 0x45; break; 
		case 'f': x = 0x46; break; 
		case 'g': x = 0x47; break; 
		case 'h': x = 0x48; break; 
		case 'i': x = 0x49; break; 
		case 'j': x = 0x4a; break; 
		case 'k': x = 0x4b; break; 
		case 'l': x = 0x4c; break; 
		case 'm': x = 0x4d; break; 
		case 'n': x = 0x4e; break; 
		case 'o': x = 0x4f; break; 
		case 'p': x = 0x50; break; 
		case 'q': x = 0x51; break; 
		case 'r': x = 0x52; break; 
		case 's': x = 0x53; break; 
		case 't': x = 0x54; break; 
		case 'u': x = 0x55; break; 
		case 'v': x = 0x56; break; 
		case 'w': x = 0x57; break; 
		case 'x': x = 0x58; break; 
		case 'y': x = 0x59; break; 
		case 'z': x = 0x5a; break; 
		/* Chiffres avec le vérouillage numérique */
		case '0': x = 0x60; break; 
		case '1': x = 0x61; break; 
		case '2': x = 0x62; break; 
		case '3': x = 0x63; break; 
		case '4': x = 0x64; break; 
		case '5': x = 0x65; break; 
		case '6': x = 0x66; break;
		case '7': x = 0x67; break; 
		case '8': x = 0x68; break; 
		case '9': x = 0x69; break; 
		case '.': x = 0x6e; break; 
		case '+': x = 0x6b; break;
		case '*': x = 0x6a; break;
		case '/': x = 0x6f; break;
		/* Chiffres au dessus des lettres */
		case 'à': x = 0x30; break; 
		case '&': x = 0x31; break; 
		case 'é': x = 0x32; break; 
		case '"': x = 0x33; break; 
		case '\'': x = 0x34; break; 
		case '(': x = 0x35; break; 
		case '-': x = 0x36; break; 
		case 'è': x = 0x37; break; 
		case '_': x = 0x38; break; 
		case 'ç': x = 0x39; break; 
		/* Chiffres au dessus des lettres */
		case '@': x = 0x30; break; 
		case '~': x = 0x32; break; 
		case '#': x = 0x33; break; 
		case '{': x = 0x34; break; 
		case '[': x = 0x35; break; 
		case '|': x = 0x36; break; 
		case '`': x = 0x37; break; 
		case '\\': x = 0x38; break; 
		case '^': x = 0x39; break; 
		case ']': x = 0xdb; break;
		case '}': x = 0xbb;break;
		case '²': x = 0xde;break;
		/* Divers */
		case '$': x = 0xba;break;
		case '£': x = 0xba;break;
		case '¤': x = 0xba;break;
		case 'µ': x = 0xdc;break;
		case '!': x = 0xdf;break;
		case '§': x = 0xdc;break;
		default: x=c;break; 
		} 
	return x ;
	}

/* Envoi de combinaison de touches de clavier comprenant des Virtual Keys */
void KeyboardMultiVirtualKey(int x, int y, int z, int nbre) { 
	if(nbre == 1) x=GetVirtualNumber(x) ;
	if(nbre == 2) y=GetVirtualNumber(y) ;
	if(nbre == 3) z=GetVirtualNumber(z) ;
	keybd_event(x,0,0,0); 
	if(nbre==2 || nbre ==3) 
		keybd_event(y,0,0,0); 
	if(nbre==3) { 
		keybd_event(z,0,0,0); 
		keybd_event(z,0,KEYEVENTF_KEYUP,0); 
		} 
	if(nbre==2 || nbre ==3) 
		keybd_event(y,0,KEYEVENTF_KEYUP,0); 
	keybd_event(x,0,KEYEVENTF_KEYUP,0); 
	}

/* Envoi de combinaison de touches de clavier comprenant des Virtual Keys */
void KeyboardMultiVirtualKey2(int x, int y, int z, int nbre) { 
  if(nbre == 1) { 
    switch(x) { 
      /* Lettres */
      case 'a': x = 0x41; break; 
      case 'b': x = 0x42; break; 
      case 'c': x = 0x43; break; 
      case 'd': x = 0x44; break; 
      case 'e': x = 0x45; break; 
      case 'f': x = 0x46; break; 
      case 'g': x = 0x47; break; 
      case 'h': x = 0x48; break; 
      case 'i': x = 0x49; break; 
      case 'j': x = 0x4a; break; 
      case 'k': x = 0x4b; break; 
      case 'l': x = 0x4c; break; 
      case 'm': x = 0x4d; break; 
      case 'n': x = 0x4e; break; 
      case 'o': x = 0x4f; break; 
      case 'p': x = 0x50; break; 
      case 'q': x = 0x51; break; 
      case 'r': x = 0x52; break; 
      case 's': x = 0x53; break; 
      case 't': x = 0x54; break; 
      case 'u': x = 0x55; break; 
      case 'v': x = 0x56; break; 
      case 'w': x = 0x57; break; 
      case 'x': x = 0x58; break; 
      case 'y': x = 0x59; break; 
      case 'z': x = 0x5a; break; 
      /* Chiffres avec le vérouillage numérique */
      case '0': x = 0x60; break; 
      case '1': x = 0x61; break; 
      case '2': x = 0x62; break; 
      case '3': x = 0x63; break; 
      case '4': x = 0x64; break; 
      case '5': x = 0x65; break; 
      case '6': x = 0x66; break;
      case '7': x = 0x67; break; 
      case '8': x = 0x68; break; 
      case '9': x = 0x69; break; 
      case '.': x = 0x6e; break; 
      /* Chiffres au dessus des lettres */
      case 'à': x = 0x30; break; 
      case '&': x = 0x31; break; 
      case 'é': x = 0x32; break; 
      case '"': x = 0x33; break; 
      case '\'': x = 0x34; break; 
      case '(': x = 0x35; break; 
      case '-': x = 0x36; break; 
      case 'è': x = 0x37; break; 
      case '_': x = 0x38; break; 
      case 'ç': x = 0x39; break; 
      default: break; 
    } 
  } 
  
  if(nbre == 2) { 
    switch(y) { 
      /* Lettres */
      case 'a': y = 0x41; break; 
      case 'b': y = 0x42; break; 
      case 'c': y = 0x43; break; 
      case 'd': y = 0x44; break; 
      case 'e': y = 0x45; break; 
      case 'f': y = 0x46; break; 
      case 'g': y = 0x47; break; 
      case 'h': y = 0x48; break; 
      case 'i': y = 0x49; break; 
      case 'j': y = 0x4a; break; 
      case 'k': y = 0x4b; break; 
      case 'l': y = 0x4c; break; 
      case 'm': y = 0x4d; break; 
      case 'n': y = 0x4e; break; 
      case 'o': y = 0x4f; break; 
      case 'p': y = 0x50; break; 
      case 'q': y = 0x51; break; 
      case 'r': y = 0x52; break; 
      case 's': y = 0x53; break; 
      case 't': y = 0x54; break; 
      case 'u': y = 0x55; break; 
      case 'v': y = 0x56; break; 
      case 'w': y = 0x57; break; 
      case 'x': y = 0x58; break; 
      case 'y': y = 0x59; break; 
      case 'z': y = 0x5a; break; 
  
      /* Chiffres au dessus des lettres */
      case '0': y = 0x30; break; 
      case '1': y = 0x31; break; 
      case '2': y = 0x32; break; 
      case '3': y = 0x33; break; 
      case '4': y = 0x34; break; 
      case '5': y = 0x35; break; 
      case '6': y = 0x36; break; 
      case '7': y = 0x37; break; 
      case '8': y = 0x38; break; 
      case '9': y = 0x39; break; 
      default: break; 
    } 
  } 
  
  if(nbre == 3) { 
    switch(z) { 
      /* Lettres */
      case 'a': z = 0x41; break; 
      case 'b': z = 0x42; break; 
      case 'c': z = 0x43; break; 
      case 'd': z = 0x44; break; 
      case 'e': z = 0x45; break; 
      case 'f': z = 0x46; break; 
      case 'g': z = 0x47; break; 
      case 'h': z = 0x48; break; 
      case 'i': z = 0x49; break; 
      case 'j': z = 0x4a; break; 
      case 'k': z = 0x4b; break; 
      case 'l': z = 0x4c; break; 
      case 'm': z = 0x4d; break; 
      case 'n': z = 0x4e; break; 
      case 'o': z = 0x4f; break; 
      case 'p': z = 0x50; break; 
      case 'q': z = 0x51; break; 
      case 'r': z = 0x52; break; 
      case 's': z = 0x53; break; 
      case 't': z = 0x54; break; 
      case 'u': z = 0x55; break; 
      case 'v': z = 0x56; break; 
      case 'w': z = 0x57; break; 
      case 'x': z = 0x58; break; 
      case 'y': z = 0x59; break; 
      case 'z': z = 0x5a; break; 
      /* Chiffres au dessus des lettres */
      case '@': z = 0x30; break; 
      case '~': z = 0x32; break; 
      case '#': z = 0x33; break; 
      case '{': z = 0x34; break; 
      case '[': z = 0x35; break; 
      case '|': z = 0x36; break; 
      case '`': z = 0x37; break; 
      case '\\': z = 0x38; break; 
      case '^': z = 0x39; break; 
      /* Chiffres avec le vérouillage numérique*/
      case '0': z = 0x60; break; 
      case '1': z = 0x61; break; 
      case '2': z = 0x62; break; 
      case '3': z = 0x63; break; 
      case '4': z = 0x64; break; 
      case '5': z = 0x65; break; 
      case '6': z = 0x66; break; 
      case '7': z = 0x67; break; 
      case '8': z = 0x68; break; 
      case '9': z = 0x69; break; 
      case '.': z = 0x6e; break; 
      default: break; 
    } 
  } 
  
    keybd_event(x,0,0,0); 
  if(nbre==2 || nbre ==3) 
     keybd_event(y,0,0,0); 
  if(nbre==3) 
  { 
     keybd_event(z,0,0,0); 
     keybd_event(z,0,KEYEVENTF_KEYUP,0); 
  } 
  if(nbre==2 || nbre ==3) 
     keybd_event(y,0,KEYEVENTF_KEYUP,0); 
    keybd_event(x,0,KEYEVENTF_KEYUP,0); 
} 

/* Simule un appuie sur une touche "normale" */
void KeyDown( const int x ) {
	int y=GetVirtualNumber(x) ;
	keybd_event(y,0,0,0);
	}
	
/* Simule un relachement de touche "normale" */
void KeyUp( const int x ) {
	int y=GetVirtualNumber(x) ;
	keybd_event(y,0,KEYEVENTF_KEYUP,0); 
	}

/* Simule un appuie sur une touche "morte" */
void VirtualKeyDown( const int x ) {
	keybd_event(x,0,0,0);
	}
	
/* Simule un relachement de touche "morte" */
void VirtualKeyUp( const int x ) {
	keybd_event(x,0,KEYEVENTF_KEYUP,0); 
	}

/* Envoi d'une touche "normale" */
void KeyboardKey(const int x) {
	if( (x>='A') && (x<='Z') ) VirtualKeyDown(VK_SHIFT) ;
	KeyDown(x);
	KeyUp(x);
	if( (x>='A') && (x<='Z') ) VirtualKeyUp(VK_SHIFT) ;
	}

/* Envoi d'une touche "virtuelle" */
void KeyboardVirtualKey(const int x) {
	VirtualKeyDown(x);
	VirtualKeyUp(x);
	}

/* Procedure generale du clavier */
void RunKeyboard(const char * cmd) {
	char * st;
	st = (char*)malloc(strlen(cmd)+1);
	strcpy(st,cmd);
	while( st[0] ){
		if( st[0] == '{' ) {
			if(pos("{BACKSPACE}",st)==1) {KeyboardVirtualKey(VK_BACK);del(st,1,11);}
			else if(pos("{+BACKSPACE}",st)==1 ) {VirtualKeyDown(VK_BACK);del(st,1,12);}
			else if(pos("{-BACKSPACE}",st)==1 ) {VirtualKeyUp(VK_BACK);del(st,1,12);}
			else if(pos("{APPS}",st)==1) {KeyboardVirtualKey(VK_APPS);del(st,1,6);}
			else if(pos("{+APPS}",st)==1) {VirtualKeyDown(VK_APPS);del(st,1,7);}
			else if(pos("{-APPS}",st)==1) {VirtualKeyUp(VK_APPS);del(st,1,7);}
			else if(pos("{ALT}",st)==1 ) {
				KeyboardMultiVirtualKey(VK_MENU,st[5],0,2);
				del(st,1,6);
				}
			else if(pos("{+ALT}",st)==1 ) {VirtualKeyDown(VK_MENU);del(st,1,6);}
			else if(pos("{-ALT}",st)==1 ) {VirtualKeyUp(VK_MENU);del(st,1,6);}
			else if(pos("{ALTGR}",st)==1 ) {
				KeyboardMultiVirtualKey(VK_RMENU,st[7],0,2);
				del(st,1,8);
				}
			else if(pos("{+ALTGR}",st)==1 ) {VirtualKeyDown(VK_RMENU);del(st,1,8);}
			else if(pos("{-ALTGR}",st)==1 ) {VirtualKeyUp(VK_RMENU);del(st,1,8);}
			else if(pos("{CAPS}",st)==1) {KeyboardVirtualKey(VK_CAPITAL);del(st,1,6);}
			else if(pos("{+CAPS}",st)==1) {VirtualKeyDown(VK_CAPITAL);del(st,1,7);}
			else if(pos("{-CAPS}",st)==1) {VirtualKeyUp(VK_CAPITAL);del(st,1,7);}
			else if(pos("{CANCEL}",st)==1) {KeyboardVirtualKey(VK_CANCEL);del(st,1,8);}
			else if(pos("{+CANCEL}",st)==1 ) {VirtualKeyDown(VK_CANCEL);del(st,1,9);}
			else if(pos("{-CANCEL}",st)==1 ) {VirtualKeyUp(VK_CANCEL);del(st,1,9);}
			else if(pos("{CTRL}",st)==1 ) {
				KeyboardMultiVirtualKey(VK_CONTROL,st[6],0,2);
				del(st,1,7);
				}
			else if(pos("{+CTRL}",st)==1 ) {VirtualKeyDown(VK_CONTROL);del(st,1,7);}
			else if(pos("{-CTRL}",st)==1 ) {VirtualKeyUp(VK_CONTROL);del(st,1,7);}
			else if(pos("{DEL}",st)==1) {KeyboardVirtualKey(VK_CLEAR);del(st,1,5);}
			else if(pos("{+DEL}",st)==1) {VirtualKeyDown(VK_CLEAR);del(st,1,6);}
			else if(pos("{-DEL}",st)==1) {VirtualKeyUp(VK_CLEAR);del(st,1,6);}
			else if(pos("{DOWN}",st)==1) {KeyboardVirtualKey(VK_DOWN);del(st,1,6);}
			else if(pos("{+DOWN}",st)==1) {VirtualKeyDown(VK_DOWN);del(st,1,7);}
			else if(pos("{-DOWN}",st)==1) {VirtualKeyUp(VK_DOWN);del(st,1,7);}
			else if(pos("{END}",st)==1) {KeyboardVirtualKey(VK_END);del(st,1,5);}
			else if(pos("{+END}",st)==1) {VirtualKeyDown(VK_END);del(st,1,6);}
			else if(pos("{-END}",st)==1) {VirtualKeyUp(VK_END);del(st,1,6);}
			else if(pos("{ESC}",st)==1) {KeyboardVirtualKey(VK_ESCAPE);del(st,1,5);}
			else if(pos("{+ESC}",st)==1) {VirtualKeyDown(VK_ESCAPE);del(st,1,6);}
			else if(pos("{-ESC}",st)==1) {VirtualKeyUp(VK_ESCAPE);del(st,1,6);}
			else if(pos("{F1}",st)==1) {KeyboardVirtualKey(VK_F1);del(st,1,4);}
			else if(pos("{+F1}",st)==1) {VirtualKeyDown(VK_F1);del(st,1,5);}
			else if(pos("{-F1}",st)==1) {VirtualKeyUp(VK_F1);del(st,1,5);}
			else if(pos("{F2}",st)==1) {KeyboardVirtualKey(VK_F2);del(st,1,4);}
			else if(pos("{+F2}",st)==1) {VirtualKeyDown(VK_F2);del(st,1,5);}
			else if(pos("{-F2}",st)==1) {VirtualKeyUp(VK_F2);del(st,1,5);}
			else if(pos("{F3}",st)==1) {KeyboardVirtualKey(VK_F3);del(st,1,4);}
			else if(pos("{+F3}",st)==1) {VirtualKeyDown(VK_F3);del(st,1,5);}
			else if(pos("{-F3}",st)==1) {VirtualKeyUp(VK_F3);del(st,1,5);}
			else if(pos("{F4}",st)==1) {KeyboardVirtualKey(VK_F4);del(st,1,4);}
			else if(pos("{+F4}",st)==1) {VirtualKeyDown(VK_F4);del(st,1,5);}
			else if(pos("{-F4}",st)==1) {VirtualKeyUp(VK_F4);del(st,1,5);}
			else if(pos("{F5}",st)==1) {KeyboardVirtualKey(VK_F5);del(st,1,4);}
			else if(pos("{+F5}",st)==1) {VirtualKeyDown(VK_F5);del(st,1,5);}
			else if(pos("{-F5}",st)==1) {VirtualKeyUp(VK_F5);del(st,1,5);}
			else if(pos("{F6}",st)==1) {KeyboardVirtualKey(VK_F6);del(st,1,4);}
			else if(pos("{+F6}",st)==1) {VirtualKeyDown(VK_F6);del(st,1,5);}
			else if(pos("{-F6}",st)==1) {VirtualKeyUp(VK_F6);del(st,1,5);}
			else if(pos("{F7}",st)==1) {KeyboardVirtualKey(VK_F7);del(st,1,4);}
			else if(pos("{+F7}",st)==1) {VirtualKeyDown(VK_F7);del(st,1,5);}
			else if(pos("{-F7}",st)==1) {VirtualKeyUp(VK_F7);del(st,1,5);}
			else if(pos("{F8}",st)==1) {KeyboardVirtualKey(VK_F8);del(st,1,4);}
			else if(pos("{+F8}",st)==1) {VirtualKeyDown(VK_F8);del(st,1,5);}
			else if(pos("{-F8}",st)==1) {VirtualKeyUp(VK_F8);del(st,1,5);}
			else if(pos("{F9}",st)==1) {KeyboardVirtualKey(VK_F9);del(st,1,4);}
			else if(pos("{+F9}",st)==1) {VirtualKeyDown(VK_F9);del(st,1,5);}
			else if(pos("{-F9}",st)==1) {VirtualKeyUp(VK_F9);del(st,1,5);}
			else if(pos("{F10}",st)==1) {KeyboardVirtualKey(VK_F10);del(st,1,5);}
			else if(pos("{+F10}",st)==1) {VirtualKeyDown(VK_F10);del(st,1,6);}
			else if(pos("{-F10}",st)==1) {VirtualKeyUp(VK_F10);del(st,1,6);}
			else if(pos("{F11}",st)==1) {KeyboardVirtualKey(VK_F11);del(st,1,5);}
			else if(pos("{+F11}",st)==1) {VirtualKeyDown(VK_F11);del(st,1,6);}
			else if(pos("{-F11}",st)==1) {VirtualKeyUp(VK_F11);del(st,1,6);}
			else if(pos("{F12}",st)==1) {KeyboardVirtualKey(VK_F12);del(st,1,5);}
			else if(pos("{+F12}",st)==1) {VirtualKeyDown(VK_F12);del(st,1,6);}
			else if(pos("{-F12}",st)==1) {VirtualKeyUp(VK_F12);del(st,1,6);}
			else if(pos("{F13}",st)==1) {KeyboardVirtualKey(VK_F13);del(st,1,5);}
			else if(pos("{+F13}",st)==1) {VirtualKeyDown(VK_F13);del(st,1,6);}
			else if(pos("{-F13}",st)==1) {VirtualKeyUp(VK_F13);del(st,1,6);}
			else if(pos("{F14}",st)==1) {KeyboardVirtualKey(VK_F14);del(st,1,5);}
			else if(pos("{+F14}",st)==1) {VirtualKeyDown(VK_F14);del(st,1,6);}
			else if(pos("{-F14}",st)==1) {VirtualKeyUp(VK_F14);del(st,1,6);}
			else if(pos("{F15}",st)==1) {KeyboardVirtualKey(VK_F15);del(st,1,5);}
			else if(pos("{+F15}",st)==1) {VirtualKeyDown(VK_F15);del(st,1,6);}
			else if(pos("{-F15}",st)==1) {VirtualKeyUp(VK_F15);del(st,1,6);}
			else if(pos("{F16}",st)==1) {KeyboardVirtualKey(VK_F16);del(st,1,5);}
			else if(pos("{+F16}",st)==1) {VirtualKeyDown(VK_F16);del(st,1,6);}
			else if(pos("{-F16}",st)==1) {VirtualKeyUp(VK_F16);del(st,1,6);}
			else if(pos("{F17}",st)==1) {KeyboardVirtualKey(VK_F17);del(st,1,5);}
			else if(pos("{+F17}",st)==1) {VirtualKeyDown(VK_F17);del(st,1,6);}
			else if(pos("{-F17}",st)==1) {VirtualKeyUp(VK_F17);del(st,1,6);}
			else if(pos("{F18}",st)==1) {KeyboardVirtualKey(VK_F18);del(st,1,5);}
			else if(pos("{+F18}",st)==1) {VirtualKeyDown(VK_F18);del(st,1,6);}
			else if(pos("{-F18}",st)==1) {VirtualKeyUp(VK_F18);del(st,1,6);}
			else if(pos("{F19}",st)==1) {KeyboardVirtualKey(VK_F19);del(st,1,5);}
			else if(pos("{+F19}",st)==1) {VirtualKeyDown(VK_F19);del(st,1,6);}
			else if(pos("{-F19}",st)==1) {VirtualKeyUp(VK_F19);del(st,1,6);}
			else if(pos("{F20}",st)==1) {KeyboardVirtualKey(VK_F20);del(st,1,5);}
			else if(pos("{+F20}",st)==1) {VirtualKeyDown(VK_F20);del(st,1,6);}
			else if(pos("{-F20}",st)==1) {VirtualKeyUp(VK_F20);del(st,1,6);}
			else if(pos("{F21}",st)==1) {KeyboardVirtualKey(VK_F21);del(st,1,5);}
			else if(pos("{+F21}",st)==1) {VirtualKeyDown(VK_F21);del(st,1,6);}
			else if(pos("{-F21}",st)==1) {VirtualKeyUp(VK_F21);del(st,1,6);}
			else if(pos("{F22}",st)==1) {KeyboardVirtualKey(VK_F22);del(st,1,5);}
			else if(pos("{+F22}",st)==1) {VirtualKeyDown(VK_F22);del(st,1,6);}
			else if(pos("{-F22}",st)==1) {VirtualKeyUp(VK_F22);del(st,1,6);}
			else if(pos("{F23}",st)==1) {KeyboardVirtualKey(VK_F23);del(st,1,5);}
			else if(pos("{+F23}",st)==1) {VirtualKeyDown(VK_F23);del(st,1,6);}
			else if(pos("{-F23}",st)==1) {VirtualKeyUp(VK_F23);del(st,1,6);}
			else if(pos("{F24}",st)==1) {KeyboardVirtualKey(VK_F24);del(st,1,5);}
			else if(pos("{+F24}",st)==1) {VirtualKeyDown(VK_F24);del(st,1,6);}
			else if(pos("{-F24}",st)==1) {VirtualKeyUp(VK_F24);del(st,1,6);}
			else if(pos("{HELP}",st)==1) {KeyboardVirtualKey(VK_HELP);del(st,1,6);}
			else if(pos("{+HELP}",st)==1) {VirtualKeyDown(VK_HELP);del(st,1,7);}
			else if(pos("{-HELP}",st)==1) {VirtualKeyUp(VK_HELP);del(st,1,7);}
			else if(pos("{HOME}",st)==1) {KeyboardVirtualKey(VK_HOME);del(st,1,6);}
			else if(pos("{+HOME}",st)==1) {VirtualKeyDown(VK_HOME);del(st,1,7);}
			else if(pos("{-HOME}",st)==1) {VirtualKeyUp(VK_HOME);del(st,1,7);}
			else if(pos("{INS}",st)==1) {KeyboardVirtualKey(VK_INSERT);del(st,1,5);}
			else if(pos("{+INS}",st)==1) {VirtualKeyDown(VK_INSERT);del(st,1,6);}
			else if(pos("{-INS}",st)==1) {VirtualKeyUp(VK_INSERT);del(st,1,6);}
			else if(pos("{LEFT}",st)==1) {KeyboardVirtualKey(VK_LEFT);del(st,1,6);}
			else if(pos("{+LEFT}",st)==1) {VirtualKeyDown(VK_LEFT);del(st,1,7);}
			else if(pos("{-LEFT}",st)==1) {VirtualKeyUp(VK_LEFT);del(st,1,7);}
			else if(pos("{NEXT}",st)==1) {KeyboardVirtualKey(VK_NEXT);del(st,1,6);}
			else if(pos("{+NEXT}",st)==1) {VirtualKeyDown(VK_NEXT);del(st,1,7);}
			else if(pos("{-NEXT}",st)==1) {VirtualKeyUp(VK_NEXT);del(st,1,7);}
			else if(pos("{NUMLOCK}",st)==1) {KeyboardVirtualKey(VK_NUMLOCK);del(st,1,9);}
			else if(pos("{+NUMLOCK}",st)==1) {VirtualKeyDown(VK_NUMLOCK);del(st,1,10);}
			else if(pos("{-NUMLOCK}",st)==1) {VirtualKeyUp(VK_NUMLOCK);del(st,1,10);}
			else if(pos("{PAUSE}",st)==1) {KeyboardVirtualKey(VK_PAUSE);del(st,1,7);}
			else if(pos("{+PAUSE}",st)==1) {VirtualKeyDown(VK_PAUSE);del(st,1,8);}
			else if(pos("{-PAUSE}",st)==1) {VirtualKeyUp(VK_PAUSE);del(st,1,8);}
			else if(pos("{PRINT}",st)==1) {KeyboardVirtualKey(VK_PRINT);del(st,1,7);}
			else if(pos("{+PRINT}",st)==1) {VirtualKeyDown(VK_PRINT);del(st,1,8);}
			else if(pos("{-PRINT}",st)==1) {VirtualKeyUp(VK_PRINT);del(st,1,8);}
			else if(pos("{PRIOR}",st)==1) {KeyboardVirtualKey(VK_PRIOR);del(st,1,7);}
			else if(pos("{+PRIOR}",st)==1) {VirtualKeyDown(VK_PRIOR);del(st,1,8);}
			else if(pos("{-PRIOR}",st)==1) {VirtualKeyUp(VK_PRIOR);del(st,1,8);}
			else if(pos("{RETURN}",st)==1) {KeyboardVirtualKey(VK_RETURN);del(st,1,8);}
			else if(pos("{+RETURN}",st)==1) {VirtualKeyDown(VK_RETURN);del(st,1,9);}
			else if(pos("{-RETURN}",st)==1) {VirtualKeyUp(VK_RETURN);del(st,1,9);}
			else if(pos("{RIGHT}",st)==1) {KeyboardVirtualKey(VK_RIGHT);del(st,1,7);}
			else if(pos("{+RIGHT}",st)==1) {VirtualKeyDown(VK_RIGHT);del(st,1,8);}
			else if(pos("{-RIGHT}",st)==1) {VirtualKeyUp(VK_RIGHT);del(st,1,8);}
			else if(pos("{SCROLLLOCK}",st)==1) {KeyboardVirtualKey(VK_SCROLL);del(st,1,12);}
			else if(pos("{+SCROLLLOCK}",st)==1) {VirtualKeyDown(VK_SCROLL);del(st,1,13);}
			else if(pos("{-SCROLLLOCK}",st)==1) {VirtualKeyUp(VK_SCROLL);del(st,1,13);}
			else if(pos("{SHIFT}",st)==1 ) {
				KeyboardMultiVirtualKey(VK_SHIFT,st[7],0,2);
				del(st,1,8);
				}
			else if(pos("{+SHIFT}",st)==1 ) {VirtualKeyDown(VK_SHIFT);del(st,1,8);}
			else if(pos("{-SHIFT}",st)==1 ) {VirtualKeyUp(VK_SHIFT);del(st,1,8);}
			else if(pos("{CTRLALT}",st)==1 ) {
				KeyboardMultiVirtualKey(VK_CONTROL,VK_MENU,st[9],3);
				del(st,1,10);
				}
			else if(pos("{SHIFTALT}",st)==1 ) {
				KeyboardMultiVirtualKey(VK_SHIFT,VK_MENU,st[10],3);
				del(st,1,11);
				}
			else if(pos("{SHIFTCTRL}",st)==1 ) {
				KeyboardMultiVirtualKey(VK_SHIFT,VK_CONTROL,st[11],3);
				del(st,1,12);
				}
			else if(pos("{SHIFTWIN}",st)==1 ) {
				KeyboardMultiVirtualKey(VK_SHIFT,VK_RWIN,st[10],3);
				del(st,1,11);
				}
			else if(pos("{SPACE}",st)==1) {KeyboardVirtualKey(VK_SPACE);del(st,1,7);}
			else if(pos("{+SPACE}",st)==1 ) {VirtualKeyDown(VK_SPACE);del(st,1,8);}
			else if(pos("{-SPACE}",st)==1 ) {VirtualKeyUp(VK_SPACE);del(st,1,8);}
			else if(pos("{TAB}",st)==1) {KeyboardVirtualKey(VK_TAB);del(st,1,5);}
			else if(pos("{+TAB}",st)==1 ) {VirtualKeyDown(VK_TAB);del(st,1,6);}
			else if(pos("{-TAB}",st)==1 ) {VirtualKeyUp(VK_TAB);del(st,1,6);}
			else if(pos("{UP}",st)==1) {KeyboardVirtualKey(VK_UP);del(st,1,4);}
			else if(pos("{+UP}",st)==1 ) {VirtualKeyDown(VK_UP);del(st,1,5);}
			else if(pos("{-UP}",st)==1 ) {VirtualKeyUp(VK_UP);del(st,1,5);}
			else if(pos("{WIN}",st)==1) {
				KeyboardMultiVirtualKey(VK_RWIN,st[5],0,2);
				del(st,1,6);
				}
			else if(pos("{+WIN}",st)==1) {VirtualKeyDown(VK_RWIN);del(st,1,6);}
			else if(pos("{-WIN}",st)==1) {VirtualKeyUp(VK_RWIN);del(st,1,6);}
			else if( st[2] == '}' ) {KeyboardKey(st[1]);del(st,1,3);}
			else if( (st[1]=='+') && (st[3] == '}') ) {KeyDown(st[2]);del(st,1,4);}
			else if( (st[1]=='-') && (st[3] == '}') ) {KeyUp(st[2]);del(st,1,4);}
			else {Keyboard1Simule(st[0]) ; del(st,1,1);}
			}
		else { Keyboard1Simule(st[0]); del(st,1,1); }
		}
	}
/*
Fonctionnement des "touches mortes" (ALT, CTRL, SHIFT, WIN)

- Pour appeler une touche morte suivie d'une touche "normale" (ex A-Z, 0-9, mais pas F1-F12 ni flèche ...)
il suffit de la nommer suivie simplement de la touche
	Ex 	Touche Windows + E => keyboard {WIN}e
		MAJ + A => keyboard {SHIFT}a
		
- Pour n'appeler que de la touche morte (sans rien derrière) 
	Ex Touche windows seule pour ouvrir le menu démarrer => keyboard {+WIN}{-WIN}
	
- Pour appeler une touche morte suivie d'une touche virtuelle
	Ex ALT + Tabulation => keyboard {+ALT}{TAB}{-ALT}
*/



/* Positionne l'etat d'une touche: 1 == DOWN , Autre == UP */
void SetKeyState( const int nVirtKey, const short state) {
	short ActualState = GetKeyState( nVirtKey ) ;
	if( (state == 1) && (ActualState != 1) ) KeyboardVirtualKey( nVirtKey ) ;
	if( (state !=1 ) && (ActualState == 1) ) KeyboardVirtualKey( nVirtKey ) ;
	}

