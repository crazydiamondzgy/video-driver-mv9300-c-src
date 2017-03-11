#ifndef __MV9300_DRIVER_LIB_H__
#define __MV9300_DRIVER_LIB_H__

#define FILE_DEVICE_UNKNOWN             0x00000022
#define METHOD_BUFFERED                 0
#define FILE_ANY_ACCESS                 0
#define CTL_CODE( DeviceType, Function, Method, Access ) (                 \
    ((DeviceType) << 16) | ((Access) << 14) | ((Function) << 2) | (Method) \
)
#define IOCTL_MV9300_REG_WRITE		CTL_CODE(FILE_DEVICE_UNKNOWN, 0x1, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_MV9300_REG_READ		CTL_CODE(FILE_DEVICE_UNKNOWN, 0x2, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_MV9300_VIDEO_FORMAT	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x3, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_MV9300_VIDEO_DISPLAY	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x4, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_MV9300_CAP_EVENT		CTL_CODE(FILE_DEVICE_UNKNOWN, 0x5, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_MV9300_CAP_MEM		CTL_CODE(FILE_DEVICE_UNKNOWN, 0x6, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_MV9300_CAP_START		CTL_CODE(FILE_DEVICE_UNKNOWN, 0x7, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_MV9300_CAP_STOP		CTL_CODE(FILE_DEVICE_UNKNOWN, 0x8, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_MV9300_AUDIO_FORMAT	CTL_CODE(FILE_DEVICE_UNKNOWN, 0x9, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_MV9300_GET_LOCK		CTL_CODE(FILE_DEVICE_UNKNOWN, 0xA, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_MV9300_SET_GPIO		CTL_CODE(FILE_DEVICE_UNKNOWN, 0xB, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_MV9300_GET_GPIO		CTL_CODE(FILE_DEVICE_UNKNOWN, 0xC, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_MV9300_SET_GPOE		CTL_CODE(FILE_DEVICE_UNKNOWN, 0xD, METHOD_BUFFERED, FILE_ANY_ACCESS)
#define IOCTL_MV9300_VIDEO_FORMAT2	CTL_CODE(FILE_DEVICE_UNKNOWN, 0xE, METHOD_BUFFERED, FILE_ANY_ACCESS)

#define VIDEOFORMAT_YUY2	0
#define VIDEOFORMAT_YUV411	1
#define VIDEOFORMAT_Y8		2
#define VIDEOFORMAT_YUV420	3
#define VIDEOFORMAT_RGB8	4
#define VIDEOFORMAT_RGB15	5
#define VIDEOFORMAT_RGB16	6
#define VIDEOFORMAT_RGB24	7

#define AUDIOFORMAT_8MONO		0
#define AUDIOFORMAT_8STEREO		1
#define AUDIOFORMAT_16MONO		2
#define AUDIOFORMAT_16STEREO	3

typedef struct {
	DWORD dwAddr;			//Resigter Address
	int	nCounter;			//Data Counter
	DWORD *pData;			//Data
} MV9300_RW, *PMV9300_RW;

typedef struct {
	int		nChannel;			//0~3
	DWORD	dwWidth;		// Image Width
	DWORD	dwHeight;		// Image Height
	BOOL	bInterlace;
	int		nFormat;		// VIDEOFORMAT_XXXX
	int		nFrame;			// FrameRate = OrgFrameRate / nFrame; ex) NTSC : 30/3 = 10 Frame.
	BOOL	bSplit;			// Split (0,1:split);
	BOOL	bMotion;
	BOOL	bStandard;
} MV9300_FORMAT, *PMV9300_FORMAT;

typedef struct {
	int		nChannel;		//0~3
	int		nStandard;		// 0: NTSC, 1:PAL
	BOOL	bOddOnly;		// TRUE : Odd, Even - FALSE : odd
	DWORD	dwWidth1;		// Image Width
	DWORD	dwHeight1;		// Image Height
	int		nFrame1;		// NTSC : 1~30, PAL : 101~125(1~25)
	DWORD	dwWidth2;		// 
	DWORD	dwHeight2;		// 
	int		nFrame2;		// 
	int		nFormat;		// VIDEOFORMAT_XXXX
	BOOL	bMotion;
} MV9300_FORMAT2, *PMV9300_FORMAT2;

typedef struct {
	int nChannel;			//0~3
	BYTE byBright;			//0~255	: Brightness
	BYTE byContrast;		//0~255	: Contrast
	BYTE bySaturation;		//0~255	: Saturation
	BYTE byHue;				//0~255	: Hue
} MV9300_DISPLAY, *PMV9300_DISPLAY;

typedef struct {
	int nChannel;			//0~7	0~3:Video, 4~7:Audio
	HANDLE	hEvent;			// Capture Event
} MV9300_EVENT, *PMV9300_EVENT;

typedef struct {
	int nChannel;			//0~7	0~3:Video, 4~7:Audio
	BYTE *pMem;				//Memory Address
	DWORD	dwSize;			//Memory Size
} MV9300_VIDEOMEM, *PMV9300_VIDEOMEM;

typedef struct {
	int		nChannel;			//4~7
	DWORD	dwFreq;				//Sampling Frequency
	int		nFormat;			//AUDIOFORMAT_XXXX
	int		nBufferSize;		//Sound Buffer Size (multiple of 256)
} MV9300_AUDIOFM, *PMV9300_AUDIOFM;

#endif