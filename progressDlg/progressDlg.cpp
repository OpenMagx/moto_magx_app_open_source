#include <ZApplication.h>
#include <ZMessageDlg.h>
#include <ZNoticeDlg.h>

#include <qtextcodec.h>

#include "progressDlg.h"

using namespace std;

//#define ctr QString::fromLocal8Bit


QString ctr(const char*ChineseString)
{
	QTextCodec* gbk_codec = QTextCodec::codecForName("UTF-8");
	return gbk_codec->toUnicode(ChineseString);
} 


progressCmd::progressCmd(const char* cmd)
{
	m_ret = 256;
	m_finishState = false;
	m_resultStr = "None";
	m_cmd = "";
	
	bzero(command, 1024);
	if (cmd!=NULL) {
		strcpy(command, cmd);
		m_cmd = QString(cmd);		
	} else {
		return;
	}	
}
progressCmd::~progressCmd()
{
	bzero(command, 1024);
	//printf(" ======= cmd over ==============\n");
}
bool progressCmd::isFinish()
{	
	return m_finishState;
}
int progressCmd::getRet()
{
	return m_ret;
}
QString progressCmd::getResultText()
{
	return m_resultStr;
}
QString progressCmd::getCmd()
{
	return m_cmd;
}
void progressCmd::run()
{
	if (command[0]=='\0')
		return;
	printf("Debug: system(%s)\n", command);
	strcat(command, " > /tmp/exec_log.txt 2>&1");
	m_ret = system(command);
	m_ret >>= 8;
	
	if ( m_ret!=0 )
	{
		FILE *fp=fopen("/tmp/exec_log.txt", "rb");
		int flen=0;
		if (fp!=NULL)
		{
			fseek(fp, 0, SEEK_END);
			flen=ftell(fp);
			if (flen>0)
			{
				char buffer[flen+1];
				memset(buffer, '\n', flen);
				rewind(fp);
				fread(buffer, 1, flen, fp);
				m_resultStr = ctr(buffer);
			}
			fclose(fp);	
			system("rm -f /tmp/exec_log.txt");
		}	
	}
	//printf("=========== system ove ===========\n");
	m_finishState = true;
}

progressDlg::progressDlg(QString &title, QString &text, const char* cmd, bool isShowPopInfo, int dlgType)
			: ZPopup((ZPopup::POPUP_TYPE_E)dlgType)
{
	this->setTitle(title);
	this->setInstructText(text);
	this->setTitleIcon("info_pop.gif");
	
	popInfoState = isShowPopInfo;
	m_hideState = false;
	m_step = 0;
	ret = 255;
	m_dlgType = dlgType;
	if( m_dlgType == 0 ) 
		popInfoState = true;

	m_progressCmd = new progressCmd(cmd);
	
	m_md = new ZMeterModule(8, this);
	m_md->setAlignment(ZMeterModule::TOP);
	m_mt = m_md->getMeter();
	m_mt->setAutoResize(true);
	
	this->insertChild( (ZWidget*)m_md );
	
	if( m_dlgType == 0 ) {
		ZSoftKey *softKey = this->getSoftKey();
		softKey->setText(ZSoftKey::LEFT, tr("TXT_RID_SOFTKEY_HIDE", "Hide"));
		softKey->setClickedSlot( ZSoftKey::LEFT, this, SLOT ( slotHide() ) );
		softKey->disableClickedSlot( ZSoftKey::RIGHT);	
	}		
	
	timer = new QTimer(this);
	connect( timer, SIGNAL(timeout()), this, SLOT( slotTimerEvent()));
	timer->start(500);
	
	m_progressCmd->start();	
}
progressDlg::~progressDlg()
{
	if( m_progressCmd != NULL ) {
		m_progressCmd->wait();
		delete m_progressCmd;
		m_progressCmd = NULL;
	}	
	if( timer->isActive() ) {
		timer->stop();
		delete timer;
		timer = NULL;
	}
}
void progressDlg::slotHide()
{
	m_hideState = true;
	qApp->processEvents();		
	this->hide();
	qApp->processEvents();	
}
void progressDlg::slotTimerEvent()
{
	//printf("====== slotTimerEvent() ======\n");
	if( !m_progressCmd->isFinish() ) 
	{
		//printf("====== %d\n", m_step);
		
		if( m_step <= 8 ) {
			m_mt->setProgress(m_step);	
		} else {
			m_step = 0;
			m_mt->setProgress(m_step);
		}
		m_step++;
		qApp->processEvents();		
	}
	else
	{
		slotDlgOver();	
	}
}
void progressDlg::slotDlgOver()
{
	//if( popInfoState ) {
	//	this->show();
	//} else {	
	//	this->hide();
	//}	
	
	if( timer->isActive() ) {
		timer->stop();		
	}	
	
	ret = m_progressCmd->getRet();
	
	if( ret != 0 ) {
		QString title = QString("Error: %1").arg(ret);
		QString text = m_progressCmd->getResultText();
		
		ZMessageDlg *dlg = new ZMessageDlg(title, text, (ZMessageDlg::MessageDlgType)2);
		dlg->setTitleIcon("error_pop.bmp");
		dlg->exec();
		delete dlg;	
		dlg = NULL;			
	} else {
		if( popInfoState ) {
			if( m_hideState ) {
				QString title = QString("OK");
				QString text = QString("%1 Ok").arg( m_progressCmd->getCmd() );
				ZMessageDlg *dlg = new ZMessageDlg(title, text, (ZMessageDlg::MessageDlgType)2);
				dlg->show();
				dlg->exec();
				delete dlg;	
				dlg = NULL;	
			
			} else
			{
				QString text = QString("%1 Ok").arg( m_progressCmd->getCmd() );
				ZNoticeDlg *dlg = new ZNoticeDlg( ZNoticeDlg::Success, 2000, "", text );
				dlg->exec();
				//dlg->show();
				delete dlg;
				dlg = NULL;	
			}	
		}
	}
	
	m_progressCmd->wait();
	delete m_progressCmd;
	m_progressCmd = NULL;	
	
	slotQuit();
}
void progressDlg::slotQuit()
{
	qApp->quit();
}
	


int main( int argc, char **argv )
{
	if( argc < 4 ) {
		printf("progressDlg <title> <text> <cmd> \n"
				"progressDlg for zn5/e8 by wanggjghost\n");
			exit(0);	
	}
	
	ZApplication* a = new ZApplication( argc, argv );
	
	QString title = ctr(argv[1]);
	QString text = ctr(argv[2]);
	
	char cmd[1024];
	sprintf(cmd, "%s", argv[3]);
	
	progressDlg *dlg = new progressDlg(title, text, cmd, true, 1);
	dlg->exec();
	int ret = dlg->ret;
	delete dlg;
	dlg = NULL;
	delete a;
	a = NULL;
	return ret;	
}
	

