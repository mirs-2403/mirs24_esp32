void *jack_up(void *arg){
  int jack_pwm = 255;
  int count = 0;
  digitalWrite(PIN_DIR_JACK,HIGH);
  
  while(digitalRead(PIN_SW_UP)){
    if(count >= NEAR_END){
      jack_pwm = 50;
    }else{
      jack_pwm = 100;
    }
    ledcWrite(jack_Channel, jack_pwm);
    count++;
    delay(10);
  }
  
  //jack_pwm = 100;
  //ledcWrite(jack_Channel, jack_pwm);
  //delay(1000);
  ledcWrite(jack_Channel, 0);
  pthread_exit(NULL);
}

void *jack_down(void *arg){
  int jack_pwm = 255;
  int count = 0;
  digitalWrite(PIN_DIR_JACK,LOW);
  while(digitalRead(PIN_SW_DOWN)){
    if(count >= NEAR_END){
      jack_pwm = 50;
    }else{
      jack_pwm = 100;
    }
    ledcWrite(jack_Channel, jack_pwm);
    count++;
    delay(10);
  }
  ledcWrite(jack_Channel, 0);
  pthread_exit(NULL);
}

void jack_test(){
  int jack_pwm = 100;
  digitalWrite(PIN_DIR_JACK,HIGH);
  ledcWrite(jack_Channel, jack_pwm);
  delay(1000);
  ledcWrite(jack_Channel, 0);
}

void jack_ctrl_set(){
  // ledcのPWM設定
  pinMode(PIN_DIR_JACK, OUTPUT);
  pinMode(PIN_SW_UP, INPUT_PULLUP);
  pinMode(PIN_SW_DOWN, INPUT_PULLUP);
  ledcSetup(jack_Channel, pwmFrequency, pwmResolution);
  ledcAttachPin(PIN_PWM_JACK, jack_Channel);

}