void  LED(){
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(1000);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(1000);   
}
int z = 0;
void neck(){
  /*
 if (z <= 0){
    while (z++ <= 200){
      pwm.setPWM(6, 0, 160 + z);
      delay(5); 
    }
  }
  else{
    while (z-- >= 0){
      pwm.setPWM(6, 0, 160 + z);
      delay(5);
    }
  } */
  pwm.setPWM(6, 0, 160);
}
