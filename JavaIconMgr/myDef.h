#ifndef MYDEF_H
#define MYDEF_H

#define E8


#define NEWUI
/***********************************************************************************/

/***********************************************************************************/


#if defined(E8) || defined(EM30)  
	#define SCREEN_H
#else
	#define SCREEN_V
#endif	



#ifdef COMMON_VER
    #define CLICK_NO_HIDE
    #define INSTALL_MGX_IN_FM
    #define RIGHT_KEY_NO_HIDE
#endif	


#ifdef SCREEN_H // for screen size 320 240
    #define SCREEN_WHIDTH 320
	#define PANEL_WHIDTH 120
#endif

#ifdef SCREEN_V // for screen size 240 320
	#define SCREEN_WHIDTH 240
	#define PANEL_WHIDTH 90 
#endif		


#define ICON_SMALL 24,24
#define ICON_BIG 48,48
	
#define KEYCODE_CLEAR  0x1032     // 4146
#define KEYCODE_GREEN  0x1030 
#define KEYCODE_RED 0x1031	 
#define KEYCODE_LEFT_SK 0x1038 //4152
#define KEYCODE_RIGHT_SK 0x103A //4154


#define PHONE_INSTALL_DB "/ezxlocal/download/appwrite/am/InstalledDB"
#define SD_INSTALL_DB "/mmc/mmca1/.system/java/CardRegistry" 
#define SD_MENU_CFG "/mmc/mmca1/.system/java/MemoryCardConfig"
#define MENU_TREE "/ezxlocal/download/appwrite/am/UserMenuTree"

#define JAVA_NET_PROFILE_PATH "/ezxlocal/download/appwrite/NetProfile"

#define PH_BASE "/ezxlocal/download/mystuff"
#define SD_BASE "/mmc/mmca1"

#define PHONE_MPKG_PATH "/ezxlocal/download/mystuff/mpkgbox"
#define SD_MPKG_PATH "/mmc/mmca1/mpkgbox"
#define CFG_FILE_PATH "/ezxlocal/download/appwrite/setup/ezx_rokrtool.cfg"


#define SD_BACKUP_DIR "/mmc/mmca1/backup"
#define PHONE_BACKUP_DIR "/ezxlocal/download/mystuff/backup"


#ifdef VE66_OLD_MP //VE66
	#define P7Z_PATH "/usr/data_resource/extra/p7zip"
#else	
	#define P7Z_PATH "/usr/local/p7zip"
#endif	

#define appUid "f0bc8dd8-b1aa-43ad-aba2-d32bcad7a9b4"


#define ctr QString::fromLocal8Bit

#define APP_TITLE "Java Mgr"
#define TITLE  "Java Mgr\n"
#define VERSION "Version : 2.6.2(For VE66)\n"// \nBuild 2010/08/28"
#define BUILD  "Build 2011/02/28\n"
#define AUTHOR "wanggjghost【泪の单翼天使】\n"
#define info1 "All rights reserved\n"
#define info2 "www.591fan.com\n"

#endif //MYDEF_H
