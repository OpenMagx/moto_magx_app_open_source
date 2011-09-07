#include "U2Panel.h"
QString ctr(const char*ChineseString){
	
	return QString::fromUtf8(ChineseString);
}
U2Panel::U2Panel(QWidget *parent,QString text):QWidget(parent){
	skin=NULL;
	initSkin();
    initGlobalVars();
    initWindowAttrs();
    initPixmapBuffer();
    initFonts();
    initPinYinDB();
    initCursorTimer();
    startCursorTimer();
	themeDialogShows=FALSE;
	text_buf=text;
	if(text_buf.length()>0){
	cout<<"text buf length "<<text_buf.length()<<endl;
	cout<<text_buf<<endl;
	
		text_ptr=text_buf.length();
		text_order();
		text_genePos();
	}
	initClipBoard();
}
U2Panel::~U2Panel(){
	delete pixbuffer;
	delete cursorTimer;
	delete db;
	delete themePreview;
	delete skin;
}

//初始化函数 initializing functions
void U2Panel::initGlobalVars(){
	cout<<"init clobal vars"<<endl;
	
    im=CHINESE;
    cursorShows=TRUE;
	window_top=0;
	alpha_ptr_front=0;
	selectMode=FALSE;
	cw_page_index=0;
	cw_pix_start=0;
	cw_pix_width=0;
	text_ptr=0;
	text_row_ptr=0;
	text_col_ptr=0;
	text_curpix_x=skin->text_curpix_x;
	text_curpix_y=skin->text_curpix_y;
	window_top=0;
	menuShows=FALSE;
	menu_index=0;
	aboutDialogShows=FALSE;
	themePreview=NULL;
	themeDialogShows=FALSE;
	copy_mode=0;
	copy_start=0;
	copy_end=0;
	cache_file="/ezxlocal/MarsInput/mars.cache";
}
void U2Panel::initWindowAttrs(){
	cout<<"initWindowAttrs"<<endl;

    setWFlags(getWFlags()|Qt::WRepaintNoErase);
    setBackgroundMode(NoBackground);
}
void U2Panel::initPixmapBuffer(){
	cout<<"initPixmapBuffer"<<endl;
    pixbuffer=new QPixmap(320,240);
}
void U2Panel::initFonts(){
cout<<"initFonts"<<endl;
    font_m=QPainter(this).font();
    font_m.setPointSize(21);
    font_s=QPainter(this).font();
    font_s.setPointSize(18);
}
void U2Panel::initPinYinDB(){
cout<<"initPinYinDB"<<endl;

	db=new PYDB(("/ezxlocal/MarsInput/db/pinyin.db"));
}
void U2Panel::initCursorTimer(){
cout<<"initCursorTimer"<<endl;

    cursorTimer=new QTimer(this);
    connect(cursorTimer,SIGNAL(timeout()),this,SLOT(updateCursor()));
}
void U2Panel::initSkin(){
cout<<"initSkin"<<endl;

	if(skin!=NULL)
		delete skin;
	//读取当前的主题
	ZConfig cfg("/ezxlocal/MarsInput/theme/theme.cfg");
	themeName=cfg.readEntry("Theme","Name");
	cout<<"themeName="<<(const char*)themeName<<endl;
    skin=MarsSkinLoader::load(QString("/ezxlocal/MarsInput/theme/")+themeName);
	themeAvilable=QDir("/ezxlocal/MarsInput/theme/").entryList(1);
	//当前可用的主题
	themeAvilable.remove(QString("."));
	themeAvilable.remove(QString(".."));
	
	themeIndex=themeAvilable.findIndex(themeName);
	if(themeIndex==-1){
		cout<<"theme load exception #1"<<endl;
		themeIndex=0;
	}
	cout<<"after skin load "<<endl;
}

//槽 SLOTS
void U2Panel::updateCursor(){
	cursorShows=!cursorShows;
	repaint();
}

