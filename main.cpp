#include "WDMHeaders.hpp"

#include <initguid.h>
DEFINE_GUID(GUID_MV9300, 
0x5665dec0, 0xa40a, 0x11d1, 0xb9, 0x84, 0x0, 0x20, 0xaf, 0xd7, 0x97, 0x83);
// 현재 우리가 사용될 DeviceStack에 대한 Interface GUID를 정의합니다


//#define WRITE_REGISTER_DPGPRINT( addr, data )	{DbgPrint("REG W(%8x : %8x)", addr, data);	WRITE_REGISTER_ULONG(addr, data); }
#define WRITE_REGISTER_DPGPRINT( addr, data )	{WRITE_REGISTER_ULONG(addr, data); }


#include "main.h"
#include "CppRt.h"
#include "Command.h"

char*	FrameRate_NTSC1[31]={
	"000000000000000000000000000000",	//0
	"000000000000000000000000000001",	//1
	"000000000000001000000000000001",	//2
	"000000000100000000010000000001",	//3
	"000000010000001000000010000001",	//4
	"000001000001000001000001000001",	//5
	"000010000100001000010000100001",	//6
	"000100001000100010001000010001",	//7
	"000100010010001000100010010001",	//8
	"001000100100100010010010001001",	//9
	"001001001001001001001001001001",	//10
	"001010010010010100100100101001",	//11
	"001010010100101001010010100101",	//12
	"010010101001010101001010100101",	//13
	"010101001010101010101001010101",	//14
	"010101010101010101010101010101",	//15
	"010101011010101010101011010101",	//16
	"010110101011010101101010110101",	//17
	"011010110101101011010110101101",	//18
	"011011011010110110101101101101",	//19
	"011011011011011011011011011011",	//20
	"101101101110110110111011011011",	//21
	"101110110111011101110110111011",	//22
	"101110111101110111011110111011",	//23
	"101111011110111101111011110111",	//24
	"110111110111110111110111110111",	//25
	"111011111101111111011111101111",	//26
	"111101111111110111111111101111",	//27
	"111111011111111111111011111111",	//28
	"111111111111110111111111111111",	//29
	"111111111111111111111111111111"	//30
};

char*	FrameRate_PAL1[26]={
	"0000000000000000000000000",	//0
	"0000000000000000000000001",	//1
	"0000000000001000000000001",	//2
	"0000000100000000100000001",	//3
	"0000010000001000001000001",	//4
	"0000100001000010000100001",	//5
	"0001000100001000100010001",	//6
	"0001001000100100010010001",	//7
	"0010010010001001001001001",	//8
	"0010010100100100101001001",	//9
	"0010100101001010010100101",	//10
	"0100101010100101010100101",	//11
	"0101010101001010101010101",	//12
	"0101010101011010101010101",	//13
	"0101101010101101010110101",	//14
	"0110101101011010110101101",	//15
	"0110110110101101101101101",	//16
	"1011011011011011011011011",	//17
	"1011011101101110111011011",	//18
	"1011101110111101110111011",	//19
	"1011110111101111011110111",	//20
	"1101111101111110111110111",	//21
	"1110111111101111111101111",	//22
	"1111101111111111110111111",	//23
	"1111111111101111111111111",	//24
	"1111111111111111111111111",	//25
};

char*	FrameRate_NTSC2[31]={
	"000000000000000000000000000000",	//0
	"000000000000000000000000000010",	//1
	"000000000000010000000000000010",	//2
	"000000001000000000100000000010",	//3
	"000000100000010000000100000010",	//4
	"000010000010000010000010000010",	//5
	"000100001000010000100001000010",	//6
	"001000010001000100010000100010",	//7
	"001000100100010001000100100010",	//8
	"010001001001000100100100010010",	//9
	"010010010010010010010010010010",	//10
	"010100100100101001001001010010",	//11
	"010100101001010010100101001010",	//12
	"100101010010101010010101001010",	//13
	"101010010101010101010010101010",	//14
	"101010101010101010101010101010",	//15
	"101010110101010101010110101010",	//16
	"101101010110101011010101101010",	//17
	"110101101011010110101101011010",	//18
	"110110110101101101011011011010",	//19
	"110110110110110110110110110110",	//20
	"011011011101101101110110110111",	//21
	"011101101110111011101101110111",	//22
	"011101111011101110111101110111",	//23
	"011110111101111011110111101111",	//24
	"101111101111101111101111101111",	//25
	"110111111011111110111111011111",	//26
	"111011111111101111111111011111",	//27
	"111110111111111111110111111111",	//28
	"111111111111101111111111111111",	//29
	"111111111111111111111111111111"	//30
};

char*	FrameRate_PAL2[26]={
	"0000000000000000000000000",	//0
	"0000000000000000000000010",	//1
	"0000000000010000000000010",	//2
	"0000001000000001000000010",	//3
	"0000100000010000010000010",	//4
	"0001000010000100001000010",	//5
	"0010001000010001000100010",	//6
	"0010010001001000100100010",	//7
	"0100100100010010010010010",	//8
	"0100101001001001010010010",	//9
	"0101001010010100101001010",	//10
	"1001010101001010101001010",	//11
	"1010101010010101010101010",	//12
	"1010101010110101010101010",	//13
	"1011010101011010101101010",	//14
	"1101011010110101101011010",	//15
	"1101101101011011011011010",	//16
	"0110110110110110110110111",	//17
	"0110111011011101110110111",	//18
	"0111011101111011101110111",	//19
	"0111101111011110111101111",	//20
	"1011111011111101111101111",	//21
	"1101111111011111111011111",	//22
	"1111011111111111101111111",	//23
	"1111111111011111111111111",	//24
	"1111111111111111111111111",	//25
};

extern "C" 
	ULONG STREAMAPI DriverEntry(
	IN PDRIVER_OBJECT DriverObject,
	IN PUNICODE_STRING RegistryPath
	)
{
	DriverObject->DriverUnload = CAdapter::DriverUnload;
	// Driver가 메모리에서 제거되면 호출됨
	
	DriverObject->DriverExtension->AddDevice = CAdapter::AddDevice;
	// 장치를 시스템이 Detect하면 호출하는 루틴
	// DeviceStack을 구성할 책임을 가지는 루틴

	// Win32 API CreateFile();
	DriverObject->MajorFunction[IRP_MJ_CREATE] = CAdapter::DispatchCreate;

	// Win32 API CloseHandle();
	DriverObject->MajorFunction[IRP_MJ_CLOSE] = CAdapter::DispatchClose;

	// Win32 API DeviceIoControl();
	DriverObject->MajorFunction[IRP_MJ_DEVICE_CONTROL] = CAdapter::DispatchControl;

	DriverObject->MajorFunction[IRP_MJ_CLEANUP] = CAdapter::DispatchCleanup;
	DriverObject->MajorFunction[IRP_MJ_POWER] = CAdapter::DispatchPower;

	// PNP 명령을 처리하는 처리기 등록
	DriverObject->MajorFunction[IRP_MJ_PNP] = CAdapter::DispatchPnp;

	return STATUS_SUCCESS;
}

CAdapter::CAdapter()
{
	m_dwINTMaskBar = 0x00F9FFFF;
	m_IRQExpected = true;
	m_InterruptObject = NULL;
	m_pBaseAddr = NULL;

	m_pSystemMemory = NULL;

	m_pRISCMemory = NULL;
	m_dwRiscPhysical = 0;

	m_dwErrorCode = 0;
	for(int i=0; i<8; i++)
	{
		m_bSplit[i] = FALSE;			// Split (0,1:split);
		m_bOddOnly[i] = TRUE;
		m_bField[i] = FALSE;

		m_dwAudioBufferSize[i] = 0;
		m_pAudioData[i] = NULL;
		m_dwAudioField[i] = 0;

		m_pCaptureMotion[i] = 0;
		m_dwCaptureMotion[i] = 0;
	}
	for(int i=0; i<16; i++)
	{
		m_bCaptureStart[i] = FALSE;
		m_bDecStateNotSave[i] = TRUE;
		m_nFrameSkip[i] = 0;

		m_pCaptureMemory[i] = NULL;
		m_pCaptureUser[i] = NULL;
		m_pCaptureMdl[i] = NULL;

		m_dwCapturePhysical[i] = 0;

		KeInitializeDpc (
			&m_IsrDpc[i], 
			reinterpret_cast <PKDEFERRED_ROUTINE> 
				(CAdapter::cbDpcFunc),
			this
			);
		KeSetTargetProcessorDpc (
			&m_IsrDpc[i],	//
			0
			);
	}
	for(int i=0; i<24; i++)
	{
		m_pEvent[i] = NULL;
	}

	KeInitializeDpc (
		&m_IsrDpcErr[0], 
		reinterpret_cast <PKDEFERRED_ROUTINE> 
			(CAdapter::cbDpcFuncErr0),
		this
		);
	KeSetTargetProcessorDpc (
		&m_IsrDpcErr[0],	//
		0
		);

	KeInitializeDpc (
		&m_IsrDpcErr[1], 
		reinterpret_cast <PKDEFERRED_ROUTINE> 
			(CAdapter::cbDpcFuncErr1),
		this
		);
	KeSetTargetProcessorDpc (
		&m_IsrDpcErr[1],	//
		0
		);

	KeInitializeDpc (
		&m_IsrDpcErr[2], 
		reinterpret_cast <PKDEFERRED_ROUTINE> 
			(CAdapter::cbDpcFuncErr2),
		this
		);
	KeSetTargetProcessorDpc (
		&m_IsrDpcErr[2],	//
		0
		);

	KeInitializeDpc (
		&m_IsrDpcErr[3], 
		reinterpret_cast <PKDEFERRED_ROUTINE> 
			(CAdapter::cbDpcFuncErr3),
		this
		);
	KeSetTargetProcessorDpc (
		&m_IsrDpcErr[3],	//
		0
		);

	KeInitializeTimer(&DMATimer);
}

CAdapter::~CAdapter()
{
	KeCancelTimer(&DMATimer);

	for(int i=0; i<16; i++)
		KeRemoveQueueDpc(&m_IsrDpc[i]);

	for(int i=0; i<4; i++)
		KeRemoveQueueDpc(&m_IsrDpcErr[i]);
}


VOID CAdapter::DriverUnload(
	IN PDRIVER_OBJECT DriverObject
	)
{
}


NTSTATUS CAdapter::AddDevice(
	PDRIVER_OBJECT DriverObject,
	PDEVICE_OBJECT PDO 
	)
{
	PDEVICE_OBJECT deviceObject = NULL;
	PDATA_EXTENSION pDataExtension;
	CAdapter *adapter;
	NTSTATUS status;

	status = IoCreateDevice(
				 DriverObject,
				 sizeof(DATA_EXTENSION),                    
				 0,
				 FILE_DEVICE_UNKNOWN,
				 0,                    
				 FALSE,                
				 &deviceObject
				 ); 	// 사용할 나의 SAMPLE DeviceObject생성

	pDataExtension = (PDATA_EXTENSION)deviceObject->DeviceExtension;
	adapter = new CAdapter();
	pDataExtension->adapter = adapter;
	
	adapter->TopOfStackDeviceObject = IoAttachDeviceToDeviceStack( deviceObject, PDO );
	// 현 DeviceStack으로 Attach시킨후, 리턴되는 TopOfStackDeviceObject를 보관한다

	deviceObject->Flags &= ~DO_DEVICE_INITIALIZING;
	// SAMPLE DeviceObject위로 다른 DeviceObject가 Attach될수 있도록 한다
	// 결국, 이렇게 되면, 우리가 올라간 DeviceStack위로 다른 DeviceObject가 올라가는것이 가능해진다
	
	deviceObject->Flags |= DO_BUFFERED_IO;
	// 대외적으로 현재 DeviceStack으로 전달되는 Read/Write명령에 대해서 사용되는 모든 파라미터버퍼는 SystemBuffer를 사용하는것으로 간주

	IoRegisterDeviceInterface( PDO, &GUID_MV9300, NULL, &adapter->UnicodeString );
	// 현재 우리가 속한 DeviceStack에 대해 InterfaceGuid를 등록합니다
	// 리턴되는 de->UnicodeString는 사용자가 접근하는 이름입니다
	
	return STATUS_SUCCESS;
}

NTSTATUS CAdapter::DispatchCreate(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
	//DbgPrint(("DispatchCreate\n"));
	PDATA_EXTENSION pDataExtension = (PDATA_EXTENSION)DeviceObject->DeviceExtension;
	CAdapter *adapter = pDataExtension->adapter;
	DWORD dwRead = READ_REGISTER_ULONG( PULONG(adapter->m_pBaseAddr + 0x00C) );
	dwRead &= 0xFFFF0000;
	dwRead |= 0x4008;
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x00C), dwRead );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x054), 0x0D00021C );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x058), 0x88888888 );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x1A8), 0x22220108 );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x1D8), 0x04004040 );

	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x200), 0x3D1009C4 );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x280), 0x3D1009C4 );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x300), 0x3D1009C4 );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x380), 0x3D1009C4 );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x400), 0x3D1009C4 );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x480), 0x3D1009C4 );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x500), 0x3D1009C4 );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x580), 0x3D1009C4 );

	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x204), 0x200A3000 );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x284), 0x200A3000 );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x304), 0x200A3000 );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x384), 0x200A3000 );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x404), 0x200A3000 );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x484), 0x200A3000 );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x504), 0x200A3000 );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x584), 0x200A3000 );
	
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x208), 0x20203030 );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x288), 0x20203030 );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x308), 0x20203030 );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x388), 0x20203030 );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x408), 0x20203030 );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x488), 0x20203030 );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x508), 0x20203030 );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x588), 0x20203030 );
	
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x218), 0x02000204 );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x298), 0x02000204 );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x318), 0x02000204 );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x398), 0x02000204 );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x418), 0x02000204 );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x498), 0x02000204 );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x518), 0x02000204 );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x598), 0x02000204 );
	
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x248), 0x0C0702D0 );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x2C8), 0x0C0702D0 );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x348), 0x0C0702D0 );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x3C8), 0x0C0702D0 );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x448), 0x0C0702D0 );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x4C8), 0x0C0702D0 );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x548), 0x0C0702D0 );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x5C8), 0x0C0702D0 );
	
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x254), 0x50467271 );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x2D4), 0x50467271 );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x354), 0x50467271 );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x3D4), 0x50467271 );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x454), 0x50467271 );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x4D4), 0x50467271 );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x554), 0x50467271 );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x5D4), 0x50467271 );

	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x258), 0x10096375 );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x2D8), 0x10096375 );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x358), 0x10096375 );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x3D8), 0x10096375 );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x458), 0x10096375 );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x4D8), 0x10096375 );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x558), 0x10096375 );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x5D8), 0x10096375 );

	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x268), 0x3F00113C );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x2E8), 0x3F00113C );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x368), 0x3F00113C );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x3E8), 0x3F00113C );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x468), 0x3F00113C );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x4E8), 0x3F00113C );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x568), 0x3F00113C );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x5E8), 0x3F00113C );
	
	
