#include "MarsSkinLoader.h"
#include <ZConfig.h>
MarsSkin::MarsSkin(){

}
MarsSkin::~MarsSkin(){
	delete pix_backGround;
	delete pix_toolbar;
	delete pix_titlebar;
	delete pix_toolbarhl;
	delete pix_btn_cancel;
	delete pix_btn_theme;
	delete pix_btn_about;
	delete pix_btn_copy;
	delete pix_btn_paste;
	delete pix_menubg;
	delete pix_nullinput;
	delete pix_cword;
	delete pix_pycur;
	delete pix_aboutdialog;
	delete pix_themeDialog;
}
MarsSkin* MarsSkinLoader::load(QString path){
    MarsSkin *ms=new MarsSkin();
	ZConfig cfg(path+"/MarsSkin.cfg");

    ms->author=cfg.readEntry("Info","Author");
    ms->skinName=cfg.readEntry("Info","SkinName");
    ms->skinPath=path;

    ms->pic_backGround=cfg.readEntry("BackGround","Pic");
    ms->pic_backGround_x=cfg.readNumEntry("BackGround","X");
    ms->pic_backGround_y=cfg.readNumEntry("BackGround","Y");
    ms->pix_backGround=new QPixmap(path+QString("/")+ms->pic_backGround);

    ms->pic_toolbar=cfg.readEntry("ToolBar","Pic");
    ms->pic_toolbar_x=cfg.readNumEntry("ToolBar","X");
    ms->pic_toolbar_y=cfg.readNumEntry("ToolBar","Y");
    ms->pix_toolbar=new QPixmap(path+QString("/")+ms->pic_toolbar);

    ms->pic_titlebar=cfg.readEntry("TitleBar","Pic");
    ms->pic_titlebar_x=cfg.readNumEntry("TitleBar","X");
    ms->pic_titlebar_y=cfg.readNumEntry("TitleBar","Y");
    ms->pix_titlebar=new QPixmap(path+QString("/")+ms->pic_titlebar);

    ms->pic_toolbarhl=cfg.readEntry("MenuHL","Pic");
    ms->pic_toolbarhl_x=cfg.readNumEntry("MenuHL","X");
    ms->pic_toolbarhl_y=cfg.readNumEntry("MenuHL","Y");
    ms->pix_toolbarhl=new QPixmap(path+QString("/")+ms->pic_toolbarhl);

    ms->pic_btn_cancel=cfg.readEntry("ButtonCancel","Pic");
    ms->pic_btn_cancel_x=cfg.readNumEntry("ButtonCancel","X");
    ms->pic_btn_cancel_y=cfg.readNumEntry("ButtonCancel","Y");
    ms->pix_btn_cancel=new QPixmap(path+QString("/")+ms->pic_btn_cancel);

    ms->pic_btn_theme=cfg.readEntry("ButtonTheme","Pic");
    ms->pic_btn_theme_x=cfg.readNumEntry("ButtonTheme","X");
    ms->pic_btn_theme_y=cfg.readNumEntry("ButtonTheme","Y");
    ms->pix_btn_theme=new QPixmap(path+QString("/")+ms->pic_btn_theme);

    ms->pic_btn_about=cfg.readEntry("ButtonAbout","Pic");
    ms->pic_btn_about_x=cfg.readNumEntry("ButtonAbout","X");
    ms->pic_btn_about_y=cfg.readNumEntry("ButtonAbout","Y");
    ms->pix_btn_about=new QPixmap(path+QString("/")+ms->pic_btn_about);

	ms->pic_btn_copy=cfg.readEntry("ButtonCopy","Pic");
    ms->pic_btn_copy_x=cfg.readNumEntry("ButtonCopy","X");
    ms->pic_btn_copy_y=cfg.readNumEntry("ButtonCopy","Y");
    ms->pix_btn_copy=new QPixmap(path+QString("/")+ms->pic_btn_copy);

	ms->pic_btn_paste=cfg.readEntry("ButtonPaste","Pic");
    ms->pic_btn_paste_x=cfg.readNumEntry("ButtonPaste","X");
    ms->pic_btn_paste_y=cfg.readNumEntry("ButtonPaste","Y");
    ms->pix_btn_paste=new QPixmap(path+QString("/")+ms->pic_btn_paste);

    ms->pic_nullinput=cfg.readEntry("OptionsMenu","Pic");
    ms->pic_nullinput_x=cfg.readNumEntry("OptionsMenu","X");
    ms->pic_nullinput_y=cfg.readNumEntry("OptionsMenu","Y");
    ms->pix_nullinput=new QPixmap(path+QString("/")+ms->pic_nullinput);

	ms->pic_menubg=cfg.readEntry("MenuBg","Pic");
	ms->pic_menubg_x=cfg.readNumEntry("MenuBg","X");
	ms->pic_menubg_y=cfg.readNumEntry("MenuBg","Y");
	ms->pix_menubg=new QPixmap(path+QString("/")+ms->pic_menubg);

	ms->pic_cword=cfg.readEntry("CwCurser","Pic");
	//ms->pic_cword_y=cfg.readNumEntry("CwCurser","Y");
	ms->pix_cword=new QPixmap(path+QString("/")+ms->pic_cword);
	
	ms->pic_pycur=cfg.readEntry("PyCurser","Pic");
	ms->pix_pycur=new QPixmap(path+QString("/")+ms->pic_pycur);

	ms->pic_aboutdialog=cfg.readEntry("AboutDialog","Pic");
	ms->pic_aboutdialog_x=cfg.readNumEntry("AboutDialog","X");
	ms->pic_aboutdialog_y=cfg.readNumEntry("AboutDialog","Y");
	ms->pix_aboutdialog=new QPixmap(path+QString("/")+ms->pic_aboutdialog);
	
	ms->pic_themeDialog=cfg.readEntry("ThemeDialog","Pic");
	ms->pic_themeDialog_x=cfg.readNumEntry("ThemeDialog","X");
	ms->pic_themeDialog_y=cfg.readNumEntry("ThemeDialog","Y");
	ms->pix_themeDialog=new QPixmap(path+QString("/")+ms->pic_themeDialog);

    ms->textColor_r=cfg.readNumEntry("Colors","TextColor_R");
    ms->textColor_g=cfg.readNumEntry("Colors","TextColor_G");
    ms->textColor_b=cfg.readNumEntry("Colors","TextColor_B");

    ms->alphaColor_r=cfg.readNumEntry("Colors","AlphaColor_R"); 
    ms->alphaColor_g=cfg.readNumEntry("Colors","AlphaColor_G");
    ms->alphaColor_b=cfg.readNumEntry("Colors","AlphaColor_B"); 

    ms->cwordColor_r=cfg.readNumEntry("Colors","CWColor_R");  
    ms->cwordColor_g=cfg.readNumEntry("Colors","CWColor_G");  
    ms->cwordColor_b=cfg.readNumEntry("Colors","CWColor_B");  

	ms->max_row_count=cfg.readNumEntry("Globals","max_row_count");  
	ms->row_max_pix=cfg.readNumEntry("Globals","row_max_pix");
	ms->cw_max_pix=cfg.readNumEntry("Globals","cw_max_pix");
	ms->char_max=cfg.readNumEntry("Globals","char_max");
	ms->text_startx=cfg.readNumEntry("Globals","text_startx");
	ms->text_starty=cfg.readNumEntry("Globals","text_starty");
	ms->text_pix_btl=cfg.readNumEntry("Globals","text_pix_btl");
	ms->py_cur_y=cfg.readNumEntry("Globals","py_cur_y");
	ms->py_cur_ad1x=cfg.readNumEntry("Globals","py_cur_ad1x");
	ms->py_text_x=cfg.readNumEntry("Globals","py_text_x");
	ms->py_text_y=cfg.readNumEntry("Globals","py_text_y");

	ms->num_text_x=cfg.readNumEntry("Globals","num_text_x");
	ms->num_text_y=cfg.readNumEntry("Globals","num_text_y");
	ms->num_color_r=cfg.readNumEntry("Colors","NumColor_R");  
	ms->num_color_g=cfg.readNumEntry("Colors","NumColor_G");  
	ms->num_color_b=cfg.readNumEntry("Colors","NumColor_B");  

	ms->cursor_color_r=cfg.readNumEntry("Colors","CurserColor_R");  
	ms->cursor_color_g=cfg.readNumEntry("Colors","CurserColor_G");  
	ms->cursor_color_b=cfg.readNumEntry("Colors","CurserColor_B");  
	ms->menu_bt=cfg.readNumEntry("Globals","menu_bt");


	ms->cw_text_x=cfg.readNumEntry("Globals","cw_text_x");
	ms->cw_text_y=cfg.readNumEntry("Globals","cw_text_y");
	ms->cw_cur_x=cfg.readNumEntry("Globals","cw_cur_x");
	ms->cw_cur_y=cfg.readNumEntry("Globals","cw_cur_y");
	ms->text_curpix_x=cfg.readNumEntry("Globals","text_curpix_x");
	ms->text_curpix_y=cfg.readNumEntry("Globals","text_curpix_y");

	ms->about_font_r=cfg.readNumEntry("Colors","About_Font_r");
	ms->about_font_g=cfg.readNumEntry("Colors","About_Font_g");
	ms->about_font_b=cfg.readNumEntry("Colors","About_Font_b");
	
	ms->about_dialog_x=cfg.readNumEntry("Globals","about_dialog_x");
	ms->about_dialog_y=cfg.readNumEntry("Globals","about_dialog_y");

	ms->theme_text_x=cfg.readNumEntry("Globals","ThemeText_X");
	ms->theme_text_y=cfg.readNumEntry("Globals","ThemeText_Y");

	ms->theme_text_r=cfg.readNumEntry("Colors","ThemeColor_R");
	ms->theme_text_g=cfg.readNumEntry("Colors","ThemeColor_G");
	ms->theme_text_b=cfg.readNumEntry("Colors","ThemeColor_B");
	
	ms->theme_preview_x=cfg.readNumEntry("ThemePreview","X");
	ms->theme_preview_y=cfg.readNumEntry("ThemePreview","Y");
	
	ms->copyinfo_r=cfg.readNumEntry("Colors","CopyInfo_R");
	ms->copyinfo_g=cfg.readNumEntry("Colors","CopyInfo_G");
	ms->copyinfo_b=cfg.readNumEntry("Colors","CopyInfo_B");

	ms->copyinfo_x=cfg.readNumEntry("Globals","CopyInfo_X");
	ms->copyinfo_y=cfg.readNumEntry("Globals","CopyInfo_Y");
	ms->cursor_adjust_x=cfg.readNumEntry("Globals","cursor_adjust_x");
	ms->cursor_adjust_y=cfg.readNumEntry("Globals","cursor_adjust_y");
    return ms;

}
