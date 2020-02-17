/*
   Goldelox_Serial_4DLib.cpp - Library for 4D Systems Serial Environment.
 */
#include "stm32f4xx_hal.h"
#include "Uoled.h"



extern UART_HandleTypeDef huart4;

//*********************************************************************************************//
//**********************************Intrinsic 4D Routines**************************************//
//*********************************************************************************************//

void WriteChars(char * charsout)
{
  unsigned char wk ;
  do
  {
    wk = *charsout++ ;
    HAL_UART_Transmit(&huart4, &wk, 1, 100);

  } while (wk) ;
}

void WriteBytes(char * Source, int Size)
{
 	unsigned char wk ;
	int i ;
	for (i = 0; i < Size; i++)
	{
		wk = *Source++ ;
    HAL_UART_Transmit(&huart4, &wk, 1, 100);
	}
}

void Writeuint16_ts(int * Source, int Size)
{
  unsigned char wk ;
  int i ;
  for (i = 0; i < Size; i++)
  {
    wk = *Source >> 8;
    HAL_UART_Transmit(&huart4, &wk, 1, 100);
    wk = (unsigned char) *Source;
    HAL_UART_Transmit(&huart4, &wk, 1, 100);  
    Source++;
  }
}
/*
void getbytes(char * data, int size)
{
  int read ;
  unsigned long sttime ;
  int readc ;
  readc  = 0 ;
  sttime = millis() ;
  while ((readc != size) && (millis() - sttime < TimeLimit4D))
  {
    if(_virtualPort->available()) 
    {
      data[readc++] = _virtualPort->read() ;
    }
  }
  if (readc != size)
  {
    Error4D = Err4D_Timeout ;
    if (Callback4D != NULL)
      Callback4D(Error4D, Error4D_Inv) ;
  }
}
*/

void GetAck(void)
{
  int read ;
  unsigned char readx ;
  read    = 0 ;
	
	
	while ((read != 1))
	{
			HAL_UART_Receive(&huart4, &readx, 1, 0xFFFF);
      read = 1 ;
  }
	
 if (readx != 6)
  {
    while(1);
  }
}
/*
uint16_t Getuint16_t(void)
{
  unsigned char readx[2] ;
  int readc ;
  unsigned long sttime ;
  
  if (Error4D != Err4D_OK)
    return 0 ;
  sttime   = millis();
  readc    = 0 ;
  while ((readc != 2) && (millis() - sttime < TimeLimit4D))
  {
    if(_virtualPort->available()) 
    {
      readx[readc++] = _virtualPort->read() ;
    }
  }
  
  if (readc != 2)
  {
    Error4D  = Err4D_Timeout ;
    if (Callback4D != NULL)
      Callback4D(Error4D, Error4D_Inv) ;
  return 0 ;
  }
  else
    return readx[0] << 8 | readx[1] ;
}

void getString(char * outStr, int strLen)
{
  unsigned char readx[2] ;
  int readc ;
  unsigned long sttime ;
  
  if (Error4D != Err4D_OK)
  {
    outStr[0] = 0 ;
    return ;
  }
  sttime   = millis();
  readc    = 0 ;
  while ((readc != strLen) && (millis() - sttime < TimeLimit4D))
  {
    if(_virtualPort->available()) 
    {
      outStr[readc++] = _virtualPort->read() ;
    }
  }
  
  if (readc != strLen)
  {
    Error4D  = Err4D_Timeout ;
    if (Callback4D != NULL)
      Callback4D(Error4D, Error4D_Inv) ;
  }
  outStr[readc] = 0 ;
}

uint16_t GetAckResp(void)
{
	GetAck() ;
	return Getuint16_t() ;
}

uint16_t GetAckRes2uint16_ts(uint16_t * uint16_t1, uint16_t * uint16_t2)
{
	int Result ;
	GetAck() ;
	Result = Getuint16_t() ;
	*uint16_t1 = Getuint16_t() ;
	*uint16_t2 = Getuint16_t() ;
	return Result ;
}

void GetAck2uint16_ts(uint16_t * uint16_t1, uint16_t * uint16_t2)
{
	GetAck() ;
	*uint16_t1 = Getuint16_t() ;
	*uint16_t2 = Getuint16_t() ;
}

uint16_t GetAckResStr(char * OutStr)
{
	int Result ;
	GetAck() ;
	Result = Getuint16_t() ;
	getString(OutStr, Result) ;
	return Result ;
}

*/


/*
uint16_t GetAckResData(t4DByteArray OutData, uint16_t size)
{
	int Result ;
	GetAck() ;
	Result = Getuint16_t() ;
	getbytes(OutData, size) ;
	return Result ;
}
*/


//void SetThisBaudrate(int Newrate)
//{
  //int br ;
  //_virtualPort->flush() ;

  //switch(Newrate)
  //{
 /*   case BAUD_110    : br = 110 ;
      break ;
    case BAUD_300    : br = 300 ;
      break ;
    case BAUD_600    : br = 600 ;
      break ;
    case BAUD_1200   : br = 1200 ;
      break ;
    case BAUD_2400   : br = 2400 ;
      break ;
    case BAUD_4800   : br = 4800 ;
      break ;*/
//    case BAUD_9600   : br = 9600 ;
//      break ;
//   case BAUD_14400  : br = 14400 ;
//      break ;
//    case BAUD_19200  : br = 19200 ;
//      break ;
 /*   case BAUD_31250  : br = 31250 ;
      break ;
    case BAUD_38400  : br = 38400 ;
      break ;
    case BAUD_56000  : br = 56000 ;
      break ;
    case BAUD_57600  : br = 57600 ;
      break ;
    case BAUD_115200 : br = 115200 ;
      break ;
    case BAUD_128000 : br = 133928 ; // actual rate is not 128000 ;
      break ;
    case BAUD_256000 : br = 281250 ; // actual rate is not  256000 ;
      break ;
    case BAUD_300000 : br = 312500 ; // actual rate is not  300000 ;
      break ;
    case BAUD_375000 : br = 401785 ; // actual rate is not  375000 ;
      break ;
    case BAUD_500000 : br = 562500 ; // actual rate is not  500000 ;
      break ;
    case BAUD_600000 : br = 703125 ; // actual rate is not  600000 ;
      break ;*/
 // }
