#ifndef ZICONVIEW_H
#define ZICONVIEW_H

#include <qscrollview.h>
#include <qiconset.h>
#include <qstring.h>
#include <qrect.h>
#include <qpoint.h>
#include <qsize.h>
#include <qfont.h>
#include <qlist.h>
#include <qbitmap.h>
#include <qmodules.h>

#include "ZSkinService.h"
#include "ZText.h"
#include "ZScrollPanel.h"


class ZIconView;
class QFontMetrics;
class QPainter;
class QMimeSource;
class QMouseEvent;
class QKeyEvent;
class QFocusEvent;
class QShowEvent;

class ZIconViewPrivate;
class ZIconViewItem;

struct ZIVItemContainer;

class ZIconViewItem : public Qt
{
public:
    enum MARKTYPE {MARK_NONE, MARK_CHECKBOX, MARK_RADIOBOX};


    ZIconViewItem();

    ZIconViewItem( ZIconView *parent );

    ZIconViewItem( ZIconView *parent, ZIconViewItem *after );

    ZIconViewItem( ZIconView *parent, const QString &text );

    ZIconViewItem( ZIconView *parent, ZIconViewItem *after, const QString &text );

    ZIconViewItem( ZIconView *parent, const QString &text, const QPixmap &icon );

    ZIconViewItem( ZIconView *parent, ZIconViewItem *after, const QString &text, const QPixmap &icon );

    virtual ~ZIconViewItem();

    void setType(MARKTYPE markType = MARK_NONE, bool isOverlayer = false);

    MARKTYPE getItemType() const;

    virtual void setText( const QString &text );

    virtual QString text() const;

    virtual void setPixmap( const QPixmap &icon );

    virtual QPixmap *pixmap() const;

    virtual void setKey( const QString &k );

    virtual QString key() const;

    virtual int compare( ZIconViewItem *i ) const;

    void setView(ZIconView* newView);

    ZIconView *iconView() const;

    ZIconViewItem *prevItem() const;

    ZIconViewItem *nextItem() const;

    int index() const;

    virtual void repaint();

    QRect rect() const;

    int x() const;

    int y() const;

    int width() const;

    int height() const;

    QSize size() const;

    QPoint pos() const;

    QRect textRect( bool relative = TRUE ) const;

    QRect pixmapRect( bool relative = TRUE ) const;

public:
    void showDrmIndicator(bool show = TRUE);

    bool isChecked() const;

    void setActive();

    void setPartialChecked(bool partial);

    bool partialChecked() const;

     void setDrmImage(const QPixmap& drm);

     const QPixmap& getDrmImage() const;

    void setEnabled(bool enabled);

    bool enabled() const ;

     void setZStyle(ZSkinService::WidgetClsID style);

     ZSkinService::WidgetClsID getZStyle() const;

     void setPixmapRectToMax(bool max = TRUE);

    void setReservedData(unsigned int rsvData);

    unsigned int getReservedData();
 
public:
    void clear(){}
    void setFont( const  QFont& ){}

    QFont font() const{return QFont();}

    virtual void drawCheckboxButton(QPainter *,int,int){}

    virtual void drawRadioboxButton(QPainter *,int,int){}

    virtual void setSelected( bool s, bool cb );

    virtual void setSelected( bool s );

    virtual void setSelectable(bool s );

    bool isSelected() const;

    bool isSelectable() const;

    enum ITEMALIGN{ ALIGN_IMAGE, ALIGN_TEXT};

    void setAlign(ITEMALIGN, int){}

    int align(ITEMALIGN) const {return Qt::AlignCenter;}

    virtual void setText( const QString &text, bool recalc, bool redraw = TRUE );

    virtual void setPixmap( const QPixmap &icon, bool recalc, bool redraw = TRUE );

    bool contains( QPoint pnt ) const;

    bool intersects( QRect r ) const;

    void setTextRect( const QRect &r );

    void setPixmapRect( const QRect &r );

protected:

    virtual void calcRect();

    virtual void paintItem( QPainter *p, const QColorGroup & ){if(p) paintItem(*p);}

    virtual void paintItem( QPainter& p);

    void setItemRect( const QRect &r );

    virtual void move( int x, int y );

    virtual void moveBy( int dx, int dy );

    virtual void move( const QPoint &pnt );

    virtual void moveBy( const QPoint &pnt );

private:

    void init( ZIconViewItem *after = 0);
    void checkRect();
    void drawPixmap(QPainter *p, QRect rect, QPixmap* pix, int align);
    QString truncate(QString& str, int len, uint width, QFont& font, QString ellpsis = NULL);
   
    bool canHasFocus() const;
    ZSkinBase::SelectionState getSelectionState() const;
    void setExtraSpace(int space){extraSpace = space;}
private:

    ZIconView *view;
    QString itemText, itemKey;
    QPixmap *itemIcon;
    ZIconViewItem *prev, *next;

    QRect itemRect, itemTextRect, itemIconRect;

    enum ToggleState { OFF, NOCHANGE, ON};
    short stat;
    short extraSpace;