/*
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x200), 0x348806B8 );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x204), 0xBD800C04 );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x208), 0x20307070 );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x210), 0xF168F168 );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x244), 0x0C05F2E4 );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x258), 0x5244F271 );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x25C), 0x10087384 );

	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x280), 0x348806B8 );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x284), 0xBD800C04 );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x288), 0x20307070 );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x290), 0xF168F168 );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x2C4), 0x0C05F2E4 );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x2D8), 0x5244F271 );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x2DC), 0x10087384 );

	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x300), 0x348806B8 );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x304), 0xBD800C04 );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x308), 0x20307070 );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x310), 0xF168F168 );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x344), 0x0C05F2E4 );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x358), 0x5244F271 );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x35C), 0x10087384 );

	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x380), 0x348806B8 );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x384), 0xBD800C04 );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x388), 0x20307070 );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x390), 0xF168F168 );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x3C4), 0x0C05F2E4 );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x3D8), 0x5244F271 );
	WRITE_REGISTER_DPGPRINT( PULONG(adapter->m_pBaseAddr + 0x3DC), 0x10087384 );
*/
	Irp->IoStatus.Status = STATUS_SUCCESS;
	IoCompleteRequest( Irp, IO_NO_INCREMENT );

	return STATUS_SUCCESS;
}

NTSTATUS CAdapter::DispatchClose(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
	//DbgPrint(("DispatchClose\n"));
	PDATA_EXTENSION pDataExtension = (PDATA_EXTENSION)DeviceObject->DeviceExtension;
	CAdapter *adapter = pDataExtension->adapter;

	for(int i=0; i<16; i++)
	{
		if(adapter->m_bCaptureStart[i])
		{
			adapter->m_bDecStateNotSave[i] = TRUE;
			adapter->CaptureStop(i);
		}

		if(adapter->m_pCaptureUser[i] != NULL)
		{
			// 우선 사용자가 사용하던 UserLevel가상메모리를 해제한다
			MmUnmapLockedPages( 
				adapter->m_pCaptureUser[i], 
				adapter->m_pCaptureMdl[i]
				);

			adapter->m_pCaptureUser[i] = NULL;

			// 그다음 Mdl을 해제한다
			IoFreeMdl( 
				adapter->m_pCaptureMdl[i] 
				);

			adapter->m_pCaptureMdl[i] = 0;
		}
	}
	adapter->m_dwINTMaskBar = 0x00F9FFFF;

	for(int i=0; i<24; i++)
	{
		if(adapter->m_pEvent[i] != NULL)
		{
			KeSetEvent(adapter->m_pEvent[i], 0, FALSE);

			ObDereferenceObject(adapter->m_pEvent[i]);
			adapter->m_pEvent[i] = NULL;
		}
	}

	for(int i=0; i<8; i++)
	{
		if(adapter->m_pAudioData[i] != NULL)
		{
			ExFreePool(adapter->m_pAudioData[i]);
			adapter->m_pAudioData[i] = NULL;
		}
	}

	Irp->IoStatus.Status = STATUS_SUCCESS;
	IoCompleteRequest( Irp, IO_NO_INCREMENT );
	return STATUS_SUCCESS;
}

NTSTATUS CAdapter::DispatchControl(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
	//DbgPrint(("DispatchControl\n"));

	CAdapter *adapter;
	PDATA_EXTENSION pDataExtension;
	int* pBuf;
	DWORD **pLock;
	DWORD **pGPIO;

	pDataExtension = (PDATA_EXTENSION)DeviceObject->DeviceExtension;
	adapter = pDataExtension->adapter;

	PIO_STACK_LOCATION pStack = IoGetCurrentIrpStackLocation( Irp );

	switch(pStack->Parameters.DeviceIoControl.IoControlCode)
	{
	case IOCTL_MV9300_REG_WRITE:
		//DbgPrint(("IOCTL_MV9300_REG_WRITE\n"));
		Irp->IoStatus.Status = adapter->RegisterWrite( PMV9300_RW(Irp->AssociatedIrp.SystemBuffer) );
		Irp->IoStatus.Information = 0;
		break;
	case IOCTL_MV9300_REG_READ:
		//DbgPrint(("IOCTL_MV9300_REG_READ\n"));
		Irp->IoStatus.Status = adapter->RegisterRead( PMV9300_RW(Irp->AssociatedIrp.SystemBuffer) );
		Irp->IoStatus.Information = sizeof(MV9300_RW);
		break;
	case IOCTL_MV9300_VIDEO_FORMAT:
		//DbgPrint(("IOCTL_MV9300_VIDEO_FORMAT\n"));
		Irp->IoStatus.Status = adapter->SetVideoFormat( PMV9300_FORMAT(Irp->AssociatedIrp.SystemBuffer) );
		Irp->IoStatus.Information = 0;
		break;
	case IOCTL_MV9300_VIDEO_DISPLAY:
		//DbgPrint(("IOCTL_MV9300_VIDEO_DISPLAY\n"));
		Irp->IoStatus.Status = adapter->SetVideoDisplay( PMV9300_DISPLAY(Irp->AssociatedIrp.SystemBuffer) );
		Irp->IoStatus.Information = 0;
		break;
	case IOCTL_MV9300_CAP_EVENT:
		//DbgPrint(("IOCTL_MV9300_CAP_EVENT\n"));
		Irp->IoStatus.Status = adapter->SetEvent( PMV9300_EVENT(Irp->AssociatedIrp.SystemBuffer), Irp->RequestorMode );
		Irp->IoStatus.Information = 0;
		break;
	case IOCTL_MV9300_CAP_MEM:
		//DbgPrint(("IOCTL_MV9300_CAP_MEM\n"));
		Irp->IoStatus.Status = adapter->GetVideoMemory( PMV9300_VIDEOMEM(Irp->AssociatedIrp.SystemBuffer) );
		Irp->IoStatus.Information = sizeof(MV9300_VIDEOMEM);
		break;
	case IOCTL_MV9300_CAP_START:
		//DbgPrint(("IOCTL_MV9300_CAP_START\n"));
		pBuf = (int*)Irp->AssociatedIrp.SystemBuffer;
		Irp->IoStatus.Status = adapter->CaptureStart( pBuf[0] );
		Irp->IoStatus.Information = 0;
		break;
	case IOCTL_MV9300_CAP_STOP:
		//DbgPrint(("IOCTL_MV9300_CAP_STOP\n"));
		pBuf = (int*)Irp->AssociatedIrp.SystemBuffer;
		Irp->IoStatus.Status = adapter->CaptureStop( pBuf[0] );
		Irp->IoStatus.Information = 0;
		break;
	case IOCTL_MV9300_AUDIO_FORMAT:
		//DbgPrint(("IOCTL_MV9300_AUDIO_FORMAT\n"));
		Irp->IoStatus.Status = adapter->SetAudioFormat( PMV9300_AUDIOFM(Irp->AssociatedIrp.SystemBuffer) );
		Irp->IoStatus.Information = 0;
		break;
	case IOCTL_MV9300_GET_LOCK:
		//DbgPrint(("IOCTL_MV9300_GET_LOCK\n"));
		pLock = (DWORD**)Irp->AssociatedIrp.SystemBuffer;
		Irp->IoStatus.Status = adapter->GetVideoLock( *pLock );
		Irp->IoStatus.Information = 0;
		break;
	case IOCTL_MV9300_SET_GPIO:
		//DbgPrint(("IOCTL_MV9300_SET_GPIO\n"));
		pGPIO = (DWORD**)Irp->AssociatedIrp.SystemBuffer;
		Irp->IoStatus.Status = adapter->SetGPIO( *pGPIO );
		Irp->IoStatus.Information = 0;
		break;
	case IOCTL_MV9300_GET_GPIO:
		//DbgPrint(("IOCTL_MV9300_GET_GPIO\n"));
		pGPIO = (DWORD**)Irp->AssociatedIrp.SystemBuffer;
		Irp->IoStatus.Status = adapter->GetGPIO( *pGPIO );
		Irp->IoStatus.Information = 0;
		break;
	case IOCTL_MV9300_SET_GPOE:
		//DbgPrint(("IOCTL_MV9300_SET_GPOE\n"));
		pGPIO = (DWORD**)Irp->AssociatedIrp.SystemBuffer;
		Irp->IoStatus.Status = adapter->SetGPOE( *pGPIO );
		Irp->IoStatus.Information = 0;
		break;
	case IOCTL_MV9300_VIDEO_FORMAT2:
		//DbgPrint(("IOCTL_MV9300_VIDEO_FORMAT2\n"));
		Irp->IoStatus.Status = adapter->SetVideoFormat2( PMV9300_FORMAT2(Irp->AssociatedIrp.SystemBuffer) );
		Irp->IoStatus.Information = 0;
		break;
	default:
		//DbgPrint(("UnKnown\n"));
		Irp->IoStatus.Status = STATUS_INVALID_PARAMETER;
		break;
	}
	IoCompleteRequest( Irp, IO_NO_INCREMENT );

	return STATUS_SUCCESS;
}

NTSTATUS CAdapter::DispatchCleanup(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
	//DbgPrint(("DispatchCleanup\n"));
	Irp->IoStatus.Status = STATUS_SUCCESS;
	IoCompleteRequest( Irp, IO_NO_INCREMENT );
	return STATUS_SUCCESS;
}

NTSTATUS CAdapter::DispatchPower(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
	//DbgPrint(("DispatchPower\n"));
	PDATA_EXTENSION pDataExtension = (PDATA_EXTENSION)DeviceObject->DeviceExtension;
	CAdapter *adapter = pDataExtension->adapter;

    PoStartNextPowerIrp(Irp);
    IoSkipCurrentIrpStackLocation(Irp);
    return PoCallDriver(adapter->TopOfStackDeviceObject, Irp);

	//IoSkipCurrentIrpStackLocation( Irp );
	//return IoCallDriver( adapter->TopOfStackDeviceObject, Irp );

//	Irp->IoStatus.Status = STATUS_SUCCESS;
//	IoCompleteRequest( Irp, IO_NO_INCREMENT );
//	return STATUS_SUCCESS;
}

