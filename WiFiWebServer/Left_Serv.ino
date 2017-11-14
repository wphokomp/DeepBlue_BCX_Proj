int   l_i = 0;
int   l_w = 0;
int   l_j = 0;
int   l_k = 0;

void wave_left_hand(int *l_wave){
  pwm1.setPWM(10, 0, 560);
  pwm1.setPWM(9, 0, 140);
  l_i = 0;
  while (l_i++ < 200){
    pwm.setPWM(11, 0, 160 + l_i);
    pwm.setPWM(8, 0, 260 + l_i);
    delay(5);
  }
  while (l_j++ < 7){
   if (l_j <= 0){
    while (l_j++ <= 100){
      pwm.setPWM(10, 0, 560 - l_j);
      delay(5); 
    }
  }
  else{
    while (l_j-- >= 0){
      pwm.setPWM(10, 0, 560 - l_j);
      delay(5);
    }
  } 
  }
  while (l_j-- >= 0){
      pwm.setPWM(10, 0, 120 + l_j);
      delay(5);
  }
  *l_wave = 1;
}

void   wave_right_hand(int *r_wave){
  pwm.setPWM(11, 0, 160 + r_i);
  pwm.setPWM(8, 0, 260 + r_i);
  delay(5);
  
  while (r_j++ < 7){
   if (r_j <= 0){
    while (r_j++ <= 100){
      pwm.setPWM(10, 0, 560 - r_j);
      delay(5); 
    }
  }
  else{
    while (r_j-- >= 0){
      pwm.setPWM(10, 0, 560 - r_j);
      delay(5);
    }
  } 
  }
  while (r_j-- >= 0){
      pwm.setPWM(10, 0, 120 + r_j);
      delay(5);
  }
  *r_wave = 1;
}