//  _virtualPort->begin(br) ;
 // delay(50) ; // Display sleeps for 100
 // _virtualPort->flush() ;
//}

//*********************************************************************************************//
//**********************************Compound 4D Routines***************************************//
//*********************************************************************************************//

int charheight(uint8_t  TestChar)
{
  unsigned char wk;
 // _virtualPort->print((char)(F_charheight >> 8)) ;
  wk = F_charheight >> 8;
  HAL_UART_Transmit(&huart4, &wk, 1, 100);


  //_virtualPort->print((char)(F_charheight)) ;
  wk = F_charheight;
  HAL_UART_Transmit(&huart4, &wk, 1, 100);

  //_virtualPort->print((char)(TestChar)) ;
  HAL_UART_Transmit(&huart4, &TestChar, 1, 100);

  //return GetAckResp() ;
  return 0;
}

/*uint16_t charwidth(char  TestChar)
{
  _virtualPort->print((char)(F_charwidth >> 8)) ;
  _virtualPort->print((char)(F_charwidth)) ;
  _virtualPort->print((char)(TestChar)) ;
  return GetAckResp() ;
}

void gfx_BGcolour(uint16_t  Color)
{
  _virtualPort->print((char)(F_gfx_BGcolour >> 8)) ;
  _virtualPort->print((char)(F_gfx_BGcolour)) ;
  _virtualPort->print((char)(Color >> 8)) ;
  _virtualPort->print((char)(Color)) ;
  GetAck() ;
}

void gfx_ChangeColour(uint16_t  OldColor, uint16_t  NewColor)
{
  _virtualPort->print((char)(F_gfx_ChangeColour >> 8)) ;
  _virtualPort->print((char)(F_gfx_ChangeColour)) ;
  _virtualPort->print((char)(OldColor >> 8)) ;
  _virtualPort->print((char)(OldColor)) ;
  _virtualPort->print((char)(NewColor >> 8)) ;
  _virtualPort->print((char)(NewColor)) ;
  GetAck() ;
}

void gfx_Circle(uint16_t  X, uint16_t  Y, uint16_t  Radius, uint16_t  Color)
{
  _virtualPort->print((char)(F_gfx_Circle >> 8)) ;
  _virtualPort->print((char)(F_gfx_Circle)) ;
  _virtualPort->print((char)(X >> 8)) ;
  _virtualPort->print((char)(X)) ;
  _virtualPort->print((char)(Y >> 8)) ;
  _virtualPort->print((char)(Y)) ;
  _virtualPort->print((char)(Radius >> 8)) ;
  _virtualPort->print((char)(Radius)) ;
  _virtualPort->print((char)(Color >> 8)) ;
  _virtualPort->print((char)(Color)) ;
  GetAck() ;
}

void gfx_CircleFilled(uint16_t  X, uint16_t  Y, uint16_t  Radius, uint16_t  Color)
{
  _virtualPort->print((char)(F_gfx_CircleFilled >> 8)) ;
  _virtualPort->print((char)(F_gfx_CircleFilled)) ;
  _virtualPort->print((char)(X >> 8)) ;
  _virtualPort->print((char)(X)) ;
  _virtualPort->print((char)(Y >> 8)) ;
  _virtualPort->print((char)(Y)) ;
  _virtualPort->print((char)(Radius >> 8)) ;
  _virtualPort->print((char)(Radius)) ;
  _virtualPort->print((char)(Color >> 8)) ;
  _virtualPort->print((char)(Color)) ;
  GetAck() ;
}
*/
void gfx_Clipping(uint16_t  OnOff)
{
	uint8_t wk;

	wk = 0xFF;
	HAL_UART_Transmit(&huart4, &wk, 1, 100);
	wk = 0x6C;
	HAL_UART_Transmit(&huart4, &wk, 1, 100);
	
	wk= OnOff >> 8;
	HAL_UART_Transmit(&huart4, &wk, 1, 0xFFFF);
	wk= OnOff;
	HAL_UART_Transmit(&huart4, &wk, 1, 0xFFFF);
	
  GetAck() ;
}

/*
void gfx_ClipWindow(uint16_t  X1, uint16_t  Y1, uint16_t  X2, uint16_t  Y2)
{
  _virtualPort->print((char)(F_gfx_ClipWindow >> 8)) ;
  _virtualPort->print((char)(F_gfx_ClipWindow)) ;
  _virtualPort->print((char)(X1 >> 8)) ;
  _virtualPort->print((char)(X1)) ;
  _virtualPort->print((char)(Y1 >> 8)) ;
  _virtualPort->print((char)(Y1)) ;
  _virtualPort->print((char)(X2 >> 8)) ;
  _virtualPort->print((char)(X2)) ;
  _virtualPort->print((char)(Y2 >> 8)) ;
  _virtualPort->print((char)(Y2)) ;
  GetAck() ;
}

*/
void gfx_Cls()
{
	uint8_t wk;
	int read ;
  unsigned char readx ;
  
	read = 0 ;
	readx = 0;
	
	while (readx != 6)
	{
		wk = 0xFF;
		HAL_UART_Transmit(&huart4, &wk, 1, 100);
		wk = 0xD7;
		HAL_UART_Transmit(&huart4, &wk, 1, 100);
			
		while (read != 1)
		{
			HAL_UART_Receive(&huart4, &readx, 1, 0xFFF);
			read = 1 ;
		}
			
		if (readx != 6)
		{
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_RESET); //Toggle RESET
			HAL_GPIO_WritePin(GPIOA,GPIO_PIN_5,GPIO_PIN_SET); //Toggle SET
			HAL_Delay(8000);

			wk = 0xFF;
			HAL_UART_Transmit(&huart4, &wk, 1, 100);
			wk = 0xD7;
			HAL_UART_Transmit(&huart4, &wk, 1, 100);
				
			read=0;
			while (read != 1)
			{
				HAL_UART_Receive(&huart4, &readx, 1, 0xFFF);
				read = 1 ;
			}				
		}
	}
	gfx_Rectangle(0,0,127,127,YELLOW);
}

