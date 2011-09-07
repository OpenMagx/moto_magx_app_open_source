#ifndef U2PANEL_H
#define U2PANEL_H
#include <qwidget.h>
#include <qpainter.h>
#include <iostream>
#include <qstringlist.h>
#include <ZText.h>
#include <ZConfig.h>
#include <qtextcodec.h>
#include <qfont.h>
#include <qpixmap.h>
#include <qcolor.h>
#include <qsize.h>
#include <qtimer.h>
#include "MarsSkinLoader.h"
#include "PYDB.h"
#include <qdir.h>
#include <qtextstream.h>
#include <qfile.h>
using namespace std;
//下面的define好像没用着，删了吧
#define MARS_KEY_1 49	
#define MARS_KEY_9 57
#define MARS_KEY_LEFT 0
#define MARS_KEY_RIGHT 0
//本来想支持多种输入法的，后来嫌麻烦，没有实现，也就没有意义了
enum InputMethod{
    CHINESE,	    //default input method
    CASE_LOWER,
    CASE_UPPER,
    NUMBER,
    PUNCTUATION
};

class U2Panel:public QWidget{
    Q_OBJECT
    public:
		U2Panel(QWidget *,QString);
		~U2Panel();
		//处理键盘事件
		void keyPre(int);
		void keyRel(int);
		QString marsHome;
		//皮肤相关
		MarsSkin* skin;
		void initSkin();
		//图形缓冲
		QPixmap* pixbuffer;
		//字体
		QFont font_m;	//文本内容字体
		QFont font_s;	//选字字体，较小的字体
		//光标闪烁Timer
		QTimer *cursorTimer;
		PYDB *db;	//读取sqlite字库的类
		QString text_buf;//正文文本
		
	signals:
		void Input_Accepted();//输入后点确定的信号
		void Output_Rejected();//输入后点放弃的信号
    private:
		void initGlobalVars();//初始化全局变量
		void initWindowAttrs();//初始化容器属性
		void initPixmapBuffer();//初始化图形缓冲
		void initFonts();////初始化字体
		void initPinYinDB();//初始化sqlite
		void initCursorTimer();//初始化光标闪烁定时器
		void initClipBoard();//初始化剪贴板相关的

		//cursor timer control 光标闪烁控制
		void startCursorTimer();
		void stopCursorTimer();
		//调整拼音显示
		void adjust_alpha_ptr_view();
		//
		void cw_page();
		//由数字键选择中文词
		void selectChineseWord(int);
		//对正文进行分行，形成多个string,以便屏幕每行显示一个string
		void orderText();
		//生成正文光标等在屏幕上的显示位置
		void text_genePos();
		//剪贴板文字
		QString clipBd;
		//正文进行分行的方法
		int suck(int);
		//屏幕是上面显示的行的行数，为了正文的滚动提供指示
		int window_top;
		//input method 输入法
		InputMethod im;
		//数字缓冲
		QString num_buf;
		//拼音字母缓冲
		QString alpha_buf;
		//由数字查出的拼音所有可能性的列表
		QStringList alpha_list;
		//以下两个变量是拼音及中文词的列表中每个词显示的横坐标的像素数
		//显示 的时候，将按这个像素数的对应关系来显示选词光标
		QValueList<int> alpha_pix_ptr;
		QValueList<int> cw_pix_ptr;
		//被选中的拼音的索引
		int alpha_ptr;
		//当前屏幕显示的最左边的拼音的索引，这个一般为0，当拼音的列表的长度很长，屏幕显示不开时，可以移动这个alpha_ptr_front
		//以便后面的拼音显示在屏幕上，但这个好像没有用到，导致了输入zhaopian等词时，右边的拼音显示不了
		int alpha_ptr_front;
		
		//中文词缓冲
		QString cw_buf;
		//查出来的被选的词(cw_buf)列表被分成的词list
		QStringList cw_list;
		QStringList cw_page_list;
		//cw_list被分成几页以便每次显示一页，按上下键来翻页
		uint cw_page_index;  // 当前显示的中文词的页指针
		int cw_pix_start,cw_pix_width;//当前被选中的词的屏幕开始X坐标及结束的X坐标
		bool selectMode;//是输入数字模式还是选词模式
		QStringList text_rows;//正文被分成多行就用这个保存，显示时，每次在屏幕上画一行就可以正常显示了
		
		QStringList themeAvilable;//当前可用的主题 ，也就是/ezxlocal/MarsInput/theme文件夹中的所有目录名
		int themeIndex;//当前显示的目录的索引
		bool themeDialogShows;//主题是否显示的标志

		int row_ptr;  //当前显示的第一行
		int text_ptr;  //插入点
		
		
		int ist_pix;//光标在所在的行中的像素数
		int cw_ptr;//选词模式时，选中的词的位置

		bool cursorShows;	//正文光标是不是显示，这个值会每750ms改变，cursorTimer会改变他，无需人工干涉
		void getChineseWords();//
		void doAbout();//关于按钮选定时被调用
		bool aboutDialogShows;//关于窗口是否显示
		QPixmap *themePreview;//当前主题的预览
		void doTheme();//显示主题 窗口时被调用
		void themeSelected();//主题选定时被调用
		QString themeName;
		void doCopy();//复制按钮选定时被调用
		void doPaste();//复制按钮选定时被调用
		int copy_start,copy_end;//要复制的文字在所有的文字中的位置的开始
		int copy_mode;//要复制的文字在所有的文字中的位置的结束，也就是在text_buf中的位置
		QString cache_file;//复制的文字被写入一个文件/ezxlocal/MarsInput/mars.cache,以便在再打开时仍能粘贴

		void clearNumBuf(); //清除数字的缓存
		void numBufChanged();	//输入的数字发生变更时
		void getPinYinWords();//从数据库中查出所有可能的拼音
		void PinYinNextGroup();//指向下一组（页）拼音，为了屏幕的显示
		void PinYinPrevGroup();
		void getPinYinPixPosistion();//计算所有显示的拼音在屏幕上的显示位置
		void getCWords();//从数据库中取得要显示的中文词
		void CWPaging();//中文词分页
		void CWNextPage();//指向下一组（页）中文词，为了屏幕的显示
		void CWPrevPage();
		void getCWPagePixPosition();
		void doInput();
		void text_order();	 //将文本生成行数组
		int text_suck(int);
		int text_row_ptr;//光标所在的行
		int text_col_ptr;//光标所在的列
		int text_curpix_x,text_curpix_y;//光标所在的位置的像素数
		void justTheOne();//输入时拼音时，直接命中那个字，也就是不用选字时
		void text_adjust_view();

		bool menuShows;//菜单是否显示的标志
		int menu_index;//当前菜单的高度的按钮的索引
		void doInputByNum(int); //按数字选择词

	public slots:
		void updateCursor();//更新光标的是否显示，以便实现闪烁
		
    protected:
		void paintEvent(QPaintEvent *);
    signals:
		void accepted();//确定输入
		void rejected();//放弃输入


};
#endif // U2PANEL_H
