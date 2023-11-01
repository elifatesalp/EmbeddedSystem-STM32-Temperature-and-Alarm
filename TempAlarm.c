#define         YESIL     GPIOD_ODR.B12
#define         TURUNCU   GPIOD_ODR.B13
#define         KIRMIZI   GPIOD_ODR.B14
#define         MAVI      GPIOD_ODR.B15


sbit LCD_RS at GPIOE_ODR.B8;
sbit LCD_EN at GPIOE_ODR.B10;
sbit LCD_D4 at GPIOE_ODR.B4;
sbit LCD_D5 at GPIOE_ODR.B5;
sbit LCD_D6 at GPIOE_ODR.B6;
sbit LCD_D7 at GPIOE_ODR.B7;


unsigned olculen=0;
long toplam=0;
float milivolt=0,sicaklik=0,ortalama=0,filterval=0;
char i=0,txt[15];

void kurulum()
{
  GPIO_Digital_Input(&GPIOB_BASE, _GPIO_PINMASK_1); // B0
  GPIO_Digital_Input(&GPIOA_BASE, _GPIO_PINMASK_13|_GPIO_PINMASK_14);  //B1 ve B2
  GPIO_Digital_Input(&GPIOC_BASE, _GPIO_PINMASK_4|_GPIO_PINMASK_5); // B3 ve B4
  GPIO_Digital_Output(&GPIOD_BASE, _GPIO_PINMASK_12|_GPIO_PINMASK_13|_GPIO_PINMASK_14|_GPIO_PINMASK_15);  //ledler
}

void main()
{
  kurulum();
 GPIO_Digital_Output(&GPIOE_BASE, _GPIO_PINMASK_9); //R/W pini saseye cekiliyor.
 GPIOE_ODR.B9=0;
  Lcd_Init();                                                  // Initialize LCD
  Lcd_Cmd(_LCD_CLEAR);                        // Clear display
  Lcd_Cmd(_LCD_CURSOR_OFF);           // Cursor off
  Lcd_Out(1,1,"Sicaklik=");                        // LCD'nin 1. satir 1.sutunundan itibaren "Sicaklik=" yazisi
  ADC1_Init();
  ADC_Set_Input_Channel(_ADC_CHANNEL_12);      // ADC biriminin 12. kanali aktif edildi (PC2)
  while(1) {                                                                       // Endless loop

    for(i=0;i<100;i++)                                               // 20 Kez okunan deger toplaniyor
    {
     olculen=ADC1_Get_Sample(12);
     toplam+=olculen;
    }

     ortalama=toplam/100.0;        // Toplanan deger 20'ye bolunerek ortalama alinmis olunuyor
     toplam=0;                                                           // Bir sonraki islem icin toplam sifirlanir
     milivolt=ortalama*3000.0/4095;                        // olculen degeri milivolta cevirmek icin // ortalama deger 3000 mv/4095 isleminden // cikan katsayi ile carpiliyor
     sicaklik=milivolt/10;                                          // Sicaklik LM35 her 10 mV 'da 1 derece arttmasi icin milivolt degeri 10'a bolunerek hesaplaniyor.
    FloatToStr(sicaklik,txt);                  //Sicaklik LCD'de gosterilmek icin Stringe donusturuluyor.
    Lcd_Chr(1,10,txt[0]);
    Lcd_Chr_CP(txt[1]);
    Lcd_Chr_CP(txt[2]);
    Lcd_Chr_CP(txt[3]);
    Lcd_Chr_CP(txt[4]);
    Lcd_Chr_CP('C');
    if(sicaklik>=27)
    {

     KIRMIZI =1;
     MAVI = 0;
     Lcd_Chr(1,10,txt[0]);
     Lcd_Out(2,1,"Alarm");
    }
            if(sicaklik<27){

                Lcd_Out(2,1,"      ");
            }