void U2Panel::keyPre(int key){
    cout<<"Key Pressed :"<<key<<endl;
	if(aboutDialogShows||themeDialogShows){
		return;
	}
	
	if(selectMode){
		cout<<"select mode"<<endl;
		//选词模式
		if(key==4146){
			//删除键
			selectMode=FALSE;
		}else if(key==4115){
			//向上
			
			if(cw_page_index==0){
				selectMode=FALSE;
			}else{
				cw_page_index--;
				getCWPagePixPosition();
				
			}
		}else if(key==4117){
			//向下
			if(cw_page_index<cw_page_list.count()-1){
				cw_page_index++;
				getCWPagePixPosition();
			}
		}else if(key==4116){
			//向右
			cw_ptr++;
			cw_ptr=cw_ptr%(cw_pix_ptr.count()-1);
		}else if(key==4114){
			//向左
			cw_ptr+=cw_pix_ptr.count()-2;
			cw_ptr=cw_ptr%(cw_pix_ptr.count()-1);
			
		}
	}else{//非选词模式
		cout<<" not select mode"<<endl;
		if(key==4146){
			//删除键
			int i=num_buf.length();
			if(i>0){
				num_buf=num_buf.left(i-1);
				if(i==1){
					cw_list.clear();
					cw_page_list.clear();
				}
				//数字发生变化
				numBufChanged();
				getCWords();
				CWPaging();
			}else{
				//删除正文
				if(text_ptr>0){
					text_buf.remove(text_ptr-1,1);
					text_ptr--;
					text_order();
					text_genePos();
				}
			}			
		}else if(key==4116){
			//向右
			if(menuShows){
				menu_index=(menu_index+1)%5;
			}else{
				if(num_buf.length()>0){
					PinYinNextGroup();
				}else{
					if(text_ptr<text_buf.length()){
						text_ptr++;
						text_genePos();
					}
				}
			}
		}else if(key==4114){
			//向左
			if(menuShows){
				menu_index=(menu_index+4)%5;
			}else{
				if(num_buf.length()>0){
					PinYinPrevGroup();
				}else{
					if(text_ptr>0){
						text_ptr--;
						text_genePos();
					}
				}
			}
		}else if(key==4115){
			//向上
			if(menuShows)
				return;
			if(num_buf.length()>0){
				num_buf="";
				cw_list.clear();
				cw_page_list.clear();
				alpha_buf="";
				alpha_pix_ptr.clear();
				cw_pix_ptr.clear();
			}else{
				//光标移动上
				if(text_row_ptr>0){
					int ii=text_col_ptr;
					if(text_rows[text_row_ptr-1].length()>ii){
						text_ptr-=text_rows[text_row_ptr-1].length();
					}else{
						text_ptr-=text_col_ptr;
					}
					text_genePos();

				}
			}

		}else if(key==4117){
			//向下
			if(menuShows)
				return;
			if(num_buf.length()>0){
				cw_page_index=0;
				selectMode=TRUE;
				getCWPagePixPosition();
			}else{
				//光标移动下
				if(text_row_ptr<text_rows.count()-1){
					//下移
					if(text_rows[text_row_ptr+1].length()>=text_col_ptr){
						text_ptr+=text_rows[text_row_ptr].length();
					}else{
						text_ptr+=(text_rows[text_row_ptr].length()-text_col_ptr+text_rows[text_row_ptr+1].length());
					}
				}
				text_genePos();
			}
		}
	}
	repaint();
}
void U2Panel::keyRel(int key){
    cout<<"Key Released :"<<key<<endl;
	if(aboutDialogShows){
		aboutDialogShows=FALSE;
		repaint();
		return;
	}
	if(themeDialogShows){
		switch(key){
			case 4100:
				themeSelected();
				break;
			case 4114:
				themeIndex+=themeAvilable.count()-1;
				themeIndex=themeIndex%themeAvilable.count();
				break;
			case 4116:
				themeIndex+=1;
				themeIndex=themeIndex%themeAvilable.count();
				break;
			case 4146:
				themeDialogShows=FALSE;
				break;
		}
		repaint();
		return;
	}
	if(selectMode){//选词模式
		cout<<"select mode"<<endl;
	
		//是数字键
		if(key==4100){
			//输入
			doInput();
			num_buf="";
			alpha_buf="";
			cw_page_list.clear();
			cw_list.clear();
			selectMode=FALSE;
		}else if(key>48&&key<58){
			doInputByNum(key);
			num_buf="";
			alpha_buf="";
			cw_page_list.clear();
			cw_list.clear();
			selectMode=FALSE;
		}
		
		
	}else{//非选词模式
		cout<<"not select mode"<<endl;
		if(key>48&&key<58){
			if(!menuShows){
				num_buf+=QString::number(key-48);
				//数字发生变化============================================================
				numBufChanged();
				getCWords();
				CWPaging();
			}
		}else if(key==4100){
			if(!menuShows){
				justTheOne();
				num_buf="";
				alpha_buf="";
				cw_page_list.clear();
				cw_list.clear();
			}else{
				switch(menu_index){
					case 0:
						emit(rejected());
						break;
					case 1:
						doCopy();
						break;
					case 2:
						doPaste();
						break;
					case 3:
						doTheme();
						break;
					case 4:
						doAbout();
						return;
						break;

				}
				menuShows=!menuShows;
			}
		}else if(key==4152){
			if(num_buf==""){
				menuShows=!menuShows;
			}
		}else if(key==4154){
			emit(accepted());
			//接受
		}
	}

	repaint();
}
void U2Panel::startCursorTimer(){
    cursorTimer->start(750);
}
void U2Panel::stopCursorTimer(){
    cursorTimer->stop();
}

