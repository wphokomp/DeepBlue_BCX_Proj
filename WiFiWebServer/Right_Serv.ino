int   r_i = 0;
int   r_w = 0;
int   r_j = 0;

void wave_right_hand(int *r_wave){
  pwm1.setPWM(10, 0, 120);
  pwm1.setPWM(9, 0, 140);
  r_i = 0;
  while (r_i++ < 200){
    pwm1.setPWM(11, 0, 160 + r_i);
    pwm1.setPWM(8, 0, 260 + r_i);
    LED();
    delay(5);
  }
  while (r_w++ < 7){
   if (r_j <= 0){
    while (r_j++ <= 100){
      pwm1.setPWM(10, 0, 120 + r_j);
      LED();
      delay(5); 
    }
  }
  else{
    while (r_j-- >= 0){
      pwm1.setPWM(10, 0, 120 + r_j);
      LED();
      delay(5);
    }
  } 
  }
  while (r_j-- >= 0){
      pwm1.setPWM(10, 0, 120 + r_j);
      LED();
      delay(5);
  }
  *r_wave = 1;
}

