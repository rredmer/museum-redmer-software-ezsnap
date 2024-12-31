/*--------------------------------------------------------------------------*/
/*                                                                          */
/*  Module......:  MAIN.C                                                   */
/*                                                                          */
/*  Description.:  RSC EZ-SNAP(R) Main Module.                              */
/*                                                                          */
/*  (c) 1995-2000 Ronald D. Redmer.  All Rights Reserved.                   */
/*--------------------------------------------------------------------------*/

	//--- GLOBAL COMPILER PRAGMAS -------------------------------------------
	#pragma pack(1)

	//--- GLOBAL FILE INCLUDE LIST ------------------------------------------
	#include <string.h>									// Standard string prototypes
	#include <stdlib.h>									// Standard Runtime lib prototypes
	#include <stdio.h>									// Standard I/O prototypes
	#include <conio.h>									// Standard console I/O prototypes
	#include "dos.h"									// Standard dos prototypes
	#include <io.h>										// Standard low level I/O prototypes
	#include <stdarg.h>									// Standard variable argument list stuff
	#include <time.h>									// Standard time prototypes
	#include <3000\bios.h>								// Symbol ADK Bios routines
	#include <3000\dos.h>             					// Symbol ADK DOS routines
	#include <3000\urm.h>								// Symbol ADK URM routines
	#include <oldadl.h>									// Symbol ADK old ADL routines
	#include <adl.h>									// Symbol ADL
	#include <screen.h>									// Symbol Screen handling
	#include <process.h>								// Standard C Process Handling

	//--- DEFINE APPLICATION SPECIFIC CONSTANTS ---------------------------------
	#define EZ_TITLE			"RSC"					// Application title
	#define EZ_APPLICATION		"     EZ-SNAP(r)   "	// Application name
	#define EZ_VERSION			"Version 2.00"			// Application major version
	#define EZ_VERSIONKEY		"RSC_EZSNAP[v002.00r0002]"	// Application key
	#define EZ_REVISION			"      r 0002            "  // Application minor revision
	#define EZ_COPYRIGHT		"(c) 2000 Redmer Co      "	// Application copyright info
	#define EZ_SUBJECTFILE		"D:\\CARDFILE.TXT"		// Subject File Name
	#define EZ_UNITFILE			"D:\\UNITFILE.TXT"		// Unit Setup File Name
	#define EZ_SETUPFILE		"D:\\SETFILE.TXT"		// Setup file name
	#define EZ_FIELDFILE		"D:\\FIELDS.TXT"		// Field setup file name
	#define EZ_PRODUCTFILE		"D:\\PRODUCTS.TXT"		// Products setup file name
	#define EZ_PASSWORDFILE		"D:\\PASSWORD.TXT"		// Password file name
	#define EZ_TRUE           	1						// Logical true
	#define EZ_FALSE           	0						// Logical false
	#define EZ_YES				"Y"						// Yes response to question
	#define EZ_NO				"N"						// No response to question
	#define EZ_BLANK_ORDER		"                              "
	#define EZ_BLANK_SUBJECT	"__________"			// Blank SUBJECT
	#define EZ_BLANK_CUST		"__________"			// Blank Customer Code
	#define EZ_BLANK_LIGHTS		"__________"			// Blank lights
	#define EZ_BLANK_CAMERA		"__________"			// Blank camera
	#define EZ_BLANK_PHOTOG		"__________"			// Blank photographer
	#define EZ_BLANK_TWINCHK	"__________"			// Blank twin-check
	#define EZ_BLANK_WORK_TYPE	"__________"			// Blank work type
	#define EZ_BLANK_JOB_NUM	"__________"			// Blank job number
	#define EZ_BLANK_MAGAZINE	"0000"					// Blank magazine
	#define EZ_BLANK_PRODUCT	"___"					// Blank product
	#define EZ_BLANK_UNIT		"0000"					// Blank unit id
	#define EZ_BLANK_STAFF		"___"					// Blank staff
	#define EZ_BLANK_SITTING	"  "					// Blank sitting
	#define EZ_SLATE_CODE		"SLATE_____"			// Slate code
	#define EZ_SLATE1_CODE		"SLATE1____"			// Slate code
	#define EZ_SLATE2_CODE		"SLATE2____"			// Slate code
	#define EZ_SLATE3_CODE		"SLATE3____"			// Slate code
	#define EZ_SLATE4_CODE		"SLATE4____"			// Slate code
	#define EZ_SLATE5_CODE		"SLATE5____"			// Slate code
	#define EZ_SLATE6_CODE		"SLATE6____"			// Slate code
	#define EZ_SLATE7_CODE		"SLATE7____"			// Slate code
	#define EZ_SLATE8_CODE		"SLATE8____"			// Slate code
	#define EZ_SLATE9_CODE		"SLATE9____"			// Slate code
	#define EZ_SLATE10_CODE		"SLATE10___"			// Slate code
	#define EZ_MPOSE_CODE		"MPOSE_____"			// Multipode code
	#define EZ_BLINK_CODE		"BLINK_____"			// Blink code
	#define EZ_SETUP_CODE       "SETUP_____"			// Setup code
	#define EZ_MENU_CODE        "MENU______"			// Main menu code
	#define EZ_HELP_CODE		"HELP______"			// Help code
	#define EZ_CODE_STAFF0		"900"					// Staff code
	#define EZ_CODE_STAFF1      "901"					// Staff code
	#define EZ_CODE_STAFF2      "902"					// Staff code
	#define EZ_CODE_STAFF3      "903"					// Staff code
	#define EZ_CODE_STAFF4      "904"					// Staff code
	#define EZ_CODE_STAFF5      "905"					// Staff code
	#define EZ_CODE_STAFF6      "906"					// Staff code
	#define EZ_CODE_STAFF7      "907"					// Staff code
	#define EZ_CODE_STAFF8      "908"					// Staff code
	#define EZ_CODE_STAFF9      "909"					// Staff code
	#define EZ_CODE_NO_PROD     "970"					// No PRODUCT code
	#define EZ_CODE_CLEAR_PROD  "960"					// Clear PRODUCTS code
	#define EZ_CODE_INCDENS     "910"					// Increase density code
	#define EZ_CODE_DECDENS     "911"					// Decrease density code
	#define EZ_DEFAULT_PASS		"9999"					// Default password for data erase
	#define EZ_BLANK_PASSWORD	"____"					// Password mask characters
	#define EZ_SUBJECT_RECLEN	58						// Subject record length
	#define EZ_SETUP_RECLEN		91						// Setup record length
	#define EZ_MAX_PRODUCTS		100						// Maximum number of products
	#define EZ_SUBJECT_LEN      10						// Length of subject Field
	#define EZ_PRODUCT_LEN      3   					// Length of Product Code Field
	#define EZ_ORDER_LEN        30						// Length of Order Field
	#define EZ_SITTING_LEN      2						// Length of sitting field
	#define EZ_STAFF_LEN        2						// Length of Staff Field
	#define EZ_ORDER_MAX        10						// Maximum number of orders per frame
	#define EZ_UNIT_LEN         10						// Length of Unit ID Field
	#define EZ_CUST_LEN         10						// Length of customer Field
	#define EZ_PHOTOG_LEN       10						// Length of Photographer Field
	#define EZ_LIGHTS_LEN       10						// Length of Light Set Field
	#define EZ_CAMERA_LEN       10						// Length of Camera ID Field
	#define EZ_WORK_TYPE_LEN    2						// Length of type of work code
	#define EZ_TWINCHECK_LEN    10						// Length of twin check field
	#define EZ_MAGAZINE_LEN     4						// Length of magazine Field
	#define EZ_JOB_NUM_LEN		10						// Length of job field
	#define EZ_DELIM_LEN		4						// Length of delimeter fields
	#define EZ_PASSWORD_LEN		4						// Length of password
	#define EZ_FILE_READ		0						// Standard file read mode
	#define EZ_FILE_WRITE		1						// Standard file write mode
	#define EZ_DELIM_QUESTION   "Q"						// Delimeter for question answer
	#define EZ_DELIM_UNIT       "\0"					// Delimeter for Unit code
	#define EZ_DELIM_SUBJECT    "C"						// Delimeter for camera SUBJECT code
	#define EZ_DELIM_WORK_TYPE  "T"						// Delimeter for work type
	#define EZ_DELIM_PACKAGE    "K"						// Delimeter for package code
	#define EZ_DELIM_CUST       "S"						// Delimeter for customer code
	#define EZ_DELIM_PHOTOG     "R"						// Delimeter for photographer code
	#define EZ_DELIM_LIGHTS     "L"						// Delimeter for light set code
	#define EZ_DELIM_CAMERA     "A"						// Delimeter for camera code
	#define EZ_DELIM_TWIN_CHECK	"\0"					// Delimeter for twin check code
	#define EZ_DELIM_MAG        "M"						// Delimeter for mag (Magazine) code
	#define EZ_DELIM_JOB        "J"						// Delimeter for Job Number
	#define EZ_ASK_NONE			"N"						// Do not ask for data
	#define EZ_ASK_PRIOR		"P"						// Ask for data prior to shoot
	#define EZ_ASK_AFTER		"A"						// Ask for data after shoot
	#define EZ_ASK_BOTH			"B"						// Ask for data prior and after shoot
	#define EZ_TYPE_NUMBER		1						// Numeric only data
	#define EZ_TYPE_ALPHA		0						// Alpha-numeric data

	#define EZ_MAX_SCAN_LEN     16						// Maximum scan length
	#define EZ_TRIP_CAMERA      46						// Shoot Key (.)
	#define EZ_VID_NORMAL		(unsigned char)0x07 	// Normal screen video attribute
	#define EZ_VID_REVERSE      (unsigned char)0x70     // Reverse video screen attribute
	#define EZ_VID_LASTCOL     	19						// Maximum screen columns
	#define EZ_VID_LASTROW     	7						// Maximum screen rows
	#define EZ_SHORTSOUND       150						// Standard audio delay counter
	#define EZ_SCAN_TIMEOUT     60						// Scanner timeout in ms
	#define EZ_SOURCE_CONTACT   1						// Source of data was keyboard
	#define EZ_SOURCE_LASER     2						// Source of data was scanner
	#define EZ_KEYS_AND_SCAN    1						// Accept both key and scan input
	#define EZ_MENU_SHOWTITLE   1						// Display menu title
	#define EZ_MENU_SCROLL_UP   0						// Menu scroll up
	#define EZ_MENU_SCROLL_DOWN 1						// Menu scroll down
	#define EZ_USER_SCANNED     3						// User scanned data flag
	#define EZ_KEY_UP           72						// Up Arrow
	#define EZ_KEY_DOWN         80						// Down Arrow
	#define EZ_KEY_BACKSPACE    0x08					// Backspace
	#define EZ_KEY_ESCAPE       0x1B					// Escape
	#define EZ_KEY_ENTER        0x0D					// Enter / Carriege Return
	#define EZ_KEY_F1           59						// F-1
	#define EZ_KEY_F2           60						// F-2
	#define EZ_KEY_F3           61						// F-3
	#define EZ_KEY_F4           62						// F-4
	#define EZ_KEY_F5           63						// F-5
	#define EZ_KEY_F6           64						// F-6
	#define EZ_KEY_F7           65						// F-7
	#define EZ_KEY_F8           66						// F-8
	#define EZ_KEY_F9           67						// F-9
	#define EZ_KEY_F10          68						// F-10
	#define EZ_MENU_KEY_ENTER   0x1C0D					// Enter Key (Hexed Return)
	#define EZ_MENU_KEY_UP      0x4800					// Up Arrow
	#define EZ_MENU_KEY_DOWN    0x5000					// Down Arrow
	#define EZ_MENU_KEY_LEFT    0x4B00					// Left Arrow
	#define EZ_MENU_KEY_RIGHT   0x4D00					// Right Arrow
	#define EZ_MENU_KEY_ESCAPE  0x011B					// Escape key
	#define EZ_MENU_KEY_BACKSPACE   0x0E08				// Backspace

	//--- GLOBAL SERIAL COMMUNICATIONS CONSTANTS --------------------------------
	#define EZ_DIRECT_SER_PORT	0						// Serial Port Number
	#define QSEG1(p)            ((unsigned)(((unsigned long)((void far *)p))>>16))
	#define QSEG2(p)            ((unsigned)(((((unsigned long)((void far *)p))+15)&0xFFFF)>>4))
	#define QSEG(p)             (QSEG1(p)+QSEG2(p))
	#define	X1K_EN				0x08					// Use 1k packets outbound
	#define	ERROR				0
	#define	GOOD				1
	#define	RETRY				2
	#define	INFO				3
	
	//--- DEFINE GLOBAL DATA TYPES ------------------------------------------
	typedef struct cEXPOSURE {							// Exposure structure declaration
		int Record;										// Record Number (File Record #)
		int SetupTag;									// Tag to setup record
	    int Frame;										// Frame # on current mag (for current setup)
	    int Density;									// Density correction
		char Staff[   EZ_STAFF_LEN + 2 ];				// Staff Code
		char Subject[ EZ_SUBJECT_LEN + 1 ];				// Subject Identification
		char Order[   EZ_ORDER_LEN +1 ];				// Orders for this card (product codes)
	    char Sitting[ EZ_SITTING_LEN + 1];				// Sitting code
	} EXPOSURE;
	typedef struct cSETUP {								// Setup Structure Type Definition
		int  SetupTag;									// Setup record number
		char date[ 10 ];								// Date the setup was made
		char time[ 10 ];								// Time the setup was made
	    char cust[	  EZ_CUST_LEN + 1 ];				// School Code
		char photog[  EZ_PHOTOG_LEN + 1 ];				// Photographer Code
		char lights[  EZ_LIGHTS_LEN + 1 ];				// Light Set Code
		char camera[  EZ_CAMERA_LEN + 1 ];				// Camera Code
	    char worktp[  EZ_WORK_TYPE_LEN + 1 ];			// Work type
	    char twinchk[ EZ_TWINCHECK_LEN + 1 ];			// Twin check
	    char mag[     EZ_MAGAZINE_LEN + 1 ];			// Magazine
		char job_num[ EZ_JOB_NUM_LEN + 1 ];				// Job Number
		char Unit[    EZ_UNIT_LEN + 1 ];				// Unit Code
	} SETUP;
	typedef struct cFields {							// Field Setup structure type definition
		char DelimCust[ EZ_DELIM_LEN ];					// Customer delimeter
		char DelimPhotog[ EZ_DELIM_LEN ];				// Photographer delimeter
		char DelimLights[ EZ_DELIM_LEN ];				// Light delimeter
		char DelimCamera[ EZ_DELIM_LEN ];				// Camera delimeter
		char DelimWorkTp[ EZ_DELIM_LEN ];				// Work Type delimeter
		char DelimTwinChk[ EZ_DELIM_LEN ];				// Twin Check delimeter
		char DelimMag[ EZ_DELIM_LEN ];					// Magazine delimeter
		char DelimJobNum[ EZ_DELIM_LEN ];				// Job number delimeter
		char DelimSubject[ EZ_DELIM_LEN ];				// Camera card delimeter
		char DelimProduct[ EZ_DELIM_LEN ];				// Product code delimeter
		char AskCust[ EZ_DELIM_LEN ];					// Ask for customer indicator
		char AskPhotog[ EZ_DELIM_LEN ];					// Ask for photographer
		char AskLights[ EZ_DELIM_LEN ];					// Ask for lights
		char AskCamera[ EZ_DELIM_LEN ];					// Ask for camera
		char AskWorkTp[ EZ_DELIM_LEN ];					// Ask for work type
		char AskTwinChk[ EZ_DELIM_LEN ];				// Ask for twin check
		char AskMag[ EZ_DELIM_LEN ];					// Ask for magazine
		char AskJobNum[ EZ_DELIM_LEN ];					// Ask for job number
		char ReqCust[ EZ_DELIM_LEN ];					// Require customer indicator
		char ReqPhotog[ EZ_DELIM_LEN ];					// Require photographer
		char ReqLights[ EZ_DELIM_LEN ];					// Require lights
		char ReqCamera[ EZ_DELIM_LEN ];					// Require camera
		char ReqWorkTp[ EZ_DELIM_LEN ];					// Require work type
		char ReqTwinChk[ EZ_DELIM_LEN ];				// Require twin check
		char ReqMag[ EZ_DELIM_LEN ];					// Require magazine
		char ReqJobNum[ EZ_DELIM_LEN ];					// Require job number
	} FIELDS;
	typedef struct cSlates {							// Slate Setup structure type definition
		char Slate1[ 10 ];								// Slate Type 1
		char Slate2[ 10 ];								// Slate Type 2
		char Slate3[ 10 ];								// Slate Type 3
		char Slate4[ 10 ];								// Slate Type 4
		char Slate5[ 10 ];								// Slate Type 5
	} SLATES;
	typedef struct cSecurity {							// Security setup structure
		char Password[ 10 ];							// Security password
	} SECURITY;
	typedef struct cProducts {							// Product validation structure
		char Enabled[ 2 ];								// Product validation enable
		char ValidProducts[ EZ_MAX_PRODUCTS + 1 ][ EZ_PRODUCT_LEN + 1 ]; // Product validation matrix
	} PRODUCTS;
	typedef struct {									// Symbol Screen Structure
		unsigned char Rows;      						// Max Rows on Screen
		unsigned char Cols;      						// Max Cols on Screen
		unsigned char SRow;      						// Starting Row for 1st menu item
		unsigned char Border;    						// Does this menu have a border?
		unsigned char Items;     						// Number of items on the menu
		int LastSelection;       						// Last selection where hilite bar was
		unsigned char HItem;     						// Hilighted item number
		unsigned char TItem;     						// Top Item number
		unsigned char BItem;     						// Bottom Item Number
	} SCREEN;
	typedef struct {									// Menu Item Structure
		char *mstr;            							// Menu Item string
		int (*MenuFunc)( int );  						// Pointer to Item Function to invoke
	} MENU;
	typedef struct {									// Menu Structure
		MENU *menu;              						// Pointer to a MENU
		unsigned char ShowTitle; 						// Show the title on 4 line displays?
		char *Title;             						// The menu Title
	} MENUS;
	typedef	struct {
		char	function;
		char	error_code;
		struct 	{
			char wak_lmt;
			char nak_lmt;
			char ttd_lmt;
			char bid_lmt;
			int	 timer2s;
			int	 timer3s;
			int	 timer20s;
			char number_crc_bids;
			char number_cksum_bids;
			char pad_char;
			char options;
		} data;
	} PROTOCOL_PARMS;
	typedef struct {
		unsigned int InQSize;
		unsigned int InQSeg;
		unsigned int OutQSize;
		unsigned int OutQSeg;
	} QParamT;

	//--- DIMENSION GLOBAL VARIABLES ----------------------------------------
	IoctlT  ioctl;										// Bios IOctl structure
	EXPOSURE Exposure;									// Exposure Structure
	SETUP Setup;										// Setup Structure
	FIELDS Field;										// Field Defintions
	SECURITY Security;									// Security - password
	PRODUCTS Products;									// Product validation codes
	FILE *STFile;										// Pointer to setup file
	SCREEN scrn;										// Screen structure
	QParamT newqs;
	union REGS regs;
	struct SREGS sregs;
	int ConsoleHandle,									// Handle for keyboard and barcode reader
		NoPackage,										// No Package Flag
		FireMode,										// Camera fire mode
		FieldPtr,										// Field pointer for main editing screen
		OrderCount,										// Order count for current card.
		err,											// Serial port errors
		handle,											// Direct serial communication handle
		TermType,										// Terminal type
		EventCnt,										// Events counter
		AnswerListNum;									// number of messages int the answer list
	static int magic = 0xaa55;							// Check value for binary communications setup file
	char Subject[ EZ_MAX_SCAN_LEN + 1],					// Buffer for input data   (*** SIZE IS CRITICAL ***)
		 ProductCode[ EZ_MAX_SCAN_LEN + 1],				// Buffer for input data
		 buffer[ 40 ],									// Data entry buffer
		 Kqueue[20],									// Keyboard que structure
		 ResponseBuf[128],								// buffer used by AdlL3GetResponse
		 ParamString[256];								// parameter string passed to Adl3 level functions
	unsigned char PhysRows,								// Number of physical screen rows (determined by BIOS call)
				  PhysCols,								// Number of physical screen columns
				  LastRow,								// Last row on the terminal
				  LastCol,								// Last column on the terminal
				  TermRows,								// The number of rows on the terminal
				  TermCols;								// The number of columns on the terminal

	//--- DIMENSION GLOBAL MENUS --------------------------------------------
	#define MENU_MAIN           0
	#define MENU_SETUP          1
	int  Stub(int idx );								// EZ-SNAP function stub (menus)
	MENU menu1[] = {{ "Shoot Pictures    ", Stub, },
					{ "Transfer Direct   ", Stub, },
					{ "Setup             ", Stub, }, };
	MENU menu2[] = {{ "Product Definition", Stub, },
					{ "Set Time and Date ", Stub, },
					{ "Set EZ-SNAP ID    ", Stub, },
					{ "Setup Barcodes    ", Stub, },
					{ "Setup Password    ", Stub, },
					{ "Clear Data Files  ", Stub, },
					{ "Quit to DOS       ", Stub, }, };
	MENUS Menus[] ={{ menu1,  EZ_MENU_SHOWTITLE, "MAIN MENU" },
					{ menu2,  EZ_MENU_SHOWTITLE, "SETUP MENU" },};
	int MenuSizes[] = {(sizeof(menu1) / sizeof(menu1[0])), 
					   (sizeof(menu2) / sizeof(menu2[0])),};

	//--- FUNCTION PROTOTYPES -----------------------------------------------

		//--- MAIN ROUTINES -------------------------------------------------
		void main(void);								// EZ-SNAP main function
		int  EZ_FileFields(int Operation);				// Process Field Setup File
		int  EZ_FileUnit(int Operation);				// Process Unit Identification File
		int  EZ_FileProducts(int Operation);			// Process Product Validation File
		int  EZ_FilePassword(int Operation);			// Process Password File
		void EZ_ShootPictures(void);					// EZ-SNAP Shoot Pictures Menu Option
		void EZ_DisplayShootForm(void);					// EZ-SNAP Shoot Pictures Form
		void EZ_ClearProducts(void);					// Shoot Pictures Clear Products
		void EZ_ShootHelp(void);						// Shoot Pictures Help
		void EZ_ShootSetup(void);						// Shoot Pictures Setup 
		void EZ_ChangeFrame(void);						// Shoot Pictures Change Frame
		void EZ_SetupDate(void);						// EZ-SNAP Setup Menu - Setup Date
		void EZ_EditFields(void);						// EZ-SNAP Setup Menu - Setup Fields
		void EZ_SetFieldDefaults(void);					// EZ-SNAP Setup Menu - Set default Delimeters
		void EZ_EditProducts(void);						// EZ-SNAP Setup Menu - Edit Products
		void EZ_SetDefaultProducts(void);				// EZ-SNAP Setup Menu - Set default Product codes
		void KillFiles(void);							// Erase data files
		void EZ_FireCamera(void);						// Fire the camera

		//--- UTILITY FUNCTIONS ---------------------------------------------
		int  EZ_SearchString(char *string, char **list);
		void EZ_FillWithUnderscores(char *buf, int count);
		void EZ_ErrorMessage(void);				// Sound audible for errors
		void EZ_DrawBorder(unsigned char Rows,unsigned char Cols, char *titlestr);
		void EZ_ClearAndHome( void );
		void EZ_Alarm(char *text);
		void EZ_PutChar(unsigned char r,unsigned char c,unsigned char ch, unsigned char attr);

		//--- DATA INPUT & MENU FUNCTION PROTOTYPES -------------------------
		int  EZ_Input(char *InputData, char *Delimeter, unsigned char InputRow, unsigned char InputCol, int InputLen, int NumberMode);
		int  EZ_GetData(char *Databuf, int *DataScanned);
		int  EZ_GetMenuSelection(int MenusID, int cSelection);	// Process menu user interface.
		void EZ_MenuDisplayItem(char *str, unsigned int CItem, unsigned int TItems);
		void EZ_MenuScroll( unsigned char dir, unsigned char lines, int arg2 );
		void EZ_DisplayItem(int MenusID, int LastSelection, unsigned int HiLite);
		unsigned char EZ_Menu_DisplayItemsAll( int StartVal, int MenusID );

		//--- DIRECT TRANSFER PROTOTYPES ------------------------------------
		int  EZ_XmodemSend(char *buffer, int len);		// Send string via X modem
		int	 EZ_DirectXModem(char *fname);				// Transfer file direct via X-modem
		int	 EZ_DirectXModem(char *fname);				// Transfer file direct via X-modem
		int  EZ_XmodemOpen(void);						// Open comm port for X modem
		int  EZ_XModemError(char *name);				// Display X modem messages
		int  EZ_BiosSerialSetParams(int port,void far *parms);
		int  EZ_BiosSerialGetParams(int port,void far *parms);
		int  EZ_BiosSerialOpen(int port);				// Open serial ports
		int  EZ_BiosSerialClose(int port);				// Close serial ports
		int  EZ_BiosSerialSetCtlLines(int port, unsigned char lines);	// Set serial control lines
		int  EZ_BiosSerialInitQueues(int port,void far *qp);	// Initialize serial queues
		int  EZ_BiosSerialDeleteQueues(void);			// Delete serial queues
		int	 EZ_BiosTxDone(int lineno);					// wait till COM1 empty
		void EZ_TransferDirect(void);					// EZ-SNAP Transfer Direct
		void EZ_XmodemXON(void);						// Configure X modem X-ON/X-OFF
		void EZ_XModemHeader(byte header,byte trailer);	// Set X modem header and trailer
		void EZ_XModemClose(void);						// Close X modem port
		void EZ_XModemSendEnd(void);					// Send X modem end block
		void EZ_XModemConfig(void);						// Configure X modem protocol

