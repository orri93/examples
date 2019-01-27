#define SERIAL_BAUD         115200

#define MESSAGE_SIZE            64

#define REPEATE              10000

byte b;
unsigned char uc;
uint8_t ui8;
float f;
double d;

struct Data1 {
  byte b;
  unsigned char ug;
  uint8_t ui8;
  float f;
  double d;
} data1;

struct Data2 {
  uint8_t ui81;
  uint16_t ui161;
  float f1;
  uint8_t ui82;
  float f2;
  uint8_t ui83;
  float f3;
  uint16_t ui162;
} data2;

struct Data3 {
  uint8_t ui81;
  uint16_t ui161;
  float f1;
  uint8_t ui82;
  float f2;
  uint8_t ui83;
  float f3;
  uint16_t ui162;
} __attribute__((packed)) data3;

char message[MESSAGE_SIZE];

unsigned long long tick, next = 0;

void reportsizeof() {
  snprintf(
    message,
    MESSAGE_SIZE,
    "Size of byte is %u",
    sizeof(b));
  Serial.println(message);
  snprintf(
    message,
    MESSAGE_SIZE,
    "Size of float is %u",
    sizeof(f));
  Serial.println(message);
  snprintf(
    message,
    MESSAGE_SIZE,
    "Size of double is %u",
    sizeof(d));
  Serial.println(message);

  snprintf(
    message,
    MESSAGE_SIZE,
    "Size of data structure 1 is %u",
    sizeof(data1));
  Serial.println(message);

  snprintf(
    message,
    MESSAGE_SIZE,
    "Size of data structure 2 is %u",
    sizeof(struct Data2));
  Serial.println(message);
  snprintf(
    message,
    MESSAGE_SIZE,
    "Size of data structure variable 2 is %u",
    sizeof(data2));
  Serial.println(message);

  snprintf(
    message,
    MESSAGE_SIZE,
    "Size of data structure 3 is %u",
    sizeof(struct Data3));
  Serial.println(message);
  snprintf(
    message,
    MESSAGE_SIZE,
    "Size of data structure variable 3 is %u",
    sizeof(data3));
  Serial.println(message);

  snprintf(
    message,
    MESSAGE_SIZE,
    "Size of buffer is %u",
    sizeof(message));
  Serial.println(message);
}

void setup() {
  Serial.begin(SERIAL_BAUD);
  if(!Serial) {
    /* Wait for serial */
    delay(5);
  }
  reportsizeof();
}

void loop() {
#if REPEATE > 0
  tick = millis();
  if(tick > next) {
    reportsizeof();
    next = tick + REPEATE;
  }
#endif
}