NTSTATUS CAdapter::DispatchPnp(PDEVICE_OBJECT DeviceObject, PIRP Irp)
{
	//DbgPrint(("DispatchPnp\n"));
	PDATA_EXTENSION pDataExtension = (PDATA_EXTENSION)DeviceObject->DeviceExtension;
	CAdapter *adapter = pDataExtension->adapter;

	PIO_STACK_LOCATION pStack = IoGetCurrentIrpStackLocation(Irp);

	switch( pStack->MinorFunction )
		{
		case IRP_MN_START_DEVICE:					DbgPrint("--IRP_MN_START_DEVICE\n");	break;
		case IRP_MN_QUERY_STOP_DEVICE:				DbgPrint("--IRP_MN_QUERY_STOP_DEVICE\n");	break;
		case IRP_MN_STOP_DEVICE:					DbgPrint("--IRP_MN_STOP_DEVICE\n");	break;
		case IRP_MN_CANCEL_STOP_DEVICE:				DbgPrint("--IRP_MN_CANCEL_STOP_DEVICE\n");	break;
		case IRP_MN_QUERY_REMOVE_DEVICE:			DbgPrint("--IRP_MN_QUERY_REMOVE_DEVICE\n");	break;
		case IRP_MN_REMOVE_DEVICE:					DbgPrint("--IRP_MN_REMOVE_DEVICE\n");	break;
		case IRP_MN_CANCEL_REMOVE_DEVICE:			DbgPrint("--IRP_MN_CANCEL_REMOVE_DEVICE\n");	break;
		case IRP_MN_SURPRISE_REMOVAL:				DbgPrint("--IRP_MN_SURPRISE_REMOVAL\n");	break;
		case IRP_MN_QUERY_CAPABILITIES:				DbgPrint("--IRP_MN_QUERY_CAPABILITIES\n");	break;
		case IRP_MN_QUERY_PNP_DEVICE_STATE:			DbgPrint("--IRP_MN_QUERY_PNP_DEVICE_STATE\n");	break;
		case IRP_MN_FILTER_RESOURCE_REQUIREMENTS:	DbgPrint("--IRP_MN_FILTER_RESOURCE_REQUIREMENTS\n");	break;
		case IRP_MN_DEVICE_USAGE_NOTIFICATION:		DbgPrint("--IRP_MN_DEVICE_USAGE_NOTIFICATION\n");	break;
		case IRP_MN_QUERY_DEVICE_RELATIONS:			DbgPrint("--IRP_MN_QUERY_DEVICE_RELATIONS\n");	break;
		case IRP_MN_QUERY_RESOURCES:				DbgPrint("--IRP_MN_QUERY_RESOURCES\n");	break;
		case IRP_MN_QUERY_RESOURCE_REQUIREMENTS:	DbgPrint("--IRP_MN_QUERY_RESOURCE_REQUIREMENTS\n");	break;
		case IRP_MN_QUERY_ID:						DbgPrint("--IRP_MN_QUERY_ID\n");	break;
		case IRP_MN_QUERY_DEVICE_TEXT:				DbgPrint("--IRP_MN_QUERY_DEVICE_TEXT\n");	break;
		case IRP_MN_QUERY_BUS_INFORMATION:			DbgPrint("--IRP_MN_QUERY_BUS_INFORMATION\n");	break;
		case IRP_MN_QUERY_INTERFACE:				DbgPrint("--IRP_MN_QUERY_INTERFACE\n");	break;
		case IRP_MN_READ_CONFIG:					DbgPrint("--IRP_MN_READ_CONFIG\n");	break;
		case IRP_MN_WRITE_CONFIG:					DbgPrint("--IRP_MN_WRITE_CONFIG\n");	break;
		case IRP_MN_EJECT:							DbgPrint("--IRP_MN_EJECT\n");	break;
		case IRP_MN_SET_LOCK:						DbgPrint("--IRP_MN_SET_LOCK\n");	break;
		};

	switch( pStack->MinorFunction )
			{
			case IRP_MN_START_DEVICE:
				{
					//DbgPrint((" IRP_MN_START_DEVICE\n"));
					PCM_RESOURCE_LIST raw = pStack->Parameters.StartDevice.AllocatedResources;
					PCM_RESOURCE_LIST translated = pStack->Parameters.StartDevice.AllocatedResourcesTranslated;

					adapter->PnpStartDevice(DeviceObject, Irp, raw, translated);
					
					IoSkipCurrentIrpStackLocation( Irp );
					return IoCallDriver( adapter->TopOfStackDeviceObject, Irp );
				}
			case IRP_MN_STOP_DEVICE:
				{
					//DbgPrint((" IRP_MN_STOP_DEVICE\n"));
					adapter->PnpStopDevice(DeviceObject);
					
					IoSkipCurrentIrpStackLocation( Irp );
					return IoCallDriver( adapter->TopOfStackDeviceObject, Irp );
				}

			case IRP_MN_REMOVE_DEVICE: // 장치를 제거하는 경우,
				{
					//DbgPrint((" IRP_MN_REMOVE_DEVICE\n"));
					PDEVICE_OBJECT LowerDevice;
					LowerDevice = adapter->TopOfStackDeviceObject;
					IoDetachDevice( adapter->TopOfStackDeviceObject );
					// SAMPLE DeviceObject를 DeviceStack으로 부터 제거.

					IoSetDeviceInterfaceState( &adapter->UnicodeString, FALSE );
					// 사용자가 우리의 DeviceStack에 접근하는 것을 금지
					
					RtlFreeUnicodeString( &adapter->UnicodeString );
					// 사용자가 접근하는 이름을 메모리에서 해제한다
					
					IoDeleteDevice( DeviceObject );
					// SAMPLE DeviceObject를 제거
					
					IoSkipCurrentIrpStackLocation( Irp );

					//DbgPrint("------------\n");
					//DbgPrint("DeleteMemory\n");

					if(adapter->m_pRISCMemory != NULL)
					{
						MmFreeContiguousMemory( adapter->m_pRISCMemory );
						adapter->m_pRISCMemory = NULL;
						adapter->m_dwRiscPhysical = 0;
					}
					if(adapter->m_pSystemMemory != NULL)
					{
						MmFreeContiguousMemory( adapter->m_pSystemMemory );
						adapter->m_pSystemMemory = NULL;
						for(int i=0; i<8; i++)
						{
							adapter->m_pCaptureMotion[i] = NULL;
							adapter->m_dwCaptureMotion[i] = 0;
						}
						for(int i=0; i<16; i++)
						{
							adapter->m_pCaptureMemory[i] = NULL;
							adapter->m_dwCapturePhysical[i] = 0;
						}

					}

					if(adapter->m_pBaseAddr != NULL)
					{
						MmUnmapIoSpace(adapter->m_pBaseAddr, 4096);
						adapter->m_pBaseAddr = NULL;
					}
					if(adapter->m_InterruptObject != NULL)
					{
						IoDisconnectInterrupt(adapter->m_InterruptObject);
						adapter->m_InterruptObject = NULL;
					}
					delete adapter;

					pDataExtension->adapter = NULL;
					return IoCallDriver( LowerDevice, Irp );
				}
			default:
				//DbgPrint((" Unknown\n"));
				IoSkipCurrentIrpStackLocation( Irp );
				return IoCallDriver( adapter->TopOfStackDeviceObject, Irp );
			}
			
	return STATUS_SUCCESS;
}

NTSTATUS CAdapter::PnpStartDevice(PDEVICE_OBJECT DeviceObject, PIRP Irp, PCM_RESOURCE_LIST raw, PCM_RESOURCE_LIST translated)
{
	//DbgPrint(("PnpStartDevice\n"));
	ULONG		int_Level;
	ULONG		int_Vector;
	KAFFINITY	int_Affinity;
	KINTERRUPT_MODE int_Mode;
	BOOLEAN int_Share;


	PCM_PARTIAL_RESOURCE_DESCRIPTOR resource = translated->List[0].PartialResourceList.PartialDescriptors;
	ULONG nres = translated->List[0].PartialResourceList.Count;

	for (ULONG i = 0; i < nres; ++i, ++resource)
	{						// for each resource
		switch (resource->Type)
		{					// switch on resource type
			case CmResourceTypeMemory:
				if(m_pBaseAddr != NULL)
				{
					MmUnmapIoSpace(m_pBaseAddr, 4096);
					m_pBaseAddr = NULL;
				}
				m_pBaseAddr = (BYTE*)MmMapIoSpace(
					resource->u.Memory.Start,
					4096,
					MmNonCached );
				break;
		
			case CmResourceTypeInterrupt:
				int_Level = (KIRQL) resource->u.Interrupt.Level;
				int_Vector = resource->u.Interrupt.Vector;
				int_Affinity = resource->u.Interrupt.Affinity;
				int_Mode = (resource->Flags == CM_RESOURCE_INTERRUPT_LATCHED)
					? Latched : LevelSensitive;
				int_Share = resource->ShareDisposition == CmResourceShareShared;

				if(m_InterruptObject != NULL)
				{
					IoDisconnectInterrupt(m_InterruptObject);
					m_InterruptObject = NULL;
				}
				IoConnectInterrupt(
					&m_InterruptObject,
					CAdapter::cbInterrupt,//PKSERVICE_ROUTINE (CCaptureDevice::Interrupt),
					this,
					NULL,
					int_Vector,
					(KIRQL)int_Level,
					(KIRQL)int_Level,
					int_Mode,
					int_Share ,
					int_Affinity,
					FALSE
				);
				break;

			default:
				KdPrint(( " - Unexpected I/O resource type %d\n", resource->Type));
				break;
		}					// switch on resource type
	}						// for each resource

	//DbgPrint("------------\n");
	PHYSICAL_ADDRESS padr = {0x0FFFFFFF, 0};
	if(m_pRISCMemory == NULL)
	{
		m_pRISCMemory = (BYTE*)MmAllocateContiguousMemory(RISC_TOTAL, padr);
		//DbgPrint("CreateMemory RISC : %X\n", m_pRISCMemory);
	}
	if(m_pSystemMemory == NULL)
	{
		m_pSystemMemory = (BYTE*)MmAllocateContiguousMemory(CAPTURE_TOTAL, padr);
		//DbgPrint("CreateMemory Capt : %X\n", m_pSystemMemory);
	}
	if(m_pRISCMemory == NULL || m_pSystemMemory == NULL)
	{
		return STATUS_ALLOTTED_SPACE_EXCEEDED;
	}


	// Create RISC Memory;
	m_dwRiscPhysical = MmGetPhysicalAddress(m_pRISCMemory).LowPart;

	m_pCaptureMemory[0] = m_pSystemMemory + CAPTURE_VIDEO_SIZE*0 + CAPTURE_MOTION_SIZE*0;
	m_pCaptureMotion[0] = m_pSystemMemory + CAPTURE_VIDEO_SIZE*1 + CAPTURE_MOTION_SIZE*0;

	m_pCaptureMemory[1] = m_pSystemMemory + CAPTURE_VIDEO_SIZE*1 + CAPTURE_MOTION_SIZE*1;
	m_pCaptureMotion[1] = m_pSystemMemory + CAPTURE_VIDEO_SIZE*2 + CAPTURE_MOTION_SIZE*1;

	m_pCaptureMemory[2] = m_pSystemMemory + CAPTURE_VIDEO_SIZE*2 + CAPTURE_MOTION_SIZE*2;
	m_pCaptureMotion[2] = m_pSystemMemory + CAPTURE_VIDEO_SIZE*3 + CAPTURE_MOTION_SIZE*2;

	m_pCaptureMemory[3] = m_pSystemMemory + CAPTURE_VIDEO_SIZE*3 + CAPTURE_MOTION_SIZE*3;
	m_pCaptureMotion[3] = m_pSystemMemory + CAPTURE_VIDEO_SIZE*4 + CAPTURE_MOTION_SIZE*3;

	m_pCaptureMemory[4] = m_pSystemMemory + CAPTURE_VIDEO_SIZE*4 + CAPTURE_MOTION_SIZE*4;
	m_pCaptureMotion[4] = m_pSystemMemory + CAPTURE_VIDEO_SIZE*5 + CAPTURE_MOTION_SIZE*4;

	m_pCaptureMemory[5] = m_pSystemMemory + CAPTURE_VIDEO_SIZE*5 + CAPTURE_MOTION_SIZE*5;
	m_pCaptureMotion[5] = m_pSystemMemory + CAPTURE_VIDEO_SIZE*6 + CAPTURE_MOTION_SIZE*5;

	m_pCaptureMemory[6] = m_pSystemMemory + CAPTURE_VIDEO_SIZE*6 + CAPTURE_MOTION_SIZE*6;
	m_pCaptureMotion[6] = m_pSystemMemory + CAPTURE_VIDEO_SIZE*7 + CAPTURE_MOTION_SIZE*6;

	m_pCaptureMemory[7] = m_pSystemMemory + CAPTURE_VIDEO_SIZE*7 + CAPTURE_MOTION_SIZE*7;
	m_pCaptureMotion[7] = m_pSystemMemory + CAPTURE_VIDEO_SIZE*8 + CAPTURE_MOTION_SIZE*7;

	m_pCaptureMemory[8] = m_pSystemMemory + CAPTURE_VIDEO_TOTAL + CAPTURE_MOTION_TOTAL + CAPTURE_AUDIO_SIZE*0;
	m_pCaptureMemory[9] = m_pSystemMemory + CAPTURE_VIDEO_TOTAL + CAPTURE_MOTION_TOTAL + CAPTURE_AUDIO_SIZE*1;
	m_pCaptureMemory[10] = m_pSystemMemory + CAPTURE_VIDEO_TOTAL + CAPTURE_MOTION_TOTAL + CAPTURE_AUDIO_SIZE*2;
	m_pCaptureMemory[11] = m_pSystemMemory + CAPTURE_VIDEO_TOTAL + CAPTURE_MOTION_TOTAL + CAPTURE_AUDIO_SIZE*3;
	m_pCaptureMemory[12] = m_pSystemMemory + CAPTURE_VIDEO_TOTAL + CAPTURE_MOTION_TOTAL + CAPTURE_AUDIO_SIZE*4;
	m_pCaptureMemory[13] = m_pSystemMemory + CAPTURE_VIDEO_TOTAL + CAPTURE_MOTION_TOTAL + CAPTURE_AUDIO_SIZE*5;
	m_pCaptureMemory[14] = m_pSystemMemory + CAPTURE_VIDEO_TOTAL + CAPTURE_MOTION_TOTAL + CAPTURE_AUDIO_SIZE*6;
	m_pCaptureMemory[15] = m_pSystemMemory + CAPTURE_VIDEO_TOTAL + CAPTURE_MOTION_TOTAL + CAPTURE_AUDIO_SIZE*7;

	for(int i=0; i<8; i++)
	{
		m_dwCaptureMotion[i] = MmGetPhysicalAddress(m_pCaptureMotion[i]).LowPart;
	}
	for(int i=0; i<16; i++)
	{
		m_dwCapturePhysical[i] = MmGetPhysicalAddress(m_pCaptureMemory[i]).LowPart;
	}
	for(int i=8; i<16; i++)
	{
		for(int j=0; j<CAPTURE_AUDIO_SIZE; j++)
			m_pCaptureMemory[i][j] = 0x20;
	}

/*
	WRITE_REGISTER_DPGPRINT( PULONG(m_pBaseAddr + 0x200), 0x348806B8 );
	WRITE_REGISTER_DPGPRINT( PULONG(m_pBaseAddr + 0x204), 0xBD800C04 );
	WRITE_REGISTER_DPGPRINT( PULONG(m_pBaseAddr + 0x208), 0x20307070 );
	WRITE_REGISTER_DPGPRINT( PULONG(m_pBaseAddr + 0x210), 0xF168F168 );
	WRITE_REGISTER_DPGPRINT( PULONG(m_pBaseAddr + 0x244), 0x0C05F2E4 );
	WRITE_REGISTER_DPGPRINT( PULONG(m_pBaseAddr + 0x258), 0x5244F271 );
	WRITE_REGISTER_DPGPRINT( PULONG(m_pBaseAddr + 0x25C), 0x10087384 );

	WRITE_REGISTER_DPGPRINT( PULONG(m_pBaseAddr + 0x280), 0x348806B8 );
	WRITE_REGISTER_DPGPRINT( PULONG(m_pBaseAddr + 0x284), 0xBD800C04 );
	WRITE_REGISTER_DPGPRINT( PULONG(m_pBaseAddr + 0x288), 0x20307070 );
	WRITE_REGISTER_DPGPRINT( PULONG(m_pBaseAddr + 0x290), 0xF168F168 );
	WRITE_REGISTER_DPGPRINT( PULONG(m_pBaseAddr + 0x2C4), 0x0C05F2E4 );
	WRITE_REGISTER_DPGPRINT( PULONG(m_pBaseAddr + 0x2D8), 0x5244F271 );
	WRITE_REGISTER_DPGPRINT( PULONG(m_pBaseAddr + 0x2DC), 0x10087384 );

	WRITE_REGISTER_DPGPRINT( PULONG(m_pBaseAddr + 0x300), 0x348806B8 );
	WRITE_REGISTER_DPGPRINT( PULONG(m_pBaseAddr + 0x304), 0xBD800C04 );
	WRITE_REGISTER_DPGPRINT( PULONG(m_pBaseAddr + 0x308), 0x20307070 );
	WRITE_REGISTER_DPGPRINT( PULONG(m_pBaseAddr + 0x310), 0xF168F168 );
	WRITE_REGISTER_DPGPRINT( PULONG(m_pBaseAddr + 0x344), 0x0C05F2E4 );
	WRITE_REGISTER_DPGPRINT( PULONG(m_pBaseAddr + 0x358), 0x5244F271 );
	WRITE_REGISTER_DPGPRINT( PULONG(m_pBaseAddr + 0x35C), 0x10087384 );

	WRITE_REGISTER_DPGPRINT( PULONG(m_pBaseAddr + 0x380), 0x348806B8 );
	WRITE_REGISTER_DPGPRINT( PULONG(m_pBaseAddr + 0x384), 0xBD800C04 );
	WRITE_REGISTER_DPGPRINT( PULONG(m_pBaseAddr + 0x388), 0x20307070 );
	WRITE_REGISTER_DPGPRINT( PULONG(m_pBaseAddr + 0x390), 0xF168F168 );
	WRITE_REGISTER_DPGPRINT( PULONG(m_pBaseAddr + 0x3C4), 0x0C05F2E4 );
	WRITE_REGISTER_DPGPRINT( PULONG(m_pBaseAddr + 0x3D8), 0x5244F271 );
	WRITE_REGISTER_DPGPRINT( PULONG(m_pBaseAddr + 0x3DC), 0x10087384 );
*/

	IoSetDeviceInterfaceState( &UnicodeString, TRUE ); 
	// 사용자가 우리의 DeviceStack에 접근하는 것을 허용

	return STATUS_SUCCESS;
}