void U2Panel::paintEvent(QPaintEvent* event){ //===================================
    QPainter ptr(pixbuffer);
    ptr.begin(pixbuffer);
    
    //渲染背景
    ptr.drawPixmap(skin->pic_backGround_x,skin->pic_backGround_y,*(skin->pix_backGround));
    //title bar
    ptr.drawPixmap(skin->pic_titlebar_x,skin->pic_titlebar_y,*(skin->pix_titlebar));
    
	// 正文
	ptr.setFont(font_m);
	ptr.setPen(QColor(skin->textColor_r,skin->textColor_g,skin->textColor_b));
	
	int ii=skin->max_row_count<text_rows.count()?skin->max_row_count:text_rows.count();
	int ix=0;
	for(;ix<ii;ix++){
		ptr.drawText(skin->text_startx,skin->text_pix_btl*ix+skin->text_starty,text_rows[ix+window_top]);
	}
	
	//正文闪烁光标
	
	if(cursorShows){	
		ptr.fillRect(text_curpix_x,text_curpix_y,2,22,QColor(skin->cursor_color_r,skin->cursor_color_g,skin->cursor_color_b));
	}
	//拼音
	ptr.setFont(font_s);
	if(alpha_buf.length()>0){
		//tool bar
		ptr.drawPixmap(skin->pic_toolbar_x,skin->pic_toolbar_y,*(skin->pix_toolbar));
		//拼音光标
		ptr.drawPixmap(skin->py_cur_ad1x+alpha_pix_ptr[alpha_ptr],skin->py_cur_y,*(skin->pix_pycur),0,0,10,-1);
		for(int i=0;i<alpha_pix_ptr[alpha_ptr+1]-alpha_pix_ptr[alpha_ptr]-18;i++){
			ptr.drawPixmap(skin->py_cur_ad1x+10+alpha_pix_ptr[alpha_ptr]+i,skin->py_cur_y,*(skin->pix_pycur),11,0,1,-1);
		}
		//拼音
		ptr.drawPixmap(alpha_pix_ptr[alpha_ptr+1]+skin->py_cur_ad1x-10,skin->py_cur_y,*(skin->pix_pycur),(skin->pix_pycur)->width()-10,0,10,-1);
		ptr.setPen(QColor(skin->alphaColor_r,skin->alphaColor_g,skin->alphaColor_b));
		ptr.drawText(skin->py_text_x-alpha_pix_ptr[alpha_ptr_front],skin->py_text_y,alpha_buf);
		
	}else if(num_buf.length()>0){
		//tool bar
		ptr.drawPixmap(skin->pic_toolbar_x,skin->pic_toolbar_y,*(skin->pix_toolbar));
		//查不到拼音 画数字
		ptr.setPen(QColor(skin->num_color_r,skin->num_color_g,skin->num_color_b));
		ptr.drawText(skin->num_text_x,skin->num_text_y,num_buf);
	}

	//中文字词
	
	if(cw_list.count()>0){//查出汉字数量不为0
		if(selectMode){
			//选词模式
			//选词光标
			
			ptr.drawPixmap(skin->cw_cur_x+cw_pix_ptr[cw_ptr],skin->cw_cur_y,*(skin->pix_cword),0,0,10,-1);
			
			for(int i=0;i<cw_pix_ptr[cw_ptr+1]-cw_pix_ptr[cw_ptr]-18;i++){
				ptr.drawPixmap(skin->cw_cur_x+10+cw_pix_ptr[cw_ptr]+i,skin->cw_cur_y,*(skin->pix_cword),11,0,1,-1);
			}
			ptr.drawPixmap(cw_pix_ptr[cw_ptr+1]+skin->cw_cur_x-10,skin->cw_cur_y,*(skin->pix_cword),(skin->pix_cword)->width()-10,0,10,-1);

			ptr.setPen(QColor(skin->cwordColor_r,skin->cwordColor_g,skin->cwordColor_b));
			ptr.drawText(skin->cw_text_x,skin->cw_text_y,cw_page_list[cw_page_index]);
		}else{
			//未进入选词模式
			ptr.setPen(QColor(skin->cwordColor_r,skin->cwordColor_g,skin->cwordColor_b));
			ptr.drawText(skin->cw_text_x,skin->cw_text_y,cw_list[0]);
			
		}
	}
	//菜单条
	if(num_buf==""){
		if(menuShows){
			//tool bar
			ptr.drawPixmap(skin->pic_menubg_x,skin->pic_menubg_y,*(skin->pix_menubg));
			ptr.drawPixmap(skin->pic_toolbarhl_x+skin->menu_bt*menu_index,skin->pic_toolbarhl_y,*(skin->pix_toolbarhl));
			ptr.drawPixmap(skin->pic_btn_cancel_x,skin->pic_btn_cancel_y,*(skin->pix_btn_cancel));
			ptr.drawPixmap(skin->pic_btn_theme_x,skin->pic_btn_theme_y,*(skin->pix_btn_theme));
			ptr.drawPixmap(skin->pic_btn_about_x,skin->pic_btn_about_y,*(skin->pix_btn_about));
			ptr.drawPixmap(skin->pic_btn_copy_x,skin->pic_btn_copy_y,*(skin->pix_btn_copy));
			ptr.drawPixmap(skin->pic_btn_paste_x,skin->pic_btn_paste_y,*(skin->pix_btn_paste));

		}else{
			ptr.drawPixmap(skin->pic_nullinput_x,skin->pic_nullinput_y,*(skin->pix_nullinput));
			//复制信息
			if(copy_mode==0){
				ptr.setPen(QColor(skin->copyinfo_r,skin->copyinfo_g,skin->copyinfo_b));
				if(clipBd.length()==0)
					ptr.drawText(skin->copyinfo_x,skin->copyinfo_y,QString::fromUtf8("空"));
				else
					ptr.drawText(skin->copyinfo_x,skin->copyinfo_y,QString::fromUtf8("内容：")+clipBd.left(8)+QString("..."));
			}else{
				ptr.setPen(QColor(skin->copyinfo_r,skin->copyinfo_g,skin->copyinfo_b));
				ptr.drawText(skin->copyinfo_x,skin->copyinfo_y,QString::fromUtf8("开始于:")+QString::number(copy_start));
			}
		}
	}
	if(aboutDialogShows){
		ptr.drawPixmap(skin->pic_aboutdialog_x,skin->pic_aboutdialog_y,*(skin->pix_aboutdialog));
		ptr.setPen(QColor(skin->about_font_r,skin->about_font_g,skin->about_font_b));
		int yy=skin->about_dialog_y;
		ptr.setFont(font_s);
		
		ptr.drawText(skin->about_dialog_x,yy,ctr("关于火星输入法："));
		yy+=20;
		ptr.drawText(skin->about_dialog_x,yy,ctr("版本：1.2"));
		yy+=20;
		ptr.drawText(skin->about_dialog_x,yy,ctr("感谢fuzhuo20的输入法源码！"));
		yy+=20;
		ptr.drawText(skin->about_dialog_x,yy,ctr("技术支持：无印"));
		yy+=20;
		ptr.drawText(skin->about_dialog_x,yy,ctr("总策划：Xmifeng"));
		yy+=20;
		ptr.drawText(skin->about_dialog_x,yy,ctr("编码：DarkDragon"));
	}
	if(themeDialogShows){
		//背景
		ptr.drawPixmap(skin->pic_themeDialog_x,skin->pic_themeDialog_y,*(skin->pix_themeDialog));
		//预览
		cout<<"length="<<themeAvilable.count()<<endl;
	
		
		QString tmp2=QString("/ezxlocal/MarsInput/theme/")+themeAvilable[themeIndex]+QString("/MarsSkin.cfg");
		if(themePreview!=NULL){
			delete themePreview;
		}
		cout<<"tmp2="<<tmp2.latin1()<<endl;
		QString tmp1=ZConfig(tmp2).readEntry("ThemePreview","Pic");
		cout<<"tmp1="<<tmp1.latin1()<<endl;
		themePreview=new QPixmap(QString("/ezxlocal/MarsInput/theme/")+themeAvilable[themeIndex]+QString("/")+tmp1);
		ptr.drawPixmap(skin->theme_preview_x,skin->theme_preview_y,*(themePreview));
		//文字说明
		ptr.setPen(QColor(skin->theme_text_r,skin->theme_text_g,skin->theme_text_b));
		ptr.drawText(skin->theme_text_x,skin->theme_text_y,QString("%1  %2/%3").arg(themeAvilable[themeIndex]).arg(themeIndex+1).arg(themeAvilable.count()));

	}
    ptr.end();
	//写缓冲
	QPainter pt(this);
	pt.begin(this);
	pt.drawPixmap(0,0,*pixbuffer);
	pt.end();
}
void U2Panel::clearNumBuf(){
	num_buf="";
}

