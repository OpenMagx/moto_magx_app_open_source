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
//�����define����û���ţ�ɾ�˰�
#define MARS_KEY_1 49	
#define MARS_KEY_9 57
#define MARS_KEY_LEFT 0
#define MARS_KEY_RIGHT 0
//������֧�ֶ������뷨�ģ��������鷳��û��ʵ�֣�Ҳ��û��������
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
		//��������¼�
		void keyPre(int);
		void keyRel(int);
		QString marsHome;
		//Ƥ�����
		MarsSkin* skin;
		void initSkin();
		//ͼ�λ���
		QPixmap* pixbuffer;
		//����
		QFont font_m;	//�ı���������
		QFont font_s;	//ѡ�����壬��С������
		//�����˸Timer
		QTimer *cursorTimer;
		PYDB *db;	//��ȡsqlite�ֿ����
		QString text_buf;//�����ı�
		
	signals:
		void Input_Accepted();//������ȷ�����ź�
		void Output_Rejected();//������������ź�
    private:
		void initGlobalVars();//��ʼ��ȫ�ֱ���
		void initWindowAttrs();//��ʼ����������
		void initPixmapBuffer();//��ʼ��ͼ�λ���
		void initFonts();////��ʼ������
		void initPinYinDB();//��ʼ��sqlite
		void initCursorTimer();//��ʼ�������˸��ʱ��
		void initClipBoard();//��ʼ����������ص�

		//cursor timer control �����˸����
		void startCursorTimer();
		void stopCursorTimer();
		//����ƴ����ʾ
		void adjust_alpha_ptr_view();
		//
		void cw_page();
		//�����ּ�ѡ�����Ĵ�
		void selectChineseWord(int);
		//�����Ľ��з��У��γɶ��string,�Ա���Ļÿ����ʾһ��string
		void orderText();
		//�������Ĺ�������Ļ�ϵ���ʾλ��
		void text_genePos();
		//����������
		QString clipBd;
		//���Ľ��з��еķ���
		int suck(int);
		//��Ļ��������ʾ���е�������Ϊ�����ĵĹ����ṩָʾ
		int window_top;
		//input method ���뷨
		InputMethod im;
		//���ֻ���
		QString num_buf;
		//ƴ����ĸ����
		QString alpha_buf;
		//�����ֲ����ƴ�����п����Ե��б�
		QStringList alpha_list;
		//��������������ƴ�������Ĵʵ��б���ÿ������ʾ�ĺ������������
		//��ʾ ��ʱ�򣬽�������������Ķ�Ӧ��ϵ����ʾѡ�ʹ��
		QValueList<int> alpha_pix_ptr;
		QValueList<int> cw_pix_ptr;
		//��ѡ�е�ƴ��������
		int alpha_ptr;
		//��ǰ��Ļ��ʾ������ߵ�ƴ�������������һ��Ϊ0����ƴ�����б�ĳ��Ⱥܳ�����Ļ��ʾ����ʱ�������ƶ����alpha_ptr_front
		//�Ա�����ƴ����ʾ����Ļ�ϣ����������û���õ�������������zhaopian�ȴ�ʱ���ұߵ�ƴ����ʾ����
		int alpha_ptr_front;
		
		//���Ĵʻ���
		QString cw_buf;
		//������ı�ѡ�Ĵ�(cw_buf)�б��ֳɵĴ�list
		QStringList cw_list;
		QStringList cw_page_list;
		//cw_list���ֳɼ�ҳ�Ա�ÿ����ʾһҳ�������¼�����ҳ
		uint cw_page_index;  // ��ǰ��ʾ�����Ĵʵ�ҳָ��
		int cw_pix_start,cw_pix_width;//��ǰ��ѡ�еĴʵ���Ļ��ʼX���꼰������X����
		bool selectMode;//����������ģʽ����ѡ��ģʽ
		QStringList text_rows;//���ı��ֳɶ��о���������棬��ʾʱ��ÿ������Ļ�ϻ�һ�оͿ���������ʾ��
		
		QStringList themeAvilable;//��ǰ���õ����� ��Ҳ����/ezxlocal/MarsInput/theme�ļ����е�����Ŀ¼��
		int themeIndex;//��ǰ��ʾ��Ŀ¼������
		bool themeDialogShows;//�����Ƿ���ʾ�ı�־

		int row_ptr;  //��ǰ��ʾ�ĵ�һ��
		int text_ptr;  //�����
		
		
		int ist_pix;//��������ڵ����е�������
		int cw_ptr;//ѡ��ģʽʱ��ѡ�еĴʵ�λ��

		bool cursorShows;	//���Ĺ���ǲ�����ʾ�����ֵ��ÿ750ms�ı䣬cursorTimer��ı����������˹�����
		void getChineseWords();//
		void doAbout();//���ڰ�ťѡ��ʱ������
		bool aboutDialogShows;//���ڴ����Ƿ���ʾ
		QPixmap *themePreview;//��ǰ�����Ԥ��
		void doTheme();//��ʾ���� ����ʱ������
		void themeSelected();//����ѡ��ʱ������
		QString themeName;
		void doCopy();//���ư�ťѡ��ʱ������
		void doPaste();//���ư�ťѡ��ʱ������
		int copy_start,copy_end;//Ҫ���Ƶ����������е������е�λ�õĿ�ʼ
		int copy_mode;//Ҫ���Ƶ����������е������е�λ�õĽ�����Ҳ������text_buf�е�λ��
		QString cache_file;//���Ƶ����ֱ�д��һ���ļ�/ezxlocal/MarsInput/mars.cache,�Ա����ٴ�ʱ����ճ��

		void clearNumBuf(); //������ֵĻ���
		void numBufChanged();	//��������ַ������ʱ
		void getPinYinWords();//�����ݿ��в�����п��ܵ�ƴ��
		void PinYinNextGroup();//ָ����һ�飨ҳ��ƴ����Ϊ����Ļ����ʾ
		void PinYinPrevGroup();
		void getPinYinPixPosistion();//����������ʾ��ƴ������Ļ�ϵ���ʾλ��
		void getCWords();//�����ݿ���ȡ��Ҫ��ʾ�����Ĵ�
		void CWPaging();//���Ĵʷ�ҳ
		void CWNextPage();//ָ����һ�飨ҳ�����Ĵʣ�Ϊ����Ļ����ʾ
		void CWPrevPage();
		void getCWPagePixPosition();
		void doInput();
		void text_order();	 //���ı�����������
		int text_suck(int);
		int text_row_ptr;//������ڵ���
		int text_col_ptr;//������ڵ���
		int text_curpix_x,text_curpix_y;//������ڵ�λ�õ�������
		void justTheOne();//����ʱƴ��ʱ��ֱ�������Ǹ��֣�Ҳ���ǲ���ѡ��ʱ
		void text_adjust_view();

		bool menuShows;//�˵��Ƿ���ʾ�ı�־
		int menu_index;//��ǰ�˵��ĸ߶ȵİ�ť������
		void doInputByNum(int); //������ѡ���

	public slots:
		void updateCursor();//���¹����Ƿ���ʾ���Ա�ʵ����˸
		
    protected:
		void paintEvent(QPaintEvent *);
    signals:
		void accepted();//ȷ������
		void rejected();//��������


};
#endif // U2PANEL_H