NTSTATUS CAdapter::PnpStopDevice(PDEVICE_OBJECT DeviceObject)
{
	//DbgPrint(("PnpStopDevice\n"));
	IoSetDeviceInterfaceState( &UnicodeString, FALSE );
	// 사용자가 우리의 DeviceStack에 접근하는 것을 금지

	return STATUS_SUCCESS;
}

typedef union {
	struct {
		DWORD	Int_Ch0			:1;
		DWORD	Int_Ch1			:1;
		DWORD	Int_Ch2			:1;
		DWORD	Int_Ch3			:1;
		DWORD	Int_Ch4			:1;
		DWORD	Int_Ch5			:1;
		DWORD	Int_Ch6			:1;
		DWORD	Int_Ch7			:1;
		DWORD	Int_Ch8			:1;
		DWORD	Int_Ch9			:1;
		DWORD	Int_Ch10			:1;
		DWORD	Int_Ch11			:1;
		DWORD	Int_Ch12			:1;
		DWORD	Int_Ch13			:1;
		DWORD	Int_Ch14			:1;
		DWORD	Int_Ch15			:1;
		DWORD	Int_GPIO			:1;
		DWORD	Int_Montion		:1;
		DWORD	DMA_Err			:1;
		DWORD	reserve1			:5;
		DWORD	AUDField0		:1;
		DWORD	AUDField1		:1;
		DWORD	AUDField2		:1;
		DWORD	AUDField3		:1;
		DWORD	AUDField4		:1;
		DWORD	AUDField5		:1;
		DWORD	AUDField6		:1;
		DWORD	AUDField7		:1;
	} ds;
	DWORD dw;
} INT_STATE;

typedef struct {
		DWORD	DMA		:1;
		DWORD	Op			:1;
}	ERR_Bit;

typedef union {
	struct {
		ERR_Bit	Ch[16]		;
	} ds;
	DWORD dw;
} ERR_STATE;


typedef union {
	struct {
		DWORD	MultiSel0		:2;
		DWORD	MultiSel1		:2;
		DWORD	MultiSel2		:2;
		DWORD	MultiSel3		:2;
		DWORD	MultiSel4		:2;
		DWORD	MultiSel5		:2;
		DWORD	MultiSel6		:2;
		DWORD	MultiSel7		:2;
		DWORD	Field0			:1;
		DWORD	Field1			:1;
		DWORD	Field2			:1;
		DWORD	Field3			:1;
		DWORD	Field4			:1;
		DWORD	Field5			:1;
		DWORD	Field6			:1;
		DWORD	Field7			:1;
		DWORD	Lock0				:1;
		DWORD	Lock1				:1;
		DWORD	Lock2				:1;
		DWORD	Lock3				:1;
		DWORD	Lock4				:1;
		DWORD	Lock5				:1;
		DWORD	Lock6				:1;
		DWORD	Lock7				:1;
	} ds;
	DWORD dw;
} CH_STATE;

BOOLEAN CAdapter::HwInterrupt()
{
   BOOLEAN fMyIRQ = FALSE; 
	INT_STATE IntState;
	CH_STATE  ChState;
	if (m_IRQExpected)
    {
		m_IRQExpected = false;
		IntState.dw = READ_REGISTER_ULONG( PULONG(m_pBaseAddr + 0x1b0) );
		if ((IntState.dw&m_dwINTMaskBar) == 0)
		{
			//DbgPrint("Masked IntState %x\n", IntState.dw);
			if( (IntState.dw&0xFF) != 0 )
			{
				ChState.dw = READ_REGISTER_ULONG( PULONG(m_pBaseAddr + 0x1b8) );
				//DbgPrint("ChState %x\n", ChState.dw);
			}
			if(IntState.ds.Int_Ch0)
			{
				if(m_nFrameSkip[0] != 0)
				{
					m_nFrameSkip[0]--;
				}
				else
				{
					m_bField[0] = ChState.ds.Field0;
					KeInsertQueueDpc( &m_IsrDpc[0], (PVOID) (0), NULL );
				}
				fMyIRQ = TRUE; 
			}
			if(IntState.ds.Int_Ch1)
			{
				if(m_nFrameSkip[1] != 0)
				{
					m_nFrameSkip[1]--;
				}
				else
				{
					m_bField[1] = ChState.ds.Field1;
					KeInsertQueueDpc( &m_IsrDpc[1], (PVOID) (1), NULL );
				}
				fMyIRQ = TRUE; 
			}
			if(IntState.ds.Int_Ch2)
			{
				if(m_nFrameSkip[2] != 0)
				{
					m_nFrameSkip[2]--;
				}
				else
				{
					m_bField[2] = ChState.ds.Field2;
					KeInsertQueueDpc( &m_IsrDpc[2], (PVOID) (2), NULL );
				}
				fMyIRQ = TRUE; 
			}
			if(IntState.ds.Int_Ch3)
			{
				if(m_nFrameSkip[3] != 0)
				{
					m_nFrameSkip[3]--;
				}
				else
				{
					m_bField[3] = ChState.ds.Field3;
					KeInsertQueueDpc( &m_IsrDpc[3], (PVOID) (3), NULL );
				}
				fMyIRQ = TRUE; 
			}
			if(IntState.ds.Int_Ch4)
			{
				if(m_nFrameSkip[4] != 0)
				{
					m_nFrameSkip[4]--;
				}
				else
				{
					m_bField[4] = ChState.ds.Field4;
					KeInsertQueueDpc( &m_IsrDpc[4], (PVOID) (4), NULL );
				}
				fMyIRQ = TRUE; 
			}
			if(IntState.ds.Int_Ch5)
			{
				if(m_nFrameSkip[5] != 0)
				{
					m_nFrameSkip[5]--;
				}
				else
				{
					m_bField[5] = ChState.ds.Field5;
					KeInsertQueueDpc( &m_IsrDpc[5], (PVOID) (5), NULL );
				}
				fMyIRQ = TRUE; 
			}
			if(IntState.ds.Int_Ch6)
			{
				if(m_nFrameSkip[6] != 0)
				{
					m_nFrameSkip[6]--;
				}
				else
				{
					m_bField[6] = ChState.ds.Field6;
					KeInsertQueueDpc( &m_IsrDpc[6], (PVOID) (6), NULL );
				}
				fMyIRQ = TRUE; 
			}
			if(IntState.ds.Int_Ch7)
			{
				if(m_nFrameSkip[7] != 0)
				{
					m_nFrameSkip[7]--;
				}
				else
				{
					m_bField[7] = ChState.ds.Field7;
					KeInsertQueueDpc( &m_IsrDpc[7], (PVOID) (7), NULL );
				}
				fMyIRQ = TRUE; 
			}
			if(IntState.ds.Int_Ch8)
			{
				if(m_nFrameSkip[8] != 0)
				{
					m_nFrameSkip[8]--;
				}
				else
				{
					KeInsertQueueDpc( &m_IsrDpc[8], (PVOID) (8), NULL );
					m_dwAudioField[0] = IntState.ds.AUDField0;
				}
				fMyIRQ = TRUE; 
			}
			if(IntState.ds.Int_Ch9)
			{
				if(m_nFrameSkip[9] != 0)
				{
					m_nFrameSkip[9]--;
				}
				else
				{
					KeInsertQueueDpc( &m_IsrDpc[9], (PVOID) (9), NULL );
					m_dwAudioField[1] = IntState.ds.AUDField1;
				}
				fMyIRQ = TRUE; 
			}
			if(IntState.ds.Int_Ch10)
			{
				if(m_nFrameSkip[10] != 0)
				{
					m_nFrameSkip[10]--;
				}
				else
				{
					KeInsertQueueDpc( &m_IsrDpc[10], (PVOID) (10), NULL );
					m_dwAudioField[2] = IntState.ds.AUDField2;
				}
				fMyIRQ = TRUE; 
			}
			if(IntState.ds.Int_Ch11)
			{
				if(m_nFrameSkip[11] != 0)
				{
					m_nFrameSkip[11]--;
				}
				else
				{
					KeInsertQueueDpc( &m_IsrDpc[11], (PVOID) (11), NULL );
					m_dwAudioField[3] = IntState.ds.AUDField3;
				}
				fMyIRQ = TRUE; 
			}
			if(IntState.ds.Int_Ch12)
			{
				if(m_nFrameSkip[12] != 0)
				{
					m_nFrameSkip[12]--;
				}
				else
				{
					KeInsertQueueDpc( &m_IsrDpc[12], (PVOID) (12), NULL );
					m_dwAudioField[4] = IntState.ds.AUDField4;
				}
				fMyIRQ = TRUE; 
			}
			if(IntState.ds.Int_Ch13)
			{
				if(m_nFrameSkip[13] != 0)
				{
					m_nFrameSkip[13]--;
				}
				else
				{
					KeInsertQueueDpc( &m_IsrDpc[13], (PVOID) (13), NULL );
					m_dwAudioField[5] = IntState.ds.AUDField5;
				}
				fMyIRQ = TRUE; 
			}
			if(IntState.ds.Int_Ch14)
			{
				if(m_nFrameSkip[14] != 0)
				{
					m_nFrameSkip[14]--;
				}
				else
				{
					KeInsertQueueDpc( &m_IsrDpc[14], (PVOID) (14), NULL );
					m_dwAudioField[6] = IntState.ds.AUDField6;
				}
				fMyIRQ = TRUE; 
			}
			if(IntState.ds.Int_Ch15)
			{
				if(m_nFrameSkip[15] != 0)
				{
					m_nFrameSkip[15]--;
				}
				else
				{
					KeInsertQueueDpc( &m_IsrDpc[15], (PVOID) (15), NULL );
					m_dwAudioField[7] = IntState.ds.AUDField7;
				}
				fMyIRQ = TRUE; 
			}

			if(IntState.ds.DMA_Err)
			{
				m_dwErrorCode = READ_REGISTER_ULONG( PULONG(m_pBaseAddr + 0x1b4) );
				KeInsertQueueDpc( &m_IsrDpcErr[0], NULL, NULL );
				//DbgPrint("DMA Error : %X\n", m_dwErrorCode);
				fMyIRQ = TRUE; 
			}
		}
		else if(IntState.dw != 0xFFFFFFFF)
		{
			DbgPrint("  [%08X]  INT Error %08X-%8X\n", m_pBaseAddr, m_dwINTMaskBar, IntState.dw);
			m_dwErrorCode = READ_REGISTER_ULONG( PULONG(m_pBaseAddr + 0x1b4) );
			KeInsertQueueDpc( &m_IsrDpcErr[0], NULL, NULL );
			fMyIRQ = TRUE; 
		}
		m_IRQExpected = true;
	}
	return fMyIRQ;
}

void CAdapter::cbDpcFunc(IN PKDPC Dpc,IN CAdapter *pAdapter, IN PVOID SystemArg1, IN PVOID SystemArg2)
{
	DWORD StreamNumber = (DWORD)SystemArg1;
	//DbgPrint("cbDpcFunc %x\n", StreamNumber);
	if(StreamNumber < 8 && pAdapter->m_bCaptureStart[StreamNumber])
	{
		DWORD ch;
		if(pAdapter->m_bSplit[StreamNumber])
		{
			ch = (pAdapter->m_dwGPIO>>StreamNumber) & 1;
			if(ch)
				pAdapter->m_dwGPIO &= ~(1<<StreamNumber);
			else
				pAdapter->m_dwGPIO |= (1<<StreamNumber);
			
			//DbgPrint("GPIO %06X - %d\n", pAdapter->m_dwGPIO, ch);
			WRITE_REGISTER_DPGPRINT( PULONG(pAdapter->m_pBaseAddr + 0x1C4), pAdapter->m_dwGPIO );
			if(ch)
			{
				pAdapter -> VideoCaptureRoutine (StreamNumber);
			}
		}
		else
		{
			pAdapter -> VideoCaptureRoutine (StreamNumber);
		}
	}
	else if(StreamNumber < 16 && pAdapter->m_bCaptureStart[StreamNumber])
	{
		pAdapter -> AudioCaptureRoutine (StreamNumber);
	}
}

