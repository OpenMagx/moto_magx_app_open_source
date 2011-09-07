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
	//һЩ��ɫ 
    int textColor_r,textColor_g,textColor_b;	//�����ı�����ɫ
    int alphaColor_r,alphaColor_g,alphaColor_b;//ƴ����ĸ����ɫ
    int cwordColor_r,cwordColor_g,cwordColor_b;//�ʵ���ɫ
	//һЩ���� ͼƬ
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
	int row_max_pix;//��������һ�����ֵ�������
	int cw_max_pix;//ѡ��ʱ������������һ���е�
	int char_max;//��������һ�����ֵ��ַ���������row_max_pix��char_max�ͻ���
	int text_startx,text_starty,text_pix_btl;//��������Ļ����ʾ�����꣬���м��
	int cursor_color_r,cursor_color_g,cursor_color_b;//���Ĺ����ɫ
	int py_cur_y;//ƴ����������
	int py_cur_ad1x,py_cur_ad2x;//ƴ��������΢��
	int py_text_x,py_text_y;//ƴ����ʾ������

	int num_text_x,num_text_y;//����ʱ�����ֵ�����
	int num_color_r,num_color_g,num_color_b;//����ʱ�����ֵ���ɫ
	int menu_bt;//�˵�һ����ť�Ŀ�ȣ��硰�������������ơ���ť
	int cw_text_r,cw_text_g,cw_text_b;//����ʱ���Ĵʵ���ɫ
	int cw_text_x,cw_text_y;//����ʱ���Ĵʵ�����
	int cw_cur_x,cw_cur_y;////����ʱ���ĴʵĹ�������
	int text_curpix_x,text_curpix_y;//���ĵĹ�����������
	int about_font_r,about_font_g,about_font_b;//���ڴ��ڵ�������ɫ 
	int about_dialog_x,about_dialog_y;

	int theme_text_r,theme_text_g,theme_text_b;//����˵�ˣ�һ����������
	int theme_text_x,theme_text_y;
	int theme_preview_x,theme_preview_y;//����˵�ˣ�һ����������
	int copyinfo_x,copyinfo_y;//��������Ϣ�ļ�����ʾ����
	int copyinfo_r,copyinfo_g,copyinfo_b;//��������Ϣ�ļ�����ɫ
	int cursor_adjust_x,cursor_adjust_y;//���Ĺ�������΢��

};

class MarsSkinLoader{
public:
    static MarsSkin* load(QString);//װ��Ƥ��
};

#endif // MARSSKINLOADER_H
