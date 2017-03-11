#ifndef __MV9300__MAIN_h__
#define __MV9300__MAIN_h__

#include "MV9300_Drv_Lib.h"


// (  REGW(1) + W(288+144) + Sync(2) + W(288) + jump(1)) * 4 *8 = 23168
// Frame Set : 23168*30 = 695040
// KByte : (695040 + 1023 ) /1024*1024 = 695296 = 679KByte

// Sync(4) + VideoLie(576) + Jump(1) = 581 * 8 = 4648
// Frame Set : 4648*30 = 139440
// KByte : (139440 + 1023 ) /1024*1024 = 140288 = 137KByte
#define RISC_VIDEO_SIZE	695296

// Sync(4) + AudioLine(4) + Jump(1) = 9 * 8 = 72
// KByte : (72 + 1023) / 1024 * 1024 = 1024 = 1KByte
#define RISC_AUDIO_SIZE	1024

//Yx4 Ux4 Vx4 = 12
#define RISC_VIDEO_TOTAL RISC_VIDEO_SIZE*8
//Audio x 4
#define RISC_AUDIO_TOTAL RISC_AUDIO_SIZE*8
#define RISC_TOTAL	RISC_VIDEO_TOTAL+RISC_AUDIO_TOTAL

// Image Size(768*576*2) * Dumy Size(768*4*2) + Motion(8*6) = 890922
// KByte : ( 890922 + 1023 ) /1024 * 1024 = 891904 = 871KByte
#define CAPTURE_VIDEO_SIZE	891904
#define CAPTURE_AUDIO_SIZE	44*1024
#define	CAPTURE_VIDEO_TOTAL	CAPTURE_VIDEO_SIZE*8
#define CAPTURE_AUDIO_TOTAL	CAPTURE_AUDIO_SIZE*8
#define CAPTURE_MOTION_SIZE	1024
#define CAPTURE_MOTION_TOTAL	1024*8
#define CAPTURE_TOTAL	CAPTURE_VIDEO_TOTAL + CAPTURE_AUDIO_TOTAL + CAPTURE_MOTION_TOTAL

class CAdapter{
public:
	typedef struct tagDATA_EXTENSION {
		class CAdapter * adapter;			// Pointer to our instance	
	} DATA_EXTENSION, *PDATA_EXTENSION;
	
	CAdapter();
	~CAdapter();

	/////////////////////////////////////////////////////////////////////////
	// Using DriverEntry
	static VOID DriverUnload(IN PDRIVER_OBJECT DriverObject);
	static NTSTATUS AddDevice(PDRIVER_OBJECT DriverObject,PDEVICE_OBJECT PDO );

	/////////////////////////////////////////////////////////////////////////
	// Dispatch function
	static NTSTATUS DispatchCreate(PDEVICE_OBJECT DeviceObject, PIRP Irp);
	static NTSTATUS DispatchClose(PDEVICE_OBJECT DeviceObject, PIRP Irp);
	static NTSTATUS DispatchControl(PDEVICE_OBJECT DeviceObject, PIRP Irp);
	static NTSTATUS DispatchCleanup(PDEVICE_OBJECT DeviceObject, PIRP Irp);
	static NTSTATUS DispatchPower(PDEVICE_OBJECT DeviceObject, PIRP Irp);
	static NTSTATUS DispatchPnp(PDEVICE_OBJECT DeviceObject, PIRP Irp);

	/////////////////////////////////////////////////////////////////////////
	// PnP Function
	NTSTATUS	PnpStartDevice(PDEVICE_OBJECT DeviceObject, PIRP Irp, PCM_RESOURCE_LIST raw, PCM_RESOURCE_LIST translated);
	NTSTATUS	PnpStopDevice(PDEVICE_OBJECT DeviceObject);

	/////////////////////////////////////////////////////////////////////////
	// Calling PNP PDO.
	PDEVICE_OBJECT TopOfStackDeviceObject;
	// DeviceStack Name
	UNICODE_STRING UnicodeString; 


