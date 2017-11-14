int   i = 0;
int   w = 0;
int   j = 0;
int   k = 0;

//R-HTWT 4
//S-TWT 6
//R-ASS 7

void hands_up(){
  pwm1.setPWM(11, 0, 160);
  pwm1.setPWM(10, 0, 120);
  pwm1.setPWM(9, 0, 140);
 
  pwm.setPWM(11, 0, 140);//140
  pwm.setPWM(10, 0, 560);//120
  pwm.setPWM(9, 0, 280);//260
  while (i++ < 200){
    pwm1.setPWM(8, 0, 260 + i);
    pwm.setPWM(8, 0, 280 - i);
    delay(5);
  }
}

void hands_down(int *down){
  if (!right_wave || !left_wave){
    pwm1.setPWM(11, 0, 160);
    pwm1.setPWM(10, 0, 120);
    pwm1.setPWM(9, 0, 140);
   
    pwm.setPWM(11, 0, 140);//140
    pwm.setPWM(10, 0, 560);//120
    pwm.setPWM(9, 0, 280);//260/
    //pwm.setPWM(8, 0, 280);
    while (i-- > 0){
      pwm1.setPWM(8, 0, 260 + i);
      pwm.setPWM(8, 0, 280 - i);
      LED();
      delay(5);
    }
  }
  else if (right_wave || left_wave){
    pwm1.setPWM(10, 0, 120);
    pwm1.setPWM(9, 0, 140);
      
    pwm.setPWM(11, 0, 140);//140
    pwm.setPWM(10, 0, 120);//120
    pwm.setPWM(9, 0, 280);//260/
    pwm.setPWM(8, 0, 280);
    while (i-- > 0){
      pwm1.setPWM(11, 0, 160 + i);
      pwm1.setPWM(8, 0, 260 + i);
      pwm.setPWM(8, 0, 280 - i);
      LED();
      delay(5);
    }
  }
  *down = 1;
}

void  idle(){
  int d = 0;
  for(int i = 0; i < 5; i++){
    hands_down(&d);
    if (raand == 0)
      return ;
    hands_up();    
  }
}