void U2Panel::numBufChanged(){
	switch(im){
		case CHINESE:
			getChineseWords();
		break;
		case NUMBER:
		break;
	}
}
void U2Panel::getPinYinWords(){
	//取得拼音
	db->find("head","NUM",num_buf);
	alpha_buf=db->result;
	alpha_list=QStringList::split(' ',alpha_buf);
	alpha_ptr=0;
	//计算每个拼音的显示像素开始位置
	getPinYinPixPosistion();
}
void U2Panel::PinYinNextGroup(){
	if(alpha_ptr<alpha_list.count()-1){
		alpha_ptr++;
		getCWords();
		CWPaging();
		getCWPagePixPosition();
	}
}
void U2Panel::PinYinPrevGroup(){
	if(alpha_ptr>0){
		alpha_ptr--;
		getCWords();
		CWPaging();
		getCWPagePixPosition();
	}
}
void U2Panel::getPinYinPixPosistion(){
	//计算每个拼音的显示像素开始位置
	alpha_pix_ptr.clear();
	alpha_pix_ptr.append(0);
	QString temp="";
	for(uint i=0;i<alpha_list.count();i++){
		temp.append(alpha_list[i]);
		temp.append(" ");
		alpha_pix_ptr.append(ZText::getStringWidth(font_s,temp));
		cout<<"For cycle getPinYinPixPosistion() "<<i<<" times"<<endl;
	}
}
//查数据库
void U2Panel::getCWords(){
	db->find("data","HEAD",alpha_list[alpha_ptr]);
	cw_buf=QTextCodec::codecForName("UTF-8")->toUnicode((db->result).latin1());
	cw_list=QStringList::split(' ',cw_buf);
	cw_ptr=0;
}
//分页
void U2Panel::CWPaging(){
	QString tmp="";
	cw_page_list.clear();
	int j=1;
	for(uint i=0;i<cw_list.count();i++){
		tmp.append(QString::number(j));
		tmp.append(cw_list[i]);
		tmp.append(" ");
		if(ZText::getStringWidth(font_s,tmp)>skin->cw_max_pix||j>9){
			tmp.truncate(tmp.length()-1-QString::number(j).length()-cw_list[i].length());
			cw_page_list.append(tmp);
			tmp="";
			--i;
			j=1;
		}else
			j++;
		cout<<"CWPaging cycle () "<<i <<"times"<<endl;
	}
	cw_page_list.append(tmp);
	cw_page_index=0;
}