	/////////////////////////////////////////////////////////////////////////
	// Interrupt control
	static BOOLEAN cbInterrupt(PKINTERRUPT Interrupt,PVOID  ServiceContext)
	{
		return ((CAdapter*)ServiceContext)->HwInterrupt();
	}
	static void cbDpcFunc(IN PKDPC Dpc,IN CAdapter *pAdapter,IN PVOID SystemArg1,IN PVOID SystemArg2);
	static void cbDpcFuncErr0(IN PKDPC Dpc,IN CAdapter *pAdapter,IN PVOID SystemArg1,IN PVOID SystemArg2);
	static void cbDpcFuncErr1(IN PKDPC Dpc,IN CAdapter *pAdapter,IN PVOID SystemArg1,IN PVOID SystemArg2);
	static void cbDpcFuncErr2(IN PKDPC Dpc,IN CAdapter *pAdapter,IN PVOID SystemArg1,IN PVOID SystemArg2);
	static void cbDpcFuncErr3(IN PKDPC Dpc,IN CAdapter *pAdapter,IN PVOID SystemArg1,IN PVOID SystemArg2);

	PKINTERRUPT		m_InterruptObject;
	BOOL			m_IRQExpected;
	KDPC			m_IsrDpc[16];
	KDPC			m_IsrDpcErr[4];
	KTIMER			DMATimer;

	/////////////////////////////////////////////////////////////////////////
	// MV9300 Control
	/////////////////////////////////////////////////////////////////////////

	// Interrupt
	BOOLEAN		HwInterrupt();
	void		VideoCaptureRoutine(DWORD dwStreamNumber);
	void		AudioCaptureRoutine(DWORD dwStreamNumber);

	// User Control Function
	NTSTATUS	RegisterWrite(PMV9300_RW pData);
	NTSTATUS	RegisterRead(PMV9300_RW pData);
	NTSTATUS	SetVideoFormat(PMV9300_FORMAT pFormat);
	NTSTATUS	SetVideoFormat2(PMV9300_FORMAT2 pFormat);
	NTSTATUS	SetVideoDisplay(PMV9300_DISPLAY pDisp);
	NTSTATUS	SetEvent(PMV9300_EVENT pEv, KPROCESSOR_MODE RequestMode);
	NTSTATUS	GetVideoMemory(PMV9300_VIDEOMEM pVideoMem);

	NTSTATUS	CaptureStart(int nCh);
	NTSTATUS	CaptureStop(int nCh);
	NTSTATUS	SetAudioFormat(PMV9300_AUDIOFM pAud);
	NTSTATUS	GetVideoLock(DWORD *pLock);
	NTSTATUS	SetGPIO(DWORD *pGPIO);
	NTSTATUS	GetGPIO(DWORD *pGPIO);
	NTSTATUS	SetGPOE(DWORD *pGPIO);

	void		CreateVideoRiscCmd(BOOL bInterlace, int cx, int cy, BOOL bSkip, PULONG *pProgLocation, DWORD dwTAddr, BOOL bSplit, BOOL bStandard, DWORD dwBase, DWORD dwMotionAddr);
	void		CreateVideoRiscCmd2(BOOL bOddOnly, int cx1, int cy1, BOOL bSkip1, int cx2, int cy2, BOOL bSkip2, PULONG *pProgLocation, DWORD dwTAddr, DWORD dwMotionAddr, DWORD dwChBaseAddr);

	BYTE*	m_pBaseAddr;

	BYTE*	m_pSystemMemory;
	BYTE*	m_pRISCMemory;
	DWORD	m_dwRiscPhysical;

	BYTE*	m_pCaptureMemory[16];
	DWORD	m_dwCapturePhysical[16];
	BYTE*	m_pCaptureMotion[8];
	DWORD	m_dwCaptureMotion[8];

	PMDL	m_pCaptureMdl[16];
	BYTE*	m_pCaptureUser[16];
	PKEVENT	m_pEvent[24];

	BOOL	m_bCaptureStart[16];
	DWORD	m_dwDecEnable[16];
	DWORD	m_dwDecDisable[16];
	BOOL	m_bDecStateNotSave[16];
	int		m_nFrameSkip[16];


	DWORD	m_dwVideoLockCh[8];
	DWORD	m_dwVideoLock;
	DWORD	m_dwINTMaskBar;

	// Video Format
	BOOL	m_bSplit[8];			// Split (0,1:split 2, 2:split 3, 4:split 4);
	BOOL	m_bField[8];
	BOOL	m_bOddOnly[8];


	// Audio Format
	DWORD	m_dwAudioBufferSize[8];

	BYTE*	m_pAudioData[8];
	DWORD	m_dwAudioField[8];
	DWORD	m_dwErrorCode;

	DWORD	m_dwGPIO;
};

#endif
