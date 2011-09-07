#ifndef __CITY_SELECT_DLG_H__
#define __CITY_SELECT_DLG_H__

#include <ZPopup.h>
#include <ZListBox.h>
#include <ZApplication.h>
#include <ZConfig.h>
#include <qstring.h>
#include <qstringlist.h>
#include <qtextcodec.h>

class City : public ZSettingItem
{
    public:
    City(ZListBox* container = 0, const QString itemType = NULL):ZSettingItem(container,itemType)
    {
    }
    
    inline void setName(QString cityName)
    {
        name = cityName;
    }
    
    inline QString getName()
    {
        return name;
    }
    
    inline void setCode(QString cityCode)
    {
        code = cityCode;
    }
   
    
    inline QString getCode()
    {
        return code;
    }
    
    private:
    QString name;
    QString code;
};

class CitySelectDlg : public ZPopup
{
    Q_OBJECT
    public:
        CitySelectDlg(QString str1,QString str2,QString str3);
        ~CitySelectDlg();
        inline QString getCityCode()
        {
            return code;
        }
    private slots:
        void slotSelected();
        void slotItemClicked(ZSettingItem *item);
    private:
        ZListBox *listBox;
        QString code;
        
        QString getAppDir();
        QString ctr(const char*ChineseString);
};

#endif
