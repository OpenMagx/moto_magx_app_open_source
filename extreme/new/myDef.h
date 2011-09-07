#ifndef MYDEF_H
#define MYDEF_H

#define VE66

//#define ZN5

//#define FONT_WRITABLE

//#define USE_NOTEPAD
/*********************************************/

#ifdef VE66
	#ifdef FONT_WRITABLE
		#define REPLACE_FONT
	#endif	
#endif	

#if defined(VE66) || defined(ZN5)

	#define SCREEN_WHIDTH 240 //320
	#define SCREEN_W 240
	#define SCREEN_H 320
#else
	#define SCREEN_WHIDTH 320
	#define SCREEN_W 320
	#define SCREEN_H 240	
#endif	


#ifdef ZN5
	#define MTD_LANG_SIZE 9437184
#else
	#define MTD_LANG_SIZE 9437184
#endif
	
	
#define KEY_LEFT              0x1012
#define KEY_UP                0x1013
#define KEY_RIGHT             0x1014
#define KEY_DOWN              0x1015
#define KEY_CENTER            0x1004
#define KEYCODE_LEFT_SK 0x1038 //4152
#define KEYCODE_RIGHT_SK 0x103A //4154
/*
#define PH_SKIN_DIR "/ezxlocal/download/mystuff/skins"
#define SD_SKIN_DIR "/mmc/mmca2/skins"
#define CHM_DIR "/ezxlocal/download/appwrite/setuptheme"
#define SKIN_FILE "/ezxlocal/download/mystuff/skin_file"
#define EZX_THEME "/ezxlocal/download/appwrite/setup/ezx_theme.cfg"

#define P7Z_PATH "/usr/local/p7zip"

#define MGR_TAB 0
#define PH_SKIN_TAB 1
#define SD_SKIN_TAB 2
*/
using namespace std;

#endif


