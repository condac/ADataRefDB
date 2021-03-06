#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <errno.h>
#include <fcntl.h>
#include <time.h>

#define USE_PRINTF_DEBUG
//#define PRINTF_ADDR "10.0.0.123"
#define PRINTF_ADDR "127.0.0.1"

#if defined(MACOSX)
#    define APL 1
#    define IBM 0
#    define LIN 0
#    include <unistd.h>
#    include <sys/socket.h>
#    include <netinet/in.h>
#    include <arpa/inet.h>
#    include <sys/select.h>
#    include <pthread.h>
#    include <time.h>
#    include <sys/time.h>
#    include <IOKit/IOKitLib.h>
#    include <IOKit/hid/IOHIDLib.h>
#    include <IOKit/hid/IOHIDDevice.h>
#elif defined(LINUX)
#    define APL 0
#    define IBM 0
#    define LIN 1
#    include <unistd.h>
#    include <sys/socket.h>
#    include <sys/types.h>
#    include <sys/stat.h>
#    include <sys/ioctl.h>
#    include <netinet/in.h>
#    include <arpa/inet.h>
#    include <sys/select.h>
#    include <pthread.h>
#    include <time.h>
#    ifdef USE_PRINTF_DEBUG
#        include <execinfo.h>
#    endif
#    include <linux/hidraw.h>
#elif defined(WINDOWS) || defined(WINDOWS64)
#    define APL 0
#    define IBM 1
#    define LIN 0
#    ifndef WINVER
#        define WINVER 0x0500
#    endif
#    ifndef _WIN32_WINNT
#        define _WIN32_WINNT 0x0500
#    endif
//#include <winsock2.h>
#    include <windows.h>
//#include <ws2tcpip.h>
//#include <winuser.h>
#    include <setupapi.h>
#    include <hidsdi.h>
#    include <dbt.h>
//#include "thread.h"
#endif

#if IBM
#    include <windows.h>
#endif
#if LIN
//#    include <GL/glew.h>

#elif __GNUC__
//#    include <GL/glew.h>

#else
//#    include <GL/glew.h>

#endif

#define FALSE 0
#define TRUE 1

/*

XPLM301—X-Plane 11.20 & newer (64-bit only)
XPLM300—X-Plane 11.10 & newer (64-bit only)
XPLM210—X-Plane 10.00 & newer (10.20 required for 64-bit plugins)
XPLM200—X-Plane 9.00 & newer
*/
#define XPLM200 1
//#define XPLM210 1
//#define XPLM300 1
//#define XPLM301 1

#include "config.h"
#include "datarefs.h"

#include "XPLMDisplay.h" // download xplane SDK and put in SDK folder https://developer.x-plane.com/sdk/plugin-sdk-downloads/
#include "XPLMGraphics.h"
#include "XPLMUtilities.h"
#include "XPLMDataAccess.h"
#include "XPLMProcessing.h"
#include "XPLMMenus.h"
#include "XPLMPlugin.h"
#include "XPLMPlanes.h"

void MyMenuHandlerCallback(void* inMenuRef, void* inItemRef);