void U2Panel::CWNextPage(){
	if(cw_page_index<cw_page_list.count()-1){
		cw_page_index++;
	}
}
void U2Panel::CWPrevPage(){
	if(cw_page_index>0){
		cw_page_index--;
	}
}
void U2Panel::getCWPagePixPosition(){
	QString temp=cw_page_list[cw_page_index];
	
	cw_pix_ptr.clear();
	cw_pix_ptr.append(0);
	int i=0;
	while(i!=-1){
		
		i=temp.find(' ',i+1);
		
		if(i!=-1)
			cw_pix_ptr.append( ZText::getStringWidth(font_s,temp.left(i+1)));
	}
	//cw_pix_ptr.append( ZText::getStringWidth(font_s,temp));
	if(cw_ptr>=cw_pix_ptr.count()-1)
		cw_ptr=0;
}
void U2Panel::getChineseWords(){
	getPinYinWords();
}
void U2Panel::doInput(){
	QString temp=cw_page_list[cw_page_index];
	int wd=temp.find(QString::number(cw_ptr+1));
	int spc=temp.find(QString(" "),wd+1);
	//text_buf.append(temp.mid(wd,spc-wd));
	QString temp2=temp.mid(wd+1,spc-wd-1);
	text_buf.insert(text_ptr,temp2);
	text_ptr+=temp2.length();
	text_order();
	text_genePos();
}
void U2Panel::doInputByNum(int key){
	QString temp=cw_page_list[cw_page_index];
	int wd=temp.find(QString::number(key-48));
	int spc=temp.find(QString(" "),wd+1);
	//text_buf.append(temp.mid(wd,spc-wd));
	QString temp2=temp.mid(wd+1,spc-wd-1);
	text_buf.insert(text_ptr,temp2);
	text_ptr+=temp2.length();
	text_order();
	text_genePos();
}
void U2Panel::justTheOne(){
	text_buf.insert(text_ptr,cw_list[0]);
	text_ptr+=cw_list[0].length();
	text_order();
	text_genePos();
}
void U2Panel::text_order(){
	text_rows.clear();
	int xx=0;
	do{
		xx=text_suck(xx);
	}while(xx!=-1);

}
int U2Panel::text_suck(int start){
	if(text_buf.length()-start<=skin->char_max){
		text_rows.append(text_buf.mid(start,skin->char_max));
		return -1;
	}
	int i=skin->char_max;
	while(start+i<text_buf.length()&&ZText::getStringWidth(font_m,text_buf.mid(start,i))<=skin->row_max_pix){
		i++;
	}
	text_rows.append(text_buf.mid(start,i-1));
	return start+i-1;	
}
void U2Panel::text_genePos(){
	
	if(text_rows.count()==0){
		text_row_ptr=0;
		text_col_ptr=0;
		return;
	}
	int tp_ptr=text_ptr;
	int i=0;
	text_col_ptr=tp_ptr;
	tp_ptr-=text_rows[i].length();
	while(tp_ptr>0){
		i++;
		text_col_ptr=tp_ptr;
		tp_ptr-=text_rows[i].length();
	}
	text_row_ptr=i;
	text_adjust_view();
	text_curpix_x=ZText::getStringWidth(font_m,text_rows[text_row_ptr].left(text_col_ptr))+skin->cursor_adjust_x;
	text_curpix_y=skin->text_pix_btl*(text_row_ptr-window_top)+skin->cursor_adjust_y;

}
void U2Panel::text_adjust_view(){
	
	if(text_row_ptr+1>skin->max_row_count){
		//超出底线
		cout<<"@1"<<endl;
		window_top=text_row_ptr-skin->max_row_count+1;
	}else if(text_row_ptr<window_top){
		window_top=text_row_ptr;
	}
	
}