/*void gfx_Contrast(uint16_t  Contrast)
{
  _virtualPort->print((char)(F_gfx_Contrast >> 8)) ;
  _virtualPort->print((char)(F_gfx_Contrast)) ;
  _virtualPort->print((char)(Contrast >> 8)) ;
  _virtualPort->print((char)(Contrast)) ;
  GetAck() ;
}

void gfx_FrameDelay(uint16_t  Msec)
{
  _virtualPort->print((char)(F_gfx_FrameDelay >> 8)) ;
  _virtualPort->print((char)(F_gfx_FrameDelay)) ;
  _virtualPort->print((char)(Msec >> 8)) ;
  _virtualPort->print((char)(Msec)) ;
  GetAck() ;
}

uint16_t gfx_GetPixel(uint16_t  X, uint16_t  Y)
{
  _virtualPort->print((char)(F_gfx_GetPixel >> 8 )) ;
  _virtualPort->print((char)(F_gfx_GetPixel )) ;
  _virtualPort->print((char)(X >> 8 )) ;
  _virtualPort->print((char)(X )) ;
  _virtualPort->print((char)(Y >> 8 )) ;
  _virtualPort->print((char)(Y )) ;
  return GetAckResp() ;
}

void gfx_Line(uint16_t  X1, uint16_t  Y1, uint16_t  X2, uint16_t  Y2, uint16_t  Color)
{
  _virtualPort->print((char)(F_gfx_Line >> 8 )) ;
  _virtualPort->print((char)(F_gfx_Line )) ;
  _virtualPort->print((char)(X1 >> 8 )) ;
  _virtualPort->print((char)(X1 )) ;
  _virtualPort->print((char)(Y1 >> 8 )) ;
  _virtualPort->print((char)(Y1 )) ;
  _virtualPort->print((char)(X2 >> 8 )) ;
  _virtualPort->print((char)(X2 )) ;
  _virtualPort->print((char)(Y2 >> 8 )) ;
  _virtualPort->print((char)(Y2 )) ;
  _virtualPort->print((char)(Color >> 8 )) ;
  _virtualPort->print((char)(Color )) ;
  GetAck() ;
}

void gfx_LinePattern(uint16_t  Pattern)
{
  _virtualPort->print((char)(F_gfx_LinePattern >> 8 )) ;
  _virtualPort->print((char)(F_gfx_LinePattern )) ;
  _virtualPort->print((char)(Pattern >> 8 )) ;
  _virtualPort->print((char)(Pattern )) ;
  GetAck() ;
}

void gfx_LineTo(uint16_t  X, uint16_t  Y)
{
  _virtualPort->print((char)(F_gfx_LineTo >> 8 )) ;
  _virtualPort->print((char)(F_gfx_LineTo )) ;
  _virtualPort->print((char)(X >> 8 )) ;
  _virtualPort->print((char)(X )) ;
  _virtualPort->print((char)(Y >> 8 )) ;
  _virtualPort->print((char)(Y )) ;
  GetAck() ;
}

void gfx_MoveTo(uint16_t  X, uint16_t  Y)
{
  _virtualPort->print((char)(F_gfx_MoveTo >> 8 )) ;
  _virtualPort->print((char)(F_gfx_MoveTo )) ;
  _virtualPort->print((char)(X >> 8 )) ;
  _virtualPort->print((char)(X )) ;
  _virtualPort->print((char)(Y >> 8 )) ;
  _virtualPort->print((char)(Y )) ;
  GetAck() ;
}

uint16_t gfx_Orbit(uint16_t  Angle, uint16_t  Distance, uint16_t *  Xdest, uint16_t *  Ydest)
{
  _virtualPort->print((char)(F_gfx_Orbit >> 8 )) ;
  _virtualPort->print((char)(F_gfx_Orbit )) ;
  _virtualPort->print((char)(Angle >> 8 )) ;
  _virtualPort->print((char)(Angle )) ;
  _virtualPort->print((char)(Distance >> 8 )) ;
  _virtualPort->print((char)(Distance )) ;
  GetAck2uint16_ts(Xdest,Ydest) ;
  return 0 ;
}

void gfx_OutlineColour(uint16_t  Color)
{
  _virtualPort->print((char)(F_gfx_OutlineColour >> 8 )) ;
  _virtualPort->print((char)(F_gfx_OutlineColour )) ;
  _virtualPort->print((char)(Color >> 8 )) ;
  _virtualPort->print((char)(Color )) ;
  GetAck() ;
}

void gfx_Polygon(uint16_t  n, t4Duint16_tArray  Xvalues, t4Duint16_tArray  Yvalues, uint16_t  Color)
{
  _virtualPort->print((char)(F_gfx_Polygon >> 8 )) ;
  _virtualPort->print((char)(F_gfx_Polygon )) ;
  _virtualPort->print((char)(n >> 8 )) ;
  _virtualPort->print((char)(n )) ;
  Writeuint16_ts(Xvalues, n) ;
  Writeuint16_ts(Yvalues, n) ;
  _virtualPort->print((char)(Color >> 8 )) ;
  _virtualPort->print((char)(Color )) ;
  GetAck() ;
}

void gfx_Polyline(uint16_t  n, t4Duint16_tArray  Xvalues, t4Duint16_tArray  Yvalues, uint16_t  Color)
{
  _virtualPort->print((char)(F_gfx_Polyline >> 8 )) ;
  _virtualPort->print((char)(F_gfx_Polyline )) ;
  _virtualPort->print((char)(n >> 8 )) ;
  _virtualPort->print((char)(n )) ;
  Writeuint16_ts(Xvalues, n) ;
  Writeuint16_ts(Yvalues, n) ;
  _virtualPort->print((char)(Color >> 8 )) ;
  _virtualPort->print((char)(Color )) ;
  GetAck() ;
}

void gfx_PutPixel(uint16_t  X, uint16_t  Y, uint16_t  Color)
{
  _virtualPort->print((char)(F_gfx_PutPixel >> 8 )) ;
  _virtualPort->print((char)(F_gfx_PutPixel )) ;
  _virtualPort->print((char)(X >> 8 )) ;
  _virtualPort->print((char)(X )) ;
  _virtualPort->print((char)(Y >> 8 )) ;
  _virtualPort->print((char)(Y )) ;
  _virtualPort->print((char)(Color >> 8 )) ;
  _virtualPort->print((char)(Color )) ;
  GetAck() ;
}
*/
void gfx_Rectangle(uint16_t  X1, uint16_t  Y1, uint16_t  X2, uint16_t  Y2, uint16_t Color)
{
	uint8_t commandes[2] ={0xFF, 0xCF};	
	uint8_t wk;

	HAL_UART_Transmit(&huart4, commandes, 1, 0xFFFF);
	HAL_UART_Transmit(&huart4, commandes+1, 1, 0xFFFF);
	wk= X1 >> 8;
	HAL_UART_Transmit(&huart4, &wk, 1, 0xFFFF);
	wk= X1;
	HAL_UART_Transmit(&huart4, &wk, 1, 0xFFFF);
	wk= Y1 >> 8;
	HAL_UART_Transmit(&huart4, &wk, 1, 0xFFFF);
	wk= Y1;
	HAL_UART_Transmit(&huart4, &wk, 1, 0xFFFF);
	wk= X2 >> 8;
	HAL_UART_Transmit(&huart4, &wk, 1, 0xFFFF);
	wk= X2;
	HAL_UART_Transmit(&huart4, &wk, 1, 0xFFFF);
	wk= Y2 >> 8;
	HAL_UART_Transmit(&huart4, &wk, 1, 0xFFFF);
	wk= Y2;
	HAL_UART_Transmit(&huart4, &wk, 1, 0xFFFF);
	wk= Color >> 8;
	HAL_UART_Transmit(&huart4, &wk, 1, 0xFFFF);
	wk= Color;
	HAL_UART_Transmit(&huart4, &wk, 1, 0xFFFF);

  GetAck() ;
}

