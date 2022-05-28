// #include <unity.h>
// #include<LED.c>


//  void setUp(void)
//  {

//      int sum(int a, int b);
//      //void led_ON(void);
//  }

// void test_sum(void){
//     //sum(1,3);
//     int expected = 1+3;
//     int actual = sum(1,3);
//     TEST_ASSERT_EQUAL_INT32(4,actual);
// }

// int main(int argc, char**argv){
//     UNITY_BEGIN();
//     RUN_TEST(test_sum);
//     UNITY_END();

//     return 0;
// }



 #include <unity.h>
 //#include<avr/io.h>
 #include "CONFIG.h"
 #include "DIO.h"
 #include "LED.h"

 void setUp(void)
 {

     void led_Set(void);
     void led_ON(void);
     void BUZZER_Set(void);

 }

 void tearDown(void)
 {
     // clean stuff up here
     void led_OFF(void);
 }

 void test_LED_pin()
 {
     TEST_ASSERT_EQUAL(1, LED_PIN);
 }

//  void test_LED_low()
//  {
//      DIO_WritePin(LED_PORT, LED_PIN, OUTPUT);
//      TEST_ASSERT_EQUAL(1, DIO_ReadPin(LED_PORT, LED_PIN));
//  }

//   void test_LED_ON()
//  {
//      char PortName = 'D';
//      unsigned char Data= 1;
//      unsigned char PinNum = 1;
//      switch (PortName) {
//     case 'D':
//       if (Data) {
//         PORTD |= (1 << PinNum);
//       } else {
//         PORTD &= ~(1 << PinNum);
//       }
//       break;
//     default:
//       break;
//   }
    

//      TEST_ASSERT_EQUAL(1, DIO_ReadPin(LED_PORT, LED_PIN));
//  }



/////////////////////////////////buzzer///////////////////////////////////
void test_Buzzer_pin()
{
   TEST_ASSERT_EQUAL(2, BUZZER_PIN);
}

// void test_buzzer_off()
// {

//     DIO_WritePin(Buzzer_PORT, Buzzer_PIN, OUTPUT);
//     TEST_ASSERT_EQUAL(0, DIO_ReadPin(Buzzer_PORT, Buzzer_PIN));
// }

// void test_buzzer_on()
// {

//     DIO_WritePin(Buzzer_PORT, Buzzer_PIN, OUTPUT);
//     TEST_ASSERT_EQUAL(1, DIO_ReadPin(Buzzer_PORT, Buzzer_PIN));
// }
///////////////////////////////////////////////////////////////////////////

 int main(int argc, char **argv)
 {
     UNITY_BEGIN();

     RUN_TEST(test_LED_pin);
     //RUN_TEST(test_LED_ON);
    //RUN_TEST(test_LED_low);
    //RUN_TEST(test_Buzzer_pin);
     UNITY_END();
 }