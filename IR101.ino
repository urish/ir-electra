#include <IRremote.h>

// #define RECV

IRrecv irrecv(A0);

unsigned int turnon[] = {3150,3750,1950,1850,2000,1850,1050,900,1950,900,1050,850,1050,900,1050,850,1050,1900,1050,900,1950,900,1050,900,1050,850,1100,900,1050,850,1100,900,1050,850,1100,850,1050,900,1050,900,1050,900,1050,900,1050,900,1050,900,1050,850,1050,900,1100,850,1050,900,1050,1900,1950,900,3100,3800,2000,1850,1950,1850,1050,900,1950,850,1050,900,1050,900,1050,900,1050,1850,1100,850,1950,900,1050,900,1050,850,1050,900,1050,900,1050,850,1050,900,1050,900,1050,850,1050,900,1050,900,1050,850,1050,900,1050,900,1050,850,1050,900,1050,900,1050,850,1050,1850,2000,900,3100,3800,1950,1850,2000,1850,1050,900,1950,900,1050,850,1050,900,1050,900,1050,1850,1100,850,1950,900,1050,900,1050,850,1050,900,1050,900,1050,850,1050,900,1050,900,1050,850,1100,850,1050,900,1050,900,1050,850,1050,900,1050,900,1050,850,1050,900,1050,900,1050,1850,2000,850,4100};

void setup()
{
  Serial.begin(115200);
  pinMode(13, OUTPUT);
  irrecv.enableIRIn(); // Start the receiver
}

void dump(decode_results *results) {
  int count = results->rawlen;
  for (int i = 1; i < results->rawlen; i++) {
    if (i > 1) {
	    Serial.write(',');
	}
    Serial.print(results->rawbuf[i]*USECPERTICK, DEC);
  }
  Serial.println();
}

void recvloop() {
  decode_results results;

  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    dump(&results);
    irrecv.resume(); // Receive the next value
  }
}

int blink = 0;

void sendloop() {
  IRsend irsend;
  irsend.sendRaw(turnon,sizeof(turnon) / sizeof(turnon[0]),38);
  blink = !blink;
  digitalWrite(13, blink);
  delay(1000);
}

void loop() {
  #ifdef RECV
    recvloop(); 
  #else
    sendloop();
  #endif   
}

