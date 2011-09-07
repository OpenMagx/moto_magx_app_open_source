#ifndef _Z_DATA_SESSION_MANAGER_
#define _Z_DATA_SESSION_MANAGER_

#ifndef __cplusplus
#error "This is a C++ header file;it requires C++ to compile."
#endif

#include <qwssocket_qws.h>
#include <qstring.h>

int     getProfileIfNoFound( QString & profileName );
int     getProfileNamebySelect( QString& profileName );
int     createProfilebyUser( QString & profileName );
void getDefaultProfileName( QString& qstrProfileName );

class   ZStateDialog;
class   ZLinkInfo;

/**
 * The ZDataSessionManager class encapsulates the Network Application 
 * Programming Interface in EZX, to provide QT application easy way
 * to use data service.
 *
 * @code
 * ZDataSessionManager * d = new ZDataSessionManager();
 * d->init();
 * @endcode
 *
 */
class ZDataSessionManager :
    public QWSSocket
{
    Q_OBJECT
public:

    /**
     * Constructor of ZDataSessionManager.
     */
    ZDataSessionManager(
        QObject*        parent = 0,
        const char*     name = 0 );

    /**
     * Destructor of ZDataSessionManager.
     */
    ~ZDataSessionManager( void );

    /**
     * initialize communication channel with server
     *
     * @param beMonitor shall we monitor all connected event
     *
     * @return on success return 0, otherwize return negative value
     */
    int     init( bool beMonitor = false );

    /**
     * start data connection with a specific profile with dialog
     */
    int     openLink( const QString& profileName );

    /**
     * start data connection with a specific profile without dialog
     */
    int     openLinkNoDialog( const QString& profileName );

    /**
     * attach to a connected link
     *
     * @param linkType NAPI_LINK_GPRS or NAPI_LINK_CSD
     * @param linkName APN (for GPRS) or Dial number (for CSD)
     */
    int     attach(
                int             linkType,
                const QString&  linkName );

    /**
     * hold a link
     *
     * @param linkType NAPI_LINK_GPRS or NAPI_LINK_CSD
     * @param linkName APN (for GPRS) or Dial number (for CSD)
     */
    int     hold(
                int             linkType,
                const QString&  linkName );

    /**
     * drop a link
     *
     * @param linkType NAPI_LINK_GPRS or NAPI_LINK_CSD
     * @param linkName APN (for GPRS) or Dial number (for CSD)
     */
    int     drop(
                int             linkType,
                const QString&  linkName );

    /**
     * bind a socket to the network device pointed by the linkid
     *
     * @param qsocket socket fd of AF_INET type
     * @param linkid bind to which network device
     */
    int     bindSocket2Link(
                int sockfd,
                int linkid );

    /**
     * close a link
     *
     * @param linkid the logical link to close
     */
    int     closeLink( int linkid );

    /**
     * get device name and local IP address associated with a link id.
     */
    int     getDeviceInfo(
                int             linkid,
                QString&        deviceName,
                unsigned long*  localIpaddr );

signals:

    /**
     * Emitted when link turn into connected state
     *
     * @param linkid which link get connected
     * @param linkInfo link details for this link
     *
     * @note linkid is zero for un-solicited indicator
     */
    void    connected(
                int         linkid,
                ZLinkInfo&  linkInfo );

    /**
     * Emitted when open link request failed
     *
     * @param linkid identify the failed request
     * @param maincode main fail reason
     * @param subcode sub fail reason
     */
    void    openFailed(
                int             linkid,
                unsigned short  maincode,
                unsigned short  subcode );

    /**
     * Emitted when a connected link break unexpectedly
     *
     * @param linkid which link is broken
     * @param linkInfo link details for this link
     */
    void    broken(
                int         linkid,
                ZLinkInfo&  linkInfo );

    private slots : void slotReadIndicator();

    void    slotLoseConnection( void );

    void    slotCancelBtnClicked( void );

    //void slotHideBtnClicked();
private:
    int             fd_napi;            ///< socket fd to read indicator from dsm
    int             inCallingLinkid;    ///< the only link in calling&negotiation state
    ZStateDialog*   myDialog;           ///< state dialog to show state transition
};
#endif