//Dec Off
void CAdapter::cbDpcFuncErr0(IN PKDPC Dpc,IN CAdapter *pAdapter, IN PVOID SystemArg1, IN PVOID SystemArg2)
{
	DWORD		dwData;
	DWORD		ProgLocBase;
	ERR_STATE	ErrState;
	ErrState.dw = pAdapter -> m_dwErrorCode;

	DbgPrint("  [Adap:%08X]  Dma Error0 - DEC Off%x\n", pAdapter, ErrState.dw);
	DbgPrint("  [Base:%08X]  Dma Error0 - DEC Off%x\n", pAdapter->m_pBaseAddr, ErrState.dw);

	DWORD		dwBase[16] = {0x200, 0x280, 0x300, 0x380, 0x400, 0x480, 0x500, 0x580, 0x270, 0x2F0, 0x370, 0x3F0, 0x470, 0x4F0, 0x570, 0x5F0};
	DWORD		dwRisc[16] = { 0x60,  0x74,  0x88,  0x9C,  0xB0,  0xC4,  0xD8,  0xEC, 0x100, 0x114, 0x128, 0x13C, 0x150, 0x164, 0x178, 0x18C};
	int i;
	int j;

	for(i=0; i<16; i++)
		KeRemoveQueueDpc(&(pAdapter->m_IsrDpc[i]));
	KeRemoveQueueDpc(&(pAdapter->m_IsrDpcErr[0]));

	for(i=0; i<16; i++)
	{
		if( pAdapter->m_bCaptureStart[i] )
		{
			// Decoder Stop
			if(pAdapter->m_bDecStateNotSave[i])
			{
				pAdapter->m_dwDecEnable[i] = READ_REGISTER_ULONG( PULONG(pAdapter->m_pBaseAddr + dwBase[i] ) );
				pAdapter->m_dwDecEnable[i] = READ_REGISTER_ULONG( PULONG(pAdapter->m_pBaseAddr + dwBase[i] ) );
				pAdapter->m_dwDecDisable[i] = pAdapter->m_dwDecEnable[i] & 0x7FFFFFFF;
				pAdapter->m_bDecStateNotSave[i] = FALSE;
				//DbgPrint("  [%08X]  Dec Read %x\n", pAdapter->m_pBaseAddr, pAdapter->m_dwDecEnable[i]);
			}
			WRITE_REGISTER_DPGPRINT( PULONG(pAdapter->m_pBaseAddr + dwBase[i]), pAdapter->m_dwDecDisable[i] );
		}
	}

	LARGE_INTEGER DueTime;
	DueTime.QuadPart = -100000L;
	KeSetTimer(
		&(pAdapter->DMATimer),
		DueTime,
		&(pAdapter->m_IsrDpcErr[1])
		);
}


void CAdapter::cbDpcFuncErr1(IN PKDPC Dpc,IN CAdapter *pAdapter, IN PVOID SystemArg1, IN PVOID SystemArg2)
{
	DWORD		dwData;
	DWORD		ProgLocBase;
	ERR_STATE	ErrState;
	ErrState.dw = pAdapter -> m_dwErrorCode;
	DbgPrint("  [RISC%:08X]  Dma Error1 - DMA off%x\n", pAdapter->m_pRISCMemory, ErrState.dw);

	DWORD		dwBase[16] = {0x200, 0x280, 0x300, 0x380, 0x400, 0x480, 0x500, 0x580, 0x270, 0x2F0, 0x370, 0x3F0, 0x470, 0x4F0, 0x570, 0x5F0};
	DWORD		dwRisc[16] = { 0x60,  0x74,  0x88,  0x9C,  0xB0,  0xC4,  0xD8,  0xEC, 0x100, 0x114, 0x128, 0x13C, 0x150, 0x164, 0x178, 0x18C};
	int i;
	int j;

	for(i=0; i<16; i++)
		KeRemoveQueueDpc(&(pAdapter->m_IsrDpc[i]));
	KeRemoveQueueDpc(&(pAdapter->m_IsrDpcErr[0]));
	KeRemoveQueueDpc(&(pAdapter->m_IsrDpcErr[1]));

	for(i=0; i<16; i++)
	{
		if( pAdapter->m_bCaptureStart[i] )
		{
			// Risc Stop
			WRITE_REGISTER_DPGPRINT( PULONG(pAdapter->m_pBaseAddr + dwRisc[i]), 0x000E8000 );
			WRITE_REGISTER_DPGPRINT( PULONG(pAdapter->m_pBaseAddr + dwRisc[i] + 0x04), 0x00000000 );
			WRITE_REGISTER_DPGPRINT( PULONG(pAdapter->m_pBaseAddr + dwRisc[i] + 0x08), 0x00000000 );
			WRITE_REGISTER_DPGPRINT( PULONG(pAdapter->m_pBaseAddr + dwRisc[i] + 0x0C), 0x00000000 );
			WRITE_REGISTER_DPGPRINT( PULONG(pAdapter->m_pBaseAddr + dwRisc[i] + 0x10), 0x00000000 );
		}
	}

	LARGE_INTEGER DueTime;
	DueTime.QuadPart = -100000L;
	KeSetTimer(
		&(pAdapter->DMATimer),
		DueTime,
		&(pAdapter->m_IsrDpcErr[2])
		);

}


void CAdapter::cbDpcFuncErr2(IN PKDPC Dpc,IN CAdapter *pAdapter, IN PVOID SystemArg1, IN PVOID SystemArg2)
{
	DWORD		dwData;
	DWORD		ProgLocBase;
	ERR_STATE	ErrState;
	ErrState.dw = pAdapter -> m_dwErrorCode;
	DbgPrint("  [SYST%:08X]  Dma Error2 - DMA on%x\n", pAdapter->m_pSystemMemory, ErrState.dw);

	DWORD		dwBase[16] = {0x200, 0x280, 0x300, 0x380, 0x400, 0x480, 0x500, 0x580, 0x270, 0x2F0, 0x370, 0x3F0, 0x470, 0x4F0, 0x570, 0x5F0};
	DWORD		dwRisc[16] = { 0x60,  0x74,  0x88,  0x9C,  0xB0,  0xC4,  0xD8,  0xEC, 0x100, 0x114, 0x128, 0x13C, 0x150, 0x164, 0x178, 0x18C};
	int i;
	int j;

	for(i=0; i<16; i++)
		KeRemoveQueueDpc(&(pAdapter->m_IsrDpc[i]));
	KeRemoveQueueDpc(&(pAdapter->m_IsrDpcErr[0]));
	KeRemoveQueueDpc(&(pAdapter->m_IsrDpcErr[1]));
	KeRemoveQueueDpc(&(pAdapter->m_IsrDpcErr[2]));

	for(i=0; i<16; i++)
	{
		if(pAdapter->m_bCaptureStart[i])
		{
			DWORD		ProgLocBase = pAdapter->m_dwRiscPhysical + RISC_VIDEO_SIZE*i;
			WRITE_REGISTER_DPGPRINT( PULONG(pAdapter->m_pBaseAddr + dwRisc[i] + 0x04), 0x00000000 );
			WRITE_REGISTER_DPGPRINT( PULONG(pAdapter->m_pBaseAddr + dwRisc[i] + 0x08), 0x00000000 );
			WRITE_REGISTER_DPGPRINT( PULONG(pAdapter->m_pBaseAddr + dwRisc[i] + 0x0C), 0x00000000 );
			WRITE_REGISTER_DPGPRINT( PULONG(pAdapter->m_pBaseAddr + dwRisc[i] + 0x10), ProgLocBase );
			WRITE_REGISTER_DPGPRINT( PULONG(pAdapter->m_pBaseAddr + dwRisc[i]), 0x000E8001 );
		}
	}
	LARGE_INTEGER DueTime;
	DueTime.QuadPart = -100000L;
	KeSetTimer(
		&(pAdapter->DMATimer),
		DueTime,
		&(pAdapter->m_IsrDpcErr[3])
		);

}


void CAdapter::cbDpcFuncErr3(IN PKDPC Dpc,IN CAdapter *pAdapter, IN PVOID SystemArg1, IN PVOID SystemArg2)
{
	DWORD		dwData;
	DWORD		ProgLocBase;
	ERR_STATE	ErrState;
	ErrState.dw = pAdapter -> m_dwErrorCode;
	DbgPrint("  [USER%:08X]  Dma Error3 - Dec on%x\n\n", pAdapter->m_pCaptureUser, ErrState.dw);

	DWORD		dwBase[16] = {0x200, 0x280, 0x300, 0x380, 0x400, 0x480, 0x500, 0x580, 0x270, 0x2F0, 0x370, 0x3F0, 0x470, 0x4F0, 0x570, 0x5F0};
	DWORD		dwRisc[16] = { 0x60,  0x74,  0x88,  0x9C,  0xB0,  0xC4,  0xD8,  0xEC, 0x100, 0x114, 0x128, 0x13C, 0x150, 0x164, 0x178, 0x18C};

	int i;

	for(i=0; i<16; i++)
		KeRemoveQueueDpc(&(pAdapter->m_IsrDpc[i]));
	KeRemoveQueueDpc(&(pAdapter->m_IsrDpcErr[0]));
	KeRemoveQueueDpc(&(pAdapter->m_IsrDpcErr[1]));
	KeRemoveQueueDpc(&(pAdapter->m_IsrDpcErr[2]));
	KeRemoveQueueDpc(&(pAdapter->m_IsrDpcErr[3]));

	for(i=0; i<16; i++)
	{
		if( pAdapter->m_bCaptureStart[i] )
		{
			// Decoder Start
			WRITE_REGISTER_DPGPRINT( PULONG(pAdapter->m_pBaseAddr + dwBase[i]), pAdapter->m_dwDecEnable[i] );
			pAdapter->m_nFrameSkip[i] = 3;
		}
	}
	//DbgPrint("  [%08X]  Dec En  %x\n\n", pAdapter->m_pBaseAddr, pAdapter->m_dwDecEnable[0]);
	//WRITE_REGISTER_DPGPRINT( PULONG(pAdapter->m_pBaseAddr + 0x1FC), ErrState.dw );

}

void	CAdapter::VideoCaptureRoutine(DWORD dwStreamNumber)
{
	//if(dwStreamNumber ==0)
	//DbgPrint("VideoCapture %d - %d\n", dwStreamNumber, m_bField[dwStreamNumber]);
	if(m_bOddOnly[dwStreamNumber] || m_bField[dwStreamNumber])
		KeSetEvent(m_pEvent[dwStreamNumber], 0, FALSE);
	else
		KeSetEvent(m_pEvent[dwStreamNumber+16], 0, FALSE);
}

void	CAdapter::AudioCaptureRoutine(DWORD dwStreamNumber)
{
	DWORD	dwAudioCh = dwStreamNumber-8;
	if(!m_dwAudioField[dwAudioCh])
	{
		//DbgPrint("Audio%02d Interrupt 1\n",dwStreamNumber);
		RtlCopyMemory(m_pAudioData[dwAudioCh], m_pCaptureMemory[dwStreamNumber]+m_dwAudioBufferSize[dwAudioCh], m_dwAudioBufferSize[dwAudioCh]);
	}
	else
	{
		//DbgPrint("Audio%02d Interrupt 0\n",dwStreamNumber);
		RtlCopyMemory(m_pAudioData[dwAudioCh], m_pCaptureMemory[dwStreamNumber], m_dwAudioBufferSize[dwAudioCh]);
	}
		
	//DbgPrint("Audio Data : %02x\n", *m_pCaptureMemory[dwStreamNumber]);
	//DbgPrint("Ch%02d Audio Data Out: %02x\n", dwStreamNumber, *m_pCaptureMemory[dwStreamNumber]);
	KeSetEvent(m_pEvent[dwStreamNumber], 0, FALSE);
}

NTSTATUS CAdapter::RegisterWrite(PMV9300_RW pData)
{
	if(pData->dwAddr+pData->nCounter*4 >= 4096)
		return STATUS_INVALID_PARAMETER;

	for(int i=0; i<pData->nCounter; i++)
	{
		if((pData->dwAddr + (DWORD)i*4) == 0x1c4)
		{
			SetGPIO(&(pData->pData[i]));
		}
		else if((pData->dwAddr + (DWORD)i*4) == 0x1c8)
		{
			SetGPOE(&(pData->pData[i]));
		}
		else
			WRITE_REGISTER_DPGPRINT( PULONG(m_pBaseAddr + pData->dwAddr + (DWORD)i*4), pData->pData[i]);
	}
	return STATUS_SUCCESS;
}

NTSTATUS CAdapter::RegisterRead(PMV9300_RW pData)
{
	if(pData->dwAddr+pData->nCounter*4 >= 4096)
		return STATUS_INVALID_PARAMETER;

	for(int i=0; i<pData->nCounter; i++)
		pData->pData[i] = READ_REGISTER_ULONG( PULONG(m_pBaseAddr + pData->dwAddr + (DWORD)i*4) );
	return STATUS_SUCCESS;
}

