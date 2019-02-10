//Original Code http://playground.arduino.cc/Main/DS1302

#define DS1302_SCLK_PIN   6    // Arduino pin for the Serial Clock
#define DS1302_IO_PIN     7    // Arduino pin for the Data I/O
#define DS1302_CE_PIN     8    // Arduino pin for the Chip Enable

#define bcd2bin(h,l)    (((h)*10) + (l))
#define bin2bcd_h(x)   ((x)/10)
#define bin2bcd_l(x)    ((x)%10)

#define DS1302_SECONDS           0x80
#define DS1302_MINUTES           0x82
#define DS1302_HOURS             0x84
#define DS1302_DATE              0x86
#define DS1302_MONTH             0x88
#define DS1302_DAY               0x8A
#define DS1302_YEAR              0x8C
#define DS1302_ENABLE            0x8E
#define DS1302_TRICKLE           0x90
#define DS1302_CLOCK_BURST       0xBE
#define DS1302_CLOCK_BURST_WRITE 0xBE
#define DS1302_CLOCK_BURST_READ  0xBF
#define DS1302_RAMSTART          0xC0
#define DS1302_RAMEND            0xFC
#define DS1302_RAM_BURST         0xFE
#define DS1302_RAM_BURST_WRITE   0xFE
#define DS1302_RAM_BURST_READ    0xFF


#define DS1302_D0 0
#define DS1302_D1 1
#define DS1302_D2 2
#define DS1302_D3 3
#define DS1302_D4 4
#define DS1302_D5 5
#define DS1302_D6 6
#define DS1302_D7 7

#define DS1302_READBIT DS1302_D0 // READBIT=1: read instruction

#define DS1302_RC DS1302_D6

#define DS1302_CH DS1302_D7   // 1 = Clock Halt, 0 = start

#define DS1302_AM_PM DS1302_D5 // 0 = AM, 1 = PM
#define DS1302_12_24 DS1302_D7 // 0 = 24 hour, 1 = 12 hour

// Enable Register
#define DS1302_WP DS1302_D7   // 1 = Write Protect, 0 = enabled

// Trickle Register
#define DS1302_ROUT0 DS1302_D0
#define DS1302_ROUT1 DS1302_D1
#define DS1302_DS0   DS1302_D2
#define DS1302_DS1   DS1302_D2
#define DS1302_TCS0  DS1302_D4
#define DS1302_TCS1  DS1302_D5
#define DS1302_TCS2  DS1302_D6
#define DS1302_TCS3  DS1302_D7


typedef struct ds1302_struct
{
  uint8_t Seconds:4;      // low decimal digit 0-9
  uint8_t Seconds10:3;    // high decimal digit 0-5
  uint8_t CH:1;           // CH = Clock Halt
  uint8_t Minutes:4;
  uint8_t Minutes10:3;
  uint8_t reserved1:1;
  union
  {
    struct
    {
      uint8_t Hour:4;
      uint8_t Hour10:2;
      uint8_t reserved2:1;
      uint8_t hour_12_24:1; // 0 for 24 hour format
    } h24;
    struct
    {
      uint8_t Hour:4;
      uint8_t Hour10:1;
      uint8_t AM_PM:1;      // 0 for AM, 1 for PM
      uint8_t reserved2:1;
      uint8_t hour_12_24:1; // 1 for 12 hour format
    } h12;
  };
  uint8_t Date:4;           // Day of month, 1 = first day
  uint8_t Date10:2;
  uint8_t reserved3:2;
  uint8_t Month:4;          // Month, 1 = January
  uint8_t Month10:1;
  uint8_t reserved4:3;
  uint8_t Day:3;            // Day of week, 1 = first day (any day)
  uint8_t reserved5:5;
  uint8_t Year:4;           // Year, 0 = year 2000
  uint8_t Year10:4;
  uint8_t reserved6:7;
  uint8_t WP:1;             // WP = Write Protect
};

char dayOfweek[7][4] = {"MON","TUE","WEN","THU","FRI","SAT","SUN"};


struct datetime
{
  int year, month, date, wod;
  int hour, minute, second;
};

struct datetime ds1302_struct_to_datetime(ds1302_struct* rtc)
{
  datetime dt;

  dt.hour = rtc->h24.Hour10 * 10 + rtc->h24.Hour;
  dt.minute = rtc->Minutes10 * 10 + rtc->Minutes;
  dt.second = rtc->Seconds10 * 10 + rtc->Seconds;

  dt.date = rtc->Date10 * 10 + rtc->Date;
  dt.month = rtc->Month10 * 10 + rtc->Month;
  dt.wod = rtc->Day;
  dt.year = 2000 + rtc->Year10 * 10 + rtc->Year;

  return dt;
}


void DS1302_clock_burst_read( uint8_t *p)
{
  int i;

  _DS1302_start();

  _DS1302_togglewrite( DS1302_CLOCK_BURST_READ, true);  

  for( i=0; i<8; i++)
  {
    *p++ = _DS1302_toggleread();
  }
  _DS1302_stop();
}

