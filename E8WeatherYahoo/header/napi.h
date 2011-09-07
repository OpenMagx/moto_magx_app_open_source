#ifndef _NAPI_H_
#define _NAPI_H_

/**
 * @file napi.h
 * @brief This file defines network APIs on EzX platform 
 */
#include <netdb.h>
#include "EZX_TypeDefs.h"

#ifdef __cplusplus
extern "C"
{
#endif

#define NAPI_MAX_DEFAULT_PROFILE_NUMBER    15
#define NAPI_MAX_PROFILE_NUMBER            NAPI_GetMaxProfiles()

/* constants used by the definitions below */
#define NAPI_MAX_PHONE_NUMBER_LENGTH        44
#define NAPI_PPP_USER_NAME_LENGTH           32
#define NAPI_PPP_PASSWORD_LENGTH            32

#define NAPI_GPRS_APN_LENGTH                100
#define NAPI_GPRS_USER_NAME_LENGTH          100
#define NAPI_GPRS_PASSWORD_LENGTH           100

#define NAPI_PROFILE_OPERATOR_LOCKED        0x0001
#define NAPI_PROFILE_WAP_SERVICE            0x0002
#define NAPI_PROFILE_IPSEC_SETTING          0x0004
#define NAPI_PROFILE_DEFAULT_HOLD           0x0008
#define NAPI_PROFILE_ENABLE_SWITCH          0x0010
#define NAPI_PROFILE_PREFER_WIFI            0x0020
#define NAPI_PROFILE_WIFI_BGSCAN            0x0040

#define NAPI_MAX_LINK_NAME_LENGTH           NAPI_GPRS_APN_LENGTH
#define NAPI_MAX_PROFILE_NAME_LENGTH        64

#define NAPI_MAX_DOMAIN_LENGTH              100
#define NAPI_MAX_IFNAME_LENGTH              16

/* All the following possible types of links are supported */
/**
 *@def NAPI_LINK_GPRS
 *@brief Defines a GPRS physical link.
 */
#define NAPI_LINK_GPRS           1

/**
 *@def NAPI_LINK_CSD
 *@brief Defines a CSD physical link.
 */
#define NAPI_LINK_CSD            2

/**
 *@def NAPI_LINK_WIFI
 *@brief Defines a WiFi physical link.
 */
#define NAPI_LINK_WIFI           3

/**
 *@def NAPI_LINK_IPSEC
 *@brief Defines a IPSec physical link.
 */
#define NAPI_LINK_IPSEC          4

/*
 * The Max number of profile.
 */
#define  MAX_PROFILE_NUMBER   NAPI_MAX_PROFILE_NUMBER

/*
 * The profile definition, also directly mapped to the file structure
 */
typedef struct  _NAPI_PROFILE_S
{
    INT8    version[4];

    /* 
     * Known attributes:
     * #define NAPI_PROFILE_OPERATOR_LOCKED  0x0001
     * #define NAPI_PROFILE_WAP_SERVICE      0x0002
     * #define NAPI_PROFILE_IPSEC_SETTING    0x0004
     * #define NAPI_PROFILE_DEFAULT_HOLD     0x0008
     * #define NAPI_PROFILE_ENABLE_SWITCH    0x0010
     * #define NAPI_PROFILE_PREFER_WIFI      0x0020
     */
    UINT32  attrib;

    /* in TAPI, #define TAPI_CALL_NAME_LEN_T 100 */
    INT8    gprsApn[NAPI_GPRS_APN_LENGTH];
    INT8    gprsUser[NAPI_GPRS_USER_NAME_LENGTH];
    INT8    gprsPasswd[NAPI_GPRS_PASSWORD_LENGTH];
    UINT32  gprsLocalIP;        /* All IP addresses are in network byte order */
    UINT32  gprsLocalDNS1;
    UINT32  gprsLocalDNS2;
    UINT16  gprsLingerTimer;    /* Linger timer, in minutes */
   
    /* Each byte stands for: precedence, delay, reliability, peak and mean, in this order */
    UINT8   gprsMiniQoS[5];
    UINT8   gprsReqQoS[5];

    /* Additional QoS values for R99 network */
    /* 
     * e\Each short stands for: max up-link rate, max down-link rate,
     * guaranteed up-link rate and guaranteed down-link rate, in this order.
     */
    UINT16  gprsMiniDataRate[4];

    /*
     * Each short stands for: traffic class, delivery order, delivery error Shared Diagnostic Unit (SDU),
     * max SDU size, SDU error ratio, residual error ratio, transfer delay and
     * traffic prior in this order
     * For SDU error ratio, and residual error ratio, the actual value
     * is xE(-y), where x is derived from higher bytes, 
     * and y is derived from lower bytes
     */
    UINT16  gprsMiniExtraQos[8];

    UINT16  gprsReqDataRate[4];
    UINT16  gprsReqExtraQos[8];

    /*Index for Qos config*/
    UINT8   gprsQosIndex;
    
    /* in TAPI, #define TAPI_CALL_MAX_NUMBER_LENGTH (41+1) */
    INT8    DialNumber[NAPI_MAX_PHONE_NUMBER_LENGTH];
    INT8    csdUser[NAPI_PPP_USER_NAME_LENGTH];
    INT8    csdPasswd[NAPI_PPP_PASSWORD_LENGTH];
    UINT32  csdLocalIP;
    UINT32  csdLocalDNS1;
    UINT32  csdLocalDNS2;
    UINT16  csdLingerTimer;     /* Linger timer, in minutes */
    UINT8   postLogin;
    UINT8   csdSpeed;           /* Please refer to GSM 07.07 +CBST */

    INT8    csd2DialNumber[NAPI_MAX_PHONE_NUMBER_LENGTH];
    INT8    csd2User[NAPI_PPP_USER_NAME_LENGTH];
    INT8    csd2Passwd[NAPI_PPP_PASSWORD_LENGTH];
    UINT32  csd2LocalIP;
    UINT32  csd2LocalDNS1;
    UINT32  csd2LocalDNS2;
    UINT16  csd2LingerTimer;     /* Linger timer, in minutes */
    UINT8   csd2postLogin;
    UINT8   csd2Speed;           /* Please refer to GSM 07.07 +CBST */
    
    /* These informaton was stored by napi but used by other applications. */
#ifdef MAKE_DATANETWORK_PROXY_URL_ENABLE
    INT8    proxy1[ NAPI_MAX_DOMAIN_LENGTH ];
#else
    UINT32 proxy1;
#endif
    UINT16  port1;
    INT8    domain1[ NAPI_MAX_DOMAIN_LENGTH ];
    UINT8   serviceType1;
#ifdef MAKE_DATANETWORK_PROXY_URL_ENABLE
    INT8    proxy2[ NAPI_MAX_DOMAIN_LENGTH ];
#else
    UINT32 proxy2;
#endif
    UINT16  port2;
    INT8    domain2[ NAPI_MAX_DOMAIN_LENGTH ];
    UINT8   serviceType2;

    /* Remaining data are VPN settings, The VPN module will deal with this */
} NAPI_PROFILE_S;

/* The start of the VPN data in the profile */
#define NAPI_IPSEC_DATA_OFFSET  sizeof(NAPI_PROFILE_S)

/* Possible flags for state indicator categories */
/**
 *@def NAPI_ALL_STATE_FLAG
 *@brief All state indicators are sent to the application
 */
#define NAPI_ALL_STATE_FLAG                0x00000001

/**
 *@def NAPI_DETAIL_STATE_FLAG
 *@brief State indicators associated with an application's own request are sent to the application */
#define NAPI_DETAIL_STATE_FLAG             0x00000002

/**
 *@def NAPI_CONNECTED_FLAG
 *@brief Only the connected state indicator is sent to the application, whether or not the application initiated the call
 *
 */
#define NAPI_CONNECTED_FLAG                0x00000004

/* List for message ids */
#define NAPI_STATE_CALLING_MSGID          0x01
#define NAPI_STATE_NEGOTIATING_MSGID      0x02
#define NAPI_STATE_CONNECTED_MSGID        0x03
#define NAPI_STATE_DISCONNECTING_MSGID    0x04
#define NAPI_STATE_IDLE_MSGID             0x05

/* 
 * Result message, only sent to requestor.
 */
#define NAPI_RESULT_SUCCESS_MSGID         0x10
#define NAPI_RESULT_FAIL_MSGID            0x11

#define NAPI_LINK_BROKEN_MSGID            0x20

#define NAPI_LINK_SWITCH_MSGID            0x30

/*
 * Data from lower layer that need transparently sent to applcation. 
 * Raw data starts from NAPI_NOTIFY_MSG_S.linkName, plus next two
 * long words. Total length for Raw data is 108bytes.
 * macro NAPIRAWDATA is defined for easy using and understanding.
 * Raw data is sent to every requestor, i.e. one copy for each linkid.
 */
#define NAPI_RAW_DATA_MSGID               0x40

/* Possible flag bit indicators */
#define NAPI_LINK_IS_WAPSERVICE          0x02
#define NAPI_LINK_IS_TUNNELON            0x04
#define NAPI_LINK_IS_HOLD                0x08

/* Possible flags for maincode */
#define NAPI_MCODE_NO_MEMORY             0x0001
#define NAPI_MCODE_LINK_NOTEXIST         0x0002
#define NAPI_MCODE_LINKID_BUSY           0x0003
#define NAPI_MCODE_PROFILE_ERROR         0x0004
#define NAPI_MCODE_UNKNOWN_VER           0x0005
#define NAPI_MCODE_SYSTEM_BUSY           0x0006
#define NAPI_MCODE_GPRS_FEATUREOFF       0x0007
#define NAPI_MCODE_GPRS_DISABLED         0x0008
#define NAPI_MCODE_GPRS_NETERROR         0x0009
#define NAPI_MCODE_UNKNOWN_REASON        0x000A
#define NAPI_MCODE_OPERATION_CANCEL      0x000B
#define NAPI_MCODE_PPPD_QUIT             0x000C
#define NAPI_MCODE_OPLOCAL_CANCEL        0x000D
#define NAPI_MCODE_WIFI_ERROR            0x000E
#define NAPI_MCODE_IKE_ERROR             0x000F
#define NAPI_MCODE_FIXED_DIAL             0x0010

/* Possible flags for subcode */
/* Possible flags for subcode of IKE fail*/
#define NAPI_SUBCODE_IKE_ERROR_NORMAL         0x0000
#define NAPI_SUBCODE_IKE_ERROR_EAPSIM         0x0001



/* Network service type*/
#define NAPI_SERVICE_UNKNOWN                  0x0000
#define NAPI_SERVICE_WAP_CONN_LESS            0x0001
#define NAPI_SERVICE_WAP_CONN_ORIENTED        0x0002
#define NAPI_SERVICE_WAP_CONN_LESS_SECURE     0x0003
#define NAPI_SERVICE_WAP_CONN_ORIENTED_SECURE 0x0004
#define NAPI_SERVICE_WAP_HTTP                 0x0005
#define NAPI_SERVICE_WAP_HTTP_SECURE          0x0006

/* Indication type definition and related macros */
typedef struct  _NAPI_NOTIFY_MSG_S
{
    UINT16  msgId;
    UINT8   linkId;
    UINT8   linkType;
    INT8    linkName[NAPI_MAX_LINK_NAME_LENGTH];
    UINT32  phyId;
    union
    {

        /* Private data to indicate state */
        UINT32  flags;

        /* Private data to indicate result */
        struct
        {
            UINT16  maincode;
            UINT16  subcode;
        } resultIndi;

        /* BROKEN indicator, not used */
        UINT32  reserve;
    } u;
} NAPI_NOTIFY_MSG_S;
#define NAPIFLAGS      u.flags
#define NAPIMAINCODE   u.resultIndi.maincode
#define NAPISUBCODE    u.resultIndi.subcode
#define NAPIRAWDATA    linkName

typedef enum _NAPI_INFO_TYPE_E
{
    NAPI_DEVICE_NAME_EV,
    NAPI_MAC_ADDRESS_EV,
    NAPI_IP_ADDRESS_EV,
    NAPI_WIFI_AP_MAC_ADDRESS_EV
}NAPI_INFO_TYPE_E;

/*----------------------    RETURN VALUES     ----------------------*/
/**
 *@def NAPI_ERROR_NOTINIT
 *@brief NAPI not initialized
 */
#define NAPI_ERROR_NOTINIT    (-1)

/**
 *@def NAPI_ERROR_INVALID
 *@brief Incorrect parameter or unexpected null parameter
 */
#define NAPI_ERROR_INVALID    (-2)

/**
 *@def NAPI_ERROR_ALREADY
 *@brief NAPI already initialized
 */
#define NAPI_ERROR_ALREADY    (-3)

/**
 *@def NAPI_ERROR_SOCK
 *@brief Socket operation failed
 */
#define NAPI_ERROR_SOCK       (-4)

/**
 *@def NAPI_ERROR_NAMELENGTH
 *@brief Name exceeds length for a string parameter
 */
#define NAPI_ERROR_NAMELENGTH (-5)

/**
 *@def NAPI_ERROR_NORESOURCE
 *@brief Application cannot have more than 15 logical links
 */
#define NAPI_ERROR_NORESOURCE (-6)

/**
 *@def NAPI_ERROR_PROFILE
 *@brief Read or write profile error
 */
#define NAPI_ERROR_PROFILE    (-7)

/**
 *@def NAPI_ERROR_BIND
 *@brief Cannot bind socket to link
 */
#define NAPI_ERROR_BIND       (-8)

/**
 *@def NAPI_ERROR_MAXLIMITED
 *@brief the number of profile exceeds the max value
 */
#define NAPI_ERROR_MAXLIMITED (-9)

/**
 *@def NAPI_ERROR_OTHER
 *@brief Any other failure that is not one of the above
 */
#define NAPI_ERROR_OTHER      (-100)

/*----------------------      PROTOTYPES      ----------------------*/
/**
 *@fn INT32 NAPI_Init(UINT32 flag)
 *@brief Initialize NAPI 
 *@param flag reserved to 0 
 *@return >=0  This is the file descriptor. It is recommended that developers have the application add this file descriptor to a fd set, then select the fd set.
 *@return ::NAPI_ERROR_ALREADY NAPI Already initialized
 *@return ::NAPI_ERROR_SOCK Socket operation failed
 *@return ::NAPI_ERROR_OTHER Failed because of unknown reasons
 */
INT32   NAPI_Init( UINT32 flag );

/**
 *@fn INT32 NAPI_OpenLink(INT8 * profileName)
 *@brief Opens a link, with the parameters defined in the profile
 *@param profileName Indicates which profile to use for a link
 *@return [1, 15] Link id
 *@return ::NAPI_ERROR_NOTINIT NAPI Not yet initialized
 *@return ::NAPI_ERROR_INVALID Invalid link type, or null link name
 *@return ::NAPI_ERROR_NAMELENGTH Profile name too long
 *@return ::NAPI_ERROR_SOCK Socket operation failed
 *@return ::NAPI_ERROR_NORESOURCE No available link id
 *@return ::NAPI_ERROR_OTHER Failed because of unknown reasons
 *@note
 */
INT32   NAPI_OpenLink( INT8* profileName );

/*
 *@fn INT32 NAPI_Attach(UINT8 linkType, INT8 * linkName)
 *@brief Request to use an existing physical link
 *@param linkType ::NAPI_LINK_GPRS or ::NAPI_LINK_CSD
 *@param linkName for GPRS this is the APN, for CSD this is the phone number
 *@return [1, 15] link id
 *@return ::NAPI_ERROR_NOTINIT NAPI Not yet initialized 
 *@return ::NAPI_ERROR_INVALID Invalid link type, or null link name
 *@return ::NAPI_ERROR_NAMELENGTH Profile name too long
 *@return ::NAPI_ERROR_SOCK Socket operation failed
 *@return ::NAPI_ERROR_OTHER Failed because of unknown reasons
 *@note A final result indicator will tell whether the operation succeeded or not 
 */
INT32   NAPI_Attach(
            UINT8   linkType,
            INT8*   linkName );

/*
 *@fn INT32 NAPI_Hold(UINT8 linkType, INT8 * linkName)
 *@brief Maintains a link even if the use counter drops to zero
 *@param linkType ::NAPI_LINK_GPRS or ::NAPI_LINK_CSD
 *@param linkName For GPRS this is the APN. For CSD this is the phone number
 *@return 0: Request has been successfully sent to server
 *@return ::NAPI_ERROR_NOTINIT NAPI Not yet initialized 
 *@return ::NAPI_ERROR_INVALID Invalid link type, or null link name
 *@return ::NAPI_ERROR_NAMELENGTH Profile name too long
 *@return ::NAPI_ERROR_SOCK Socket operation failed
 *@return ::NAPI_ERROR_OTHER Failed because of unknown reasons
 *@note If the link is not aleady on hold, a new connnection indicator will 
 * be sent with the hold flag set
 */
INT32   NAPI_Hold(
            UINT8   linkType,
            INT8*   linkName );

/*
 *@fn INT32 NAPI_Drop(UINT8 linkType, INT8 * linkName)
 *@brief Drops a physical link identified by linkType and linkName
 *@param linkType ::NAPI_LINK_GPRS or ::NAPI_LINK_CSD
 *@param linkName For GPRS this is the APN. For CSD this is the phone number
 *@return 0: Operation successful
 *@return ::NAPI_ERROR_NOTINIT NAPI Not yet initialized
 *@return ::NAPI_ERROR_INVALID Invalid link type, or null link name
 *@return ::NAPI_ERROR_NAMELENGTH Profile name too long
 *@return ::NAPI_ERROR_SOCK Socket operation failed
 *@return ::NAPI_ERROR_OTHER Failed because of unknown reasons
 */
INT32   NAPI_Drop(
            UINT8   linkType,
            INT8*   linkName );

/**
 *@fn INT32 NAPI_CloseLink(INT32 linkid)
 *@brief Drops a logical link identified by linkid
 *@param linkid The link to close
 *@return 0: Operation successful
 *@return ::NAPI_ERROR_NOTINIT NAPI Not yet initialized
 *@return ::NAPI_ERROR_INVALID Invalid argument
 *@return ::NAPI_ERROR_SOCK Socket operation failed
 *@return ::NAPI_ERROR_OTHER Failed because of unknown reasons
 */
INT32   NAPI_CloseLink( INT32 linkid );

/**
 *@fn void NAPI_Fini(void)
 *@brief Return NAPI to uninitialized state
 *@param NONE
 *@return NONE
 */
void    NAPI_Fini( void );

/**
 *@fn INT32 NAPI_BindSocket2Link(int sockfd, INT32 linkid)
 *@brief Tells the system to send its data over a link designated 
 * by the linkid. The behavior is not predictable if the socket is not bound to
 * the correct link.
 *@param sockfd  File descriptor, only an IPV4 address family socket can be used here.
 *@param linkid The link connecting to the destination
 *@return 0: Operation successful
 *@return ::NAPI_ERROR_NOTINIT NAPI Not yet initialized
 *@return ::NAPI_ERROR_INVALID Invalid argument
 *@return ::NAPI_ERROR_SOCK Socket operation failed
 *@return ::NAPI_ERROR_BIND Socket bind failed
 *@return ::NAPI_ERROR_OTHER Failed because of unknown reasons
 */
INT32   NAPI_BindSocket2Link(
            int     sockfd,
            INT32   linkid );

/*
 *@fn INT32 NAPI_GetDeviceInfo(
            INT32             linkid,
            NAPI_INFO_TYPE_E  request,
            void*             pParam,
            UINT32            paramLength)
 *@brief Manipulates the device parameters.
 *@param linkid The inquired about link 
 *@param request The request type
 *@param pParam The request parameter
 *@param paramLength The buffer length of the pParam
 *@return 0: Operation successful
 *@return ::NAPI_ERROR_NOTINIT NAPI Not yet initialized
 *@return ::NAPI_ERROR_INVALID Invalid argument
 *@return ::NAPI_ERROR_SOCK Socket operation failed
 *@return ::NAPI_ERROR_OTHER Failed because of unknown reasons
 */
INT32   NAPI_GetDeviceInfo(
            INT32               linkid,
            NAPI_INFO_TYPE_E    request,
            void*               pParam,
            UINT32              paramLength);
/*
 *@fn INT32 NAPI_ReadProfile(INT8* profileName, \            
 * NAPI_PROFILE_S* pBasic, INT8* pExt, UINT32 size)
 *@brief Reads profile information from flash, stores the basic information in pBasic,
 * and stores the extended information(up to size bytes) in pExt. pBasic currently consists of settings for GPRS and CSD. 0 is used to pad
 * pExt when there is not enough data in the flash profile.
 *@param profileName Profile to read
 *@param pBasic Stores basic profile information  
 *@param pExt Stores extended profile information
 *@param size Buffer size of pExt
 *@return 0: Operation successful. Profile data is placed into the output buffer 
 *@return ::NAPI_ERROR_INVALID Profile name is null or pBasic is null
 *@return ::NAPI_ERROR_PROFILE Read profile error
 *@return ::NAPI_ERROR_OTHER Failed because of unknown reasons
 */
INT32   NAPI_ReadProfile(
            INT8*               profileName,
            NAPI_PROFILE_S*     pBasic,
            INT8*               pExt,
            UINT32              size );

/*
 *@fn INT32 NAPI_CreateProfile(INT8* profileName, \
 * NAPI_PROFILE_S* pBasic, INT8* pExt, UINT32 size)
 *@brief Creates profile based on the information in pBasic and pExt. The profile must not previously exist.
 *@param profileName Profile to create
 *@param pBasic Basic information in profile
 *@param pExt Extended information in profile
 *@param size Buffer size of pExt
 *@return 0: Operation successful
 *@return ::NAPI_ERROR_INVALID Profile name is null or pBasic is null
 *@return ::NAPI_ERROR_PROFILE Profile write error
 *@return ::NAPI_ERROR_OTHER Failed because of unknown reasons
 *@note pExt If null, the profile will only contain the information in pBasic.
 */
INT32   NAPI_CreateProfile(
            INT8*               profileName,
            NAPI_PROFILE_S*     pBasic,
            INT8*               pExt,
            UINT32              size );

/**
 *@fn INT32 NAPI_ListAllProfile(INT8* profileNameList, UINT32* counter)
 *@brief Gets a list of all profile names. Applications should allocate memory
 * equal in size to NAPI_MAX_PROFILE_NAME_LENGTH * n, and set the counter equal to
 * n. Upon return, the counter will contain the actual profile number in the system.
 * If counter > n, profileNameList will list the n profiles.
 *@param profileNameList Fixed length string array to store profile name
 *@param counter Inputs memory size, outputs profile number
 *@return 0: Operation successful
 *@return ::NAPI_ERROR_INVALID Counter is null
 *@return ::NAPI_ERROR_OTHER Failed because of unknown reasons
 */
INT32   NAPI_ListAllProfile(
            INT8*       profileNameList,
            UINT32*     counter );

/*
 *@fn INT32 NAPI_ModifyProfile(INT8* profileName, \
 * NAPI_PROFILE_S* pBasic, INT8* pExt, UINT32 size)
 *@brief Modifies profile content for the named profile. The profile must first exist
 *@param profileName Profile to modify
 *@param pBasic Basic profile information
 *@param pExt Extended profile information
 *@param size Buffer size of pExt
 *@return 0: Operation successful
 *@return ::NAPI_ERROR_INVALID Profile name is null or pBasic and pExt are both null
 *@return ::NAPI_ERROR_PROFILE Write profile error
 *@return ::NAPI_ERROR_OTHER Failed because of unknown reasons
 *@note If pBasic is NULL, the basic information will be left unchanged. This rule 
 * also applies to pExt.
 */
INT32   NAPI_ModifyProfile(
            INT8*               profileName,
            NAPI_PROFILE_S*     pBasic,
            INT8*               pExt,
            UINT32              size );

/*
 *@remarks new!!!
 *@fn INT32 NAPI_RenameProfile(INT8* curProfileName, INT8* newProfileName)
 *@brief rename the curProfileName profile to newProfileName
 *@param curProfileName current profile name
 *@param newProfileName new profile name
 *@return 0 operation succeed
 *@return ::NAPI_ERROR_INVALID profile name is null
 *@return ::NAPI_ERROR_PROFILE profile not exist
 *@return ::NAPI_ERROR_OTHER failed because unknown reason
 */
INT32 NAPI_RenameProfile(INT8* curProfileName, INT8* newProfileName);

/*
 *@fn INT32 NAPI_DeleteProfile(INT8* profileName)
 *@brief Delete the named profile from the system
 *@param profileName Profile to delete
 *@return 0: Operation successful
 *@return ::NAPI_ERROR_INVALID Profile name is null
 *@return ::NAPI_ERROR_OTHER Failed because of unknown reasons
 */
INT32   NAPI_DeleteProfile( INT8* profileName );

/*
 *@fn INT32 NAPI_IsProfileValid(INT8* profileName)
 *@brief Checks if the profile is a valid profile
 *@param profileName The profile to check
 *@return 0: The profile exists and every field is valid
 *@return ::NAPI_ERROR_INVALID Profile name is null
 *@return ::NAPI_ERROR_PROFILE Profile does not exist
 *@return ::NAPI_ERROR_OTHER Some fields do not pass the validity check
 */
INT32   NAPI_IsProfileValid( INT8* profileName );

/*
 *@remarks new!!!
 *@fn INT32 NAPI_GetProfileIDByName(INT8* profileName, UINT32 * pProfileID)
 *@Get profile ID by profile name
 *@param profileName the profile interested
 *@param profileID output for profile ID
 *@return 0 operation succeed
 *@return ::NAPI_ERROR_INVALID profile name is null
 *@return ::NAPI_ERROR_PROFILE profile not exist
 */
INT32 NAPI_GetProfileIDByName( INT8* profileName, UINT32 * pProfileID );

/*
 *@remarks new!!!
 *@fn INT32 NAPI_GetProfileNameByID( UINT32 profileID, INT8* profileName )
 *@Get profile name by profile id
 *@param profileName output for profile name
 *@param profileID  the profile id interested
 *@return 0 operation succeed
 *@return ::NAPI_ERROR_INVALID profile name is null
 *@return ::NAPI_ERROR_PROFILE profile not exist
 */
INT32 NAPI_GetProfileNameByID( UINT32 profileID, INT8* profileName );

/*
 *@remarks new!!!
 *@fn NAPI_SetProfileNameByID( UINT32 profileID, INT8* profileName )
 *@Get profile name by profile id
 *@param profileName new profile name
 *@param profileID  the profile id interested
 *@return 0 operation succeed
 *@return ::NAPI_ERROR_INVALID profile name is null
 *@return ::NAPI_ERROR_PROFILE profile not exist
 */
INT32 NAPI_SetProfileNameByID( UINT32 profileID, INT8* profileName );

/*
 *@fn INT32 NAPI_BuildIPSecTunnel(INT32 parentLinkId, const INT8* pIKEConfig)
 *@brief Build an ipsec tunnel with policy defined in ikeConfig
 *@param parentLinkId The link to build the tunnel on
 *@param pIKEConfig IKE policy configuration file
 *@return [1, 15] tunnel id
 *@return ::NAPI_ERROR_NOTINIT NAPI Not yet initialized
 *@return ::NAPI_ERROR_INVALID Invalid argument
 *@return ::NAPI_ERROR_SOCK Socket operation failed
 *@return ::NAPI_ERROR_OTHER Failed because of unknown reasons
 */
INT32 NAPI_BuildIPSecTunnel(INT32 parentLinkId, const INT8* pIKEConfig);

/**
 *@fn INT32 NAPI_TearIPSecTunnel(INT32 tunnelId)
 *@brief Tears an ipsec tunnel identified by tunnel ID 
 *@param tunnelId The tunnel to close
 *@return 0: Operation successful
 *@return ::NAPI_ERROR_NOTINIT NAPI Not yet initialized
 *@return ::NAPI_ERROR_INVALID Invalid argument
 *@return ::NAPI_ERROR_SOCK Socket operation failed
 *@return ::NAPI_ERROR_OTHER Failed because of unknown reasons
 */
#define NAPI_TearIPSecTunnel(tunnelId) \
        NAPI_CloseLink(tunnelId)

/*
 *@fn INT32 NAPI_UmaBuildSecureTunnel(INT32 parentLinkId, const char* pServAddr)
 *@brief Build a secure tunnel to UNC on the parent link
 *@param linkid The link to build the tunnel on
 *@param pServAddr The gateway address
 *@return [1, 15] tunnel id
 *@return ::NAPI_ERROR_NOTINIT NAPI Not yet initialized
 *@return ::NAPI_ERROR_INVALID Invalid argument
 *@return ::NAPI_ERROR_SOCK Socket operation failed
 *@return ::NAPI_ERROR_OTHER Failed because of unknown reasons
 */
INT32 NAPI_UmaBuildSecureTunnel(INT32 parentLinkId, const char* pServAddr);

/**
 *@fn INT32 NAPI_UmaTearSecureTunnel(INT32 tunnelId)
 *@brief Tears a secure tunnel identified by tunnel ID 
 *@param tunnelId The tunnel to close
 *@return 0: Operation successful
 *@return ::NAPI_ERROR_NOTINIT NAPI Not yet initialized
 *@return ::NAPI_ERROR_INVALID Invalid argument
 *@return ::NAPI_ERROR_SOCK Socket operation failed
 *@return ::NAPI_ERROR_OTHER Failed because of unknown reasons
 */
#define NAPI_UmaTearSecureTunnel(tunnelId) \
        NAPI_CloseLink(tunnelId)

UINT32 NAPI_GetMaxProfiles();

INT32 NAPI_DnsResolverConfig(int link);

#ifdef __cplusplus
}
#endif
#endif