void CAdapter::CreateVideoRiscCmd(BOOL bInterlace, int cx, int cy, BOOL bSkip, PULONG *pProgLocation, DWORD dwTAddr, BOOL bSplit, BOOL bStandard, DWORD dwBase, DWORD dwMotionAddr)
{
	//DbgPrint("\n\nCreateVideoRiscCmd\n  BOOL bInterlace = %d\n  int cx = %d\n  int cy = %d\n  BOOL bSkip = %d\n", bInterlace, cx, cy, bSkip);
	//DbgPrint("  PULONG *pProgLocation = %x\n  DWORD dwTAddr = %x\n  DWORD dwMultiAddr = %x\n  DWORD dwMotionAddr = %x\n", 
	//	*pProgLocation, dwTAddr, dwMultiAddr, dwMotionAddr);
	PULONG pProgLoc = *pProgLocation;

	if(bSkip)
	{
		if(bSplit)
		{
			RISC_SYNC(pProgLoc, SC_VRO, 0, 0);
			
			RISC_SYNC(pProgLoc, SC_VRO, 0, 0);
		}
		else
		{
			RISC_SYNC(pProgLoc, SC_VRO, 0, 0);
		}
	}
	else
	{
		if(bSplit)
		{
			// Split 0;
			//RISC_REGW(pProgLoc, 0,0, 0x1C4, 0x00000000);	//Sel 1
			//RISC_REGW(pProgLoc, 0,0, dwBase+0x1C, 0x98000002);	//Sel 0
			//RISC_REGW(pProgLoc, 0,0, dwBase, 0x251009C4);	//Sel 1
			//RISC_REGW(pProgLoc, 0,0, dwBase, 0xA51009C4);	//Sel 1
			/*if(bStandard)
			{
				RISC_REGW(pProgLoc, 0,0, dwBase, 0x451009C4);	//Sel 1
				RISC_REGW(pProgLoc, 0,0, dwBase, 0xC51009C4);	//Sel 1
			}
			else
			{
				RISC_REGW(pProgLoc, 0,0, dwBase, 0x051009C4);	//Sel 1
				RISC_REGW(pProgLoc, 0,0, dwBase, 0x851009C4);	//Sel 1
			}*/
			for(int i=0; i<100; i++)
			{
				RISC_WRITE(pProgLoc, dwTAddr + cx*2*i, cx/4, 1,1,0,0, 0);
			}
			/*RISC_SYNC(pProgLoc, SC_VRO, 0, 0);
			RISC_SYNC(pProgLoc, SC_VRO, 0, 0);*/
			//RISC_SYNC(pProgLoc, SC_VRE, 0, 0);
			//RISC_SYNC(pProgLoc, SC_VRO, 0, 0);
			//RISC_SYNC(pProgLoc, SC_VRE, 0, 0);
			RISC_SYNC(pProgLoc, SC_VRO, 0, 0);
			RISC_SYNC(pProgLoc, SC_FM1, 0, 0);
			for(int i=0; i<cy-1; i++)
			//for(int i=0; i<cy; i++)
			{
				RISC_WRITE(pProgLoc, dwTAddr + cx*2*i, cx/4, 1,1,0,0, 0);
			}
			RISC_WRITE(pProgLoc, dwTAddr + cx*2*(cy-1), cx/4, 1,1,1,0, 0);

			// Split 1;
			//RISC_REGW(pProgLoc, 0,0, 0x1C4, 0x00FFFFFF);	//Sel 1
			//RISC_REGW(pProgLoc, 0,0, dwBase+0x1C, 0xB8000002);	//Sel 1
			//RISC_REGW(pProgLoc, 0,0, dwBase, 0x251009C4);	//Sel 1
			//RISC_REGW(pProgLoc, 0,0, dwBase, 0xA51009C4);	//Sel 1
			//RISC_REGW(pProgLoc, 0,0, dwBase, 0x459009C4);	//Sel 1
			//RISC_REGW(pProgLoc, 0,0, dwBase, 0xC59009C4);	//Sel 1
			for(int i=0; i<100; i++)
			{
				RISC_WRITE(pProgLoc, dwTAddr + cx + cx*2*i, cx/4, 1,1,0,0, 0);
			}
			//RISC_SYNC(pProgLoc, SC_VRO, 0, 0);
			//RISC_SYNC(pProgLoc, SC_VRE, 0, 0);
			RISC_SYNC(pProgLoc, SC_VRO, 0, 0);
			RISC_SYNC(pProgLoc, SC_FM1, 0, 0);
			for(int i=0; i<cy-1; i++)
			{
				RISC_WRITE(pProgLoc, dwTAddr + cx + cx*2*i, cx/4, 1,1,0,0, 0);
			}
			// Interrupt output..
			RISC_WRITE(pProgLoc, dwTAddr + cx + cx*2*(cy-1), cx/4, 1,1,1,0, 0);
		}
		else
		{
			if(bInterlace)
			{
				// SYNC VRO
				RISC_SYNC(pProgLoc, SC_VRO, 0, 0);

				if(dwMotionAddr != 0)
				{
					// Motion Detect data
					RISC_WRITE(pProgLoc, dwMotionAddr, 6, 1,1,0,0, 0);
				}

				// SYNC FM1
				RISC_SYNC(pProgLoc, SC_FM1, 0, 0);

				// Image Data
				for(int i=0; i<cy/2; i++)
				{
					RISC_WRITE(pProgLoc, dwTAddr + cx*2*i, cx/4, 1,1,0,0, 0);
				}

				// SYNC FM1
				RISC_SYNC(pProgLoc, SC_FM1, 0, 0);

				// Image Data
				for(int i=0; i<cy/2-1; i++)
				{
					RISC_WRITE(pProgLoc, dwTAddr +cx +cx*2*i, cx/4, 1,1,0,0, 0);
				}

				// Interrupt out
				RISC_WRITE(pProgLoc, dwTAddr + (cy-1)*cx, cx/4, 1,1,1,0, 0);
			}
			else
			{	// Non Interlace
				RISC_SYNC(pProgLoc, SC_VRO, 0, 0);

				if(dwMotionAddr != 0)
				{
					RISC_WRITE(pProgLoc, dwMotionAddr, 6, 1,1,0,0, 0);
				}

				RISC_SYNC(pProgLoc, SC_FM1, 0, 0);

				if(cy>288)
				{
					for(int i=0; i<cy/2; i++)
					{
						RISC_WRITE(pProgLoc, dwTAddr+cx*i, cx/4, 1,1,0,0, 0);
					}
					RISC_SYNC(pProgLoc, SC_FM1, 0, 0);
					for(int i=0; i<cy/2-1; i++)
					{
						RISC_WRITE(pProgLoc, dwTAddr+cx*(i+cy/2), cx/4, 1,1,0,0, 0);
					}
				}
				else
				{
					for(int i=0; i<cy-1; i++)
					{
						RISC_WRITE(pProgLoc, dwTAddr+cx*i, cx/4, 1,1,0,0, 0);
					}
				}
				RISC_WRITE(pProgLoc, dwTAddr + (cy-1)*cx, cx/4, 1,1,1,0, 0);
			}
		}

	}
	*pProgLocation = pProgLoc;
}

NTSTATUS CAdapter::SetVideoFormat(PMV9300_FORMAT pFormat)
{
	DWORD	dwLinePitch;
	int nCh = pFormat->nChannel;
	m_bOddOnly[nCh] = TRUE;

	//1. Memory allocation
	if(m_pCaptureUser[nCh] == NULL)
	{
		// Mdl을 준비한다
		m_pCaptureMdl[nCh] = IoAllocateMdl( 
			m_pCaptureMemory[nCh], 
			CAPTURE_VIDEO_SIZE+CAPTURE_MOTION_SIZE, 
			0, 0, 0 );
		// Mdl을 완성시킨다
		MmBuildMdlForNonPagedPool( m_pCaptureMdl[nCh] );

		// 사용자가 볼 수 있는 가상메모리를 매핑시킨다
		m_pCaptureUser[nCh] = (BYTE*)MmMapLockedPagesSpecifyCache(m_pCaptureMdl[nCh],	UserMode, MmWriteCombined , NULL, FALSE, HighPagePriority );
	}

	//2. Line Pitch
	switch(pFormat->nFormat)
	{
	case VIDEOFORMAT_YUY2:
	case VIDEOFORMAT_RGB15:
	case VIDEOFORMAT_RGB16:
		dwLinePitch = pFormat->dwWidth * 2;
		break;
	case VIDEOFORMAT_RGB24:
		dwLinePitch = pFormat->dwWidth * 3;
		break;
	case VIDEOFORMAT_YUV420:
	case VIDEOFORMAT_YUV411:
		dwLinePitch = pFormat->dwWidth * 12 /8;
		break;
	case VIDEOFORMAT_Y8:
	case VIDEOFORMAT_RGB8:
		dwLinePitch = pFormat->dwWidth;
		break;
	}

	if(pFormat->nFrame < 100)
	{
		if(pFormat->nFrame < 1)
			pFormat->nFrame = 1;
		if(pFormat->nFrame > 30)
			pFormat->nFrame = 30;
	}
	else
	{
		if(pFormat->nFrame < 101)
			pFormat->nFrame = 101;
		if(pFormat->nFrame > 125)
			pFormat->nFrame = 125;
	}
	m_bSplit[nCh] = pFormat->bSplit;			// Split (0,1:split);
	
		// Decoder Register Setting
		DWORD				dwBase = 0x200 + nCh*0x80;
		DWORD				dwReg00;
		DWORD				dwReg10;
		DWORD				dwReg14;
		DWORD				dwReg1C;

		// Color format and Decoder Disable
		dwReg00 = READ_REGISTER_ULONG( PULONG(m_pBaseAddr + dwBase + 0x000) );
		dwReg00 &= 0x7FFF8FFF;	//Decoder Enable is Bit [31] , VideoFormat is Bit [13:11] in Register300
		dwReg00 |= ( (pFormat->nFormat & 0x07)<<12 ); //0:YUV2, 1:BTYUV, 2,Y8, 3:YUV420, 4:RGB8, 5:RGB15, 6:RGB16, 7:RGB24 
		WRITE_REGISTER_DPGPRINT( PULONG(m_pBaseAddr + dwBase + 0x000), dwReg00 );

		// Horizontal Scaling
		dwReg10 = READ_REGISTER_ULONG( PULONG(m_pBaseAddr + dwBase + 0x010) );
		dwReg10 &= 0xFFC00000;
		dwReg10 |= pFormat->dwWidth;			//Even Field Image width Size
		dwReg10 |= (pFormat->dwWidth << 11);	//Odd  Field Image width Size

		WRITE_REGISTER_DPGPRINT( PULONG(m_pBaseAddr + dwBase + 0x010), dwReg10 );

		// Vertical Scaling
		dwReg14 = READ_REGISTER_ULONG( PULONG(m_pBaseAddr + dwBase + 0x014) );
		dwReg14 &= 0xFFC00000;
		if(pFormat->bInterlace)
		{
			dwReg14 |= pFormat->dwHeight/2;
			dwReg14 |= ((pFormat->dwHeight/2) << 11);
		}
		else
		{
			dwReg14 |= pFormat->dwHeight;
			dwReg14 |= (pFormat->dwHeight << 11);
		}

		WRITE_REGISTER_DPGPRINT( PULONG(m_pBaseAddr + dwBase + 0x014), dwReg14 );

		// Split Setting
		/*if(m_bSplit[nCh])
		{
			dwReg1C = 0x90005000;
		}
		else*/
		{
			dwReg1C = 0x00005000;
		}
		WRITE_REGISTER_DPGPRINT( PULONG(m_pBaseAddr + dwBase + 0x01C), dwReg1C );

		if(pFormat->bMotion)
		{
			WRITE_REGISTER_DPGPRINT( PULONG(m_pBaseAddr + dwBase + 0x024), 0x802000FB);
		}
		else
		{
			WRITE_REGISTER_DPGPRINT( PULONG(m_pBaseAddr + dwBase + 0x024), 0x002000FB);
		}

		////////////////////////////////////////////////////////////////////////
		// RISC program setting
		DWORD		ProgLocBase = m_dwRiscPhysical + RISC_VIDEO_SIZE*nCh;
		PULONG		pProgLoc    = PULONG(m_pRISCMemory + RISC_VIDEO_SIZE*nCh);
		PULONG		pProgLocBase = PULONG(m_pRISCMemory + RISC_VIDEO_SIZE*nCh);

		for(DWORD dwI=0; dwI<RISC_VIDEO_SIZE/8; dwI++)
		{
			RISC_JUMP(pProgLoc, ProgLocBase, 0);
		}
		pProgLoc    = PULONG(m_pRISCMemory + RISC_VIDEO_SIZE*nCh);

		if(pFormat->nFrame > 100)
		{	// PAL
			char *pCh;
			pCh = FrameRate_PAL1[pFormat->nFrame-100];
			for(int i=0; i<25; i++)
			{
				if(pCh[i] == '0')
				{	// Skip
					CreateVideoRiscCmd(pFormat->bInterlace, dwLinePitch, pFormat->dwHeight, TRUE, &pProgLoc, m_dwCapturePhysical[nCh],m_bSplit[nCh], pFormat->bStandard, dwBase, pFormat->bMotion?m_dwCaptureMotion[nCh]:0);
				}
				else
				{
					CreateVideoRiscCmd(pFormat->bInterlace, dwLinePitch, pFormat->dwHeight, FALSE, &pProgLoc, m_dwCapturePhysical[nCh],m_bSplit[nCh], pFormat->bStandard, dwBase, pFormat->bMotion?m_dwCaptureMotion[nCh]:0);
				}
			}
		}
		else
		{	// NTSC
			char *pCh;
			pCh = FrameRate_NTSC1[pFormat->nFrame];
			for(int i=0; i<30; i++)
			{
				if(pCh[i] == '0')
				{	// Skip
					CreateVideoRiscCmd(pFormat->bInterlace, dwLinePitch, pFormat->dwHeight, TRUE, &pProgLoc, m_dwCapturePhysical[nCh],m_bSplit[nCh], pFormat->bStandard, dwBase, pFormat->bMotion?m_dwCaptureMotion[nCh]:0);
				}
				else
				{
					CreateVideoRiscCmd(pFormat->bInterlace, dwLinePitch, pFormat->dwHeight, FALSE, &pProgLoc, m_dwCapturePhysical[nCh],m_bSplit[nCh], pFormat->bStandard, dwBase, pFormat->bMotion?m_dwCaptureMotion[nCh]:0);
				}
			}
		}
		RISC_JUMP(pProgLoc, ProgLocBase, 0);

	return STATUS_SUCCESS;
}