/*--------------------------------------------------------------------------*/
/*                                                                          */
/*                         M A I N   R O U T I N E S                        */
/*                         M A I N   R O U T I N E S                        */
/*                         M A I N   R O U T I N E S                        */
/*                         M A I N   R O U T I N E S                        */
/*                                                                          */
/*--------------------------------------------------------------------------*/

	//--- APPLICATION MAIN FUNCTION -----------------------------------------
	void main() {
		int InputKey = 0, item = 0,	SetupKey = 0;
		unsigned char PGMExit = False, SetupExit = False, KbState;
		IoctlT iob;
		DosOpen( "con", (unsigned)READWRITE, &ConsoleHandle );	// Open the console for read/write
		DosIoCtrlSetInfo( ConsoleHandle, DosIoCtrlGetInfo( ConsoleHandle ) | RAWMODE ); // SYMBOL Set console mode to raw data
		iob.funcode = ConsIoctlGetScanParms;
		DosIoCtrlRdData( ConsoleHandle, &iob, ConsIoctlScanParamLen );
		iob.data.scanparms.labeltermchar = 0;
		iob.data.scanparms.beepondecode = EZ_TRUE;
		iob.data.scanparms.beeptime = 250;
		DosIoCtrlWrData( ConsoleHandle, &iob, ConsIoctlScanParamLen );
		iob.funcode = ConsIoctlSetInputMode;				// Set console input mode function
		iob.data.inputmode.inmode = EZ_KEYS_AND_SCAN;		// Set the mode to keyboard or scanner
		iob.data.inputmode.labeltimeout = EZ_SCAN_TIMEOUT;	// Set the scanner timeout
		DosIoCtrlWrData(ConsoleHandle,&iob,ConsIoctlSetInputModeLen);
		BiosGetLogScrSize( &PhysRows, &PhysCols );		    // Get logical screen size
		PhysRows--;										    // Make rows Zero Relative
		PhysCols--;										    // Make cols Zero Relative
		BiosGetPhysScrSize( &TermRows, &TermCols );			// get display size
		LastRow = TermRows - (unsigned char)1;				// determine number of rows
		LastCol = TermCols - (unsigned char)1;				// determine number of columns
		BiosAutoRepeat(0, 0);							    // Disable the BIOS Auto Key Repeat
		KbState = BiosGetKeyboardState();				    // SYMBOL get the state of the keyboard
		BiosSetKeyboardState( 0 );						    // SYMBOL set the keyboard state to normal (unmodified)
		//--- DISPLAY THE SIGNON SCREEN -----------------------------------------
		EZ_ClearAndHome();
		EZ_DrawBorder(PhysRows, PhysCols, EZ_TITLE);
		BiosPutStrStay(2, 1, strlen(EZ_APPLICATION), EZ_APPLICATION, EZ_VID_REVERSE);
		BiosPutStrStay(3, 3, strlen(EZ_VERSION),     EZ_VERSION,     EZ_VID_NORMAL);
		BiosPutStrStay(4, 3, strlen(EZ_REVISION),    EZ_REVISION,    EZ_VID_NORMAL);
		BiosPutStrStay(6, 1, strlen(EZ_COPYRIGHT),   EZ_COPYRIGHT,   EZ_VID_NORMAL);
		BiosHideCursor();
		BiosDelay(5000);
		BiosShowCursor();
		memset((void *)&scrn,0x00,sizeof(SCREEN));			// Initialize Menus
	
		//--- RETRIEVE SETUP INFORMATION ----------------------------------------
		EZ_SetFieldDefaults();								// Set default Field Setup values
		EZ_FileFields( EZ_FILE_READ );						// Read Field Setup file
		strcpy(Setup.Unit, EZ_BLANK_UNIT);					// Set default Unit Identification
		EZ_FileUnit( EZ_FILE_READ );						// Read Unit Identification file
		EZ_FileProducts( EZ_FILE_READ );					// Read the product file
		EZ_FilePassword( EZ_FILE_READ );					// Read the password file
	
		//--- MAIN PROCESSING LOOP ----------------------------------------------
		while (!PGMExit) {
			InputKey = EZ_GetMenuSelection( MENU_MAIN, 0 );	// Menu selection
			switch (InputKey ) {							// Test the menu selection
				//--- SHOOT PICTURES --------------------------------------------
				case 0:										// The user selected the first menu item
					EZ_ShootPictures();						// Shoot Pictures
					break;
				//--- TRANSFER DATA FROM SYMBOL TO HOST PC ----------------------
				case 1:										// The user selected the second menu item
					EZ_TransferDirect();					// Transmit data to host PC
					break;
				//--- PROCESS THE SETUP MENU ------------------------------------
				case 2:
	                SetupExit = False;						// Initialize setup exit flag
					while (!SetupExit) {
						SetupKey = EZ_GetMenuSelection( MENU_SETUP, 0 );      // MENU.C Return Menu selection
						switch(SetupKey) {
	                        //--- SETUP PRODUCT DEFINITIONS ---------------------
							case 0:
								EZ_EditProducts();
								break;
							//--- SET THE DATE AND TIME -------------------------
							case 1:
								EZ_SetupDate();
								break;
							//--- SET THE EZ-SNAP ID ----------------------------
							case 2:
								EZ_ClearAndHome();
								BiosPutStrStay(0,  0,  20, "  ENTER EZ-SNAP ID  ", EZ_VID_REVERSE);
								BiosPutStrStay(1,  0,   3, "ID?",                  EZ_VID_NORMAL);
								BiosPutStrStay(1,  5,   4, Setup.Unit,             EZ_VID_NORMAL);
								EZ_Input(Setup.Unit, EZ_DELIM_UNIT, 1, 5, EZ_UNIT_LEN, EZ_TYPE_ALPHA);
								EZ_FileUnit( EZ_FILE_WRITE );
								break;
							//--- SETUP BARCODES --------------------------------
							case 3:
								EZ_EditFields();
								break;
							//--- SETUP ERASE DATA PASSWORD ---------------------
							case 4:
								EZ_ClearAndHome();
								BiosPutStrStay(0,  0,  20, "   SETUP PASSWORD   ", EZ_VID_REVERSE);
								BiosPutStrStay(1,  0,   9, "Password?",            EZ_VID_NORMAL);
								BiosPutStrStay(1, 10,   4, Security.Password,      EZ_VID_NORMAL);
								EZ_Input(Security.Password, "", 1, 10, EZ_PASSWORD_LEN, EZ_TYPE_ALPHA);
								EZ_FilePassword( EZ_FILE_WRITE );
								break;
							//--- CLEAR DATA FILES ------------------------------
							case 5:
								KillFiles();
								break;
							//--- QUIT TO DOS -----------------------------------
							case 6:
								PGMExit = True;
								SetupExit = True;
								break;
							//--- EXIT THE SETUP MENU ---------------------------
							default:
	                            SetupExit = True;
						}
					}
					break;
				default:									// The menu selection was not in the test case
					break;									// Break the test
			}
		}
		BiosClrScr(EZ_VID_NORMAL);							// Clear the screen
		BiosSetCursorPos(0,0);								// Set the cursor position to home
		BiosSetKeyboardState( KbState );					// Restore the keyboard state
		DosClose(ConsoleHandle);							// Close the console
		return;												// Exit the program
	}

	//--- PROCESS THE SHOOT PICTURES FORM -----------------------------------
	void EZ_ShootPictures()	{
		int LoopExit = EZ_FALSE, ClearPkgCount = 0,	retv = 0, valid = 0, bytecount = 0;
		char buf[ 22 ], InBuf[ 150 ];
		FILE *CFFile;

		//--- PROCESS THE EXPOSURE FILE -----------------------------------------
		EZ_ClearAndHome();									// Clear and home the cursor
		CFFile = fopen(EZ_SUBJECTFILE, "a+b");				// Open the subject file in append mode
		fseek(CFFile, -EZ_SUBJECT_RECLEN, SEEK_END);		// Seek to start of the last record
		fgets(InBuf, EZ_SUBJECT_RECLEN + 20, CFFile);		// Read the record into a text buffer
		if ((strlen(InBuf)) == EZ_SUBJECT_RECLEN) {			// Process into field values
			sscanf(InBuf, "%4d%2d%4d%%2s%2s%2d%30s%10s", &Exposure.Record, &Exposure.SetupTag, &Exposure.Frame,	Exposure.Staff,	Exposure.Sitting, &Exposure.Density, Exposure.Order, Exposure.Subject);
			BiosPutStrStay(0,  0,  20, "    DATA EXISTS     ", EZ_VID_REVERSE);
			BiosPutStrStay(2,  0,  20, "Data will be added  ", EZ_VID_NORMAL);
			BiosPutStrStay(3,  0,  20, "to the end of the   ", EZ_VID_NORMAL);
			BiosPutStrStay(4,  0,  20, "current file.       ", EZ_VID_NORMAL);
			sprintf(buf, "[%4.4d] Students     ", Exposure.Record);
			BiosPutStrStay(5,  0,  20, buf, EZ_VID_NORMAL);
			BiosPutStrStay(6,  0,  20, "Press ENTER to start", EZ_VID_NORMAL);
			Exposure.Frame++;
			Exposure.Record++;
			EZ_ErrorMessage();
			getch();
		}
		else {
			BiosPutStrStay(0,  0,  20, "      DATA FILE     ", EZ_VID_REVERSE);
			BiosPutStrStay(2,  0,  20, "Data file is empty. ", EZ_VID_NORMAL);
			BiosPutStrStay(6,  0,  20, "Press ENTER to start", EZ_VID_NORMAL);
			Exposure.Frame = 1;
			Exposure.Record = 1;
			BiosBeep(EZ_SHORTSOUND);
			getch();
		}
		fseek(CFFile, 0, SEEK_END);
		strncpy(Exposure.Subject, EZ_BLANK_SUBJECT, EZ_SUBJECT_LEN);
		EZ_ClearProducts();
		NoPackage = 0;
		
		//---  OPEN THE EXPOSURE SETUP FILE -------------------------------------
		STFile = fopen(EZ_SETUPFILE, "a+b");				// Open the exposure setup file
		fseek(STFile, -EZ_SETUP_RECLEN, SEEK_END);			// Seek to the start of the last record
		fgets(InBuf, EZ_SETUP_RECLEN+10, STFile);			// Read the setup record into text buffer
		if ((strlen(InBuf)) == EZ_SETUP_RECLEN) 			// If the buffer is valid length
			sscanf(InBuf, "%2d%8s%5s%10s%10s%10s%10s%10s%10s%10s%4s", &Setup.SetupTag, Setup.date, Setup.time, Setup.cust, Setup.photog, Setup.lights, Setup.camera, Setup.worktp, Setup.job_num, Setup.twinchk, Setup.mag);
		else {												// The setup file is a new file
			Setup.SetupTag = 0;								// Initialize the setup structure to default
			strncpy(Setup.cust,    EZ_BLANK_CUST,     EZ_CUST_LEN);
			strncpy(Setup.photog,  EZ_BLANK_PHOTOG,   EZ_PHOTOG_LEN);
			strncpy(Setup.lights,  EZ_BLANK_LIGHTS,   EZ_LIGHTS_LEN);
			strncpy(Setup.camera,  EZ_BLANK_CAMERA,   EZ_CAMERA_LEN);
			strncpy(Setup.twinchk, EZ_BLANK_TWINCHK,  EZ_TWINCHECK_LEN);
			strncpy(Setup.worktp,  EZ_BLANK_WORK_TYPE,   EZ_WORK_TYPE_LEN);
			strncpy(Setup.job_num, EZ_BLANK_JOB_NUM,  EZ_JOB_NUM_LEN);
			strncpy(Setup.mag,     EZ_BLANK_MAGAZINE, EZ_MAGAZINE_LEN);
		}												
		fseek(STFile, 0, SEEK_END);
		EZ_ShootSetup();									// Get setup information from the user
		EZ_ClearAndHome();									// Clear the screen (display shoot form does not)
		EZ_DisplayShootForm();								// Initialize the point of sale screen
		EZ_FillWithUnderscores(ProductCode, 0);				// Initialize the package field with underscores
		FieldPtr = 1;										// Index of current data entry field
		do {												// Shoot pictures processing loop
			switch(FieldPtr) {								// Test by field number
				//--- PROCESS SUBJECT ENTRY ---------------------------------
				case 1:
					if (Field.DelimSubject[0] == ' ') Field.DelimSubject[0] = '\0';
					retv = EZ_Input(Exposure.Subject, Field.DelimSubject, 1, 5, EZ_SUBJECT_LEN, EZ_TYPE_ALPHA);
					//--- TEST CASE FOR NULL DELIMETERS ---------------------
					if (Field.DelimSubject[0] == '\0') {						// if no delimeters were specified
						if (Exposure.Subject[ 0 ] == Field.DelimProduct[0]) {	// the first char of subject cannot be a product delim
							EZ_ErrorMessage();
							strncpy(Exposure.Subject, EZ_BLANK_SUBJECT, EZ_SUBJECT_LEN);
							EZ_DisplayShootForm();
							FieldPtr = 1;
							break;
						}
					}
					//--- PROCESS SLATE, BLINK & MULTI-POSE  CODES ----------
					if ((!strncmp(Exposure.Subject, EZ_SLATE_CODE, EZ_SUBJECT_LEN)) ||
						(!strncmp(Exposure.Subject, EZ_SLATE1_CODE, EZ_SUBJECT_LEN)) ||
						(!strncmp(Exposure.Subject, EZ_SLATE2_CODE, EZ_SUBJECT_LEN)) ||
						(!strncmp(Exposure.Subject, EZ_SLATE3_CODE, EZ_SUBJECT_LEN)) ||
						(!strncmp(Exposure.Subject, EZ_SLATE4_CODE, EZ_SUBJECT_LEN)) ||
						(!strncmp(Exposure.Subject, EZ_SLATE5_CODE, EZ_SUBJECT_LEN)) ||
						(!strncmp(Exposure.Subject, EZ_SLATE6_CODE, EZ_SUBJECT_LEN)) ||
						(!strncmp(Exposure.Subject, EZ_SLATE7_CODE, EZ_SUBJECT_LEN)) ||
						(!strncmp(Exposure.Subject, EZ_SLATE8_CODE, EZ_SUBJECT_LEN)) ||
						(!strncmp(Exposure.Subject, EZ_SLATE9_CODE, EZ_SUBJECT_LEN)) ||
						(!strncmp(Exposure.Subject, EZ_SLATE10_CODE, EZ_SUBJECT_LEN)) ||
						(!strncmp(Exposure.Subject, EZ_BLINK_CODE, EZ_SUBJECT_LEN)) ||
						(!strncmp(Exposure.Subject, EZ_MPOSE_CODE, EZ_SUBJECT_LEN))) {
						EZ_DisplayShootForm();
						FieldPtr = 2;
						break;
					}
					//--- PROCESS SETUP MENU --------------------------------
					if (!strncmp(Exposure.Subject, EZ_SETUP_CODE, EZ_SUBJECT_LEN)) {
						EZ_ShootSetup();
						strncpy(Exposure.Subject, EZ_BLANK_SUBJECT, EZ_SUBJECT_LEN);
						FieldPtr = 1;
						EZ_DisplayShootForm();
						break;
					}
					//--- PROCESS HELP BARCODE ------------------------------
					if (!strncmp(Exposure.Subject, EZ_HELP_CODE, EZ_SUBJECT_LEN)) {
						EZ_ShootHelp();
						strncpy(Exposure.Subject, EZ_BLANK_SUBJECT, EZ_SUBJECT_LEN);
						FieldPtr = 1;
						EZ_DisplayShootForm();
						break;
					}
					//--- PROCESS MAIN MENU ---------------------------------
					if (!strncmp(Exposure.Subject, EZ_MENU_CODE, EZ_SUBJECT_LEN))
						LoopExit = EZ_TRUE;
	
					FieldPtr++;
					break;
		        
				//--- PROCESS PRODUCT ENTRY -------------------------------------
				case 2:	{
					strcpy(ProductCode, EZ_BLANK_PRODUCT);
					FireMode = 1;
					retv = EZ_Input(ProductCode, Field.DelimProduct, 1, 16, EZ_PRODUCT_LEN, EZ_TYPE_ALPHA);
					FireMode = 0;
					_strupr(ProductCode);
	
					//--- PROCESS CLEAR PRODUCTS CODE ---------------------------
					if (!(strncmp(ProductCode, EZ_CODE_CLEAR_PROD, EZ_PRODUCT_LEN))) {
						if (ClearPkgCount == 0)	{
							EZ_ClearProducts();
							NoPackage = 0;
							EZ_DisplayShootForm();
							ClearPkgCount=1;
							FieldPtr = 2;
							BiosBeep(EZ_SHORTSOUND);
							break;
						}
						else {
							EZ_ClearProducts();
							ClearPkgCount=0;
							strncpy(Exposure.Subject, EZ_BLANK_SUBJECT, EZ_SUBJECT_LEN);
							NoPackage = 0;
							EZ_DisplayShootForm();
							FieldPtr = 1;
							BiosBeep(EZ_SHORTSOUND);
							break;
						}
					}
					else ClearPkgCount = 0;
	
					//--- PROCESS NO PRODUCT CODE -------------------------------
					if (!(strncmp(ProductCode, EZ_CODE_NO_PROD, 3))) {
						NoPackage = (NoPackage == 0 ? 1 : 0);
						EZ_ClearProducts();
						EZ_DisplayShootForm();
						break;
					}
		
					//--- PROCESS DENSITY INCREASE ------------------------------
					if (!(strncmp(ProductCode, EZ_CODE_INCDENS, 3))) {
						Exposure.Density = (Exposure.Density <= 9 ?	Exposure.Density++ : 0);
						EZ_DisplayShootForm();
						FieldPtr = 2;
						BiosBeep(EZ_SHORTSOUND);
						break;
					}                                
	
					//--- PROCESS DENSITY DECREASE ------------------------------
					if (!(strncmp(ProductCode, EZ_CODE_DECDENS, 3))) {
						Exposure.Density = (Exposure.Density >= -9 ? Exposure.Density-- : 0);
						EZ_DisplayShootForm();
						FieldPtr = 2;
						BiosBeep(EZ_SHORTSOUND);
						break;
					}                                
	
					//--- PROCESS SITTING CODE ----------------------------------
					if (!(strncmp(ProductCode, "80", 2))) {
						Exposure.Sitting[0] = ProductCode[1];
						Exposure.Sitting[1] = ProductCode[2];
						EZ_DisplayShootForm();
						OrderCount = 1;
						break;
					}
	
					//--- PROCESS STAFF CODES -----------------------------------
					if (!(strncmp(ProductCode, EZ_CODE_STAFF0, 3)) ||
						!(strncmp(ProductCode, EZ_CODE_STAFF1, 3)) ||
						!(strncmp(ProductCode, EZ_CODE_STAFF2, 3)) ||
						!(strncmp(ProductCode, EZ_CODE_STAFF3, 3)) ||
						!(strncmp(ProductCode, EZ_CODE_STAFF4, 3)) ||
						!(strncmp(ProductCode, EZ_CODE_STAFF5, 3)) ||
						!(strncmp(ProductCode, EZ_CODE_STAFF6, 3)) ||
						!(strncmp(ProductCode, EZ_CODE_STAFF7, 3)) ||
						!(strncmp(ProductCode, EZ_CODE_STAFF8, 3)) ||
						!(strncmp(ProductCode, EZ_CODE_STAFF9, 3))) {
						if (!(strncmp(Exposure.Staff, "00", 2)) ||
							!(strncmp(Exposure.Staff, "01", 2)) ||
							!(strncmp(Exposure.Staff, "02", 2)) ||
							!(strncmp(Exposure.Staff, "03", 2)) ||
							!(strncmp(Exposure.Staff, "04", 2)) ||
							!(strncmp(Exposure.Staff, "05", 2)) ||
							!(strncmp(Exposure.Staff, "06", 2)) ||
							!(strncmp(Exposure.Staff, "07", 2)) ||
							!(strncmp(Exposure.Staff, "08", 2)) ||
							!(strncmp(Exposure.Staff, "09", 2)))
							strncpy(Exposure.Staff, EZ_BLANK_STAFF, EZ_STAFF_LEN);
						else {
							Exposure.Staff[0] = ProductCode[1];
							Exposure.Staff[1] = ProductCode[2];
							Exposure.Staff[3] = '\0';
						}
						EZ_DisplayShootForm();
						FieldPtr = 2;
						BiosBeep(EZ_SHORTSOUND);
						break;
					}                                

					//--- PROCESS PRODUCT CODES ---------------------------------
					if (Products.Enabled[0] == 'Y') {			// If product validation enabled
						valid = 0;
						for (bytecount = 0; bytecount < EZ_MAX_PRODUCTS ; bytecount++ ) {
							if (!strncmp(ProductCode, Products.ValidProducts[ bytecount ], EZ_PRODUCT_LEN)) {
								valid = 1;
								break;
							}
						}
						if (!valid) {
							EZ_ErrorMessage();
							break;
						}
					}
					if ((strncmp(ProductCode, EZ_BLANK_PRODUCT, 3))) {
						if (OrderCount < 10) {
							for (bytecount = 0; bytecount < 3; bytecount ++) {
								if ( ProductCode[ bytecount ] >= '0' && ProductCode[ bytecount ] <= 'Z' ) Exposure.Order[ (OrderCount * 3) + bytecount ] = ProductCode[ bytecount ];
								else Exposure.Order[ (OrderCount * 3) + bytecount ] = '_';
							}
							OrderCount++;
							EZ_DisplayShootForm();
							break;
						}
					}
				}
				default:									// default action is to get subject field
					FieldPtr = 1;							// set field pointer to first field
			}
			switch(retv) {									// Process return value
				case EZ_KEY_F1:								// HELP
					EZ_ShootHelp();
					break;
				case EZ_KEY_F2:								// ROLL SETUP
					EZ_ShootSetup();
					FieldPtr = 1;
					break;
				case EZ_KEY_F3:								// CHANGE FRAME NUMBER
					EZ_ChangeFrame();
					FieldPtr = 1;
					break;
				case EZ_KEY_UP:								// UP ARROW - previous field
					FieldPtr = (FieldPtr == 1 ? 2 : 1);
					break;
				case EZ_KEY_DOWN:							// DOWN ARROW - next field
					FieldPtr = (FieldPtr == 2 ? 1 : 2);
					break;
				case EZ_KEY_F10:							// MAIN MENU
					LoopExit = EZ_TRUE;						// Set loop exit flag to true (force exit from the loop)
					break;
				case EZ_TRIP_CAMERA:						// FIRE CAMERA
					//--- CHECK FOR BLANK CARD ----------------------------------
					if (!strncmp(Exposure.Subject, EZ_BLANK_SUBJECT, EZ_SUBJECT_LEN)) {
						EZ_ErrorMessage();
						FieldPtr = 1;
						break;
					}
					//--- CHECK FOR SLATE, BLINK, & MULTIPOSE -------------------
					if ((strncmp(Exposure.Subject, EZ_SLATE_CODE, EZ_SUBJECT_LEN)) &&
						(strncmp(Exposure.Subject, EZ_MPOSE_CODE, EZ_SUBJECT_LEN)) &&
						(strncmp(Exposure.Subject, EZ_BLINK_CODE, EZ_SUBJECT_LEN))) {
						if ((!NoPackage) && (!OrderCount)) {		// if not no product & products were enterred for valid subject
							EZ_ErrorMessage();
						FieldPtr = 2;
							break;
						}
					}
					EZ_FireCamera();								// Fire the camera
					fprintf(CFFile, "%4.4d%2.2d%4.4d%-2.2s%-2.2s%+2d%-30.30s%-10.10s%\r\n", Exposure.Record, Exposure.SetupTag, Exposure.Frame, Exposure.Staff, Exposure.Sitting, Exposure.Density, Exposure.Order, Exposure.Subject);
					Exposure.Record++;								// Increment the record number
					Exposure.Frame++;						        // Increment the frame number
					strncpy(Exposure.Subject, EZ_BLANK_SUBJECT, EZ_SUBJECT_LEN);
					EZ_FillWithUnderscores(ProductCode, 0);         // Reset the package field
					EZ_ClearProducts();                             // Clear the package definitions
					NoPackage = 0;                                  // Clear No Package Indicator
					EZ_DisplayShootForm();                          // Initialize the POS screen
					FieldPtr = 1;                                   // Set the field pointer back to one
			}
		} while (!LoopExit);										// Loop until exit flag is set true
		fclose(CFFile);												// Close the exposure file
		fclose(STFile);												// Close the setup file
		return;
		}

	//--- PROCESS UNIT IDENTIFICATION FILE ----------------------------------
	int EZ_FileUnit(int Operation) {
		FILE *UnitFile;
		int retv = 0;
		char Temp[ 50 ];
		if ((UnitFile = fopen(EZ_UNITFILE, "r+b")) == NULL) {
			strncpy(Setup.Unit, EZ_BLANK_UNIT, EZ_UNIT_LEN);
			Operation = EZ_FILE_WRITE;
			if ((UnitFile = fopen(EZ_UNITFILE, "w+b")) == NULL)	EZ_Alarm("File Error [1]");
		}
		if (Operation == EZ_FILE_WRITE)	fprintf(UnitFile, "%s\r\n%s\r\n", EZ_VERSIONKEY, Setup.Unit);
		else {
			fgets(Temp, 50, UnitFile);			// Strip off EZ-SNAP ID.
			fgets(Setup.Unit, 10, UnitFile);
		}
		fclose(UnitFile);
		return( retv );
	}

	//--- PROCESS PASSWORD FILE ---------------------------------------------
	int EZ_FilePassword(int Operation) {
		FILE *PasswordFile;
		int retv = 0;
		if ((PasswordFile = fopen(EZ_PASSWORDFILE, "r+b")) == NULL) {
			strncpy(Security.Password, EZ_BLANK_PASSWORD, EZ_PASSWORD_LEN);
			Operation = EZ_FILE_WRITE;
			if ((PasswordFile = fopen(EZ_PASSWORDFILE, "w+b")) == NULL)	EZ_Alarm("File Error [1]");
		}
		if (Operation == EZ_FILE_WRITE)	fputs(Security.Password, PasswordFile);
		else fgets(Security.Password, 10, PasswordFile);
		fclose(PasswordFile);
		return(retv);
	}

	//--- FIRE THE CAMERA ---------------------------------------------------
	void EZ_FireCamera() {
		ComParamT oldparams;								// BIOS serial comm parameters
		ComParamT newparams = {8,3,4,0,0,0,0,0,0,0,0,0,3,30,0,0,0,0,4,0,0,0,50,1,};
		char *InQ, *OutQ;									// Serial comm queues
		newqs.OutQSize = 192+8+16;							// Setup output queue
		OutQ = malloc(newqs.OutQSize);						// Allocate output queue
		newqs.OutQSeg  = QSEG(OutQ);						// Determine segment offset
		newqs.InQSize  = 192+8+16;							// Setup input queue
		InQ = malloc(newqs.InQSize);						// Allocate input queue
		newqs.InQSeg   = QSEG(InQ);							// Determine segment offset
		EZ_BiosSerialInitQueues(EZ_DIRECT_SER_PORT,&newqs);
		EZ_BiosSerialGetParams(EZ_DIRECT_SER_PORT,&oldparams);
		EZ_BiosSerialSetParams(EZ_DIRECT_SER_PORT,&newparams);
		EZ_BiosSerialOpen(EZ_DIRECT_SER_PORT);
		EZ_BiosSerialSetCtlLines(EZ_DIRECT_SER_PORT, (unsigned char)1); // Fire the camera by setting the control line high.
		EZ_BiosSerialClose(EZ_DIRECT_SER_PORT);
		EZ_BiosSerialSetParams(EZ_DIRECT_SER_PORT,&oldparams);
		EZ_BiosSerialDeleteQueues();						// Remove the serial queues
		free(OutQ);											// Free Output Queue
		free(InQ);											// Free Input Queue
		return;
	}

	//--- DISPLAY THE SHOOT PICTURES FORM -----------------------------------
	void EZ_DisplayShootForm() {
		int intmOrder = 0, bytecount = 0;
		char tmpbuf[10];
		unsigned char intmRow = 3, intmCol = 0;
		sprintf(tmpbuf, "%4.4d", Exposure.Frame);
		BiosPutStrStay(0,  0,  4, "Roll", EZ_VID_REVERSE);
		BiosPutStrStay(0, 10,  5, "Frame", EZ_VID_REVERSE);
		BiosPutStrStay(0,  4,  5, Setup.twinchk, EZ_VID_NORMAL);
		BiosPutStrStay(0, 16,  4, tmpbuf, EZ_VID_NORMAL);
		BiosPutStrStay(1,  0, 4, "Subj", EZ_VID_REVERSE);
		BiosPutStrStay(1,  5,  EZ_SUBJECT_LEN, Exposure.Subject, EZ_VID_NORMAL);
		BiosPutStrStay(1,  16, EZ_PRODUCT_LEN, EZ_BLANK_PRODUCT, EZ_VID_NORMAL);
		sprintf(tmpbuf, "%+2d", Exposure.Density);
		BiosPutStrStay(2,  0, 4, "Dens", EZ_VID_REVERSE);
		BiosPutStrStay(2, 4, 2, tmpbuf, EZ_VID_NORMAL);
		
		if (strncmp(Exposure.Staff, EZ_BLANK_STAFF, EZ_STAFF_LEN)) BiosPutStrStay(2, 16, EZ_STAFF_LEN, Exposure.Staff, EZ_VID_REVERSE);
		else BiosPutStrStay(2, 16, EZ_STAFF_LEN, "   ", EZ_VID_NORMAL);
		if (strncmp(Exposure.Sitting, EZ_BLANK_SITTING, EZ_SITTING_LEN)) BiosPutStrStay(2, 8, EZ_SITTING_LEN, Exposure.Sitting, EZ_VID_REVERSE);
		else BiosPutStrStay(2, 8, EZ_SITTING_LEN, EZ_BLANK_SITTING, EZ_VID_NORMAL);
		if (NoPackage == 1)	BiosPutStrStay(2, 10, 6, "NO PKG", EZ_VID_REVERSE);
		else BiosPutStrStay(2, 10, 6, "      ", EZ_VID_NORMAL);
		//--- Display the order information
		for (intmOrder = 0; intmOrder < EZ_ORDER_MAX; intmOrder++) {
			for (bytecount = 0; bytecount < 3; bytecount++)
				tmpbuf[ bytecount ] = Exposure.Order[ (intmOrder * 3) + bytecount ];
			BiosPutStrStay(intmRow,  intmCol,  3, tmpbuf, EZ_VID_NORMAL);
			intmRow++;
			if (intmRow == 7) {
				intmRow = 3;
				switch(intmCol)	{
					case 0:
						intmCol = 5;
						break;
					case 5:
						intmCol = 10;
						break;
					case 10:
						intmCol = 15;
						break;
					case 15:
						intmCol = 0;
				}
			}
		}
		return;
	}

	//--- CLEAR THE CURRENT PRODUCT DEFINITIONS -----------------------------
	void EZ_ClearProducts()	{
		OrderCount = 0;
		Exposure.Density = 0;
		strncpy(Exposure.Order,   EZ_BLANK_ORDER,   EZ_ORDER_LEN);
		strncpy(Exposure.Sitting, EZ_BLANK_SITTING, EZ_SITTING_LEN);
		strncpy(Exposure.Staff,   EZ_BLANK_STAFF,   EZ_STAFF_LEN);
		return;
	}

	//--- DISPLAY SHOOT PICTURES HELP SCREEN --------------------------------
	void EZ_ShootHelp()	{
		EZ_ClearAndHome();
		BiosPutStrStay(0,  0,  20, "        HELP        ", EZ_VID_REVERSE);
		BiosPutStrStay(1,  0,   4, " F2 ", EZ_VID_REVERSE);
		BiosPutStrStay(1,  5,  12, "Change Setup", EZ_VID_NORMAL);
		BiosPutStrStay(2,  0,   4, " F3 ", EZ_VID_REVERSE);
		BiosPutStrStay(2,  5,  12, "Change Frame", EZ_VID_NORMAL);
		BiosPutStrStay(5,  0,   4, " F10", EZ_VID_REVERSE);
		BiosPutStrStay(5,  5,  12, "Exit to menu", EZ_VID_NORMAL);
		BiosPutStrStay(6,  0, strlen(EZ_VERSION), EZ_VERSION, EZ_VID_REVERSE);
		BiosGetChar();
		EZ_ClearAndHome();
		EZ_DisplayShootForm();
		return;
	}

	//--- DISPLAY SHOOT PICTURES SETUP FORM ---------------------------------
	void EZ_ShootSetup() {
		unsigned char weekday, day, month, year, century, hours, minutes, seconds;
		char twinchk[ EZ_TWINCHECK_LEN + 2 ];
		int retv = 0, FieldPtr = 1,	ExitFlag = 0, bytecount = 0;
		EZ_ClearAndHome();
		strncpy(twinchk, Setup.twinchk, EZ_TWINCHECK_LEN);
		BiosPutStrStay(0,  0,  20, "     ROLL SETUP    ", EZ_VID_REVERSE);
		BiosPutStrStay(1,  0,   6, "Cust  ", EZ_VID_NORMAL);
		BiosPutStrStay(2,  0,   6, "Photog", EZ_VID_NORMAL);
		BiosPutStrStay(3,  0,   6, "Lights", EZ_VID_NORMAL);
		BiosPutStrStay(4,  0,   6, "Camera", EZ_VID_NORMAL);
		BiosPutStrStay(5,  0,   6, "Roll  ", EZ_VID_NORMAL);
		BiosPutStrStay(6,  0,   6, "Mag   ", EZ_VID_NORMAL);
		BiosPutStrStay(6, 13,   6, "Type  ", EZ_VID_NORMAL);
		BiosPutStrStay(7,  0,   6, "Job   ", EZ_VID_NORMAL);
		BiosPutStrStay(1,  7,   EZ_CUST_LEN,      Setup.cust,    EZ_VID_NORMAL);
		BiosPutStrStay(2,  7,   EZ_PHOTOG_LEN,    Setup.photog,  EZ_VID_NORMAL);
		BiosPutStrStay(3,  7,   EZ_LIGHTS_LEN,    Setup.lights,  EZ_VID_NORMAL);
		BiosPutStrStay(4,  7,   EZ_CAMERA_LEN,    Setup.camera,  EZ_VID_NORMAL);
		BiosPutStrStay(5,  7,   EZ_TWINCHECK_LEN, twinchk,		 EZ_VID_NORMAL);
		BiosPutStrStay(6, 17,   EZ_WORK_TYPE_LEN, Setup.worktp,  EZ_VID_NORMAL);
		BiosPutStrStay(6,  7,   EZ_MAGAZINE_LEN,  Setup.mag,     EZ_VID_NORMAL);
		BiosPutStrStay(7,  7,   EZ_JOB_NUM_LEN,   Setup.job_num, EZ_VID_NORMAL);
		do {
			switch(FieldPtr) {
				case 1:
					retv = EZ_Input(Setup.cust, Field.DelimCust, 1, 7, EZ_CUST_LEN, EZ_TYPE_ALPHA);
					if ((Field.ReqCust[0] == 'Y') && (strncmp(Setup.cust, EZ_BLANK_CUST, EZ_CUST_LEN) == 0)) {
						EZ_ErrorMessage();
						FieldPtr--;
						}
					break;
				case 2:
					retv = EZ_Input(Setup.photog, Field.DelimPhotog, 2, 7, EZ_PHOTOG_LEN, EZ_TYPE_ALPHA);
					if ((Field.ReqPhotog[0] == 'Y') && (strncmp(Setup.photog, EZ_BLANK_PHOTOG, EZ_PHOTOG_LEN) == 0)) {
						EZ_ErrorMessage();
						FieldPtr--;
						}
					break;
				case 3:
					retv = EZ_Input(Setup.lights, Field.DelimLights, 3, 7, EZ_LIGHTS_LEN, EZ_TYPE_ALPHA);
					if ((Field.ReqLights[0] == 'Y') && (strncmp(Setup.lights, EZ_BLANK_LIGHTS, EZ_LIGHTS_LEN) == 0)) {
						EZ_ErrorMessage();
						FieldPtr--;
						}
					break;
				case 4:
					retv = EZ_Input(Setup.camera, Field.DelimCamera, 4, 7, EZ_CAMERA_LEN, EZ_TYPE_ALPHA);
					if ((Field.ReqCamera[0] == 'Y') && (strncmp(Setup.camera, EZ_BLANK_CAMERA, EZ_CAMERA_LEN) == 0)) {
						EZ_ErrorMessage();
						FieldPtr--;
						}
					break;
				case 5:
					retv = EZ_Input(twinchk, Field.DelimTwinChk, 5, 7, EZ_TWINCHECK_LEN, EZ_TYPE_NUMBER);
					if ((Field.ReqTwinChk[0] == 'Y') && (strncmp(twinchk, EZ_BLANK_TWINCHK, EZ_TWINCHECK_LEN) == 0)) {
						EZ_ErrorMessage();
						FieldPtr--;
						}
					break;
				case 6:
					retv = EZ_Input(Setup.mag, Field.DelimMag, 6, 7, EZ_MAGAZINE_LEN, EZ_TYPE_ALPHA);
					if ((Field.ReqMag[0] == 'Y') && (strncmp(Setup.mag, EZ_BLANK_MAGAZINE, EZ_MAGAZINE_LEN) == 0)) {
						EZ_ErrorMessage();
						FieldPtr--;
						}
					break;
				case 7:
					retv = EZ_Input(Setup.worktp,  Field.DelimWorkTp, 6, 17, EZ_WORK_TYPE_LEN, EZ_TYPE_ALPHA);
					if ((Field.ReqWorkTp[0] == 'Y') && (strncmp(Setup.worktp, EZ_BLANK_WORK_TYPE, EZ_WORK_TYPE_LEN) == 0)) {
						EZ_ErrorMessage();
						FieldPtr--;
						}
					break;
				case 8:
					retv = EZ_Input(Setup.job_num, Field.DelimJobNum, 7, 7, EZ_JOB_NUM_LEN, EZ_TYPE_ALPHA);
					if ((Field.ReqJobNum[0] == 'Y') && (strncmp(Setup.job_num, EZ_BLANK_JOB_NUM, EZ_JOB_NUM_LEN) == 0)) {
						EZ_ErrorMessage();
						FieldPtr--;
						}
					break;

				case 9:														// WRITE A NEW SETUP RECORD
					BiosGetDate(&weekday, &day, &month, &year, &century);   // SYMBOL get the current system date
					BiosGetTime(&hours, &minutes, &seconds);                // SYMBOL get the current system time
					sprintf(Setup.date, "%2.2x/%2.2x/%2.2x", (int)month, (int)day, (int)year);
					sprintf(Setup.time, "%2.2x:%2.2x", (int)hours, (int)minutes);
					if (strncmp(twinchk, Setup.twinchk, EZ_TWINCHECK_LEN) != 0)
						Exposure.Frame = 1;
					strncpy(Setup.twinchk, twinchk, EZ_TWINCHECK_LEN);
					Setup.SetupTag = Setup.SetupTag + 1;
					Exposure.SetupTag = Setup.SetupTag;
					bytecount = fprintf(STFile, "%-2.2d%-8.8s%-5.5s%-10.10s%-10.10s%-10.10s%-10.10s%-10.10s%-10.10s%-10.10s%-4.4s\r\n", Setup.SetupTag,Setup.date,Setup.time,Setup.cust,Setup.photog,Setup.lights,Setup.camera,Setup.worktp,Setup.job_num,Setup.twinchk,Setup.mag);
					if (bytecount != EZ_SETUP_RECLEN) EZ_Alarm("WRITE ERROR.");
					BiosBeep(EZ_SHORTSOUND);
					BiosBeep(EZ_SHORTSOUND);
					ExitFlag = EZ_TRUE;
				}
			switch(retv) {
				case EZ_KEY_UP:
					FieldPtr = (FieldPtr-1 < 1 ? 8 : FieldPtr - 1);
					break;
				default:
					FieldPtr = (FieldPtr+1 > 8 ? 9: FieldPtr + 1);
					break;
				}
		} while (!ExitFlag);
		EZ_ClearAndHome();
		EZ_DisplayShootForm();
		FieldPtr = 1;
		return;
	}

	//--- DISPLAY FRAME CHANGE FORM -----------------------------------------
	void EZ_ChangeFrame() {
		char Frame[ 10 ];
		EZ_ClearAndHome();
		sprintf(Frame, "%4.4d", Exposure.Frame);
		BiosPutStrStay(0,  0,  20, " ENTER FRAME NUMBER ", EZ_VID_REVERSE);
		BiosPutStrStay(1,  0,   5, "Frame", EZ_VID_NORMAL);
		BiosPutStrStay(1,  7,   4, Frame,   EZ_VID_NORMAL);
		EZ_Input(Frame, "", 1, 7, 4, EZ_TYPE_NUMBER);
		Exposure.Frame = atoi(Frame);
		BiosBeep(EZ_SHORTSOUND);
		EZ_ClearAndHome();
		EZ_DisplayShootForm();
		FieldPtr = 1;
		return;
	}

	//--- DISPLAY DATE/TIME SETUP FORM --------------------------------------
	void EZ_SetupDate()	{
		DOS_DATET CurDate, *pDate, CurTime, *pTime;
		char *p, buffer[40];
		unsigned char FirstRow;
		int done;
		AdlClearScreen();
		FirstRow = 3;
		AdlReverseVideo();
		AdlPrintAt((unsigned char)0,(unsigned char)0,"%-20s", "SETUP DATE & TIME");
		AdlNormalVideo();
		AdlPrintAt(7, 0, "%-20s", "Press Clear or Enter");
		done = 0;
		do {
			DosGetDate(&CurDate);
			p = AdlDosDateToFormat(&CurDate, DATE_DDMMYY);	
			strcpy(buffer, p);
			AdlPrintAt(FirstRow, (unsigned char)0, "%-20s", "Date: ");
			AdlKeyin(FirstRow, (unsigned char)6, buffer, "99/99/99", "MV1C.", ENTER, END);
			if (*buffer) {
				pDate = AdlFormatToDosDate(buffer, DATE_DDMMYY);
				if (pDate) {
					DosSetDate(pDate);
					done = 1;
				}
			}
		} while (!done);
		done = 0;
		do {
			DosGetTime(&CurTime);
			p = AdlDosTimeToFormat(&CurTime, TIME_HHMMSS_24);
			strcpy(buffer, p);
			AdlPrintAt((unsigned char)(FirstRow+1), (unsigned char)0, "%-20s", "Time: ");
			AdlKeyin((unsigned char)(FirstRow + 1), (unsigned char)6, buffer, "99:99:99", "MV1C.", ENTER, END);
			if (*buffer) {
				pTime = AdlFormatToDosTime(buffer, TIME_HHMMSS_24);
				if (pTime) {
					DosSetTime(pTime);
					done = 1;
				}
			}
		} while (!done);
	}

	//--- PROCESS CLEAR DATA MENU OPTION - DELETE ACTIVE FILES --------------
	void KillFiles() {
		char password[ EZ_PASSWORD_LEN + 10 ];
		strcpy(password, EZ_BLANK_PASSWORD);
		EZ_ClearAndHome();
		BiosPutStrStay(0,  0,  20, "  * ERASE DATA *   ", EZ_VID_REVERSE);
		BiosPutStrStay(1,  0,   9, "Password?",           EZ_VID_NORMAL);
		BiosPutStrStay(1, 10,   4, password,              EZ_VID_NORMAL);
		EZ_Input(password, "", 1, 10, EZ_PASSWORD_LEN, EZ_TYPE_ALPHA);
		if (!strncmp(password, Security.Password, EZ_PASSWORD_LEN)) {
			remove(EZ_SUBJECTFILE);
			remove(EZ_SETUPFILE);
			BiosBeep(EZ_SHORTSOUND);
		}
	}

	//--- PROCESS FIELD VALIDATION CODES ------------------------------------
	void EZ_EditFields(void) {
		int retv = 0, Page = 1,	FieldPtr = 1, ExitFlag = 0;
		do	{
			if (Page == 1) {					// PROCESS FIRST PAGE OF FIELDS
				EZ_ClearAndHome();
				BiosPutStrStay(0,  0, 20, "FIELD   REQ DEL    ", EZ_VID_REVERSE);
				BiosPutStrStay(1,  0, 20, "Cust    [ ] [ ]    ", EZ_VID_NORMAL);
				BiosPutStrStay(2,  0, 20, "Photog  [ ] [ ]    ", EZ_VID_NORMAL);
				BiosPutStrStay(3,  0, 20, "Lights  [ ] [ ]    ", EZ_VID_NORMAL);
				BiosPutStrStay(4,  0, 20, "Camera  [ ] [ ]    ", EZ_VID_NORMAL);
				BiosPutStrStay(5,  0, 20, "Roll    [ ] [ ]    ", EZ_VID_NORMAL);
				BiosPutStrStay(6,  0, 20, "WorkType[ ] [ ]    ", EZ_VID_NORMAL);
				BiosPutStrStay(1,  9,  1, Field.ReqCust,     EZ_VID_NORMAL);
				BiosPutStrStay(2,  9,  1, Field.ReqPhotog,   EZ_VID_NORMAL);
				BiosPutStrStay(3,  9,  1, Field.ReqLights,   EZ_VID_NORMAL);
				BiosPutStrStay(4,  9,  1, Field.ReqCamera,   EZ_VID_NORMAL);
				BiosPutStrStay(5,  9,  1, Field.ReqTwinChk,  EZ_VID_NORMAL);
				BiosPutStrStay(6,  9,  1, Field.ReqWorkTp,   EZ_VID_NORMAL);
				BiosPutStrStay(1, 13,  1, Field.DelimCust,   EZ_VID_NORMAL);
				BiosPutStrStay(2, 13,  1, Field.DelimPhotog, EZ_VID_NORMAL);
				BiosPutStrStay(3, 13,  1, Field.DelimLights, EZ_VID_NORMAL);
				BiosPutStrStay(4, 13,  1, Field.DelimCamera, EZ_VID_NORMAL);
				BiosPutStrStay(5, 13,  1, Field.DelimTwinChk,EZ_VID_NORMAL);
				BiosPutStrStay(6, 13,  1, Field.DelimWorkTp, EZ_VID_NORMAL);
				switch(FieldPtr) {
					case 1:
						retv = EZ_Input(Field.ReqCust,     "", 1, 9, 1, EZ_TYPE_ALPHA);
						if ((Field.ReqCust[0] != 'N') && (Field.ReqCust[0] != 'Y')) {
							EZ_ErrorMessage();
							Field.ReqCust[0] = 'N';
						}
						break;
					case 2:
						retv = EZ_Input(Field.DelimCust,   "", 1, 13, 1, EZ_TYPE_ALPHA);
						break;
					case 3:
						retv = EZ_Input(Field.ReqPhotog,   "", 2, 9, 1, EZ_TYPE_ALPHA);
						if ((Field.ReqPhotog[0] != 'N') && (Field.ReqPhotog[0] != 'Y')) {
							EZ_ErrorMessage();
							Field.ReqPhotog[0] = 'N';
						}
						break;
					case 4:
						retv = EZ_Input(Field.DelimPhotog, "", 2, 13, 1, EZ_TYPE_ALPHA);
						break;
					case 5:
						retv = EZ_Input(Field.ReqLights,   "", 3, 9, 1, EZ_TYPE_ALPHA);
						if ((Field.ReqLights[0] != 'N') && (Field.ReqLights[0] != 'Y')) {
							EZ_ErrorMessage();
							Field.ReqLights[0] = 'N';
						}
						break;
					case 6:
						retv = EZ_Input(Field.DelimLights, "", 3, 13, 1, EZ_TYPE_ALPHA);
						break;
					case 7:
						retv = EZ_Input(Field.ReqCamera,   "", 4, 9, 1, EZ_TYPE_ALPHA);
						if ((Field.ReqCamera[0] != 'N') && (Field.ReqCamera[0] != 'Y')) {
							EZ_ErrorMessage();
							Field.ReqCamera[0] = 'N';
						}
						break;
					case 8:
						retv = EZ_Input(Field.DelimCamera, "", 4, 13, 1, EZ_TYPE_ALPHA);
						break;
					case 9:
						retv = EZ_Input(Field.ReqTwinChk,  "", 5, 9, 1, EZ_TYPE_ALPHA);
						if ((Field.ReqTwinChk[0] != 'N') && (Field.ReqTwinChk[0] != 'Y')) {
							EZ_ErrorMessage();
							Field.ReqTwinChk[0] = 'N';
						}
						break;
					case 10:
						retv = EZ_Input(Field.DelimTwinChk,"", 5, 13, 1, EZ_TYPE_ALPHA);
						break;
					case 11:
						retv = EZ_Input(Field.ReqWorkTp,  "", 6, 9, 1, EZ_TYPE_ALPHA);
						if ((Field.ReqWorkTp[0] != 'N') && (Field.ReqWorkTp[0] != 'Y')) {
							EZ_ErrorMessage();
							Field.ReqWorkTp[0] = 'N';
						}
						break;
					case 12:
						retv = EZ_Input(Field.DelimWorkTp,"", 6, 13, 1, EZ_TYPE_ALPHA);
						break;
					case 13: {
						FieldPtr = 0;
						Page = 2;
					}
				}
				switch(retv) {
					case EZ_KEY_F2:
						EZ_SetFieldDefaults();
						break;
					case EZ_KEY_UP:
						FieldPtr = (FieldPtr-1 < 1 ? 12 : FieldPtr - 1);
						break;
					default:
						FieldPtr++;
						break;
				}
			}
			else {										// PROCESS SECOND PAGE OF FIELDS
				EZ_ClearAndHome();
				BiosPutStrStay(0,  0, 20, "FIELD   REQ DEL    ", EZ_VID_REVERSE);
				BiosPutStrStay(1,  0, 20, "Job     [ ] [ ]    ", EZ_VID_NORMAL);
				BiosPutStrStay(2,  0, 20, "Magazine[ ] [ ]    ", EZ_VID_NORMAL);
				BiosPutStrStay(3,  0, 20, "Subject     [ ]    ", EZ_VID_NORMAL);
				BiosPutStrStay(4,  0, 20, "Product     [ ]    ", EZ_VID_NORMAL);
				BiosPutStrStay(1,  9,  1, Field.ReqJobNum,       EZ_VID_NORMAL);
				BiosPutStrStay(1, 13,  1, Field.DelimJobNum,     EZ_VID_NORMAL);
				BiosPutStrStay(2,  9,  1, Field.ReqMag,          EZ_VID_NORMAL);
				BiosPutStrStay(2, 13,  1, Field.DelimMag,        EZ_VID_NORMAL);
				BiosPutStrStay(3, 13,  1, Field.DelimSubject,    EZ_VID_NORMAL);
				BiosPutStrStay(4, 13,  1, Field.DelimProduct,    EZ_VID_NORMAL);
				switch(FieldPtr) {
					case 1:
						retv = EZ_Input(Field.ReqJobNum,     "", 1, 9, 1, EZ_TYPE_ALPHA);
						if ((Field.ReqJobNum[0] != 'N') && (Field.ReqJobNum[0] != 'Y')) {
							EZ_ErrorMessage();
							Field.ReqJobNum[0] = 'N';
						}
						break;
					case 2:
						retv = EZ_Input(Field.DelimJobNum, "", 1, 13, 1, EZ_TYPE_ALPHA);
						break;
					case 3:
						retv = EZ_Input(Field.ReqMag, "", 2, 9, 1, EZ_TYPE_ALPHA);
						if ((Field.ReqMag[0] != 'N') && (Field.ReqMag[0] != 'Y')) {
							EZ_ErrorMessage();
							Field.ReqMag[0] = 'N';
						}
						break;
					case 4:
						retv = EZ_Input(Field.DelimMag,      "", 2, 13, 1, EZ_TYPE_ALPHA);
						break;
					case 5:
						retv = EZ_Input(Field.DelimSubject,  "", 3, 13, 1, EZ_TYPE_ALPHA);
						break;
					case 6:
						retv = EZ_Input(Field.DelimProduct,  "", 4, 13, 1, EZ_TYPE_ALPHA);
						break;
					case 7:
						ExitFlag = 1;
						break;
				}
				switch(retv) {
					case EZ_KEY_UP:
						if (FieldPtr - 1 < 1) {
							FieldPtr = 1;
							Page = 1;
							}
						else
							FieldPtr = FieldPtr-1;
						break;
					default:
						FieldPtr++;
						break;
				}
			}
		} while (!ExitFlag);
		EZ_FileFields( EZ_FILE_WRITE );
		EZ_ClearAndHome();
		return;
	}
	
	//--- PROCESS FIELD FILE ------------------------------------------------
	int EZ_FileFields(int Operation) {
		FILE *FieldFile;
		int retv = 0;
		if ((FieldFile = fopen(EZ_FIELDFILE, "r+b")) == NULL) {
			EZ_SetFieldDefaults();
			Operation = EZ_FILE_WRITE;
			if ((FieldFile = fopen(EZ_FIELDFILE, "w+b")) == NULL) EZ_Alarm("File Error [1]");
			}
		if (Operation == EZ_FILE_WRITE)	fwrite(&Field, sizeof(Field), 1, FieldFile);
		else fread(&Field, sizeof(Field), 1, FieldFile);
		fclose(FieldFile);
		return(retv);
	}

	//--- SET DEFAULT FIELD VALUES ------------------------------------------
	void EZ_SetFieldDefaults() {
		strncpy(Field.DelimCust,    EZ_DELIM_CUST, 1);
		strncpy(Field.DelimPhotog,  EZ_DELIM_PHOTOG, 1);
		strncpy(Field.DelimLights,  EZ_DELIM_LIGHTS, 1);
		strncpy(Field.DelimCamera,  EZ_DELIM_CAMERA, 1);
		strncpy(Field.DelimTwinChk, EZ_DELIM_TWIN_CHECK, 1);
		strncpy(Field.DelimWorkTp,  EZ_DELIM_WORK_TYPE, 1);
		strncpy(Field.DelimMag,     EZ_DELIM_MAG, 1);
		strncpy(Field.DelimJobNum,  EZ_DELIM_JOB, 1);
		strncpy(Field.DelimSubject, EZ_DELIM_SUBJECT, 1);
		strncpy(Field.DelimProduct, EZ_DELIM_PACKAGE, 1);
		strncpy(Field.AskCust,      EZ_ASK_PRIOR, 1);
		strncpy(Field.AskPhotog,    EZ_ASK_PRIOR, 1);
		strncpy(Field.AskLights,    EZ_ASK_PRIOR, 1);
		strncpy(Field.AskCamera,    EZ_ASK_PRIOR, 1);
		strncpy(Field.AskWorkTp,    EZ_ASK_PRIOR, 1);
		strncpy(Field.AskTwinChk,   EZ_ASK_PRIOR, 1);
		strncpy(Field.AskMag,       EZ_ASK_PRIOR, 1);
		strncpy(Field.AskJobNum,    EZ_ASK_PRIOR, 1);
		strncpy(Field.ReqCust,      EZ_YES, 1);
		strncpy(Field.ReqPhotog,    EZ_YES, 1);
		strncpy(Field.ReqLights,    EZ_YES, 1);
		strncpy(Field.ReqCamera,    EZ_YES, 1);
		strncpy(Field.ReqWorkTp,    EZ_YES, 1);
		strncpy(Field.ReqTwinChk,   EZ_YES, 1);
		strncpy(Field.ReqMag,       EZ_YES, 1);
		strncpy(Field.ReqJobNum,    EZ_YES, 1);
	}

	//--- PRODUCT VALIDATION CODES ------------------------------------------
	void EZ_EditProducts() {
		int ProdNum = 0, retv = 0, Page = 1, FieldPtr = 1, SubExit = 0, ExitFlag = 0;
		unsigned char row = 0, col = 0;
		char buf[25];
		do {											// Product validation editing loop
			if (Page == 1) {							// First page - set active or inactive
				EZ_ClearAndHome();
				BiosPutStrStay(0,  0, 20, " PRODUCT SETUP     ",    EZ_VID_REVERSE);
				BiosPutStrStay(1,  0, 20, "Enable products?   ",    EZ_VID_NORMAL);
				BiosPutStrStay(6,  0, 20, "PAGE 1/5           ",    EZ_VID_REVERSE);
				retv = EZ_Input(Products.Enabled, EZ_DELIM_QUESTION, 1, 17, 1, EZ_TYPE_ALPHA);
				if (Products.Enabled[0] == '0') Products.Enabled[0] = 'Y';
				if (Products.Enabled[0] == 'Y') {
					FieldPtr = 1;
					Page = 2;
				}
				else ExitFlag = 1;
			}
			else {										// Process product validation code entry
				EZ_ClearAndHome();
				BiosPutStrStay(0,  0, 20, "   PRODUCT SETUP    ",    EZ_VID_REVERSE);
				sprintf(buf, "PAGE [%d]/5          ", Page);
				BiosPutStrStay(6,  0, 20, buf, EZ_VID_REVERSE);
				row = 1;
				col = 0;
				for (ProdNum = 0; ProdNum < 20; ProdNum++)	{
					BiosPutStrStay(row, (col * 4), EZ_PRODUCT_LEN, Products.ValidProducts[ (((Page-2)*20) + ProdNum) ], EZ_VID_NORMAL);
					row++;
					if (row == 5) {
						row = 1;
						col++;
					}
				}
				row = 1;
				col = 0;
				SubExit = 0;
				do {
					retv = EZ_Input(Products.ValidProducts[  (((Page-2)*20) + (FieldPtr-1)) ], Field.DelimProduct, row, (col * 4), EZ_PRODUCT_LEN, EZ_TYPE_ALPHA);
					row++;
					if (row == 5) {
						row = 1;
						col++;
					}
					switch(retv) {
						case EZ_KEY_F2:
							EZ_SetDefaultProducts();
							Page = 2;
							SubExit = 1;
							break;
						case EZ_KEY_F10:
							SubExit = 1;
							ExitFlag = 1;
							break;
						case EZ_KEY_UP:
							if (FieldPtr - 1 < 1) {
								FieldPtr = 1;
								Page--;
								SubExit = 1;
							}
							else
								FieldPtr = FieldPtr - 1;
							break;
						default:
							if (FieldPtr + 1 > 20) {
								FieldPtr = 1;
								Page++;
								SubExit = 1;
							}
							else
								FieldPtr = FieldPtr + 1;
							break;
					}
					if (Page > 5)
						SubExit = 1;
				} while (!SubExit);
			}
		} while (!ExitFlag);
		EZ_FileProducts( EZ_FILE_WRITE );
		EZ_ClearAndHome();
		return;
	}

	//--- SET DEFAULT PRODUCT VALIDATION CODES ------------------------------
	void EZ_SetDefaultProducts() {
		int ProdNum = 0;
		strcpy(Products.Enabled, EZ_NO);
		for (ProdNum = 0; ProdNum < EZ_MAX_PRODUCTS; ProdNum++)
			strncpy(Products.ValidProducts[ ProdNum ], EZ_BLANK_PRODUCT, EZ_PRODUCT_LEN);
		return;
	}

	//--- PROCESS PRODUCT VALIDATION FILE -----------------------------------
	int EZ_FileProducts(int Operation) {
		FILE *ProductFile;
		int retv = 0, ProdNum = 0;
		if ((ProductFile = fopen(EZ_PRODUCTFILE, "r+b")) == NULL) {
			if ((ProductFile = fopen(EZ_PRODUCTFILE, "w+b")) == NULL) EZ_Alarm("File Error [1]");
			EZ_SetDefaultProducts();
			Operation = EZ_FILE_WRITE;
			}
		if (Operation == EZ_FILE_WRITE)	fwrite(&Products, sizeof(Products), 1, ProductFile);
		else fread(&Products, sizeof(Products), 1, ProductFile);
		fclose(ProductFile);
		return(retv);
	}
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*               M E N U   AND   F I E L D   R O U T I N E S                */
/*               M E N U   AND   F I E L D   R O U T I N E S                */
/*               M E N U   AND   F I E L D   R O U T I N E S                */
/*               M E N U   AND   F I E L D   R O U T I N E S                */
/*                                                                          */
/*--------------------------------------------------------------------------*/

	//--- PROCESS DATA ENTRY FIELD --------------------------------------
	int EZ_Input(char *InputData, char *Delimeter, unsigned char InputRow, unsigned char InputCol, int InputLen, int NumberMode) {
		int	InputByteCount = 0,	DataScanned = 0, Byte = 0, retv = 0, CharOffset = 0;
		char BarCode[ EZ_MAX_SCAN_LEN +1 ], TmpBuff[ EZ_MAX_SCAN_LEN +1 ];
		unsigned char EnterHit = EZ_FALSE, KeyMode = 0, currow = 0, curcol = 0;
		do {														// Low level data input loop
			BiosSetCursorPos(InputRow, (unsigned char)(InputCol + CharOffset));	
			InputByteCount = EZ_GetData(BarCode, &DataScanned);		// get data from the console
			if (InputByteCount) {									// if characters were returned
				if (DataScanned == EZ_TRUE) {						// Data processed from laser scanner
       				EZ_FillWithUnderscores(BarCode, InputByteCount); // blank fill bar code to EZ_MAX_SCAN_LEN characters
					if (Delimeter[0] != '\0') {						// If a delimeter was specified
						if (BarCode[0] != Delimeter[0])				// Delimeters do not match
							EZ_ErrorMessage();						// Process error message
						else {										// Delimeters match, strip them off
							for (Byte=1;Byte<=(InputByteCount-2);Byte++)
								TmpBuff[Byte-1] = BarCode[Byte];
							for (Byte=InputByteCount-2;Byte<=InputLen;Byte++)
								TmpBuff[Byte] = '_';
							TmpBuff[(InputLen+1)] = '\0';
							sprintf(BarCode, "%s\0", TmpBuff);
							BiosPutStrMove(InputRow, InputCol, InputLen, BarCode, EZ_VID_NORMAL);
							strcpy(InputData, BarCode);				// Copy the data enterred into the source buffer
       						EnterHit = EZ_TRUE;						// Set the enter key to hit (auto-enter on scans)
							retv = EZ_USER_SCANNED;					// Set return value to scanned input flag
						}
					}
					else {											// Delimeters were NOT specified
						BiosPutStrMove(InputRow, InputCol, InputLen, BarCode, EZ_VID_NORMAL);
       					strncpy(InputData, BarCode, InputLen);		// Copy the data enterred into the source buffer
						InputData[InputLen+1]='\0';					// append a null byte
       					EnterHit = EZ_TRUE;							// Set the enter key to hit (auto-enter on scans)
       					retv = EZ_USER_SCANNED;						// Set return value to scanned input flag
					}
				}													// ----------------------------------------------
				else {												// Else a key was hit on the keypad (not a scan!)
					switch (*BarCode) {								// Test the character returned
						case 0:										// if 0, then the key was extended (shift/func modified)
		                	InputByteCount = EZ_GetData(BarCode, &DataScanned); // Get the extended key code
							retv = *BarCode;						// Simply store the keycode for testing in form process
							break;									// Break the test
						case EZ_TRIP_CAMERA:						// If key_shoot, the user pressed the SHOOT key [.]
							retv = EZ_TRIP_CAMERA;					// Set return value to the shoot key code (defined in MAIN.H)
							break;									// Break the test
						case EZ_KEY_BACKSPACE:						// The user hit the backspace key
							if (CharOffset > 0) { 					// If the index in the buffer is greater than zero
								InputData[--CharOffset] = '_';		// Set the previous character in the input buffer to underscore
								BiosGetCursorPos(&currow, &curcol);	// SYMBOL get the cursor position
								if (curcol == 0) {					// if the current column is 0
		    						currow--;						// Go to the previous row
   									curcol = EZ_VID_LASTCOL;		// Set cursor column to last column on the screen
   									BiosSetCursorPos(currow, curcol); // SYMBOL set tye physical cursor location
   								}
								else								// Else the cursor is not at the first column
									BiosPutCharMove(0x08);			// SYMBOL move the physical cursor back a space
								BiosPutCharStay('_');				// SYMBOL display the underscore symbol (i.e. car rubbed out)
  								}
							else 									// Else at the start of the data entry field
								BiosBeep(EZ_SHORTSOUND);			// SYMBOL give the user a warning beep
							break;									// Break the test
						case EZ_KEY_ESCAPE:							// The user pressed the ESCAPE key
							if (CharOffset == 0)					// If at the start of the buffer
                   				BiosBeep(EZ_SHORTSOUND);			// SYMBOL beep
							else {									// else within the buffer, clear the entire entry
								EZ_FillWithUnderscores(InputData, 0); // Fill the current input field with underscores
								CharOffset = 0;						// Set the character offset back to beginning
								BiosPutStrStay(InputRow, InputCol, InputLen, InputData, EZ_VID_NORMAL);     // Display the field
							}
							break;									// Break the test
       					case EZ_KEY_ENTER:							// The user hit ENTER
							EnterHit = EZ_TRUE;						// Set the enter hit flag
							retv = EZ_KEY_ENTER;
							break;									// Break the test
						default: {									// Another character was hit, stuff it into the input buffer
							if (CharOffset < (unsigned char) InputLen) {
								if (FireMode == 1) {
	                        		if ((*BarCode == 'A') ||
										(*BarCode == 'B') ||
										(*BarCode == 'C') ||
										(*BarCode == 'D') ||
										(*BarCode == 'E') ||
										(*BarCode == 'F') ||
										(*BarCode == 'G') ||
										(*BarCode == 'H') ||
										(*BarCode == 'I') ||
										(*BarCode == 'J') ||
										(*BarCode == 'K') ||
										(*BarCode == 'L') ||
										(*BarCode == 'a') ||
										(*BarCode == 'b') ||
										(*BarCode == 'c') ||
										(*BarCode == 'd') ||
										(*BarCode == 'e') ||
										(*BarCode == 'f') ||
										(*BarCode == 'g') ||
										(*BarCode == 'h') ||
										(*BarCode == 'i') ||
										(*BarCode == 'j') ||
										(*BarCode == 'k') ||
										(*BarCode == 'l') ||
										(*BarCode == '[') ||										
										(*BarCode == ']') ||
										(*BarCode == '\'') ||
										(*BarCode == '=') ||
										(*BarCode == '*') ||
										(*BarCode == '/') ||
										(*BarCode == ',') ||
										(*BarCode == '\\') ||
										(*BarCode == ';') ||
										(*BarCode == '+')) {
	                         				retv = EZ_TRIP_CAMERA;
										break;
									}
								}
								if ((!NumberMode) ||				// If not locked on numbers
									((NumberMode)  &&			// OR locked on numbers and the input IS numeric (0..9)
									((*BarCode >= '0') &&		// greater than 0
									(*BarCode <= '9')))) {		// less than 9
									InputData[CharOffset++] = *BarCode; // Stuff the character
									BiosPutStrStay(InputRow, InputCol, InputLen, InputData, EZ_VID_NORMAL); // SYMBOL display the character
									if (InputLen == 1)			// If single character input field
		                             	EnterHit = EZ_TRUE;		// Set the enter hit key to TRUE (force exit)											
								}
								else EZ_ErrorMessage();
							}
							else {								// else at the end of the field
								EnterHit = EZ_TRUE;				// Set the enter hit key to TRUE (force exit)
								break;
							}
						}
					}
  					}
   				}
			} while ((!EnterHit) && (!retv));
		return(retv);										// Return field exit mode
	}

	//--- LOW LEVEL INPUT FUNCTION ------------------------------------------
	int EZ_GetData(char *Databuf, int *DataScanned) {		// Handle scanning of barcode or single key input
		IoctlT iob;
		int	count = 0, RemainingCharCount = 0;
		char InputBuffer[30];								// Buffer containing barcode label
		*DataScanned = EZ_FALSE;							// Initialize the data scanned flag to false
		DosRead(ConsoleHandle, InputBuffer, 1, &count);		// SYMBOL read the console using DOS (into input buffer)
		if (count)	{										// If characters were read from the console
		    iob.funcode = ConsIoctlGetCharStatus;			// Console error status (scan error?)
			DosIoCtrlRdData(ConsoleHandle, &iob, ConsIoctlGetCharStatusLen); // Read console control structure information
			if ((iob.data.charstatus.source == EZ_SOURCE_CONTACT)  ||		 // If source of data was contact
				(iob.data.charstatus.source == EZ_SOURCE_LASER)) {			 // if source of data was laser
				if ((RemainingCharCount = iob.data.charstatus.labellen - 1)) { // If characters remain to be read
		        	DosRead(ConsoleHandle, InputBuffer + 1, RemainingCharCount, &count);	// Read remaining characters into input buffer
		    		count++;								// Increment the character count
      			}
				if (count > EZ_MAX_SCAN_LEN)				// If the count is larger than the maximum barcode size
			    	count = EZ_MAX_SCAN_LEN;				// Set to maximum size
				*DataScanned = EZ_TRUE;						// Set the data scanned indicator to true
			}
			strncpy(Databuf, InputBuffer, count);			// Copy local input buffer to source data buffer
			Databuf[count] = '\0';							// Null terminate the source data buffer
		}
		return(count);										// return the size of the source data buffer
	}

	//--- PROCESS MENU ------------------------------------------------------
	int EZ_GetMenuSelection(int MenusID, int cSelection) {
		int ii,	retval = -2, MenuItem;
		char tstr[sizeof(Kqueue)];
		unsigned int  iUserKey;
		unsigned char Rows,	Cols;
		EZ_ClearAndHome();
		BiosGetLogScrSize(&Rows,&Cols);
		Rows--; Cols--;										// Make 0 Relative
		scrn.Rows = Rows;
		scrn.Cols = Cols;
		scrn.Border = 1;
		scrn.SRow = 0;
		EZ_DrawBorder(Rows,Cols, Menus[MenusID].Title);
		scrn.Items = (unsigned char) MenuSizes[MenusID];
		scrn.HItem = scrn.TItem = 0;
		scrn.BItem = EZ_Menu_DisplayItemsAll( scrn.Border + scrn.SRow, MenusID );
		if (scrn.LastSelection < 0 || scrn.LastSelection > (int) scrn.Items)
			scrn.LastSelection = 0;
		MenuItem = cSelection;
		memset(Kqueue,0x00,sizeof(Kqueue));
		BiosHideCursor();
		do {
			EZ_DisplayItem(MenusID, MenuItem, strlen(Kqueue));
			BiosShowCursor();
			iUserKey = BiosGetChar();
			BiosHideCursor();
			switch( iUserKey ) {
				case EZ_MENU_KEY_ENTER:
					retval = MenuItem;
					break;
				case EZ_MENU_KEY_UP:
					if ((--MenuItem) < 0)
						MenuItem = scrn.Items-1;			// Roll Back
					memset(Kqueue,0x00,sizeof(Kqueue));
					break;
				case EZ_MENU_KEY_DOWN:
					if ((++MenuItem) > scrn.Items-1)
						MenuItem = 0;						// Roll Over
					memset(Kqueue,0x00,sizeof(Kqueue));
					break;
				case EZ_MENU_KEY_LEFT:
					MenuItem = 0;
					memset(Kqueue,0x00,sizeof(Kqueue));
					break;
				case EZ_MENU_KEY_RIGHT:
					MenuItem = scrn.Items-1;
					memset(Kqueue,0x00,sizeof(Kqueue));
					break;
				case EZ_MENU_KEY_ESCAPE:
					retval = -1;
					break;
				default:
					if (iUserKey == EZ_MENU_KEY_BACKSPACE && strlen(Kqueue) > 0) /* BACKSPACE */
						Kqueue[ (strlen(Kqueue) - 1) ] = 0x00;
					memcpy(tstr,Kqueue,sizeof(tstr));
					tstr[strlen(Kqueue)] = (char) (iUserKey & 0x00FF);
					for (ii = MenuItem; ii < (int) scrn.Items; ii++) {
						if (!strnicmp(tstr,Menus[MenusID].menu[ii].mstr,strlen(tstr))) {
							Kqueue[strlen(Kqueue)] = (char) ( iUserKey & 0x00FF);
							MenuItem = ii;
							ii = -1;
							break;
						}
					}
					if (ii != -1) {							// Go back to the top
						for (ii = 0; ii < MenuItem; ii++) {
							if (!strnicmp(tstr,Menus[MenusID].menu[ii].mstr,strlen(tstr))) {
								Kqueue[strlen(Kqueue)] = (char) ( iUserKey & 0x00FF);
								MenuItem = ii;
								break;
							}
						}
					}
					break;
			}
		} while( retval == -2  );							// Loop until a selection is made
		BiosShowCursor();									// Show the cursor
		scrn.LastSelection = retval;
		return( scrn.LastSelection );
	}

	//--- DISPLAY MENU ITEM -------------------------------------------------
	void EZ_DisplayItem(int MenusID, int LastSelection, unsigned int HiLite) {
		char str[20];
		BiosPutStrMove((unsigned char)(scrn.HItem-scrn.TItem+scrn.Border+scrn.SRow),(unsigned char)1,(unsigned char)18, Menus[MenusID].menu[scrn.HItem].mstr,EZ_VID_NORMAL);
		if ((unsigned char) LastSelection >= scrn.TItem && (unsigned char) LastSelection <= scrn.BItem) {
			scrn.HItem = (unsigned char) LastSelection;
			BiosPutStrMove( (unsigned char) (LastSelection-scrn.TItem+scrn.Border+scrn.SRow), (unsigned char)1, (unsigned char)18, Menus[MenusID].menu[LastSelection].mstr, EZ_VID_REVERSE);
		}
		else {												// Scroll menu
			if (LastSelection < scrn.TItem - 1) {			// more than 1 jump up
				EZ_MenuScroll( EZ_MENU_SCROLL_UP, 0, scrn.Rows-scrn.Border );
				scrn.HItem = scrn.TItem = (unsigned char) LastSelection;
				scrn.BItem = EZ_Menu_DisplayItemsAll( scrn.TItem + scrn.Border + scrn.SRow, MenusID );
				BiosPutStrMove((unsigned char) (LastSelection-scrn.TItem+scrn.Border+scrn.SRow),(unsigned char)1,(unsigned char)18, Menus[MenusID].menu[LastSelection].mstr,EZ_VID_REVERSE);
			}
			else if (LastSelection > scrn.BItem + 1) {		// more than 1 jump down
				EZ_MenuScroll( EZ_MENU_SCROLL_UP, 0, scrn.Rows-scrn.Border-scrn.SRow );
				scrn.HItem = scrn.BItem = (unsigned char) LastSelection;
				scrn.TItem = (unsigned char)(scrn.BItem - scrn.Rows + (scrn.Border * 2) + scrn.SRow);
				EZ_Menu_DisplayItemsAll( scrn.Border + scrn.SRow, MenusID );
				BiosPutStrMove((unsigned char) (LastSelection-scrn.TItem+scrn.Border+scrn.SRow),(unsigned char)1,(unsigned char)18, Menus[MenusID].menu[LastSelection].mstr,EZ_VID_REVERSE);
			}
			else if ((unsigned char) LastSelection > scrn.BItem) {	// going down past the bottom
				EZ_MenuScroll( EZ_MENU_SCROLL_UP, 1, scrn.Rows-scrn.Border );
				scrn.BItem = scrn.HItem = (unsigned char ) LastSelection;
				scrn.TItem++;	
				BiosPutStrMove((unsigned char) (LastSelection-scrn.TItem+scrn.Border+scrn.SRow),(unsigned char)1,(unsigned char)18, Menus[MenusID].menu[LastSelection].mstr,EZ_VID_REVERSE);
			}
			else if ((unsigned char) LastSelection < scrn.TItem) {  // going up past the top
				EZ_MenuScroll( EZ_MENU_SCROLL_DOWN, 1, scrn.Rows-scrn.Border );
				scrn.TItem = scrn.HItem = (unsigned char) LastSelection;
				scrn.BItem--;	
				BiosPutStrMove((unsigned char) (LastSelection-scrn.TItem+scrn.Border+scrn.SRow),(unsigned char)1,(unsigned char)18, Menus[MenusID].menu[LastSelection].mstr,EZ_VID_REVERSE);
			}
		}
		if (HiLite > 0)	{
			HiLite--;
			BiosSetCursorPos((unsigned char) (LastSelection-scrn.TItem+scrn.Border+scrn.SRow),(unsigned char)(1+HiLite));
			BiosPutCharAttr(*((Menus[MenusID].menu[LastSelection].mstr)+HiLite), EZ_VID_NORMAL,1);
		}
		if (scrn.Border) {
			EZ_MenuDisplayItem(str,scrn.HItem+1,scrn.Items);
			BiosPutStrMove(scrn.Rows,(unsigned char)(scrn.Cols-strlen(str)-1), strlen(str),str,EZ_VID_NORMAL);
		}
		else {
			BiosSetCursorPos(1,scrn.Cols);
			if (scrn.HItem == 0)
				BiosPutCharAttr(0x19, EZ_VID_NORMAL,1);
			else if (scrn.HItem == (unsigned char)(scrn.Items-1))
				BiosPutCharAttr(0x18, EZ_VID_NORMAL,1);
			else
				BiosPutCharAttr(0x12, EZ_VID_NORMAL,1);
			BiosSetCursorPos((unsigned char) (LastSelection-scrn.TItem+scrn.Border+scrn.SRow),scrn.Cols);
		}
		return;
	}
	void EZ_MenuDisplayItem(char *str, unsigned int CItem, unsigned int TItems) {
		register int ii;
		strcpy(str,"Item    of   ");
		ii = 6;
		while(CItem != 0) {
			str[ii] = (char) (((int)CItem % 10) + '0');
			CItem /= 10;
			ii--;
		}
		ii = 12;
		while(TItems != 0) {
			str[ii] = (char) (((int) TItems % 10) + '0');
			TItems /= 10;
			ii--;
		}
	}
	unsigned char EZ_Menu_DisplayItemsAll( int StartVal, int MenusID ) {
		register int jj,ii;
		for (ii = StartVal, jj = (int) scrn.TItem; (ii <= (int) (scrn.Rows - scrn.Border) && jj < (int) scrn.Items); jj++,ii++)
			BiosPutStrMove((unsigned char) ii,1,18, Menus[MenusID].menu[jj].mstr,EZ_VID_NORMAL);
		return((unsigned char)(jj - 1));
	}
	void EZ_MenuScroll( unsigned char dir, unsigned char lines, int arg2 ) {
		if (dir == EZ_MENU_SCROLL_DOWN) {
			BiosScrollDown((unsigned char)(scrn.Border+scrn.SRow),1,(unsigned char) arg2, (unsigned char) (scrn.Cols-1),lines,EZ_VID_NORMAL);
		}
		else {
			BiosScrollUp  ((unsigned char)(scrn.Border+scrn.SRow),1,(unsigned char) arg2, (unsigned char) (scrn.Cols-1),lines,EZ_VID_NORMAL);
		}
	}