    uint reserved;

    short markType;
 
    short mAlignText;    
    short mAlignImage;    

    QPixmap* drmImage;

    ZSkinService::WidgetClsID itemClsId;

    uint selected : 1;
    uint selectable : 1;
    uint dirty : 1;

    uint pixRectExtend : 1;
    uint own_AlignText : 1;    
    uint own_AlignImage : 1;           
    uint own_drm : 1;
    uint own_style:1;

    uint isShowDrm : 1;
    uint mEnabled : 1;
    uint isWarpable : 1;
    uint mPartialChecked : 1;

    struct ZIVItemContainer *container1, *container2;


    friend class ZIconView;
};


class ZIconView : public ZScrollPanel
{
    friend class ZIconViewItem;
    friend class ZIconViewPrivate;

    Q_OBJECT
public:

    enum ResizeMode {
	Fixed = 0,
	Adjust
    };

    ZIconView( QWidget *parent = 0, const char *name = 0, WFlags f = 0,
            int initCount = 20, int initStep = 10,
            const ZSkinService::WidgetClsID clsId = ZSkinService::clsZIconView1);

    virtual ~ZIconView();


    virtual void insertItem( ZIconViewItem *item, ZIconViewItem *after = 0L );

    virtual void takeItem( ZIconViewItem *item );

    int index( const ZIconViewItem *item ) const;


    ZIconViewItem *item(int i) const;

    ZIconViewItem *firstItem() const;

    ZIconViewItem *lastItem() const;

    ZIconViewItem *currentItem() const;

    virtual void setCurrentItem( ZIconViewItem *item );

    uint count() const;

    virtual void showEvent( QShowEvent * );

    ZIconViewItem *findItem( const QPoint &pos ) const;

    ZIconViewItem *findItem( const QString &text ) const;

    virtual void repaintItem( ZIconViewItem *item );

    void ensureItemVisible( ZIconViewItem *item );

    ZIconViewItem* findFirstVisibleItem( const QRect &r ) const;

    ZIconViewItem* findLastVisibleItem( const QRect &r ) const;

    virtual void clear();

    QSize maxmumSizeHint();

    QSize minimumSizeHint() const;

    QSizePolicy sizePolicy() const;

    void setSorting( bool sort, bool ascending = TRUE );

    bool sorting() const;

    bool sortDirection() const;

    virtual void sort( bool ascending = TRUE );

    bool eventFilter( QObject * o, QEvent * );

public:

    void updateSkin();

    void checkItem(int index, bool select);

     void checkItem(ZIconViewItem* item, bool select);

     bool itemChecked(ZIconViewItem* item) const;

     bool itemChecked(int index);

     QList<ZIconViewItem>* itemsChecked();

     void removeItem(int index);

     void setDrmImage(const QPixmap& drm);

     const QPixmap& getDrmImage();

    void insertItemAtHead( ZIconViewItem *item);

    void setZItemStyle(ZSkinService::WidgetClsID style);

    ZSkinService::WidgetClsID getZItemStyle() const;

    void setLayout(uint row, uint column, bool scrollbar = TRUE);

    void setItemSize(QSize size);

    QSize getItemSize() const;

    QSize iconAreaSize();

    bool isShowLabel() const;

    void setShowLabel(bool show);

    QSize sizeHint() const;

    void setZBorder( WIDGET_BORDER_INFO_T borderItems[StateCount]);

     QSize calcItemSizeByIconSize(QSize size);

     void setIconStretchPolicy(PIXMAP_STRETCH_POLICY_E type);

     PIXMAP_STRETCH_POLICY_E getIconStretchPolicy() const;

     void enableModalEditing(bool enable) ;

     void enableMarquee(bool enable);

     bool marqueeEnabled() const;

     typedef void (*DeleteItemCallBack)(ZIconViewItem*);

     void setDeleteItemCallBackFunction(DeleteItemCallBack func);

     DeleteItemCallBack getDeleteItemCallBackFunction() const ;

     QRect itemRect(ZIconViewItem* item);

public:

    void setVScrollBarMode(QScrollView::ScrollBarMode mode){ZScrollPanel::setVScrollBarMode((ZScrollPanel::ScrollBarMode)mode);}

    int frameWidth(){return 0;}

    int getPoolStep(){return 0;}

    void setPoolStep(int){}

    ZIconViewItem* newItem(){return new ZIconViewItem(this);}

    ZIconViewItem* newItem(ZIconViewItem *after, const QString &text)
    {return new ZIconViewItem(this, after, text);}

    ZIconViewItem* newItem(ZIconViewItem *after, const QString &text, const QPixmap &icon)
    {return new ZIconViewItem(this, after, text, icon);}

    virtual void setFont( const QFont & ){}

    void setHighlight(bool){}

    bool getHighlight(){return FALSE;}

    enum Arrangement {
	LeftToRight = 0,
	TopToBottom
    };

    virtual void setArrangement( Arrangement){}

    Arrangement arrangement() const{return LeftToRight;}