void CAdapter::CreateVideoRiscCmd2(BOOL bOddOnly, int cx1, int cy1, BOOL bSkip1, int cx2, int cy2, BOOL bSkip2, PULONG *pProgLocation, DWORD dwTAddr, DWORD dwMotionAddr, DWORD dwChBaseAddr)
{
	//DbgPrint("RiscCmd2\nbOddOnly = %d\ncx1 = %d\ncy1 = %d\nbSkip1 = %d\ncx2 = %d\ncy2 = %d\nbSkip2 = %d\npProgLocation=%XdwTAddr = %x\ndwMotionAddr = %d\ndwChBaseAddr = %d\n\n",bOddOnly, cx1, cy1, bSkip1, cx2, cy2, bSkip2, *pProgLocation, dwTAddr, dwMotionAddr, dwChBaseAddr);

	//DbgPrint("  PULONG *pProgLocation = %x\n  DWORD dwTAddr = %x\n  DWORD dwMultiAddr = %x\n  DWORD dwMotionAddr = %x\n", 
	//	*pProgLocation, dwTAddr, dwMultiAddr, dwMotionAddr);
	PULONG pProgLoc = *pProgLocation;

	if(bOddOnly)
	{
		if(bSkip1)
		{
			RISC_SYNC(pProgLoc, SC_VRO, 0, 0);
		}
		else
		{
			if(cy1>288)
			{
				// SYNC VRO
				RISC_SYNC(pProgLoc, SC_VRO, 0, 0);

				if(dwMotionAddr != 0)
				{
					// Motion Detect data
					RISC_WRITE(pProgLoc, dwMotionAddr, 6, 1,1,0,0, 0);
				}

				// SYNC FM1
				RISC_SYNC(pProgLoc, SC_FM1, 0, 0);

				// Image Data
				for(int i=0; i<cy1/2; i++)
				{
					RISC_WRITE(pProgLoc, dwTAddr + cx1*2*i, cx1/4, 1,1,0,0, 0);
				}

				// SYNC FM1
				RISC_SYNC(pProgLoc, SC_FM1, 0, 0);

				// Image Data
				for(int i=0; i<cy1/2-1; i++)
				{
					RISC_WRITE(pProgLoc, dwTAddr +cx1 +cx1*2*i, cx1/4, 1,1,0,0, 0);
				}

				// Interrupt out
				RISC_WRITE(pProgLoc, dwTAddr + (cy1-1)*cx1, cx1/4, 1,1,1,0, 0);
			}
			else
			{	// Non Interlace
				RISC_SYNC(pProgLoc, SC_VRO, 0, 0);

				if(dwMotionAddr != 0)
				{
					RISC_WRITE(pProgLoc, dwMotionAddr, 6, 1,1,0,0, 0);
				}

				RISC_SYNC(pProgLoc, SC_FM1, 0, 0);

				for(int i=0; i<cy1-1; i++)
				{
					RISC_WRITE(pProgLoc, dwTAddr+cx1*i, cx1/4, 1,1,0,0, 0);
				}
				RISC_WRITE(pProgLoc, dwTAddr + (cy1-1)*cx1, cx1/4, 1,1,1,0, 0);
			}
		}
	}
	else
	{
		if(bSkip1)
		{
			RISC_SYNC(pProgLoc, SC_VRO, 0, 0);
		}
		else
		{
			RISC_SYNC(pProgLoc, SC_VRO, 0, 0);

			if(dwMotionAddr != 0)
			{
				RISC_WRITE(pProgLoc, dwMotionAddr, 6, 1,1,0,0, 0);
			}

			RISC_SYNC(pProgLoc, SC_FM1, 0, 0);
			for(int i=0; i<cy1-1; i++)
			{
				RISC_WRITE(pProgLoc, dwTAddr + cx1*i, cx1/4, 1,1,0,0, 0);
			}
			RISC_WRITE(pProgLoc, dwTAddr + (cy1-1)*cx1, cx1/4, 1,1,1,0, 0);
		}			

		if(!bSkip2)
		{
			//RISC_SYNC(pProgLoc, SC_VRE, 0, 0);
			RISC_SYNC(pProgLoc, SC_FM1, 0, 0);
			for(int i=0; i<cy2-1; i++)
			{
				RISC_WRITE(pProgLoc, dwTAddr+cx1*cy1 + cx2*i, cx2/4, 1,1,0,0, 0);
			}
			RISC_WRITE(pProgLoc, dwTAddr+cx1*cy1 + (cy2-1)*cx2, cx2/4, 1,1,1,0, 0);
		}
	}

	*pProgLocation = pProgLoc;
}

NTSTATUS CAdapter::SetVideoFormat2(PMV9300_FORMAT2 pFormat)
{
	DWORD	dwLinePitch1;
	DWORD	dwLinePitch2;
	int nCh = pFormat->nChannel;
	m_bOddOnly[nCh] = pFormat->bOddOnly;
	
	//1. Memory allocation
	if(m_pCaptureUser[nCh] == NULL)
	{
		// Mdl을 준비한다
		m_pCaptureMdl[nCh] = IoAllocateMdl( 
			m_pCaptureMemory[nCh], 
			CAPTURE_VIDEO_SIZE+CAPTURE_MOTION_SIZE, 
			0, 0, 0 );
		// Mdl을 완성시킨다
		MmBuildMdlForNonPagedPool( m_pCaptureMdl[nCh] );

		// 사용자가 볼 수 있는 가상메모리를 매핑시킨다
		//m_pCaptureUser[nCh] = (BYTE*)MmMapLockedPages( m_pCaptureMdl[nCh],	UserMode );
		m_pCaptureUser[nCh] = (BYTE*)MmMapLockedPagesSpecifyCache(m_pCaptureMdl[nCh],	UserMode, MmWriteCombined , NULL, FALSE, HighPagePriority );
	}

	//2. Line Pitch
	switch(pFormat->nFormat)
	{
	case VIDEOFORMAT_YUY2:
	case VIDEOFORMAT_RGB15:
	case VIDEOFORMAT_RGB16:
		dwLinePitch1 = pFormat->dwWidth1 * 2;
		dwLinePitch2 = pFormat->dwWidth2 * 2;
		break;
	case VIDEOFORMAT_RGB24:
		dwLinePitch1 = pFormat->dwWidth1 * 3;
		dwLinePitch2 = pFormat->dwWidth2 * 3;
		break;
	case VIDEOFORMAT_YUV420:
	case VIDEOFORMAT_YUV411:
		dwLinePitch1 = pFormat->dwWidth1 * 12 /8;
		dwLinePitch2 = pFormat->dwWidth2 * 12 /8;
		break;
	case VIDEOFORMAT_Y8:
	case VIDEOFORMAT_RGB8:
		dwLinePitch1 = pFormat->dwWidth1;
		dwLinePitch2 = pFormat->dwWidth2;
		break;
	}

	if(pFormat->nStandard)
	{	//PAL
		if(pFormat->nFrame1 < 101)
			pFormat->nFrame1 = 101;
		if(pFormat->nFrame1 > 125)
			pFormat->nFrame1 = 125;
		if(pFormat->nFrame2 < 101)
			pFormat->nFrame2 = 101;
		if(pFormat->nFrame2 > 125)
			pFormat->nFrame2 = 125;
	}
	else
	{
		if(pFormat->nFrame1 < 1)
			pFormat->nFrame1 = 1;
		if(pFormat->nFrame1 > 30)
			pFormat->nFrame1 = 30;
		if(pFormat->nFrame2 < 1)
			pFormat->nFrame2 = 1;
		if(pFormat->nFrame2 > 30)
			pFormat->nFrame2 = 30;
	}
	m_bSplit[nCh] = FALSE;			// Split (0,1:split);

		// Decoder Register Setting
		DWORD				dwBase = 0x200 + nCh*0x80;
		DWORD				dwReg00;
		DWORD				dwReg10;
		DWORD				dwReg14;
		DWORD				dwReg1C;

		// Color format and Decoder Disable
		dwReg00 = READ_REGISTER_ULONG( PULONG(m_pBaseAddr + dwBase + 0x000) );
		dwReg00 &= 0x7FFF8FFF;	//Decoder Enable is Bit [31] , VideoFormat is Bit [13:11] in Register300
		dwReg00 |= ( (pFormat->nFormat & 0x07)<<12 ); //0:YUV2, 1:BTYUV, 2,Y8, 3:YUV420, 4:RGB8, 5:RGB15, 6:RGB16, 7:RGB24 
		WRITE_REGISTER_DPGPRINT( PULONG(m_pBaseAddr + dwBase + 0x000), dwReg00 );


		// Horizontal Scaling
		dwReg10 = READ_REGISTER_ULONG( PULONG(m_pBaseAddr + dwBase + 0x010) );
		dwReg10 &= 0xFFC00000;
		if(pFormat->bOddOnly)
		{
			dwReg10 |= pFormat->dwWidth1;			//Even Field Image width Size
			dwReg10 |= (pFormat->dwWidth1 << 11);	//Odd  Field Image width Size
		}
		else
		{
			dwReg10 |= pFormat->dwWidth2;			//Even Field Image width Size
			dwReg10 |= (pFormat->dwWidth1 << 11);	//Odd  Field Image width Size
		}
		WRITE_REGISTER_DPGPRINT( PULONG(m_pBaseAddr + dwBase + 0x010), dwReg10 );

		// Vertical Scaling
		dwReg14 = READ_REGISTER_ULONG( PULONG(m_pBaseAddr + dwBase + 0x014) );
		dwReg14 &= 0xFFC00000;

		if(pFormat->bOddOnly && pFormat->dwHeight1 > 288)
		{
			dwReg14 |= pFormat->dwHeight1/2;
			dwReg14 |= (pFormat->dwHeight1/2 << 11);
		}
		else
		{
			if(pFormat->dwHeight2 > 288)
				pFormat->dwHeight2 = 288;
			dwReg14 |= pFormat->dwHeight2;
			if(pFormat->dwHeight1 > 288)
				pFormat->dwHeight1 = 288;
			dwReg14 |= (pFormat->dwHeight1 << 11);
		}
		WRITE_REGISTER_DPGPRINT( PULONG(m_pBaseAddr + dwBase + 0x014), dwReg14 );

		dwReg1C = 0x00005000;
		WRITE_REGISTER_DPGPRINT( PULONG(m_pBaseAddr + dwBase + 0x01C), dwReg1C );

		if(pFormat->bMotion)
		{
			WRITE_REGISTER_DPGPRINT( PULONG(m_pBaseAddr + dwBase + 0x024), 0x802000FB);
		}
		else
		{
			WRITE_REGISTER_DPGPRINT( PULONG(m_pBaseAddr + dwBase + 0x024), 0x002000FB);
		}

		////////////////////////////////////////////////////////////////////////
		// RISC program setting
		DWORD		ProgLocBase = m_dwRiscPhysical + RISC_VIDEO_SIZE*nCh;
		PULONG		pProgLoc    = PULONG(m_pRISCMemory + RISC_VIDEO_SIZE*nCh);
		PULONG		pProgLocBase = PULONG(m_pRISCMemory + RISC_VIDEO_SIZE*nCh);

		if(pFormat->nStandard)
		{	// PAL
			char *pCh1;
			char *pCh2;
			pCh1 = FrameRate_PAL1[pFormat->nFrame1-100];
			pCh2 = FrameRate_PAL2[pFormat->nFrame2-100];
			for(int i=0; i<25; i++)
			{
				BOOL bSkip1 = pCh1[i] == '0';
				BOOL bSkip2 = pCh2[i] == '0';
				//DbgPrint("\nCh%d - %d -%d:%d\n", nCh, i, bSkip1, bSkip2);
				CreateVideoRiscCmd2(pFormat->bOddOnly, dwLinePitch1, pFormat->dwHeight1, bSkip1,
													   dwLinePitch2, pFormat->dwHeight2, bSkip2,
													   &pProgLoc, m_dwCapturePhysical[nCh], pFormat->bMotion?m_dwCaptureMotion[nCh]:0, dwBase);
			}
		}
		else
		{	// NTSC
			char *pCh1;
			char *pCh2;
			pCh1 = FrameRate_NTSC1[pFormat->nFrame1];
			pCh2 = FrameRate_NTSC2[pFormat->nFrame2];
			for(int i=0; i<30; i++)
			{
				BOOL bSkip1 = pCh1[i] == '0';
				BOOL bSkip2 = pCh2[i] == '0';
				//DbgPrint("\nCh%d - %d -%d:%d\n", nCh, i, bSkip1, bSkip2);
				CreateVideoRiscCmd2(pFormat->bOddOnly, dwLinePitch1, pFormat->dwHeight1, bSkip1,
													   dwLinePitch2, pFormat->dwHeight2, bSkip2,
													   &pProgLoc, m_dwCapturePhysical[nCh], pFormat->bMotion?m_dwCaptureMotion[nCh]:0, dwBase);
			}
		}
		RISC_JUMP(pProgLoc, ProgLocBase, 0);


	return STATUS_SUCCESS;
}

NTSTATUS CAdapter::SetVideoDisplay(PMV9300_DISPLAY pDisp)
{
	DWORD dwChBaseAddr = (DWORD)m_pBaseAddr + 0x200 + pDisp->nChannel*0x80;
	DWORD dwData = ((DWORD)pDisp->byBright<<24) + ((DWORD)pDisp->byContrast<<16) + ((DWORD)pDisp->bySaturation<<8) + ((DWORD)pDisp->byHue);
	WRITE_REGISTER_DPGPRINT( PULONG(dwChBaseAddr + 0xC), dwData );
	return STATUS_SUCCESS;
}

NTSTATUS CAdapter::SetEvent(PMV9300_EVENT pEv, KPROCESSOR_MODE RequestMode)
{
	NTSTATUS	status;

	if( m_pEvent[pEv->nChannel] != NULL)
	{
		ObDereferenceObject(m_pEvent[pEv->nChannel]);
		m_pEvent[pEv->nChannel] = NULL;
	}

	status = ObReferenceObjectByHandle(pEv->hEvent, EVENT_MODIFY_STATE,
				*ExEventObjectType, RequestMode, (PVOID*) &m_pEvent[pEv->nChannel], NULL);
	if(status != STATUS_SUCCESS)
	{
		if( m_pEvent[pEv->nChannel] != NULL)
		{
			ObDereferenceObject(m_pEvent[pEv->nChannel]);
			m_pEvent[pEv->nChannel] = NULL;
		}
	}
	return STATUS_SUCCESS;
}

NTSTATUS CAdapter::GetVideoMemory(PMV9300_VIDEOMEM pVideoMem)
{
	pVideoMem->pMem = m_pCaptureUser[pVideoMem->nChannel];
	pVideoMem->dwSize = CAPTURE_VIDEO_SIZE;
	return STATUS_SUCCESS;
}