void gfx_RectangleFilled(uint16_t  X1, uint16_t  Y1, uint16_t  X2, uint16_t  Y2, uint16_t  Color)
{
 
	uint8_t commandes[2] ={0xFF, 0xCE};	
	uint8_t wk;
	uint16_t wk_temp;


	HAL_UART_Transmit(&huart4, commandes, 1, 0xFFFF);
	HAL_UART_Transmit(&huart4, commandes+1, 1, 0xFFFF);
	
	wk_temp=X1*7;
	wk= wk_temp >> 8;
	HAL_UART_Transmit(&huart4, &wk, 1, 0xFFFF);
	wk= wk_temp;
	HAL_UART_Transmit(&huart4, &wk, 1, 0xFFFF);
	
	wk_temp = Y1*8;
	wk= wk_temp >> 8;
	HAL_UART_Transmit(&huart4, &wk, 1, 0xFFFF);
	wk= wk_temp;
	HAL_UART_Transmit(&huart4, &wk, 1, 0xFFFF);
	
	wk_temp = X2*7;
	wk= wk_temp >> 8;
	HAL_UART_Transmit(&huart4, &wk, 1, 0xFFFF);
	wk= wk_temp;
	HAL_UART_Transmit(&huart4, &wk, 1, 0xFFFF);
	
	wk_temp = Y2*8;
	wk= wk_temp >> 8;
	HAL_UART_Transmit(&huart4, &wk, 1, 0xFFFF);
	wk= wk_temp;
	HAL_UART_Transmit(&huart4, &wk, 1, 0xFFFF);
	
	wk= Color >> 8;
	HAL_UART_Transmit(&huart4, &wk, 1, 0xFFFF);
	wk= Color;
	HAL_UART_Transmit(&huart4, &wk, 1, 0xFFFF);
	
	
  GetAck() ;
}

