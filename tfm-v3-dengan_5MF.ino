//---(1)-------------------------------(ok)
  //input-dht11
    #include <dht.h>
    dht DHT;
    #define DHT11_PIN 8

  //output-motor-PWM
    int pin_pwm=9;
    int motor1pin1= 2;
    int motor1pin2= 3;
//-------------------------------------


//---(2)-------------------------------(ok)
  #include <Fuzzy.h>
  Fuzzy *fuzzy = new Fuzzy();

  //FuzzyInput analog1-temperature-ok
    //sdingin=sangat dingin dst 
  //FuzzySet *sdingin          = new FuzzySet(20, 25, 30, 32);
  FuzzySet *sdingin          = new FuzzySet(25, 25, 30, 32);
  FuzzySet *dingin           = new FuzzySet(30, 32, 35, 37);
  FuzzySet *anormal           = new FuzzySet(35, 37, 40, 42);
  FuzzySet *panas            = new FuzzySet(40, 42, 45, 47);
  FuzzySet *spanas           = new FuzzySet(45, 47, 50, 50);
  //FuzzySet *sdingin          = new FuzzySet(0, 5, 9, 11);
  //FuzzySet *dingin           = new FuzzySet(9, 11, 15, 18);
  //FuzzySet *anormal           = new FuzzySet(15, 18, 24, 25);
  //FuzzySet *panas            = new FuzzySet(24, 25, 30, 35);
  //FuzzySet *spanas           = new FuzzySet(30, 35, 40, 45);
  
  // FuzzyInput analog2-humidity-ok
  FuzzySet *skering         = new FuzzySet(0, 0, 30, 40);
  FuzzySet *kering          = new FuzzySet(30, 40, 45, 50);
  FuzzySet *bnormal          = new FuzzySet(45, 50, 60, 70);
  FuzzySet *lembab          = new FuzzySet(60, 70, 80, 90);
  FuzzySet *slembab         = new FuzzySet(80, 90, 100, 100);

  // FuzzyOutput-motor_PWM(kipas)-ok
  FuzzySet *slambat        = new FuzzySet(0, 0, 26, 51);
  FuzzySet *lambat         = new FuzzySet(26, 51, 81, 102);
  FuzzySet *cnormal        = new FuzzySet(81, 102, 132, 153);
  FuzzySet *cepat          = new FuzzySet(132, 153, 183, 204);
  FuzzySet *scepat         = new FuzzySet(183, 204, 250, 250);
  //FuzzySet *scepat         = new FuzzySet(183, 204, 230, 255);
//-------------------------------------



