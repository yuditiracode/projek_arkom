
//  WIRING (sesuaikan dengan koneksi PCB kamu):
//  Sensor IR (output LOW = deteksi garis hitam):
//    Sensor Kiri-Luar  -> PIN A0
//    Sensor Kiri-Dalam -> PIN A1
//    Sensor Kanan-Dalam-> PIN A2
//    Sensor Kanan-Luar -> PIN A3
//
//  L293D Motor Driver:
//    IN1 (Motor Kiri Forward)  -> PIN 2
//    IN2 (Motor Kiri Backward) -> PIN 3
//    IN3 (Motor Kanan Forward) -> PIN 4
//    IN4 (Motor Kanan Backward)-> PIN 5
//    ENA (Enable Motor Kiri)   -> PIN 9  (PWM)
//    ENB (Enable Motor Kanan)  -> PIN 10 (PWM)

#define SENSOR_KL  A0  
#define SENSOR_KD  A1  
#define SENSOR_KND A2  
#define SENSOR_KNL A3 
#define IN1  2
#define IN2  3
#define IN3  4
#define IN4  5
#define ENA  9   
#define ENB  10  
#define THRESHOLD    500  
#define SPEED_NORMAL 180  
#define SPEED_BELOK  130  
#define SPEED_TAJAM  60   
bool sensorKL, sensorKD, sensorKND, sensorKNL;

void setup() {
  Serial.begin(9600);

  // Motor pins
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);

  berhenti();
  delay(1000);
  Serial.println("Lane Follower Siap!");
}

void loop() {
  bacaSensor();
  cetakDebug();
  ikutiGaris();
}

void bacaSensor() {
  sensorKL  = (analogRead(SENSOR_KL)  < THRESHOLD);  // true = deteksi garis
  sensorKD  = (analogRead(SENSOR_KD)  < THRESHOLD);
  sensorKND = (analogRead(SENSOR_KND) < THRESHOLD);
  sensorKNL = (analogRead(SENSOR_KNL) < THRESHOLD);
}


void ikutiGaris() {
  // Berhenti di persimpangan / ujung track
  if (sensorKL && sensorKD && sensorKND && sensorKNL) {
    berhenti();
    return;
  }

  // Lurus sempurna
  if (!sensorKL && sensorKD && sensorKND && !sensorKNL) {
    maju(SPEED_NORMAL, SPEED_NORMAL);
  }
  // Tidak ada sensor aktif (keluar garis), lanjut maju
  else if (!sensorKL && !sensorKD && !sensorKND && !sensorKNL) {
    maju(SPEED_NORMAL, SPEED_NORMAL);
  }
  // Belok kiri halus (hanya sensor kiri dalam aktif)
  else if (!sensorKL && sensorKD && !sensorKND && !sensorKNL) {
    maju(SPEED_BELOK, SPEED_NORMAL);
  }
  // Belok kiri tajam
  else if (sensorKL && sensorKD && !sensorKND && !sensorKNL) {
    maju(SPEED_TAJAM, SPEED_NORMAL);
  }
  // Belok kiri sangat tajam
  else if (sensorKL && !sensorKD && !sensorKND && !sensorKNL) {
    maju(0, SPEED_NORMAL);
  }
  // Belok kanan halus (hanya sensor kanan dalam aktif)
  else if (!sensorKL && !sensorKD && sensorKND && !sensorKNL) {
    maju(SPEED_NORMAL, SPEED_BELOK);
  }
  // Belok kanan tajam
  else if (!sensorKL && !sensorKD && sensorKND && sensorKNL) {
    maju(SPEED_NORMAL, SPEED_TAJAM);
  }
  // Belok kanan sangat tajam
  else if (!sensorKL && !sensorKD && !sensorKND && sensorKNL) {
    maju(SPEED_NORMAL, 0);
  }
  // Default: maju
  else {
    maju(SPEED_NORMAL, SPEED_NORMAL);
  }
}

void maju(int kecepatanKiri, int kecepatanKanan) {
  // Motor Kiri maju
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, kecepatanKiri);

  // Motor Kanan maju
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, kecepatanKanan);
}

// Mundur
void mundur(int kecepatanKiri, int kecepatanKanan) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, kecepatanKiri);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  analogWrite(ENB, kecepatanKanan);
}

// Berhenti total
void berhenti() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}

void cetakDebug() {
  Serial.print("KL:");  Serial.print(sensorKL);
  Serial.print(" KD:"); Serial.print(sensorKD);
  Serial.print(" KND:");Serial.print(sensorKND);
  Serial.print(" KNL:");Serial.println(sensorKNL);
}