/*
void gfx_ScreenMode(uint16_t  ScreenMode)
{
  _virtualPort->print((char)(F_gfx_ScreenMode >> 8 )) ;
  _virtualPort->print((char)(F_gfx_ScreenMode )) ;
  _virtualPort->print((char)(ScreenMode >> 8 )) ;
  _virtualPort->print((char)(ScreenMode )) ;
  GetAck() ;
}

void gfx_Set(uint16_t  Func, uint16_t  Value)
{
  _virtualPort->print((char)(F_gfx_Set >> 8 )) ;
  _virtualPort->print((char)(F_gfx_Set )) ;
  _virtualPort->print((char)(Func >> 8 )) ;
  _virtualPort->print((char)(Func )) ;
  _virtualPort->print((char)(Value >> 8 )) ;
  _virtualPort->print((char)(Value )) ;
  GetAck() ;
}

void gfx_SetClipRegion()
{
  _virtualPort->print((char)(F_gfx_SetClipRegion >> 8)) ;
  _virtualPort->print((char)(F_gfx_SetClipRegion)) ;
  GetAck() ;
}

void gfx_Transparency(uint16_t  OnOff)
{
  _virtualPort->print((char)(F_gfx_Transparency >> 8)) ;
  _virtualPort->print((char)(F_gfx_Transparency)) ;
  _virtualPort->print((char)(OnOff >> 8)) ;
  _virtualPort->print((char)(OnOff)) ;
  GetAck() ;
}

void gfx_TransparentColour(uint16_t  Color)
{
  _virtualPort->print((char)(F_gfx_TransparentColour >> 8)) ;
  _virtualPort->print((char)(F_gfx_TransparentColour)) ;
  _virtualPort->print((char)(Color >> 8)) ;
  _virtualPort->print((char)(Color)) ;
  GetAck() ;
}

void gfx_Triangle(uint16_t  X1, uint16_t  Y1, uint16_t  X2, uint16_t  Y2, uint16_t  X3, uint16_t  Y3, uint16_t  Color)
{
  _virtualPort->print((char)(F_gfx_Triangle >> 8)) ;
  _virtualPort->print((char)(F_gfx_Triangle)) ;
  _virtualPort->print((char)(X1 >> 8)) ;
  _virtualPort->print((char)(X1)) ;
  _virtualPort->print((char)(Y1 >> 8)) ;
  _virtualPort->print((char)(Y1)) ;
  _virtualPort->print((char)(X2 >> 8)) ;
  _virtualPort->print((char)(X2)) ;
  _virtualPort->print((char)(Y2 >> 8)) ;
  _virtualPort->print((char)(Y2)) ;
  _virtualPort->print((char)(X3 >> 8)) ;
  _virtualPort->print((char)(X3)) ;
  _virtualPort->print((char)(Y3 >> 8)) ;
  _virtualPort->print((char)(Y3)) ;
  _virtualPort->print((char)(Color >> 8)) ;
  _virtualPort->print((char)(Color)) ;
  GetAck() ;
}

uint16_t media_Flush()
{
  _virtualPort->print((char)(F_media_Flush >> 8)) ;
  _virtualPort->print((char)(F_media_Flush)) ;
  return GetAckResp() ;
}

void media_Image(uint16_t  X, uint16_t  Y)
{
  _virtualPort->print((char)(F_media_Image >> 8)) ;
  _virtualPort->print((char)(F_media_Image)) ;
  _virtualPort->print((char)(X >> 8)) ;
  _virtualPort->print((char)(X)) ;
  _virtualPort->print((char)(Y >> 8)) ;
  _virtualPort->print((char)(Y)) ;
  GetAck() ;
}

uint16_t media_Init()
{
  _virtualPort->print((char)(F_media_Init >> 8)) ;
  _virtualPort->print((char)(F_media_Init)) ;
  return GetAckResp() ;
}

uint16_t media_ReadByte()
{
  _virtualPort->print((char)(F_media_ReadByte >> 8)) ;
  _virtualPort->print((char)(F_media_ReadByte)) ;
  return GetAckResp() ;
}

uint16_t media_Readuint16_t()
{
  _virtualPort->print((char)(F_media_Readuint16_t >> 8)) ;
  _virtualPort->print((char)(F_media_Readuint16_t)) ;
  return GetAckResp() ;
}

void media_SetAdd(uint16_t  Hiuint16_t, uint16_t  Louint16_t)
{
  _virtualPort->print((char)(F_media_SetAdd >> 8)) ;
  _virtualPort->print((char)(F_media_SetAdd)) ;
  _virtualPort->print((char)(Hiuint16_t >> 8)) ;
  _virtualPort->print((char)(Hiuint16_t)) ;
  _virtualPort->print((char)(Louint16_t >> 8)) ;
  _virtualPort->print((char)(Louint16_t)) ;
  GetAck() ;
}

void media_SetSector(uint16_t  Hiuint16_t, uint16_t  Louint16_t)
{
  _virtualPort->print((char)(F_media_SetSector >> 8)) ;
  _virtualPort->print((char)(F_media_SetSector)) ;
  _virtualPort->print((char)(Hiuint16_t >> 8)) ;
  _virtualPort->print((char)(Hiuint16_t)) ;
  _virtualPort->print((char)(Louint16_t >> 8)) ;
  _virtualPort->print((char)(Louint16_t)) ;
  GetAck() ;
}

void media_Video(uint16_t  X, uint16_t  Y)
{
  _virtualPort->print((char)(F_media_Video >> 8)) ;
  _virtualPort->print((char)(F_media_Video)) ;
  _virtualPort->print((char)(X >> 8)) ;
  _virtualPort->print((char)(X)) ;
  _virtualPort->print((char)(Y >> 8)) ;
  _virtualPort->print((char)(Y)) ;
  GetAck() ;
}

void media_VideoFrame(uint16_t  X, uint16_t  Y, uint16_t  Framenumber)
{
  _virtualPort->print((char)(F_media_VideoFrame >> 8)) ;
  _virtualPort->print((char)(F_media_VideoFrame)) ;
  _virtualPort->print((char)(X >> 8)) ;
  _virtualPort->print((char)(X)) ;
  _virtualPort->print((char)(Y >> 8)) ;
  _virtualPort->print((char)(Y)) ;
  _virtualPort->print((char)(Framenumber >> 8)) ;
  _virtualPort->print((char)(Framenumber)) ;
  GetAck() ;
}

uint16_t media_WriteByte(uint16_t  Byte)
{
  _virtualPort->print((char)(F_media_WriteByte >> 8)) ;
  _virtualPort->print((char)(F_media_WriteByte)) ;
  _virtualPort->print((char)(Byte >> 8)) ;
  _virtualPort->print((char)(Byte)) ;
  return GetAckResp() ;
}

uint16_t media_Writeuint16_t(uint16_t  uint16_t)
{
  _virtualPort->print((char)(F_media_Writeuint16_t >> 8)) ;
  _virtualPort->print((char)(F_media_Writeuint16_t)) ;
  _virtualPort->print((char)(uint16_t >> 8)) ;
  _virtualPort->print((char)(uint16_t)) ;
  return GetAckResp() ;
}

*/
void putCH(uint16_t  uint16_tChar)
{
	
	uint8_t commandes[2] ={0xFF, 0xFE};	
	uint8_t wk;

	HAL_UART_Transmit(&huart4, commandes, 1, 0xFFFF);
	HAL_UART_Transmit(&huart4, commandes+1, 1, 0xFFFF);
	wk= uint16_tChar >> 8;
	HAL_UART_Transmit(&huart4, &wk, 1, 0xFFFF);
	wk= uint16_tChar;
	HAL_UART_Transmit(&huart4, &wk, 1, 0xFFFF);
	
  GetAck() ;
}