void DS1302_clock_burst_write( uint8_t *p)
{
  int i;

  _DS1302_start();

  _DS1302_togglewrite( DS1302_CLOCK_BURST_WRITE, false);  

  for( i=0; i<8; i++)
  {
    _DS1302_togglewrite( *p++, false);  
  }
  _DS1302_stop();
}

uint8_t DS1302_read(int address)
{
  uint8_t data;

  bitSet( address, DS1302_READBIT);  

  _DS1302_start();
  _DS1302_togglewrite( address, true);  
  data = _DS1302_toggleread();
  _DS1302_stop();

  return (data);
}

void DS1302_write( int address, uint8_t data)
{
  bitClear( address, DS1302_READBIT);   

  _DS1302_start();
  _DS1302_togglewrite( address, false); 
  _DS1302_togglewrite( data, false); 
  _DS1302_stop();  
}

void _DS1302_start( void)
{
  digitalWrite( DS1302_CE_PIN, LOW); // default, not enabled
  pinMode( DS1302_CE_PIN, OUTPUT);  

  digitalWrite( DS1302_SCLK_PIN, LOW); // default, clock low
  pinMode( DS1302_SCLK_PIN, OUTPUT);

  pinMode( DS1302_IO_PIN, OUTPUT);

  digitalWrite( DS1302_CE_PIN, HIGH); // start the session
  delayMicroseconds( 4);           // tCC = 4us
}

void _DS1302_stop(void)
{
  digitalWrite( DS1302_CE_PIN, LOW);

  delayMicroseconds( 4);           // tCWH = 4us
}


uint8_t _DS1302_toggleread( void)
{
  uint8_t i, data;

  data = 0;
  for( i = 0; i <= 7; i++)
  {
    digitalWrite( DS1302_SCLK_PIN, HIGH);
    delayMicroseconds( 1);

    digitalWrite( DS1302_SCLK_PIN, LOW);
    delayMicroseconds( 1);        // tCL=1000ns, tCDD=800ns

    bitWrite( data, i, digitalRead( DS1302_IO_PIN)); 
  }
  return( data);
}

void _DS1302_togglewrite( uint8_t data, uint8_t release)
{
  int i;

  for( i = 0; i <= 7; i++)
  { 
    digitalWrite( DS1302_IO_PIN, bitRead(data, i));  
    delayMicroseconds( 1);     // tDC = 200ns

    digitalWrite( DS1302_SCLK_PIN, HIGH);     
    delayMicroseconds( 1);     // tCH = 1000ns, tCDH = 800ns

    if( release && i == 7)
    {
      pinMode( DS1302_IO_PIN, INPUT);
    }
    else
    {
      digitalWrite( DS1302_SCLK_PIN, LOW);
      delayMicroseconds( 1);       // tCL=1000ns, tCDD=800ns
    }
  }
}


void setup()
{      
  ds1302_struct rtc;


  Serial.begin(9600);
  Serial.println("DS1302 Real Time Clock");
  Serial.println("Version 2, March 2013");

  DS1302_write (DS1302_ENABLE, 0);

  DS1302_write (DS1302_TRICKLE, 0x00);

#define SET_DATE_TIME_JUST_ONCE
#ifdef SET_DATE_TIME_JUST_ONCE  

  int seconds, minutes, hours, dayofweek, dayofmonth, month, year;

  seconds    = 0;
  minutes    = 8;
  hours      = 10;
  dayofweek  = 4;  // Day of week, any day can be first, counts 1...7
  dayofmonth = 8; // Day of month, 1...31
  month      = 11;  // month 1...12
  year       = 2018;

  memset ((char *) &rtc, 0, sizeof(rtc));

  rtc.Seconds    = bin2bcd_l( seconds);
  rtc.Seconds10  = bin2bcd_h( seconds);
  rtc.CH         = 0;      // 1 for Clock Halt, 0 to run;
  rtc.Minutes    = bin2bcd_l( minutes);
  rtc.Minutes10  = bin2bcd_h( minutes);

  rtc.h24.Hour   = bin2bcd_l( hours);
  rtc.h24.Hour10 = bin2bcd_h( hours);
  rtc.h24.hour_12_24 = 0; // 0 for 24 hour format
  rtc.Date       = bin2bcd_l( dayofmonth);
  rtc.Date10     = bin2bcd_h( dayofmonth);
  rtc.Month      = bin2bcd_l( month);
  rtc.Month10    = bin2bcd_h( month);
  rtc.Day        = dayofweek;
  rtc.Year       = bin2bcd_l( year - 2000);
  rtc.Year10     = bin2bcd_h( year - 2000);
  rtc.WP = 0;  

  DS1302_clock_burst_write( (uint8_t *) &rtc);
#endif
}
void loop()
{
  ds1302_struct rtc;
  char buffer[80];     // the code uses 70 characters.

  DS1302_clock_burst_read( (uint8_t *) &rtc);
    struct datetime dt = ds1302_struct_to_datetime(&rtc);

  
  sprintf( buffer, "%02d:%02d:%02d %s", dt.hour, dt.minute, dt.second, dayOfweek[dt.wod - 1]);
  Serial.println(buffer);

  sprintf(buffer, "%04d-%02d-%02d", dt.year, dt.month, dt.date);
  Serial.println( buffer);

  delay( 5000);
}