NTSTATUS CAdapter::CaptureStart(int nCh)
{
	//DbgPrint("CaptureStart %d\n", nCh);
	if(m_bCaptureStart[nCh])	
		return STATUS_SUCCESS;

	WRITE_REGISTER_DPGPRINT( PULONG(m_pBaseAddr + 0x1F0), (DWORD)m_pBaseAddr );

	if( nCh < 8 )
	{
		////////////////////////////////////////////////////////////////////////


		////////////////////////////////////////////////////////////////////////
		// RISC Register setting
		DWORD		ProgLocBase = m_dwRiscPhysical + RISC_VIDEO_SIZE*nCh;
		PULONG		pProgLocBase = PULONG(m_pRISCMemory + RISC_VIDEO_SIZE*nCh);
		DWORD	dwRisc = 0x060 + nCh*0x14;
		WRITE_REGISTER_DPGPRINT( PULONG(m_pBaseAddr + dwRisc + 0x04), 0x00000000 );
		WRITE_REGISTER_DPGPRINT( PULONG(m_pBaseAddr + dwRisc + 0x08), 0x00000000 );
		WRITE_REGISTER_DPGPRINT( PULONG(m_pBaseAddr + dwRisc + 0x0C), 0x00000000 );
		WRITE_REGISTER_DPGPRINT( PULONG(m_pBaseAddr + dwRisc + 0x10), ProgLocBase );

/*		ProgLocBase = m_dwRiscPhysical + RISC_VIDEO_SIZE*nCh;
		pProgLocBase = PULONG(m_pRISCMemory + RISC_VIDEO_SIZE*nCh);
		for(int i=0; i<576*; i++)
		{

			DbgPrint("%8X - %8X\n", ProgLocBase+i*4, *(pProgLocBase+i));
		}*/
		// Risc Start
		WRITE_REGISTER_DPGPRINT( PULONG(m_pBaseAddr + dwRisc), 0x000E8001 );
	
		m_dwGPIO &= ~(DWORD(1<<nCh));
		
		WRITE_REGISTER_DPGPRINT( PULONG(m_pBaseAddr + 0x1C4), m_dwGPIO );

		m_bCaptureStart[nCh] = TRUE;
		m_bDecStateNotSave[nCh] = TRUE;
		m_dwINTMaskBar &= ~(1<<nCh);
	}
	else if(nCh < 16)
	{	// Audio

		DWORD				ProgLocBase;
		PULONG				pProgLoc;

		ProgLocBase = m_dwRiscPhysical + RISC_VIDEO_TOTAL + RISC_AUDIO_SIZE*(nCh-8);
		pProgLoc = PULONG(m_pRISCMemory + RISC_VIDEO_TOTAL + RISC_AUDIO_SIZE*(nCh-8));

		DWORD dwBase = 0x200 + (nCh-8)*0x80 + 0x70;
		DWORD dwRisc = 0x060 + (nCh)*0x14;

		// Create RISC Instruction
		//0~3
		RISC_SYNC(pProgLoc, SC_VRO, 0, 0);
		RISC_WRITE(pProgLoc, m_dwCapturePhysical[nCh]                           ,m_dwAudioBufferSize[nCh-8]/2/4 ,1,1,1,0, 0);
		RISC_WRITE(pProgLoc, m_dwCapturePhysical[nCh]+m_dwAudioBufferSize[nCh-8]/2,m_dwAudioBufferSize[nCh-8]/2/4 ,1,1,0,0, 0);
		RISC_JUMP(pProgLoc, ProgLocBase+8*4, 0);

		//8~11
		RISC_SYNC(pProgLoc, SC_VRE, 0, 0);
		RISC_WRITE(pProgLoc, m_dwCapturePhysical[nCh]+m_dwAudioBufferSize[nCh-8]                           ,m_dwAudioBufferSize[nCh-8]/2/4 ,1,1,1,0, 0);
		RISC_WRITE(pProgLoc, m_dwCapturePhysical[nCh]+m_dwAudioBufferSize[nCh-8]+m_dwAudioBufferSize[nCh-8]/2,m_dwAudioBufferSize[nCh-8]/2/4 ,1,1,0,0, 0);

		RISC_JUMP(pProgLoc, ProgLocBase, 0);

		pProgLoc = PULONG(m_pRISCMemory + RISC_VIDEO_TOTAL + RISC_AUDIO_SIZE*(nCh-8));

		//DWORD dwAudio = READ_REGISTER_ULONG( PULONG(m_pBaseAddr + dwBase) );
		//dwAudio |= 0x80000000;
		//WRITE_REGISTER_DPGPRINT( PULONG(m_pBaseAddr + dwBase), dwAudio );

		WRITE_REGISTER_DPGPRINT( PULONG(m_pBaseAddr + dwRisc + 0x04), 0x00000000 );
		WRITE_REGISTER_DPGPRINT( PULONG(m_pBaseAddr + dwRisc + 0x08), 0x00000000 );
		WRITE_REGISTER_DPGPRINT( PULONG(m_pBaseAddr + dwRisc + 0x0C), 0x00000000 );
		WRITE_REGISTER_DPGPRINT( PULONG(m_pBaseAddr + dwRisc + 0x10), ProgLocBase );
		WRITE_REGISTER_DPGPRINT( PULONG(m_pBaseAddr + dwRisc), 0x000E8001 );

		m_bCaptureStart[nCh] = TRUE;
		m_bDecStateNotSave[nCh] = TRUE;
		m_dwINTMaskBar &= ~(1<<nCh);
	}
	return STATUS_SUCCESS;
}

NTSTATUS CAdapter::CaptureStop(int nCh)
{
	//DbgPrint("CaptureStop %d\n", nCh);

	if(nCh < 8)
	{	// Video
		DWORD dwBase = 0x200 + nCh*0x80;
		DWORD dwRisc = 0x060 + nCh*0x14;

		// Risc Stop
		// Risc Start
		dwRisc = 0x060 + nCh*0x14;
		WRITE_REGISTER_DPGPRINT( PULONG(m_pBaseAddr + dwRisc), 0x000E8000 );
		WRITE_REGISTER_DPGPRINT( PULONG(m_pBaseAddr + dwRisc + 0x04), 0x00000000 );
		WRITE_REGISTER_DPGPRINT( PULONG(m_pBaseAddr + dwRisc + 0x08), 0x00000000 );
		WRITE_REGISTER_DPGPRINT( PULONG(m_pBaseAddr + dwRisc + 0x0C), 0x00000000 );
		WRITE_REGISTER_DPGPRINT( PULONG(m_pBaseAddr + dwRisc + 0x10), 0x00000000 );

		// Decoder Stop
		DWORD	dwReg00;
		dwReg00 = READ_REGISTER_ULONG( PULONG(m_pBaseAddr + dwBase + 0x000) );
		dwReg00 &= 0x7FFFFFFF;	//Decoder Enable is Bit [31] , VideoFormat is Bit [13:11] in Register300
		WRITE_REGISTER_DPGPRINT( PULONG(m_pBaseAddr + dwBase), dwReg00 );

		m_bCaptureStart[nCh] = FALSE;
		m_bDecStateNotSave[nCh] = TRUE;

		m_dwINTMaskBar |= (1<<nCh);
	}
	else if(nCh<16)
	{	// Audio
		DWORD dwBase = 0x200 + (nCh-8)*0x80 + 0x70;
		DWORD dwRisc = 0x060 + (nCh)*0x14;
        //DWORD dwAudio = READ_REGISTER_ULONG( PULONG(m_pBaseAddr + dwBase) );
		//dwAudio &= 0x7FFFFFFF;
		//WRITE_REGISTER_DPGPRINT( PULONG(m_pBaseAddr + dwBase), dwAudio );
		WRITE_REGISTER_DPGPRINT( PULONG(m_pBaseAddr + dwRisc), 0x000E8000 );

		m_bCaptureStart[nCh] = FALSE;
		m_bDecStateNotSave[nCh] = TRUE;

		m_dwINTMaskBar |= (1<<nCh);
	}
	return STATUS_SUCCESS;
}

NTSTATUS CAdapter::SetAudioFormat(PMV9300_AUDIOFM pAud)
{
	if(CAPTURE_AUDIO_SIZE/2 < pAud->nBufferSize)
		return STATUS_INVALID_PARAMETER;

	//DbgPrint(("Audio Format "));
	//DbgPrint("Ch(%d) : Freq:%ld, Format:%d, Buffer%d\n", pAud->nChannel, pAud->dwFreq, pAud->nFormat, pAud->nBufferSize);

	DWORD dwBase = 0x200 + (pAud->nChannel-8)*0x80 + 0x70;
	DWORD dwReg = READ_REGISTER_ULONG( PULONG(m_pBaseAddr + dwBase) );

	//Frequency
	dwReg = 0x80000000;

	//ClkScale = Freq / MainClk(100Khz) *4096
	DWORD	dwDst = ((pAud->dwFreq) * 4096 + 50000) / 100000;

	dwReg |= (dwDst&0xFFF);
	//DbgPrint("Freq : %8x\n", dwReg);

	// Line is 2
	dwReg |= 0x04000000;

	// Audio Mode and Buffer size
	dwReg |= (pAud->nFormat&0x3) << 29;
	//DbgPrint("Mode : %8x\n", dwReg);
	switch(pAud->nFormat)
	{
	case AUDIOFORMAT_8MONO:
		dwReg |= (pAud->nBufferSize/2) << 12;	//data size : 8bit
		break;
	case AUDIOFORMAT_8STEREO:
		dwReg |= (pAud->nBufferSize/2/2) << 12;	//data size : 16bit
		break;
	case AUDIOFORMAT_16MONO:
		dwReg |= (pAud->nBufferSize/2/2) << 12;	//data size : 16bit
		break;
	case AUDIOFORMAT_16STEREO:
		dwReg |= (pAud->nBufferSize/4/2) << 12;	//data size : 32bit
		break;
	}
	//DbgPrint("Buff : %8x\n", dwReg);

	WRITE_REGISTER_DPGPRINT( PULONG(m_pBaseAddr + dwBase), dwReg );


	m_dwAudioBufferSize[pAud->nChannel-8] = pAud->nBufferSize;

	//기존 메모리를 삭제
	if(m_pAudioData[pAud->nChannel-8] != NULL)
	{
		ExFreePool(m_pAudioData[pAud->nChannel-8]);
		m_pAudioData[pAud->nChannel-8] = NULL;
	}

	//새로운 메모리를 만듬.
	//m_pAudioData[pAud->nChannel-8] = (BYTE*)ExAllocatePool(NonPagedPool, pAud->nBufferSize);	//m_dwCaptureMemorySize[pFormat->nChannel]/10 은 여유분..
	m_pAudioData[pAud->nChannel-8] = (BYTE*)ExAllocatePoolWithTag(NonPagedPool, pAud->nBufferSize,'ISmD'); //  DmSI
	for(int i=0; i<pAud->nBufferSize; i++)
	{
		m_pAudioData[pAud->nChannel-8][i] = 0x20;
	}

	if(m_pCaptureUser[pAud->nChannel] != NULL)
	{
		// 우선 사용자가 사용하던 UserLevel가상메모리를 해제한다
		MmUnmapLockedPages( 
			m_pCaptureUser[pAud->nChannel], 
			m_pCaptureMdl[pAud->nChannel]
			);

		m_pCaptureUser[pAud->nChannel] = NULL;

		// 그다음 Mdl을 해제한다
		IoFreeMdl( 
			m_pCaptureMdl[pAud->nChannel] 
			);

		m_pCaptureMdl[pAud->nChannel] = 0;
	}
	//if(m_pCaptureUser[pAud->nChannel] == NULL)
	{
		// Mdl을 준비한다
		m_pCaptureMdl[pAud->nChannel] = IoAllocateMdl( 
			m_pAudioData[pAud->nChannel-8], 
			pAud->nBufferSize, 
			0, 0, 0 );

		// Mdl을 완성시킨다
		MmBuildMdlForNonPagedPool( m_pCaptureMdl[pAud->nChannel] );

		// 사용자가 볼 수 있는 가상메모리를 매핑시킨다
		//m_pCaptureUser[pAud->nChannel] = (BYTE*)MmMapLockedPages( m_pCaptureMdl[pAud->nChannel],	UserMode );
		m_pCaptureUser[pAud->nChannel] = (BYTE*)MmMapLockedPagesSpecifyCache(m_pCaptureMdl[pAud->nChannel],	UserMode, MmWriteCombined  , NULL, FALSE, HighPagePriority );
	}
	return STATUS_SUCCESS;
}

NTSTATUS CAdapter::GetVideoLock(DWORD *pLock)
{
	*pLock = READ_REGISTER_ULONG( PULONG(m_pBaseAddr + 0x1AC) );
	return STATUS_SUCCESS;
}

NTSTATUS CAdapter::SetGPIO(DWORD *pGPIO)
{
	int i;
	if(m_bSplit[0])
	{
		m_dwGPIO &= 0xFF;
		m_dwGPIO |= (*pGPIO & 0xFFFF00);
	}
	else
		m_dwGPIO = *pGPIO;
	
	for(i=0;i<8; i++)
	{
		if(m_bCaptureStart[i])
			break;
	}
	if(i == 8 || !m_bSplit[0])
		WRITE_REGISTER_DPGPRINT( PULONG(m_pBaseAddr + 0x1C4), m_dwGPIO );
	return STATUS_SUCCESS;
}

NTSTATUS CAdapter::GetGPIO(DWORD *pGPIO)
{
	*pGPIO = READ_REGISTER_ULONG( PULONG(m_pBaseAddr + 0x1C4) );
	return STATUS_SUCCESS;
}

NTSTATUS CAdapter::SetGPOE(DWORD *pGPIO)
{
	*pGPIO &= 0xFFFFFF;
	if(m_bSplit[0])
	{
		m_dwGPIO &= 0xFF;
		m_dwGPIO |= (*pGPIO & 0xFFFF00);
	}

	WRITE_REGISTER_DPGPRINT( PULONG(m_pBaseAddr + 0x1C8), *pGPIO );	

	return STATUS_SUCCESS;
}