    virtual void setResizeMode( ResizeMode am );

    ResizeMode resizeMode() const;

    enum ItemTextPos {
	Bottom = 0,
	Right
    };

    virtual void setItemTextPos( ItemTextPos ){}

    ItemTextPos itemTextPos() const {return Bottom;}

    virtual void setItemTextBackground( const QBrush & ){}

    QBrush itemTextBackground() const {return QBrush();}

    virtual void setItemsMovable( bool){}

    bool itemsMovable()const{return true;}

    virtual void setWordWrapIconText( bool){}

    bool wordWrapIconText() const{return true;}

    virtual void setAutoArrange( bool b );

    bool autoArrange() const;

    virtual void setGridX( int){}

    virtual void setGridY( int){}

    int gridX() const{return -1;}

    int gridY() const{return -1;}

    virtual void setMaxItemWidth( int){}

    int maxItemWidth() const{return 200;}

    virtual void setMaxItemTextLength( int){}

    int maxItemTextLength() const{return 255;}

    void setItemSizeFixed(bool fixedSize = TRUE){}

    bool isItemSizeFixed() const{return TRUE;}

    enum SelectionMode {
	Single = 0,
	Multi,
	Extended,
	NoSelection
    };

    virtual void setSelectionMode( SelectionMode){}

    SelectionMode selectionMode() const {return Single;}

    virtual void selectAll( bool ){}

    virtual void clearSelection(){}

    virtual void invertSelection(){}

    virtual void setSelected( ZIconViewItem *item, bool s, bool cb = FALSE );


public slots:
    virtual void arrangeItemsInGrid( const QSize &grid, bool update = TRUE );

    virtual void arrangeItemsInGrid( bool update = TRUE );

    virtual void setContentsPos( int x, int y );

    virtual void updateContents();

    virtual void ensureCurrentVisible();

signals:
    void selectionChanged();

    void selectionChanged( ZIconViewItem *item );

    void currentChanged( ZIconViewItem *item );

    void clicked( ZIconViewItem * );

    void clicked( ZIconViewItem *, const QPoint & );

    void pressed( ZIconViewItem * );

    void pressed( ZIconViewItem *, const QPoint & );

    void doubleClicked( ZIconViewItem *item );

    void returnPressed( ZIconViewItem *item );

    void rightButtonClicked( ZIconViewItem* item, const QPoint& pos );

    void rightButtonPressed( ZIconViewItem* item, const QPoint& pos );

    void mouseButtonPressed( int button, ZIconViewItem* item, const QPoint& pos );

    void mouseButtonClicked( int button, ZIconViewItem* item, const QPoint& pos );

    void moved();

    void onItem( ZIconViewItem *item );

    void onViewport();

protected slots:
    virtual void adjustItems();
    virtual void slotUpdate();

private slots:
    void movedContents( int dx, int dy );

    void slotWaitWrapFinished();

protected:

    virtual void ZIconView::viewportResizeEvent( QResizeEvent* e);

    virtual void drawContents( QPainter *p, int cx, int cy, int cw, int ch ){}

    void        keyReleaseEvent( QKeyEvent *e );

    void viewportPaintEvent( QPaintEvent * event);
                                                                                                                       
    virtual void setPalette( const QPalette & ){updateSkin();update();}

    virtual void resizeEvent( QResizeEvent* e );

    virtual void keyPressEvent( QKeyEvent *e );

    virtual void focusInEvent( QFocusEvent *e );

    virtual void focusOutEvent( QFocusEvent *e );

    virtual void enterEvent( QEvent *e );

    virtual void insertInGrid( ZIconViewItem *item );

    void emitSelectionChanged( ZIconViewItem * i = 0 );

    void emitRenamed( ZIconViewItem *item );

    ZIconViewItem *makeRowLayout( ZIconViewItem *begin, int &y );

    ZIconViewItem *makeRowLayout( ZIconViewItem *begin, int y, int count, bool sb );

private:
    QSize calcItemSize();

    int scrollStep(int step);

    int handleOmgKey(int key, int step);
    void omgWrap(bool next, bool& bDone, int& actualStep);

    void drawContents( QPainter* );
    void handleItemChange( ZIconViewItem *old, bool shift, bool control );

    int calcGridNum( int w, int x ) const;
    ZIconViewItem *rowBegin( ZIconViewItem *item ) const;
    void updateItemContainer( ZIconViewItem *item );
    void appendItemContainer();
    void rebuildContainers();

    void selectBtns(ZIconViewItem* it);
    ZSkinBase* getItemSkin(SelectionState state);
    ZSkinBase* getImageContainerSkin(SelectionState state);

    QPixmap& markImage(SelectionState state, bool single, bool partial) const;

    QFont& getItemFont(SelectionState state) const;
    QColor textColor(SelectionState) const;
    int textAlign(SelectionState) const;

    ZMarqueeText* marquee() const;
    void startMarquee();

    ZIconViewPrivate *d;

private:
    ZIconView( const ZIconView & );
    ZIconView& operator=( const ZIconView & );
};


#endif 
