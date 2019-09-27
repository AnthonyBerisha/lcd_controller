#define RS    4
#define RW    9
#define E     6
#define D7    13
#define D6    12
#define D5    11
#define D4    10
#define BUFF  24

int strlen(char *s)
{
  int i = 0;
  while (s[i])
    s[i++];
  return (i);
}

void strobe(void)
{
  digitalWrite(E, HIGH);
  digitalWrite(E, LOW);
}

// This function receives a byte of data
// It then sets or resets the corresponding bits and sends them to the display
void send_byte(byte c)
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

// This initializes the display in 4-bit mode
void lcd_init(void)
{
  pinMode(RS, OUTPUT);
  pinMode(RW, INPUT);
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
  // 4-bit mode
  send_byte(0x28);
  send_byte(0x0c);
  send_byte(0x06);
  send_byte(0x01);
}



// Takes a string as an argument and sends each byte of each char of the string to the display
void lcd_puts(const char * s)
{
  digitalWrite(RS,HIGH);
  if (strlen(s) > 16)
  {
    int i = 0;
    while (i < 16)                   // Write text until the end of the display
    { 

        send_byte(s[i]);
        i++;
    }
    int x = 0;
    while (x < BUFF)                 // Add the spaces to fill the buffer
    {
      send_byte(' ');
      x++;
    }
    if (s[i] == ' ')i++;             // Get rid of the beginning space if at the cut
    while(s[i])send_byte(s[i++]);    // Write the rest of the text
  }
  else
    while(*s)send_byte(*s++);
}

// Takes a char as an argument and sends the corresponding byte of the passed char
void lcd_putc(const char c)
{
  digitalWrite(RS,HIGH);      // write character
  if (c == '\n')  
  {
    for (int i = 0; i < 24; i++)
      send_byte(' ');
  }
  else
    send_byte(c);
}

void setup() 
{
  Serial.begin(9600);
  while (! Serial);
  lcd_init();
}

//* Instruction set *//

// clear instruction
void iclear()
{
  digitalWrite(RS, LOW);
  send_byte(0x01);
}


void loop()
{ 
  lcd_puts("0123456789ABDCE F je suis un pd");
  Serial.print("op: ");
  Serial.println(digitalRead(RW));
  delay(1000);
  iclear();
  delay(1000);
  
}
