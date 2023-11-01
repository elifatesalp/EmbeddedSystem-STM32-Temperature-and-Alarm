#line 1 "C:/Users/elifa/OneDrive/Masaüstü/s_cakl_kalarm.c"






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
 GPIO_Digital_Input(&GPIOB_BASE, _GPIO_PINMASK_1);
 GPIO_Digital_Input(&GPIOA_BASE, _GPIO_PINMASK_13|_GPIO_PINMASK_14);
 GPIO_Digital_Input(&GPIOC_BASE, _GPIO_PINMASK_4|_GPIO_PINMASK_5);
 GPIO_Digital_Output(&GPIOD_BASE, _GPIO_PINMASK_12|_GPIO_PINMASK_13|_GPIO_PINMASK_14|_GPIO_PINMASK_15);
}

void main()
{
 kurulum();
 GPIO_Digital_Output(&GPIOE_BASE, _GPIO_PINMASK_9);
 GPIOE_ODR.B9=0;
 Lcd_Init();
 Lcd_Cmd(_LCD_CLEAR);
 Lcd_Cmd(_LCD_CURSOR_OFF);
 Lcd_Out(1,1,"Sicaklik=");
 ADC1_Init();
 ADC_Set_Input_Channel(_ADC_CHANNEL_12);
 while(1) {

 for(i=0;i<100;i++)
 {
 olculen=ADC1_Get_Sample(12);
 toplam+=olculen;
 }

 ortalama=toplam/100.0;
 toplam=0;
 milivolt=ortalama*3000.0/4095;
 sicaklik=milivolt/10;


 FloatToStr(sicaklik,txt);
 Lcd_Chr(1,10,txt[0]);
 Lcd_Chr_CP(txt[1]);
 Lcd_Chr_CP(txt[2]);
 Lcd_Chr_CP(txt[3]);
 Lcd_Chr_CP(txt[4]);
 Lcd_Chr_CP('C');
 if(sicaklik>=27)
 {

  GPIOD_ODR.B14  =1;
  GPIOD_ODR.B15  = 0;
 Lcd_Chr(1,10,txt[0]);
 Lcd_Out(2,1,"Alarm");

 }
 if(sicaklik<27){

 Lcd_Out(2,1,"      ");
 }