/*
void putstr(char *  InString)
{
  _virtualPort->print((char)(F_putstr >> 8)) ;
  _virtualPort->print((char)(F_putstr)) ;
  WriteChars(InString) ;
  GetAck() ;
}

*/
//////////////////////////////////////////////////////
//-----------------print----------------------------------

/*#ifdef AVR
void print(const __FlashStringHelper *ifsh)
{
  PGM_P p = reinterpret_cast<PGM_P>(ifsh);
  size_t n = 0;
  while (1) {
    unsigned char c = pgm_read_byte(p++);
    if (c == 0) break;
    putCH(c);
  }
}
#endif

void print(const String &s)
{
	int len = s.length();
	char arr[len + 1];
	s.toCharArray(arr,len + 1);
	//putstr(arr);
	for(int x=0; x<len; x++)
	{
		putCH(arr[x]);
	}
}

void print(const char str[])
{
  int len = strlen(str);
  for(int x = 0; x<len; x++)
  {
	putCH(str[x]);
  }
}

void print(char c)
{
  putCH(c);
}

void print(unsigned char b, int base)
{
  print((unsigned long) b, base);
}

void print(int n, int base)
{
  print((long) n, base);
}

void print(unsigned int n, int base)
{
  print((unsigned long) n, base);
}
*/
void putINT(uint16_t n)
{ 
	
  if (n < 10) 
	{
			//putCH('A');
			putCH(n+'0');
   }
	else if (n < 100)
	{
		putCH(n/10+'0');
		putCH(n%10+'0');
	}
	else
		putCH('A');

}
/*
void print(unsigned long n, int base)
{
  printNumber(n, base);
}

void print(double n, int digits)
{
  printFloat(n, digits);
}


//println

void println(const __FlashStringHelper *ifsh)
{
  print(ifsh);
  putCH('\n');
  putCH('\r');
}

void println(const String &s)
{
  print(s);
  putCH('\n');
  putCH('\r');
}

void println(const char c[])
{
  print(c);
  putCH('\n');
  putCH('\r');
}

void println(char c)
{
  print((char)c);
  putCH('\n');
  putCH('\r');
}

void println(unsigned char b, int base)
{
  print((unsigned char)b, base);
  putCH('\n');
  putCH('\r');
}

void println(int num, int base)
{
  print((int)num, base);
  putCH('\n');
  putCH('\r');
}

void println(unsigned int num, int base)
{
  print((unsigned int)num, base);
  putCH('\n');
  putCH('\r');
}

void println(long num, int base)
{
  print((long)num, base);
  putCH('\n');
  putCH('\r');
}

void println(unsigned long num, int base)
{
  print((unsigned long)num, base);
  putCH('\n');
  putCH('\r');
}

void println(double num, int digits)
{
  print((double)num, digits);
  putCH('\n');
  putCH('\r');
}
*/

//-Private:

/*void printNumber(unsigned long n, uint8_t base) {
  char buf[8 * sizeof(long) + 1]; // Assumes 8-bit chars plus zero byte.
  int count = 0;
  do {
    unsigned long m = n;
    n /= base;
    char c = m - base * n;
    buf[count] = c < 10 ? c + '0' : c + 'A' - 10;
    count++;
  } while(n);
  
  for(int x = count - 1; x>=0; x--)
  {
	putCH(buf[x]);
  }
}

void printFloat(double number, uint8_t digits) 
{ 
  size_t n = 0;
  if (isnan(number)) print("nan"); 
  else if (isinf(number)) print("inf"); 
  else if (number > 4294967040.0) print ("ovf");  // constant determined empirically
  else if (number <-4294967040.0) print ("ovf");  // constant determined empirically
  else{
  // Handle negative numbers
  if (number < 0.0)
  {
     putCH('-');
     number = -number;
  }

  // Round correctly so that print(1.999, 2) prints as "2.00"
  double rounding = 0.5;
  for (uint8_t i=0; i<digits; ++i)
    rounding /= 10.0;
  
  number += rounding;

  // Extract the integer part of the number and print it
  unsigned long int_part = (unsigned long)number;
  double remainder = number - (double)int_part;
  //print((unsigned long)int_part);
  printNumber(int_part, 10);

  // Print the decimal point, but only if there are digits beyond
  if (digits > 0) {
    putCH('.'); 
  }

  // Extract digits from the remainder one at a time
  while (digits-- > 0)
  {
    remainder *= 10.0;
    int toPrint = int(remainder);
    printNumber((unsigned long)toPrint, 10);
    remainder -= toPrint; 
  } 
  }
}

*/
//--------------------------------------------------------