void U2Panel::doAbout(){
	aboutDialogShows=TRUE;
	menuShows=FALSE;
	repaint();
}
void U2Panel::doTheme(){
	cout<<"Theme show is invoked!"<<endl;
	themeDialogShows=TRUE;
	stopCursorTimer();
}
void U2Panel::themeSelected(){
	themeDialogShows=FALSE;
	ZConfig cfg1("/ezxlocal/MarsInput/theme/theme.cfg");
	cfg1.writeEntry("Theme","Name",themeAvilable[themeIndex]);
	cfg1.flush();
	initSkin();
	text_ptr=0;
	text_order();
	text_genePos();
	startCursorTimer();
}
void U2Panel::doCopy(){
	switch(copy_mode){
		case 0:
			copy_start=text_ptr;
			copy_mode++;
			break;
		case 1:
			copy_end=text_ptr;
			if(copy_end>copy_start)
				clipBd=text_buf.mid(copy_start,copy_end);
			else 
				clipBd=text_buf.mid(copy_end,copy_start);
			//写入文件中去
			QFile f(cache_file);
			if(f.open(IO_WriteOnly)){
				QTextStream sm(&f);
				sm<<clipBd.utf8()<<endl;
			}
			f.close();
			copy_mode=0;
			break;
	}
}
void U2Panel::doPaste(){
	/*
	QFile ff(cache_file);
	QString toread;
	QCString cs;
	if(ff.open(IO_ReadOnly)){
		QTextStream smm(&ff);
		smm>>cs;
	}
	ff.close();

	toread=QString::fromUtf8(cs);
	*/
	text_buf.insert(text_ptr,clipBd);
	text_ptr+=clipBd.length();
	text_order();
	text_genePos();
	copy_mode=0;
}
void U2Panel::initClipBoard(){
cout<<"initClipBoard"<<endl;

	QFile ff(cache_file);
	
	QCString cs;
	if(ff.open(IO_ReadOnly)){
		QTextStream smm(&ff);
		smm>>cs;
		clipBd=QString::fromUtf8(cs);
	}
	ff.close();
	
}
