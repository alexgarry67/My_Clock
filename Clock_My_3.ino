#define TM1638_CLK_PIN      2
#define TM1638_DIO_PIN      3
#define TM1638_STB0_PIN     4
#include <ErriezTM1638.h>
#include <ErriezLKM1638Board.h>
#include <Wire.h>
#include <DS3231.h>
// Create DS3231 object
DS3231 clock;
RTCDateTime dt;

// Create LKM1638Board object
LKM1638Board lkm1638(TM1638_CLK_PIN, TM1638_DIO_PIN, TM1638_STB0_PIN);

//char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};

static uint8_t led = 0;
static uint8_t dir = 1;
static LedColor color = LedRed;
static uint8_t ledDelay = 0;
static uint8_t ledDelayInit = 30;
static bool countEnable = false;
static bool countUp = true;
static unsigned long countValue = 0;
static uint8_t countDelay = 0;
static uint8_t countDelayInit = 10;
static uint8_t brightness = 2;

//обьявление переменных
volatile uint8_t buttons ;
volatile unsigned long int   timer_1   ;

//declare prototipes
void ustanovka_hour(void);
void ustanovka_minute(void);
void ustanovka_day(void);
void ustanovka_month(void);
void ustanovka_year(void);

//---------------------------------------------------
void timer1_init()
{
  cli();           // disable all interrupts
 TCCR1A = 0;
  TCCR1B = 0;

  TCNT1 = 0;            // preload timer 65536-16MHz/256/2Hz
  //TCCR1B |= (1 << CS12);    // 256 prescaler 
  TCCR1B |= (0 << CS12) | (0 << CS11) | (1 << CS10) ;
  TIMSK1 |= (1 << TOIE1);   // enable timer overflow interrupt
 sei();             // enable all interrupts
}//end void timer1_init()
//--------------------------------------------------------

void setup()
{
    Serial.begin(9600);
  // Initialize DS3231
  Serial.println("Initialize DS3231");;
  clock.begin();

    // Initialize TM1638
    lkm1638.begin();
    lkm1638.clear();
    lkm1638.setBrightness(brightness);
}

void loop()
{
// инитим таймер   
timer1_init(); 
//получаем время  
  dt = clock.getDateTime();
//выводим значения времени на LKM
    lkm1638.setPrintPos(6);
    lkm1638.print(dt.hour, DEC, 2,2);    
    lkm1638.setPrintPos(4);
    lkm1638.print(dt.minute, DEC, 2,2);
    lkm1638.setPrintPos(0);
    lkm1638.print(dt.second, DEC, 2,2);
    lkm1638.dotOn(6);
    
buttons = lkm1638.getButtons();
if (buttons == 128)
   {
    lkm1638.clear();   
    lkm1638.setColorLED(7, LedGreen);
    lkm1638.setPrintPos(6);
    lkm1638.print(dt.day, DEC, 2,2);
    lkm1638.dotOn(6);        
    lkm1638.setPrintPos(4);
    lkm1638.print(dt.month, DEC, 2,2);    
    lkm1638.dotOn(4);
    lkm1638.setPrintPos(0);
    lkm1638.print(dt.year, DEC, 4,4); 
    delay(5000);   
    lkm1638.clear();
    }//end button 128
if (buttons == 64)    
    {
//      d_hour_ust = d_hour;
      //d_minute_ust = d_minute;
      delay(500);
      ustanovka_hour();
      }//end button 64
 
}// end void loop()
//1==================================================
void ustanovka_hour(void)
{
}
//===================================================
//2==================================================
void ustanovka__minute(void)
{
}
//===================================================
//3==================================================
void ustanovka_day(void)
{
}
//===================================================
//4==================================================
void ustanovka_month(void)
{
}
//===================================================
//===================================================
void ustanovka_year(void)
{
}
//=================================================== 
//===================================================
ISR(TIMER1_OVF_vect)
{
   cli();
    timer_1++;
   sei();
}//end ISR(TIMER1_OVF_vect)
//===================================================  