void setup() {
//---(3)-------------------------------(ok)  
  Serial.begin(9600);

  //pin-motor-output
    int motor1pin1 = 2;
    int motor1pin2 = 3;  
//-------------------------------------


//---(4)-------------------------------(ok)  
  // FuzzyInput-1(temperature)
  FuzzyInput *temperature = new FuzzyInput(1);
  temperature->addFuzzySet(sdingin);
  temperature->addFuzzySet(dingin);
  temperature->addFuzzySet(anormal);
  temperature->addFuzzySet(panas);
  temperature->addFuzzySet(spanas);
  fuzzy->addFuzzyInput(temperature);

  // FuzzyInput-2(humidity)
  FuzzyInput *humidity = new FuzzyInput(2);
  humidity->addFuzzySet(skering);
  humidity->addFuzzySet(kering);
  humidity->addFuzzySet(bnormal);
  humidity->addFuzzySet(lembab);
  humidity->addFuzzySet(slembab);
  fuzzy->addFuzzyInput(humidity);

   // FuzzyOutput-PWM_motor_kipas
  FuzzyOutput *motor = new FuzzyOutput(1);
  motor->addFuzzySet(slambat);
  motor->addFuzzySet(lambat);
  motor->addFuzzySet(cnormal);
  motor->addFuzzySet(cepat);
  motor->addFuzzySet(scepat);
  fuzzy->addFuzzyOutput(motor);
//-------------------------------------


//---(4)-------------------------------(ok)
  //Bagian FuzzyRule////////////////////////////////////////////////////////////////// 1 (ok)
    FuzzyRuleAntecedent *sdingin_skering = new FuzzyRuleAntecedent();
    sdingin_skering->joinWithAND(sdingin, skering);

    FuzzyRuleConsequent *motor_slambat1 = new FuzzyRuleConsequent();
    motor_slambat1->addOutput(slambat);

    FuzzyRule *fuzzyRule1 = new FuzzyRule(1, sdingin_skering, motor_slambat1);
    fuzzy->addFuzzyRule(fuzzyRule1); 
  //---end---------////////////////////////////////////////////////////////////////// 

  //Bagian FuzzyRule////////////////////////////////////////////////////////////////// 2 (ok)
    FuzzyRuleAntecedent *dingin_skering = new FuzzyRuleAntecedent();
    dingin_skering->joinWithAND(dingin, skering);

    FuzzyRuleConsequent *motor_slambat2 = new FuzzyRuleConsequent();//angka sll beriterasi
    motor_slambat2->addOutput(slambat);//angka sll beriterasi

    FuzzyRule *fuzzyRule2 = new FuzzyRule(2, sdingin_skering, motor_slambat2);//angka sll beriterasi
    fuzzy->addFuzzyRule(fuzzyRule2);//angka sll beriterasi 
  //---end---------//////////////////////////////////////////////////////////////////

  //Bagian FuzzyRule////////////////////////////////////////////////////////////////// 3 (ok)
    FuzzyRuleAntecedent *anormal_skering = new FuzzyRuleAntecedent();
    anormal_skering->joinWithAND(anormal, skering);

    FuzzyRuleConsequent *motor_lambat3 = new FuzzyRuleConsequent();//angka sll beriterasi
    motor_lambat3->addOutput(lambat);//angka sll beriterasi

    FuzzyRule *fuzzyRule3 = new FuzzyRule(3, anormal_skering, motor_lambat3);//angka sll beriterasi
    fuzzy->addFuzzyRule(fuzzyRule3);//angka sll beriterasi 
  //---end---------//////////////////////////////////////////////////////////////////

  //Bagian FuzzyRule////////////////////////////////////////////////////////////////// 4 (ok)
    FuzzyRuleAntecedent *panas_skering = new FuzzyRuleAntecedent();
    panas_skering->joinWithAND(panas, skering);

    FuzzyRuleConsequent *motor_cepat4 = new FuzzyRuleConsequent();//angka sll beriterasi
    motor_cepat4->addOutput(cepat);//angka sll beriterasi

    FuzzyRule *fuzzyRule4 = new FuzzyRule(4, panas_skering, motor_cepat4);//angka sll beriterasi
    fuzzy->addFuzzyRule(fuzzyRule4);//angka sll beriterasi 
  //---end---------////////////////////////////////////////////////////////////////// 

  //Bagian FuzzyRule////////////////////////////////////////////////////////////////// 5 (ok)
    FuzzyRuleAntecedent *spanas_skering = new FuzzyRuleAntecedent();
    spanas_skering->joinWithAND(spanas, skering);

    FuzzyRuleConsequent *motor_scepat5 = new FuzzyRuleConsequent();//angka sll beriterasi
    motor_scepat5->addOutput(scepat);//angka sll beriterasi

    FuzzyRule *fuzzyRule5 = new FuzzyRule(5, spanas_skering, motor_scepat5);//angka sll beriterasi
    fuzzy->addFuzzyRule(fuzzyRule5);//angka sll beriterasi 
  //---end---------//////////////////////////////////////////////////////////////////

  //Bagian FuzzyRule////////////////////////////////////////////////////////////////// 6 (ok)
    FuzzyRuleAntecedent *sdingin_kering = new FuzzyRuleAntecedent();
    sdingin_kering->joinWithAND(sdingin, kering);

    FuzzyRuleConsequent *motor_slambat6 = new FuzzyRuleConsequent();//angka sll beriterasi
    motor_slambat6->addOutput(slambat);//angka sll beriterasi

    FuzzyRule *fuzzyRule6 = new FuzzyRule(6, sdingin_kering, motor_slambat6);//angka sll beriterasi
    fuzzy->addFuzzyRule(fuzzyRule6);//angka sll beriterasi 
  //---end---------////////////////////////////////////////////////////////////////// 

  //Bagian FuzzyRule////////////////////////////////////////////////////////////////// 7 (ok)
    FuzzyRuleAntecedent *dingin_kering = new FuzzyRuleAntecedent();
    dingin_kering->joinWithAND(dingin, kering);

    FuzzyRuleConsequent *motor_lambat7 = new FuzzyRuleConsequent();//angka sll beriterasi
    motor_lambat7->addOutput(lambat);//angka sll beriterasi

    FuzzyRule *fuzzyRule7 = new FuzzyRule(7, dingin_kering, motor_lambat7);//angka sll beriterasi
    fuzzy->addFuzzyRule(fuzzyRule7);//angka sll beriterasi 
  //---end---------////////////////////////////////////////////////////////////////// 

  //Bagian FuzzyRule////////////////////////////////////////////////////////////////// 8 (ok)
    FuzzyRuleAntecedent *anormal_kering = new FuzzyRuleAntecedent();
    anormal_kering->joinWithAND(anormal, kering);

    FuzzyRuleConsequent *motor_lambat8 = new FuzzyRuleConsequent();//angka sll beriterasi
    motor_lambat8->addOutput(lambat);//angka sll beriterasi

    FuzzyRule *fuzzyRule8 = new FuzzyRule(8, anormal_kering, motor_lambat8);//angka sll beriterasi
    fuzzy->addFuzzyRule(fuzzyRule8);//angka sll beriterasi 
  //---end---------//////////////////////////////////////////////////////////////////

  //Bagian FuzzyRule////////////////////////////////////////////////////////////////// 9 (ok)
    FuzzyRuleAntecedent *panas_kering = new FuzzyRuleAntecedent();
    panas_kering->joinWithAND(panas, kering);

    FuzzyRuleConsequent *motor_cepat9 = new FuzzyRuleConsequent();//angka sll beriterasi
    motor_cepat9->addOutput(cepat);//angka sll beriterasi

    FuzzyRule *fuzzyRule9 = new FuzzyRule(9, panas_kering, motor_cepat9);//angka sll beriterasi
    fuzzy->addFuzzyRule(fuzzyRule9);//angka sll beriterasi 
  //---end---------//////////////////////////////////////////////////////////////////

  //Bagian FuzzyRule////////////////////////////////////////////////////////////////// 10 (ok)
    FuzzyRuleAntecedent *spanas_kering = new FuzzyRuleAntecedent();
    spanas_kering->joinWithAND(spanas, kering);

    FuzzyRuleConsequent *motor_scepat10 = new FuzzyRuleConsequent();//angka sll beriterasi
    motor_scepat10->addOutput(scepat);//angka sll beriterasi

    FuzzyRule *fuzzyRule10 = new FuzzyRule(10, spanas_kering, motor_scepat10);//angka sll beriterasi
    fuzzy->addFuzzyRule(fuzzyRule10);//angka sll beriterasi 
  //---end---------//////////////////////////////////////////////////////////////////

  //Bagian FuzzyRule////////////////////////////////////////////////////////////////// 11 (ok)
    FuzzyRuleAntecedent *sdingin_bnormal = new FuzzyRuleAntecedent();
    sdingin_bnormal->joinWithAND(sdingin, bnormal);

    FuzzyRuleConsequent *motor_slambat11 = new FuzzyRuleConsequent();//angka sll beriterasi
    motor_slambat11->addOutput(slambat);//angka sll beriterasi

    FuzzyRule *fuzzyRule11 = new FuzzyRule(11, sdingin_bnormal, motor_slambat11);//angka sll beriterasi
    fuzzy->addFuzzyRule(fuzzyRule11);//angka sll beriterasi 
  //---end---------//////////////////////////////////////////////////////////////////

  //Bagian FuzzyRule////////////////////////////////////////////////////////////////// 12 (ok)
    FuzzyRuleAntecedent *dingin_bnormal = new FuzzyRuleAntecedent();
    dingin_bnormal->joinWithAND(dingin, bnormal);

    FuzzyRuleConsequent *motor_lambat12 = new FuzzyRuleConsequent();//angka sll beriterasi
    motor_lambat12->addOutput(lambat);//angka sll beriterasi

    FuzzyRule *fuzzyRule12 = new FuzzyRule(12, dingin_bnormal, motor_lambat12);//angka sll beriterasi
    fuzzy->addFuzzyRule(fuzzyRule12);//angka sll beriterasi 
  //---end---------//////////////////////////////////////////////////////////////////

  //Bagian FuzzyRule////////////////////////////////////////////////////////////////// 13 (ok)
    FuzzyRuleAntecedent *anormal_bnormal = new FuzzyRuleAntecedent();
    anormal_bnormal->joinWithAND(anormal, bnormal);

    FuzzyRuleConsequent *motor_slambat13 = new FuzzyRuleConsequent();//angka sll beriterasi
    motor_slambat13->addOutput(slambat);//angka sll beriterasi

    FuzzyRule *fuzzyRule13 = new FuzzyRule(13, anormal_bnormal, motor_slambat13);//angka sll beriterasi
    fuzzy->addFuzzyRule(fuzzyRule13);//angka sll beriterasi 
  //---end---------//////////////////////////////////////////////////////////////////

  //Bagian FuzzyRule////////////////////////////////////////////////////////////////// 14 (ok)
    FuzzyRuleAntecedent *panas_bnormal = new FuzzyRuleAntecedent();
    panas_bnormal->joinWithAND(panas, bnormal);

    FuzzyRuleConsequent *motor_scepat14 = new FuzzyRuleConsequent();//angka sll beriterasi
    motor_scepat14->addOutput(scepat);//angka sll beriterasi

    FuzzyRule *fuzzyRule14 = new FuzzyRule(14, panas_bnormal, motor_scepat14);//angka sll beriterasi
    fuzzy->addFuzzyRule(fuzzyRule14);//angka sll beriterasi 
  //---end---------//////////////////////////////////////////////////////////////////

  //Bagian FuzzyRule////////////////////////////////////////////////////////////////// 15 (ok)
    FuzzyRuleAntecedent *spanas_bnormal = new FuzzyRuleAntecedent();
    spanas_bnormal->joinWithAND(spanas, bnormal);

    FuzzyRuleConsequent *motor_cepat15 = new FuzzyRuleConsequent();//angka sll beriterasi
    motor_cepat15->addOutput(cepat);//angka sll beriterasi

    FuzzyRule *fuzzyRule15 = new FuzzyRule(15, spanas_bnormal, motor_cepat15);//angka sll beriterasi
    fuzzy->addFuzzyRule(fuzzyRule15);//angka sll beriterasi 
  //---end---------//////////////////////////////////////////////////////////////////

  //Bagian FuzzyRule////////////////////////////////////////////////////////////////// 16 (ok)
    FuzzyRuleAntecedent *sdingin_lembab = new FuzzyRuleAntecedent();
    sdingin_lembab->joinWithAND(sdingin, lembab);

    FuzzyRuleConsequent *motor_slambat16 = new FuzzyRuleConsequent();//angka sll beriterasi
    motor_slambat16->addOutput(slambat);//angka sll beriterasi

    FuzzyRule *fuzzyRule16 = new FuzzyRule(16, sdingin_lembab, motor_slambat16);//angka sll beriterasi
    fuzzy->addFuzzyRule(fuzzyRule16);//angka sll beriterasi 
  //---end---------//////////////////////////////////////////////////////////////////

  //Bagian FuzzyRule////////////////////////////////////////////////////////////////// 17 (ok)
    FuzzyRuleAntecedent *dingin_lembab = new FuzzyRuleAntecedent();
    dingin_lembab->joinWithAND(dingin, lembab);

    FuzzyRuleConsequent *motor_lambat17 = new FuzzyRuleConsequent();//angka sll beriterasi
    motor_lambat17->addOutput(lambat);//angka sll beriterasi

    FuzzyRule *fuzzyRule17 = new FuzzyRule(17, dingin_lembab, motor_lambat17);//angka sll beriterasi
    fuzzy->addFuzzyRule(fuzzyRule17);//angka sll beriterasi 
  //---end---------//////////////////////////////////////////////////////////////////

  //Bagian FuzzyRule////////////////////////////////////////////////////////////////// 18 (ok)
    FuzzyRuleAntecedent *anormal_lembab = new FuzzyRuleAntecedent();
    anormal_lembab->joinWithAND(anormal, lembab);

    FuzzyRuleConsequent *motor_lambat18 = new FuzzyRuleConsequent();//angka sll beriterasi
    motor_lambat18->addOutput(lambat);//angka sll beriterasi

    FuzzyRule *fuzzyRule18 = new FuzzyRule(18, anormal_lembab, motor_lambat18);//angka sll beriterasi
    fuzzy->addFuzzyRule(fuzzyRule18);//angka sll beriterasi 
  //---end---------//////////////////////////////////////////////////////////////////

  //Bagian FuzzyRule////////////////////////////////////////////////////////////////// 19 (ok)
    FuzzyRuleAntecedent *panas_lembab = new FuzzyRuleAntecedent();
    panas_lembab->joinWithAND(panas, lembab);

    FuzzyRuleConsequent *motor_cepat19 = new FuzzyRuleConsequent();//angka sll beriterasi
    motor_cepat19->addOutput(cepat);//angka sll beriterasi

    FuzzyRule *fuzzyRule19 = new FuzzyRule(19, panas_lembab, motor_cepat19);//angka sll beriterasi
    fuzzy->addFuzzyRule(fuzzyRule19);//angka sll beriterasi 
  //---end---------//////////////////////////////////////////////////////////////////

  //Bagian FuzzyRule////////////////////////////////////////////////////////////////// 20 (ok)
    FuzzyRuleAntecedent *spanas_lembab = new FuzzyRuleAntecedent();
    spanas_lembab->joinWithAND(spanas, lembab);

    FuzzyRuleConsequent *motor_scepat20 = new FuzzyRuleConsequent();//angka sll beriterasi
    motor_scepat20->addOutput(scepat);//angka sll beriterasi

    FuzzyRule *fuzzyRule20 = new FuzzyRule(20, spanas_lembab, motor_scepat20);//angka sll beriterasi
    fuzzy->addFuzzyRule(fuzzyRule20);//angka sll beriterasi 
  //---end---------//////////////////////////////////////////////////////////////////

  //Bagian FuzzyRule////////////////////////////////////////////////////////////////// 21 (ok)
    FuzzyRuleAntecedent *sdingin_slembab = new FuzzyRuleAntecedent();
    sdingin_slembab->joinWithAND(sdingin, slembab);

    FuzzyRuleConsequent *motor_slambat21 = new FuzzyRuleConsequent();//angka sll beriterasi
    motor_slambat21->addOutput(slambat);//angka sll beriterasi

    FuzzyRule *fuzzyRule21 = new FuzzyRule(21, sdingin_slembab, motor_slambat21);//angka sll beriterasi
    fuzzy->addFuzzyRule(fuzzyRule21);//angka sll beriterasi 
  //---end---------//////////////////////////////////////////////////////////////////

  //Bagian FuzzyRule////////////////////////////////////////////////////////////////// 22 (ok)
    FuzzyRuleAntecedent *dingin_slembab = new FuzzyRuleAntecedent();
    dingin_slembab->joinWithAND(dingin, slembab);

    FuzzyRuleConsequent *motor_slambat22 = new FuzzyRuleConsequent();//angka sll beriterasi
    motor_slambat22->addOutput(slambat);//angka sll beriterasi

    FuzzyRule *fuzzyRule22 = new FuzzyRule(22, dingin_slembab, motor_slambat22);//angka sll beriterasi
    fuzzy->addFuzzyRule(fuzzyRule22);//angka sll beriterasi 
  //---end---------//////////////////////////////////////////////////////////////////

  //Bagian FuzzyRule////////////////////////////////////////////////////////////////// 23 (ok)
    FuzzyRuleAntecedent *anormal_slembab = new FuzzyRuleAntecedent();
    anormal_slembab->joinWithAND(anormal, slembab);

    FuzzyRuleConsequent *motor_slambat23 = new FuzzyRuleConsequent();//angka sll beriterasi
    motor_slambat23->addOutput(slambat);//angka sll beriterasi

    FuzzyRule *fuzzyRule23 = new FuzzyRule(23, anormal_slembab, motor_slambat23);//angka sll beriterasi
    fuzzy->addFuzzyRule(fuzzyRule23);//angka sll beriterasi 
  //---end---------//////////////////////////////////////////////////////////////////

  //Bagian FuzzyRule////////////////////////////////////////////////////////////////// 24 (ok)
    FuzzyRuleAntecedent *panas_slembab = new FuzzyRuleAntecedent();
    panas_slembab->joinWithAND(panas, slembab);

    FuzzyRuleConsequent *motor_scepat24 = new FuzzyRuleConsequent();//angka sll beriterasi
    motor_scepat24->addOutput(scepat);//angka sll beriterasi

    FuzzyRule *fuzzyRule24 = new FuzzyRule(24, panas_slembab, motor_scepat24);//angka sll beriterasi
    fuzzy->addFuzzyRule(fuzzyRule24);//angka sll beriterasi 
  //---end---------//////////////////////////////////////////////////////////////////

  //Bagian FuzzyRule////////////////////////////////////////////////////////////////// 25 ()
    FuzzyRuleAntecedent *spanas_slembab = new FuzzyRuleAntecedent();
    spanas_slembab->joinWithAND(spanas, slembab);

    FuzzyRuleConsequent *motor_scepat25 = new FuzzyRuleConsequent();//angka sll beriterasi
    motor_scepat25->addOutput(scepat);//angka sll beriterasi

    FuzzyRule *fuzzyRule25 = new FuzzyRule(25, spanas_slembab, motor_scepat25);//angka sll beriterasi
    fuzzy->addFuzzyRule(fuzzyRule25);//angka sll beriterasi 
  //---end---------//////////////////////////////////////////////////////////////////
 //-------------------------------------
}