/*--------------------------------------------------------------------------*/
/*                                                                          */
/*           T R A N S F E R   D I R E C T   R O U T I N E S                */
/*           T R A N S F E R   D I R E C T   R O U T I N E S                */
/*           T R A N S F E R   D I R E C T   R O U T I N E S                */
/*           T R A N S F E R   D I R E C T   R O U T I N E S                */
/*                                                                          */
/*--------------------------------------------------------------------------*/

	//--- TRANSFER DIRECT TO PC THROUGH SERIAL PORT -------------------------
	void EZ_TransferDirect() {
		int Error = 0;										// Error condition
		DosOpen("COM1",READWRITE,&handle);
		EZ_XmodemXON();
		EZ_XmodemOpen();
		EZ_ClearAndHome();
		printf("\nStarting...");
	
		//---- SEND START OF TRANSMISSION CHARACTERS ----------------------------
		Error = EZ_XmodemSend("SSSSSS", 6);
		if (!Error) {
			EZ_XModemConfig();
			EZ_XmodemOpen();
			printf("\nxMODEM SetupFile");
			Error = EZ_DirectXModem(EZ_SETUPFILE);			// Send setup file
			if (!Error) {
				EZ_XModemHeader(0,1);
				EZ_XModemSendEnd();
				EZ_XModemClose();
				EZ_XModemConfig();
				EZ_XmodemOpen();
				printf("\nxMODEM UnitFile");
				Error = EZ_DirectXModem(EZ_UNITFILE);
				if (!Error) {
					EZ_XModemHeader(0,1);
					EZ_XModemSendEnd();
					EZ_XModemClose();
					EZ_XModemConfig();
					EZ_XmodemOpen();
					printf("\nxMODEM Subject");
					EZ_DirectXModem(EZ_SUBJECTFILE);
					EZ_XModemHeader(0,1);
					EZ_XModemSendEnd();
					EZ_XModemClose();
					EZ_XmodemXON();
				}
			}
		}
		EZ_XModemClose();
		DosClose(handle);
		if (!Error)	KillFiles();
		return;
	}

	//--- SEND A FILE USING X-MODEM PROTOCOL --------------------------------
	int	EZ_DirectXModem(char *fname) {
		FILE *in;
		int	rlen   = 0,
			Error  = 0,
			retval = 0;
		char buff[128];
		EZ_XModemHeader(0,0);
		in = fopen(fname,"rb");
		if (in != NULL) {
			while ((rlen = fread(buff, 1, sizeof(buff), in ))) {
				Error = EZ_XmodemSend( buff, rlen );
				if (Error) {
					retval = -1;
					break;
				}
			}
		}
		else {
			EZ_Alarm("Can't find input file");
			retval = -1;
		}
		fclose(in);
		EZ_XModemHeader(0,0);
		return(retval);
	}

	//--- SEND AN INDIVIDUAL STRING USING X-MODEM ---------------------------
	int EZ_XmodemSend(char *buffer, int len) {
		int count = 0,								// Number of characers to send
			retval = 0;								// Return value
		DosWrite( handle, buffer, len, &count);
		if (count != len)
			retval = -1;
		ioctl.funcode = ComIoctlGetWrStatus;
		if ( DosIoCtrlRdData(handle,(char *)&ioctl,ComIoctlFunctionLen) != ComIoctlFunctionLen )
		    retval = -1;
		return( retval );
	}

	//--- DISPLAY X-MODEM ERROR MESSAGES ------------------------------------
	int EZ_XModemError(char *name) {
		if ( err && ( err != 0x50 && err != 0x51 && err != 0x52) ) {
	  		printf ("%s=%.4X\n",name,err);
			if ( err ) {
				printf("\nAborting session\n");
				ioctl.funcode = ComIoctlAbortProtocol;
				DosIoCtrlWrData(handle,(char *)&ioctl,ComIoctlFunctionLen);
				ioctl.funcode = ComIoctlCloseLine;
				ioctl.data.index = 0;
				DosIoCtrlWrData(handle,(char *)&ioctl,ComIoctlFunctionLen);
				BiosBeep(500);
				ioctl.funcode = ComIoctlFlushInputQ;
				DosIoCtrlWrData(handle,(char *)&ioctl,ComIoctlComParamLen);
				ioctl.funcode = ComIoctlFlushOutputQ;
				DosIoCtrlWrData(handle,(char *)&ioctl,ComIoctlComParamLen);
				ioctl.funcode = ComIoctlCloseProtocol;
				DosIoCtrlWrData(handle,(char *)&ioctl,ComIoctlFunctionLen);
				ioctl.funcode = ComIoctlCloseLine;
				ioctl.data.index = 0;
				DosIoCtrlWrData(handle,(char *)&ioctl,ComIoctlFunctionLen);
				DosClose(handle);
				return(err);
			}
		}
	}

	//--- PROCESS X-MODEM CONFIGURATION -------------------------------------
	void EZ_XModemConfig() {
		unsigned int DeviceInfo;
		EZ_BiosTxDone(0);	 							/* wait till COM1 empty		*/
		DeviceInfo = DosIoCtrlGetInfo(handle);
		if ( ( DeviceInfo & ISDEVICE ) == 0 )
			err = -1;
		else
		    err = 0;
		ioctl.funcode = ComIoctlFlushInputQ;
		DosIoCtrlWrData(handle,(char *)&ioctl,ComIoctlComParamLen);
		EZ_XModemError("Get Info");
		DeviceInfo |= RAWMODE;
		DosIoCtrlSetInfo(handle,DeviceInfo);
		ioctl.data.comparameters.databits       	= DATABITS8;
		ioctl.data.comparameters.parity         	= PARITYNONE;
		ioctl.data.comparameters.flowctl        	= NOFLOWCTL;
		ioctl.data.comparameters.baudrate             = BAUD19200;
		ioctl.data.comparameters.stopbits       	= STOPBITS1;
		ioctl.data.comparameters.duplex         	= DUPLEXFULL;
		ioctl.data.comparameters.modemdelay     	= 0;
		ioctl.data.comparameters.dsrwait        	= 30;
		ioctl.data.comparameters.cdwait         	= 0;		 	/* ignore carrier	*/
		ioctl.data.comparameters.marktime       	= 0;
		ioctl.data.comparameters.spacetime      	= 0;
		ioctl.data.comparameters.linecondflags  	= CTSCOND | DSRCOND;
		ioctl.data.comparameters.rxcharwait     	= 30;
		ioctl.data.comparameters.carrierlossdetect = 3;
		ioctl.data.comparameters.ctslossdetect  	= 3;
		ioctl.funcode = ComIoctlComParamCmd;
		if ( DosIoCtrlWrData(handle,(char *)&ioctl,ComIoctlComParamLen) != ComIoctlComParamLen)
			err = -1;
		else
		    err = ioctl.errcode;
		EZ_XModemError("Set Parm");
		ioctl.funcode = ComIoctlSelectProtCmd;
		ioctl.data.selectprotocol.protocol = 0x36;						// XMODEM
		if ( DosIoCtrlWrData(handle, (char *)&ioctl, ComIoctlSelectProtLen) != ComIoctlSelectProtLen)
			err = -1;
		else
		    err = ioctl.errcode;
		EZ_XModemError("Set Prot");
	}

	void EZ_XmodemXON() {
		unsigned int DeviceInfo;
		DeviceInfo = DosIoCtrlGetInfo(handle);
		if ( ( DeviceInfo & ISDEVICE ) == 0 )
			err = -1;
		else
		    err = 0;
	    EZ_XModemError("Get Info");
		DeviceInfo |= RAWMODE;
		DosIoCtrlSetInfo(handle,DeviceInfo);
		ioctl.data.comparameters.databits       = DATABITS8;
		ioctl.data.comparameters.parity         = PARITYNONE;
		ioctl.data.comparameters.flowctl        = NOFLOWCTL;
		ioctl.data.comparameters.baudrate       = BAUD19200;
		ioctl.data.comparameters.stopbits       = STOPBITS1;
		ioctl.data.comparameters.duplex         = DUPLEXFULL;
		ioctl.data.comparameters.modemdelay     = 10;
		ioctl.data.comparameters.dsrwait        = 0;
		ioctl.data.comparameters.cdwait         = 0;
		ioctl.data.comparameters.marktime       = 0;
		ioctl.data.comparameters.spacetime      = 0;
		ioctl.data.comparameters.linecondflags  = MODEMLINECOND;
		ioctl.data.comparameters.rxcharwait     = 3;
		ioctl.data.comparameters.connectwait    = 0;
		ioctl.data.comparameters.dtrsettle      = 500;
		ioctl.funcode = ComIoctlComParamCmd;
		if ( DosIoCtrlWrData(handle, (char *)&ioctl, ComIoctlComParamLen) != ComIoctlComParamLen)
			err = -1;
		else
			err = ioctl.errcode;
		EZ_XModemError("Set Parm");
		ioctl.funcode = ComIoctlSelectProtCmd;
		ioctl.data.selectprotocol.protocol = DOSSTD;
		if ( DosIoCtrlWrData(handle, (char *)&ioctl, ComIoctlSelectProtLen) != ComIoctlSelectProtLen)
			err = -1;
		else
		    err = ioctl.errcode;
		EZ_XModemError("Set Prot");
	}
	
	int EZ_XmodemOpen() {
		ioctl.funcode = ComIoctlOpenLine;
		if ( DosIoCtrlWrData(handle,(char *)&ioctl,ComIoctlFunctionLen) != ComIoctlFunctionLen )
			err = -1;
		else
		    err = ioctl.errcode;
		if ( err ) {
			EZ_XModemError("\nOpen Line Failed\n");
			BiosBeep(500);
			BiosGetChar();
			return(err);
		}
		else
			EZ_XModemError("Open Line");
		ioctl.funcode = ComIoctlStartProtocol;
		if ( DosIoCtrlWrData(handle,(char *)&ioctl,ComIoctlFunctionLen) != ComIoctlFunctionLen )
			err = -1;
		else
		    err = ioctl.errcode;
		if ( err ) {
			ioctl.funcode = ComIoctlCloseLine;
			ioctl.data.index = 0;
			DosIoCtrlWrData(handle,(char *)&ioctl,ComIoctlFunctionLen);
			EZ_XModemError("\nStart Proto Failed\n");
			BiosBeep(500);
			BiosGetChar();
			return(err);
		}
		else
			EZ_XModemError("Open Port");
	}

	void EZ_XModemSendEnd() {
		ioctl.funcode = ComIoctlSendEnd;
		if ( DosIoCtrlWrData(handle,(char *)&ioctl,ComIoctlFunctionLen) != ComIoctlFunctionLen )
			err = -1;
		else
		    err = ioctl.errcode;
		EZ_XModemError("Send End");
	}
	
	void EZ_XModemClose() {
		ioctl.funcode = ComIoctlCloseProtocol;
		if ( DosIoCtrlWrData(handle,(char *)&ioctl,ComIoctlFunctionLen) != ComIoctlFunctionLen )
			err = -1;
		else
		    err = ioctl.errcode;
		EZ_XModemError("Close Prot");
		ioctl.funcode = ComIoctlCloseLine;
		ioctl.data.index = 0;
		if ( DosIoCtrlWrData(handle,(char *)&ioctl,ComIoctlFunctionLen) != ComIoctlFunctionLen )
			err = -1;
		else
		    err = ioctl.errcode;
	}
	
	void EZ_XModemHeader(byte header,byte trailer) {
		ioctl.funcode = ComIoctlSetHdrTrlr;
		ioctl.data.hdrtrlr.header = header;
		ioctl.data.hdrtrlr.trailer = trailer;
		if ( DosIoCtrlWrData(handle,(char *)&ioctl,ComIoctlHdrTrlrLen) != ComIoctlHdrTrlrLen )
			err = -1;
		else
		    err = ioctl.errcode;
		EZ_XModemError("Set Flags");
	}

	int	EZ_BiosTxDone(int port) {
		union REGS regs;
		regs.x.ax=0x8A00;
		regs.x.dx=port;
		int86(0xA5,&regs,&regs);
		if (regs.x.cflag)
			return regs.x.ax;
 		return 0;
	}

	int EZ_BiosSerialSetParams(int port,void far *parms) { // Set serial port params
		regs.h.ah = 0x80;
		regs.x.dx = port;
		regs.x.si = FP_OFF(parms);
		sregs.es = FP_SEG(parms);
		int86x(0xA5,&regs,&regs,&sregs);
		return(regs.x.ax);
	}
	
	int EZ_BiosSerialGetParams(int port,void far *parms) { // Get serial port params
		regs.h.ah = 0x81;
		regs.h.al = 0;
		regs.x.dx = port;
		regs.x.di = FP_OFF(parms);
		sregs.es = FP_SEG(parms);
		int86x(0xA5,&regs,&regs,&sregs);
		return(regs.x.ax);
	}
	
	int EZ_BiosSerialOpen(int port) {		// Open serial port
		regs.h.ah = 0x82;
		regs.x.dx = port;
		int86(0xA5,&regs,&regs);
		return(regs.x.ax);
	}
	
	int EZ_BiosSerialClose(int port) {		// Close serial port
		regs.h.ah = 0x83;
		regs.x.dx = port;
		int86(0xA5,&regs,&regs);
		return(regs.x.ax);
	}

	int EZ_BiosSerialSetCtlLines(int port,unsigned char lines) { // Set selected output control lines
		regs.h.ah = 0x8B;
		regs.h.al = lines;
		regs.x.dx = port;
		int86(0xA5,&regs,&regs);
		return(regs.x.ax);
	}

	int EZ_BiosSerialInitQueues(int port, void far *qp) {	// Initialize input and output queues
		regs.h.ah = 0x8D;
		regs.x.dx = port;
		regs.x.si = FP_OFF(qp);
		sregs.es = FP_SEG(qp);
		int86x(0xA5,&regs,&regs,&sregs);
		return(regs.x.ax);
	}

	int EZ_BiosSerialDeleteQueues() {						// Request the cradle data bus
		regs.h.ah = 0x91;
		int86(0xA5,&regs,&regs);
		return(regs.x.ax);
	}

