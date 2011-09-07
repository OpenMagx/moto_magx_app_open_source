#ifndef MARSSKINLOADER_H
#define MARSSKINLOADER_H
#include <qstring.h>
#include <qpixmap.h>

class MarsSkin{
public:
	MarsSkin();
	~MarsSkin();
    QString skinName;
    QString author;
    QString skinPath;
	//一些颜色 
    int textColor_r,textColor_g,textColor_b;	//正文文本折颜色
    int alphaColor_r,alphaColor_g,alphaColor_b;//拼音字母的颜色
    int cwordColor_r,cwordColor_g,cwordColor_b;//词的颜色
	//一些主题 图片
    QString pic_backGround;
    int pic_backGround_x;
    int pic_backGround_y;
    QPixmap *pix_backGround;

    QString pic_toolbar;
    int pic_toolbar_x;
    int pic_toolbar_y;
    QPixmap *pix_toolbar;

    QString pic_titlebar;
    int pic_titlebar_x;
    int pic_titlebar_y;
    QPixmap *pix_titlebar;

    QString pic_toolbarhl;
    int pic_toolbarhl_x;
    int pic_toolbarhl_y;
    QPixmap *pix_toolbarhl;

    QString pic_btn_cancel;
    int pic_btn_cancel_x;
    int pic_btn_cancel_y;
    QPixmap *pix_btn_cancel;

    QString pic_btn_theme;
    int pic_btn_theme_x;
    int pic_btn_theme_y;
    QPixmap *pix_btn_theme;

    QString pic_btn_about;
    int pic_btn_about_x;
    int pic_btn_about_y;
    QPixmap *pix_btn_about;

    QString pic_btn_copy;
    int pic_btn_copy_x;
    int pic_btn_copy_y;
    QPixmap *pix_btn_copy;

    QString pic_btn_paste;
    int pic_btn_paste_x;
    int pic_btn_paste_y;
    QPixmap *pix_btn_paste;

	QString pic_menubg;
	int pic_menubg_x;
	int pic_menubg_y;
	QPixmap *pix_menubg;

    QString pic_nullinput;
    int pic_nullinput_x;
    int pic_nullinput_y;
    QPixmap *pix_nullinput;

	QString pic_cword;
	//int pic_cword_y;
	QPixmap *pix_cword;

	QString pic_pycur;
	QPixmap *pix_pycur;

	QString pic_aboutdialog;
	int pic_aboutdialog_x;
	int pic_aboutdialog_y;
	QPixmap *pix_aboutdialog;
	
	QString pic_themeDialog;
	int pic_themeDialog_x;
	int pic_themeDialog_y;
	QPixmap *pix_themeDialog;
	
	int max_row_count;
	int row_max_pix;//正文最大的一行文字的像素数
	int cw_max_pix;//选词时最多的像素数，一行中的
	int char_max;//正文最大的一行文字的字符数，满足row_max_pix或char_max就换行
	int text_startx,text_starty,text_pix_btl;//正文在屏幕上显示的坐标，及行间距
	int cursor_color_r,cursor_color_g,cursor_color_b;//正文光标颜色
	int py_cur_y;//拼音的纵坐标
	int py_cur_ad1x,py_cur_ad2x;//拼音的坐标微调
	int py_text_x,py_text_y;//拼音显示的坐标

	int num_text_x,num_text_y;//输入时的数字的坐标
	int num_color_r,num_color_g,num_color_b;//输入时的数字的颜色
	int menu_bt;//菜单一个按钮的宽度，如“放弃”，“复制”按钮
	int cw_text_r,cw_text_g,cw_text_b;//输入时中文词的颜色
	int cw_text_x,cw_text_y;//输入时中文词的坐标
	int cw_cur_x,cw_cur_y;////输入时中文词的光标的坐标
	int text_curpix_x,text_curpix_y;//正文的光标的像素坐标
	int about_font_r,about_font_g,about_font_b;//关于窗口的文字颜色 
	int about_dialog_x,about_dialog_y;

	int theme_text_r,theme_text_g,theme_text_b;//不用说了，一看就明白了
	int theme_text_x,theme_text_y;
	int theme_preview_x,theme_preview_y;//不用说了，一看就明白了
	int copyinfo_x,copyinfo_y;//剪贴板信息文件的显示坐标
	int copyinfo_r,copyinfo_g,copyinfo_b;//剪贴板信息文件的颜色
	int cursor_adjust_x,cursor_adjust_y;//正文光标的坐标微调

};

class MarsSkinLoader{
public:
    static MarsSkin* load(QString);//装载皮肤
};

#endif // MARSSKINLOADER_H
