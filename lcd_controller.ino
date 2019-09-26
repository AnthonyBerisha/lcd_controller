#define RS  4
#define RW  9
#define E   6
#define D7  13
#define D6  12
#define D5  11
#define D4  10

void strobe(void)
{
  digitalWrite(E, HIGH);
  digitalWrite(E, LOW);
}

void lcd_write(byte c)
{
  if (c & 0x80) digitalWrite(D7, HIGH); else  digitalWrite(D7, LOW);
  if (c & 0x40) digitalWrite(D6, HIGH); else  digitalWrite(D6, LOW);
  if (c & 0x20) digitalWrite(D5, HIGH); else  digitalWrite(D5, LOW);
  if (c & 0x10) digitalWrite(D4, HIGH); else  digitalWrite(D4, LOW);
  strobe();
  if (c & 0x08) digitalWrite(D7, HIGH); else  digitalWrite(D7, LOW);
  if (c & 0x04) digitalWrite(D6, HIGH); else  digitalWrite(D6, LOW);
  if (c & 0x02) digitalWrite(D5, HIGH); else  digitalWrite(D5, LOW);
  if (c & 0x01) digitalWrite(D4, HIGH); else  digitalWrite(D4, LOW);
  strobe();
  delayMicroseconds(40);
}

void lcd_init(void)
{
  pinMode(RS, OUTPUT);
  pinMode(E , OUTPUT);
  pinMode(D7, OUTPUT);
  pinMode(D6, OUTPUT);
  pinMode(D5, OUTPUT);
  pinMode(D4, OUTPUT);

  digitalWrite(RS, LOW);
  delay(15);

  digitalWrite(D4, HIGH);
  digitalWrite(D5, HIGH);
  strobe();
  delay(5);
  strobe();
  delayMicroseconds(100);

  strobe();
  delay(5);

  lcd_write(0x28);
  lcd_write(0x0c);
  lcd_write(0x06);
  lcd_write(0x01);
}


void setup() 
{
  // put your setup code here, to run once:
  lcd_init();
}

void loop()
{
  
}
