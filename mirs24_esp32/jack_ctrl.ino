void jack_up(){
  int jack_pwm = 255;
  int count = 0;
  digitalWrite(PIN_DIR_JACK,HIGH);
  while(1){
    int isPushUpperSwitch = digitalRead(PIN_SW_UP);
    if(isPushUpperSwitch == HIGH)break;
    if(count >= NEAR_END){
      jack_pwm = 100;
    }else{
      jack_pwm = 255;
    }
    ledcWrite(jack_Channel, jack_pwm);
    count++;
    delay(10);
  }
}

void jack_down(){
  int jack_pwm = 255;
  int count = 0;
  digitalWrite(PIN_DIR_JACK,LOW);
  while(1){
    int isPushLowerSwitch = digitalRead(PIN_SW_UP);
    if(isPushLowerSwitch == HIGH)break;
    if(count >= NEAR_END){
      jack_pwm = 100;
    }else{
      jack_pwm = 255;
    }
    ledcWrite(jack_Channel, jack_pwm);
    count++;
    delay(10);
  }
}

void jack_ctrl_set(){
  // ledcのPWM設定
  pinMode(PIN_DIR_JACK, OUTPUT);
  pinMode(PIN_SW_UP, INPUT_PULLUP);
  pinMode(PIN_SW_DOWN, INPUT_PULLUP);
  ledcSetup(jack_Channel, pwmFrequency, pwmResolution);
  ledcAttachPin(PIN_PWM_JACK, jack_Channel);

}