void loop() {
 //---(5)-------------------------------(ok)
   //bagian input untuk mendapatkan angka temperature dan humidity, lalu dicetak di serial monitor
     int chk = DHT.read11(DHT11_PIN);

     Serial.print("Temperature = ");
     Serial.println(DHT.temperature);

     Serial.print("Humidity = ");
     Serial.println(DHT.humidity);
  //------------------------------------
 //-------------------------------------


 //---(6)-------------------------------(ok)
   //bagian input untuk memasukkan angka temperature dan humidity ke dalam proses fuzzy
     int in_1 = DHT.temperature;
     int in_2 = DHT.humidity;
   //-----------------------------------
 //-------------------------------------


 
 //---(7)defuzzyfikasi dan output-------(ok)
   //defuzzyfikasi
     fuzzy->setInput(1, in_1);
     fuzzy->setInput(2, in_2);
     fuzzy->fuzzify(); //untuk input dari tahap fuzzyfication
 
   //output--kirim defuzzyfikasi ke pin pwm l298n
     int out_motor = fuzzy->defuzzify(1); //utk hasil deffuzyfikasi dari fuzzy output
     analogWrite(pin_pwm , out_motor); //hasil dari defuzzyfikasi dipindah ke pin led (PWM), diseting di pin 11, nilainya 0-255

   //seting pin +&- motor dc di l298n 
     digitalWrite(motor1pin1, HIGH);
     digitalWrite(motor1pin2, LOW);
 //-------------------------------------

 //---(8)-------------------------------()
   //cetak hasil defuzzyfikasi ke serial monitor
     Serial.println("hasil: ");
     Serial.print("       defuzzyfikasi/pwm_motor: ");
     Serial.println(out_motor);
     Serial.println("");
     Serial.println("");
   //----------------------------------
 //-------------------------------------
}