//////////////////////////////////////////////////////
/*
void txt_Attributes(uint16_t  Attribs)
{
  _virtualPort->print((char)(F_txt_Attributes >> 8)) ;
  _virtualPort->print((char)(F_txt_Attributes)) ;
  _virtualPort->print((char)(Attribs >> 8)) ;
  _virtualPort->print((char)(Attribs)) ;
  GetAck() ;
}
*/
void txt_BGcolour(uint16_t  Color)
{
  uint8_t commandes[2] ={0xFF, 0x7E};	
	uint8_t wk;

	HAL_UART_Transmit(&huart4, commandes, 1, 0xFFFF);
	HAL_UART_Transmit(&huart4, commandes+1, 1, 0xFFFF);
	wk= Color >> 8;
	HAL_UART_Transmit(&huart4, &wk, 1, 0xFFFF);
	wk= Color;
	HAL_UART_Transmit(&huart4, &wk, 1, 0xFFFF);
	
  GetAck() ;
}
/*
void txt_Bold(uint16_t  Bold)
{
  _virtualPort->print((char)(F_txt_Bold >> 8)) ;
  _virtualPort->print((char)(F_txt_Bold)) ;
  _virtualPort->print((char)(Bold >> 8)) ;
  _virtualPort->print((char)(Bold)) ;
  GetAck() ;
}
*/
void txt_FGcolour(uint16_t  Color)
{
  uint8_t commandes[2] ={0xFF, 0x7F};	
	uint8_t wk;

	HAL_UART_Transmit(&huart4, commandes, 1, 0xFFFF);
	HAL_UART_Transmit(&huart4, commandes+1, 1, 0xFFFF);
	wk= Color >> 8;
	HAL_UART_Transmit(&huart4, &wk, 1, 0xFFFF);
	wk= Color;
	HAL_UART_Transmit(&huart4, &wk, 1, 0xFFFF);
	
  GetAck() ;
}
/*
void txt_FontID(uint16_t  FontNumber)
{
  _virtualPort->print((char)(F_txt_FontID >> 8)) ;
  _virtualPort->print((char)(F_txt_FontID)) ;
  _virtualPort->print((char)(FontNumber >> 8)) ;
  _virtualPort->print((char)(FontNumber)) ;
  GetAck() ;
}

void txt_Height(uint16_t  Multiplier)
{
  _virtualPort->print((char)(F_txt_Height >> 8)) ;
  _virtualPort->print((char)(F_txt_Height)) ;
  _virtualPort->print((char)(Multiplier >> 8)) ;
  _virtualPort->print((char)(Multiplier)) ;
  GetAck() ;
}

void txt_Inverse(uint16_t  Inverse)
{
  _virtualPort->print((char)(F_txt_Inverse >> 8)) ;
  _virtualPort->print((char)(F_txt_Inverse)) ;
  _virtualPort->print((char)(Inverse >> 8)) ;
  _virtualPort->print((char)(Inverse)) ;
  GetAck() ;
}

void txt_Italic(uint16_t  Italic)
{
  _virtualPort->print((char)(F_txt_Italic >> 8)) ;
  _virtualPort->print((char)(F_txt_Italic)) ;
  _virtualPort->print((char)(Italic >> 8)) ;
  _virtualPort->print((char)(Italic)) ;
  GetAck() ;
}
*/
void txt_MoveCursor(uint16_t  Line, uint16_t  Column)
{
	uint8_t commandes[2] ={0xFF, 0xE4};	
	uint8_t wk;

	HAL_UART_Transmit(&huart4, commandes, 1, 0xFFFF);
	HAL_UART_Transmit(&huart4, commandes+1, 1, 0xFFFF);
	
	wk= Column >> 8;
	HAL_UART_Transmit(&huart4, &wk, 1, 0xFFFF);
	wk= Column;
	HAL_UART_Transmit(&huart4, &wk, 1, 0xFFFF);
	wk= Line >> 8;
	HAL_UART_Transmit(&huart4, &wk, 1, 0xFFFF);
	wk= Line;
	HAL_UART_Transmit(&huart4, &wk, 1, 0xFFFF);
	
  GetAck() ;
}
/*
void txt_Opacity(uint16_t  TransparentOpaque)
{
  _virtualPort->print((char)(F_txt_Opacity >> 8)) ;
  _virtualPort->print((char)(F_txt_Opacity)) ;
  _virtualPort->print((char)(TransparentOpaque >> 8)) ;
  _virtualPort->print((char)(TransparentOpaque)) ;
  GetAck() ;
}

void txt_Set(uint16_t  Func, uint16_t  Value)
{
  _virtualPort->print((char)(F_txt_Set >> 8)) ;
  _virtualPort->print((char)(F_txt_Set)) ;
  _virtualPort->print((char)(Func >> 8)) ;
  _virtualPort->print((char)(Func)) ;
  _virtualPort->print((char)(Value >> 8)) ;
  _virtualPort->print((char)(Value)) ;
  GetAck() ;
}

void txt_Underline(uint16_t  Underline)
{
  _virtualPort->print((char)(F_txt_Underline >> 8)) ;
  _virtualPort->print((char)(F_txt_Underline)) ;
  _virtualPort->print((char)(Underline >> 8)) ;
  _virtualPort->print((char)(Underline)) ;
  GetAck() ;
}

void txt_Width(uint16_t  Multiplier)
{
  _virtualPort->print((char)(F_txt_Width >> 8)) ;
  _virtualPort->print((char)(F_txt_Width)) ;
  _virtualPort->print((char)(Multiplier >> 8)) ;
  _virtualPort->print((char)(Multiplier)) ;
  GetAck() ;
}

void txt_Xgap(uint16_t  Pixels)
{
  _virtualPort->print((char)(F_txt_Xgap >> 8)) ;
  _virtualPort->print((char)(F_txt_Xgap)) ;
  _virtualPort->print((char)(Pixels >> 8)) ;
  _virtualPort->print((char)(Pixels)) ;
  GetAck() ;
}

void txt_Ygap(uint16_t  Pixels)
{
  _virtualPort->print((char)(F_txt_Ygap >> 8)) ;
  _virtualPort->print((char)(F_txt_Ygap)) ;
  _virtualPort->print((char)(Pixels >> 8)) ;
  _virtualPort->print((char)(Pixels)) ;
  GetAck() ;
}
*/
void BeeP(uint16_t  Note, uint16_t  Duration)
{
	uint8_t commandes[2] ={0xFF, 0xDA};	
	uint8_t wk;

	HAL_UART_Transmit(&huart4, commandes, 1, 0xFFFF);
	HAL_UART_Transmit(&huart4, commandes+1, 1, 0xFFFF);
	wk= Note >> 8;
	HAL_UART_Transmit(&huart4, &wk, 1, 0xFFFF);
	wk= Note;
	HAL_UART_Transmit(&huart4, &wk, 1, 0xFFFF);
	wk= Duration >> 8;
	HAL_UART_Transmit(&huart4, &wk, 1, 0xFFFF);
	wk= Duration;
	HAL_UART_Transmit(&huart4, &wk, 1, 0xFFFF);
	
  GetAck() ;
}
/*
uint16_t sys_GetModel(char *  ModelStr)
{
  _virtualPort->print((char)(F_sys_GetModel >> 8)) ;
  _virtualPort->print((char)(F_sys_GetModel)) ;
  return GetAckResStr(ModelStr) ;
}

uint16_t sys_GetVersion()
{
  _virtualPort->print((char)(F_sys_GetVersion >> 8)) ;
  _virtualPort->print((char)(F_sys_GetVersion)) ;
  return GetAckResp() ;
}

uint16_t sys_GetPmmC()
{
  _virtualPort->print((char)(F_sys_GetPmmC >> 8)) ;
  _virtualPort->print((char)(F_sys_GetPmmC)) ;
  return GetAckResp() ;
}

void blitComtoDisplay(uint16_t  X, uint16_t  Y, uint16_t  Width, uint16_t  Height, t4DByteArray  Pixels)
{
  _virtualPort->print((char)(F_blitComtoDisplay >> 8)) ;
  _virtualPort->print((char)(F_blitComtoDisplay)) ;
  _virtualPort->print((char)(X >> 8)) ;
  _virtualPort->print((char)(X)) ;
  _virtualPort->print((char)(Y >> 8)) ;
  _virtualPort->print((char)(Y)) ;
  _virtualPort->print((char)(Width >> 8)) ;
  _virtualPort->print((char)(Width)) ;
  _virtualPort->print((char)(Height >> 8)) ;
  _virtualPort->print((char)(Height)) ;
  WriteBytes(Pixels, Width*Height*2) ;
  GetAck() ;
}
*/
void setbaudWait(uint32_t  Newrate, uint16_t  BaudrateDivisor)
{
  //_virtualPort->print((char)(F_setbaudWait >> 8)) ;
  //_virtualPort->print((char)(F_setbaudWait)) ;
  //_virtualPort->print((char)(Newrate >> 8)) ;
  //_virtualPort->print((char)(Newrate)) ;
	uint8_t commandes[2] ={0x00, 0x0B};	
	uint8_t wk;

	HAL_UART_Transmit(&huart4, commandes, 1, 0xFFFF);
	HAL_UART_Transmit(&huart4, commandes+1, 1, 0xFFFF);

	wk= BaudrateDivisor >> 8;
	HAL_UART_Transmit(&huart4, &wk, 1, 0xFFFF);
	wk= BaudrateDivisor;
	HAL_UART_Transmit(&huart4, &wk, 1, 0xFFFF);
	
  //SetThisBaudrate(Newrate) ; // change this systems baud rate to match new display rate, ACK is 100ms away
	
	huart4.Init.BaudRate = Newrate;
	HAL_UART_Init(&huart4);
	HAL_Delay(100);	// Display sleeps for 100

  GetAck() ;
}
/*
uint16_t peekW(uint16_t  Address)
{
  _virtualPort->print((char)(F_peekW >> 8)) ;
  _virtualPort->print((char)(F_peekW)) ;
  _virtualPort->print((char)(Address >> 8)) ;
  _virtualPort->print((char)(Address)) ;
  return GetAckResp() ;
}

void pokeW(uint16_t  Address, uint16_t  uint16_tValue)
{
  _virtualPort->print((char)(F_pokeW >> 8)) ;
  _virtualPort->print((char)(F_pokeW)) ;
  _virtualPort->print((char)(Address >> 8)) ;
  _virtualPort->print((char)(Address)) ;
  _virtualPort->print((char)(uint16_tValue >> 8)) ;
  _virtualPort->print((char)(uint16_tValue)) ;
  GetAck() ;
}

uint16_t peekB(uint16_t  Address)
{
  _virtualPort->print((char)(F_peekB >> 8)) ;
  _virtualPort->print((char)(F_peekB)) ;
  _virtualPort->print((char)(Address >> 8)) ;
  _virtualPort->print((char)(Address)) ;
  return GetAckResp() ;
}

void pokeB(uint16_t  Address, uint16_t  ByteValue)
{
  _virtualPort->print((char)(F_pokeB >> 8)) ;
  _virtualPort->print((char)(F_pokeB)) ;
  _virtualPort->print((char)(Address >> 8)) ;
  _virtualPort->print((char)(Address)) ;
  _virtualPort->print((char)(ByteValue >> 8)) ;
  _virtualPort->print((char)(ByteValue)) ;
  GetAck() ;
}

uint16_t joystick()
{
  _virtualPort->print((char)(F_joystick >> 8)) ;
  _virtualPort->print((char)(F_joystick)) ;
  return GetAckResp() ;
}

void SSTimeout(uint16_t  Seconds)
{
  _virtualPort->print((char)(F_SSTimeout >> 8)) ;
  _virtualPort->print((char)(F_SSTimeout)) ;
  _virtualPort->print((char)(Seconds >> 8)) ;
  _virtualPort->print((char)(Seconds)) ;
  GetAck() ;
}

void SSSpeed(uint16_t  Speed)
{
  _virtualPort->print((char)(F_SSSpeed >> 8)) ;
  _virtualPort->print((char)(F_SSSpeed)) ;
  _virtualPort->print((char)(Speed >> 8)) ;
  _virtualPort->print((char)(Speed)) ;
  GetAck() ;
}

void SSMode(uint16_t  Parm)
{
  _virtualPort->print((char)(F_SSMode >> 8)) ;
  _virtualPort->print((char)(F_SSMode)) ;
  _virtualPort->print((char)(Parm >> 8)) ;
  _virtualPort->print((char)(Parm)) ;
  GetAck() ;
}
*/
