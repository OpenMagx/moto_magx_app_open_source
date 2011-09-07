#ifndef UTILSENUM_H
#define UTILSENUM_H

enum ITEMTYPE  // for app list box
{
	ITEM_NATIV,
	ITEM_JAVA,
	ITEM_SPECIAL,  //"phone" "flowplayer" "xp" "messaging" "RokrToolsPro"
	//ITEM_OTHE
	ITEM_FAV_OBJ,
	ITEM_MGX_OBJ,
	ITEM_MPKG_OBJ,
	ITEM_JAVA_OBJ,
	ITEM_MENU_OBJ
};

enum ITEMMODE // for ztask item
{
    NORMAL,
	MULTI,	
};

enum FILE_MOD_TYPE
{
	FILE_PASTE,
	FILE_DELETE,
	FILE_MOVE,
	FILE_OTHER
};

#endif //UTILSENUM_H