/*--------------------------------------------------------------------------*/
/*                                                                          */
/*                    U T I L I T Y   R O U T I N E S                       */
/*                    U T I L I T Y   R O U T I N E S                       */
/*                    U T I L I T Y   R O U T I N E S                       */
/*                    U T I L I T Y   R O U T I N E S                       */
/*                                                                          */
/*--------------------------------------------------------------------------*/

	//--- DRAW A SIMPLE BORDER ----------------------------------------------
	void EZ_DrawBorder(unsigned char Rows,unsigned char Cols, char *titlestr) {
		unsigned char ii;									// Counter
		EZ_PutChar((unsigned char)0,(unsigned char)0,(unsigned char)'Ö',(unsigned char)EZ_VID_NORMAL);
		EZ_PutChar((unsigned char)0,(unsigned char)Cols,(unsigned char)'·',(unsigned char)EZ_VID_NORMAL);
		EZ_PutChar((unsigned char)Rows,(unsigned char)0,(unsigned char)'Ó',(unsigned char)EZ_VID_NORMAL);
		EZ_PutChar((unsigned char)Rows,(unsigned char)Cols,(unsigned char)'½',(unsigned char)EZ_VID_NORMAL);
		for (ii = 1; ii < Cols; ii++) {
			EZ_PutChar((unsigned char)0,ii, (unsigned char)'Ä', (unsigned char)EZ_VID_NORMAL);
			EZ_PutChar((unsigned char)Rows,ii, (unsigned char)'Ä', (unsigned char)EZ_VID_NORMAL);
		}
		for (ii = 1; ii < Rows; ii++) {
			EZ_PutChar(ii,(unsigned char)0,(unsigned char)'º',(unsigned char)EZ_VID_NORMAL);
			EZ_PutChar(ii,(unsigned char)Cols,(unsigned char)'º',(unsigned char)EZ_VID_NORMAL);
		}
		BiosPutStrStay(0,(unsigned char)((Cols / 2) - (strlen(titlestr) / 2) + 1),strlen(titlestr),titlestr,EZ_VID_NORMAL);
		return;
	}

	//--- OUTPUT A SINGLE CHARACTER AT A FIXED POSITION ON THE SCREEN -------
	void EZ_PutChar(unsigned char r,unsigned char c,unsigned char ch, unsigned char attr) {
		BiosSetCursorPos(r,c);
		BiosPutCharAttr(ch,attr,1);
	}

	//--- CLEAR AND HOME THE CURSOR -----------------------------------------
	void EZ_ClearAndHome( void ) {
		BiosClrScr( EZ_VID_NORMAL );
		BiosSetCursorPos( 0, 0);
		return;
	}

	//--- DISPLAY A MESSAGE WITH AUDIBLE ------------------------------------
	void EZ_Alarm(char *text) {
		char savebuf[ 320 ];
		unsigned char currow = 0, curcol = 0;
		BiosGetCursorPos(&currow, &curcol);
		BiosTextRectToMem(0, 0, EZ_VID_LASTCOL, EZ_VID_LASTROW, savebuf);
		BiosClrScr( EZ_VID_NORMAL );
		BiosPutStrMove(0, 0, strlen(text), text, EZ_VID_NORMAL);
		EZ_ErrorMessage();
		getch();
		BiosMemToTextRect(0, 0, EZ_VID_LASTCOL, EZ_VID_LASTROW, savebuf);
		BiosSetCursorPos(currow, curcol);
		return;
	}

	//--- SOUND AUDIBLE ERROR MESSAGE ---------------------------------------
	void EZ_ErrorMessage() {
		unsigned char i = 0;
		for (i = 1; i <= 3; i++) {
			BiosBeep( EZ_SHORTSOUND );
			BiosDelay( (long) EZ_SHORTSOUND );
   		}
		return;
	}

	//--- FILL A CHARACTER STRING WITH UNDERSCORES --------------------------
	void EZ_FillWithUnderscores(char *buf, int count) {
		int ii = 0;
		for (ii = count; ii <= EZ_MAX_SCAN_LEN; ii++) buf[ii] = '_';
		buf[EZ_MAX_SCAN_LEN] = '\0';
		return;
	}

	//--- SEARCH FOR A STRING IN AN ARRAY OF STRINGS ------------------------
	int EZ_SearchString(char *string, char **list) {
		int item = 0, i = 0;
		while (list[i]) {									// Loop through each item
			if(!strcmp(list[i], string)) {					// if string matches
				item = i + 1;								// set the item number
				break;										// break the loop
			}
			else i++;										// else the string does not match increment counter
		}
		return(item);										// Return the item number
	}

	//--- MENU FUNCTION POINTER STUB ----------------------------------------
	int Stub( int idx )	{return(0);}
