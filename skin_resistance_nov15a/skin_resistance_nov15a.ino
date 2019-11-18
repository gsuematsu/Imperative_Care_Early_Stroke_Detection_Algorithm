#define PIN_READ A5
#define RESISTOR_1 560 // Resistance in kOhms
#define V_IN 3.3 // Voltage in Volts

double val;
double voltage; // Volts
double skinResist; // kOhms

void setup() {
  // put your setup code here, to run once:
  pinMode(PIN_READ, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  val = analogRead(PIN_READ);
  voltage = val * (3.3/1024);
  skinResist = RESISTOR_1 / (V_IN/voltage - 1);

  Serial.println(skinResist);
}
