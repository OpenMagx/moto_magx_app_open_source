#include "citySelectDlg.h"

extern "C" QString ctr(const char*ChineseString);

QString CitySelectDlg::getAppDir()
{
    QString tmp = QString(qApp->argv()[0]);
    int i = tmp.findRev("/");
    tmp.remove(i+1,tmp.length()-1);
    return tmp;
}


QString CitySelectDlg::ctr(const char*ChineseString)
{
	QTextCodec* gbkstr = QTextCodec::codecForName("UTF-8");
	return gbkstr->toUnicode(ChineseString);
}

CitySelectDlg::CitySelectDlg(QString str1,QString str2,QString str3):ZPopup()
{
    setTitle(str1);
    listBox = new ZListBox("%I%M",this);
    
    // insert menu items with images from SysRegistry
    ZConfig config ( getAppDir() + "cities.ini", false );
    QStringList grouplist;
    config.getGroupsKeyList ( grouplist );
    QString cityCode = "";
    
    for ( QStringList::Iterator it = grouplist.begin(); it != grouplist.end(); ++it ) 
    {
        cityCode = config.readEntry(*it, "Code", "");
        City *city = new City(listBox);
        qDebug(*it);
        qDebug(cityCode);
        city->setName(*it);
        city->setCode(cityCode);
        
        listBox->insertItem(city);
        city->appendSubItem(1,ctr(city->getName()));
        
    }
    
    insertChild(listBox);
    setSoftkeyText(str2,str3);
    connect(this,SIGNAL(leftSoftkeyClicked()),this,SLOT(slotSelected()));
    connect(listBox,SIGNAL(returnPressed(ZSettingItem *)),this,SLOT(slotItemClicked(ZSettingItem *)));
    
}

CitySelectDlg::~CitySelectDlg()
{
    delete listBox;
}

void CitySelectDlg::slotItemClicked(ZSettingItem *item)
{
    City *citem = (City *)item;
    code = citem->getCode();
    accept();
}

void CitySelectDlg::slotSelected()
{
    City *item = (City *)listBox->item(listBox->currentItem());
    code = item->getCode();
}

