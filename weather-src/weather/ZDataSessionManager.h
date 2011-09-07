#if !defined(__ZDATASESSIONMANAGER_H__)
#define __ZDATASESSIONMANAGER_H__

#include <qwssocket_qws.h>

/*
 * As a warning, the NAPI API does not appear to be the least bit
 * thread-safe -- it stores its state in global variables.
 */

/*
 * getProfileNamebySelect() presents a dialog box to the user
 * displaying the possible network connection profiles.  It will
 * block for the lifetime of the dialog box.
 *
 * The name_inout parameter may contain the name of the profile
 * that should be initially selected, and will contain the name of
 * the selected profile on return.
 *
 * Return value:
 *	0	Success, name_inout contains the string name of the
 *		chosen profile.
 *	-100	User clicked "Cancel"
 */
int getProfileNamebySelect(QString &name_inout);


/* These names are all educated guesses from perusing a disassembly */
enum NAPI_RESULT_T {
	NAPI_ERROR_NOT_INITIALIZED = -1,
	NAPI_ERROR_INVALID_PROFILE = -2,
	NAPI_ERROR_ALREADY_INITIALIZED = -3,
	NAPI_ERROR_DSM_SOCKET = -4,
	NAPI_ERROR_NAME_TOO_LONG = -5,
	NAPI_ERROR_DSM_RESPONSE = -6,
	NAPI_ERROR_BIND_FAILED = -8,
	NAPI_ERROR_LINK_REMOVED = -100,
};


/*
 * ZLinkInfo is passed to slot methods of ZDataSessionManager
 * and describes a network link.
 */

struct ZLinkInfo {
	/* Unknown */
	int	li_flags;

	/* li_linkid is a number [1..15] describing the connection */
	int	li_linkid;

	/* li_dest is the string name of the APN, for GPRS connections */
	char	li_dest[96];
};

/* ZStateDialog seems to be internal to this module */
class ZStateDialog;

class ZDataSessionManager : public QWSSocket {
	Q_OBJECT
public:
	ZDataSessionManager(QObject *parent = NULL,
			    char const *obj_name = NULL);
	virtual ~ZDataSessionManager();

	/*
	 * init() opens a connection to the SYStapi/dsm process.
	 *
	 * The boolean parameter decides whether notifications are
	 * sent for *all* link events vs. just events initiated by
	 * this application.
	 *
	 * Return value:
	 *	>=0	Success, the value is the notification file
	 *		descriptor, which this class has already
	 *		setu up event handlers for.
	 *	<0	Failure, the value is a NAPI_RESULT_T.
	 */
	int init(bool notifyAll = false);

	/*
	 * openLink() tries to connect to a data service profile,
	 * and displays a message box on the screen apprising the
	 * user of this.
	 *
	 * It will return before the connection is complete.  To
	 * find out when the connection completes, and therefore
	 * when the dialog goes away or it is possible to use the
	 * link, use the connected and openFailed slots.
	 *
	 * Return value:
	 *	>0	Success, the value is the link ID of the
	 *		connection.
	 *	<0	Failure, the value is a NAPI_RESULT_T.
	 */
	int openLink(QString const &profilename);

	/*
	 * openLinkNoDialog() is otherwise identical to openLink(),
	 * but suppresses the message box.
	 */
	int openLinkNoDialog(QString const &profilename);

	int closeLink(int linkid);

	/*
	 * getDeviceInfo() retrieves parameters of an active connection.
	 *
	 * Return value:
	 *	0	Success, iface_out and ipaddr_out are filled in.
	 *	<0	Failure, the value is a NAPI_RESULT_T.
	 */
	int getDeviceInfo(int linkid,
			  QString &iface_out, unsigned long *ipaddr_out);

	/*
	 * bindSocket2Link() will determine the interface parameters
	 * of the given data connection, and will setsockopt() the
	 * given socket so that it may only operate over that link.
	 */
	int bindSocket2Link(int fd, int linkid);


	/* There don't appear to be any users of these methods. */
	int attach(int, QString const&);
	int hold(int, QString const&);
	int drop(int, QString const&);


	int			m_napifd38;
	int			m_linkid3c;
	ZStateDialog		*m_dialog40;

signals:
	void connected(int linkid, ZLinkInfo&);
	void openFailed(int, unsigned short, unsigned short);
	void broken(int linkid, ZLinkInfo&);

public slots:
	/*
	 * This is for cancelation of dialog-oriented connections.
	 * It will invoke openFailed().
	 */
	void slotCancelBtnClicked();

	/* These appear to be internal slots for the DSM socket */
	void slotReadIndicator();
	void slotLoseConnection();
};


#endif  /* !defined(__ZDATASESSIONMANAGER_H__) */
