// UART functions for SDCC by Chin-Shiuh Shieh on 2011-04-04
// uart_initialize() should be called before using UART
// No syntax error handling
// Comment un-used functions to reduce code size

// UART function prototypes
void uart_initialize(void);	// Set UART Baud Rate to 9600 bps
void uart_put_char(char c);	// Put Character to UART
char uart_get_char(void);	// Get Character from UART
char uart_get_char_echo(void);	// Get Character from UART with Echo, Require uart_put_char()
void uart_put_string(char *s);	// Put String to UART, Require uart_put_char()
void uart_get_string(char *s);	// Get String from UART, Require uart_get_char_echo()
void uart_i2s(int i,char *s);	// Convert Integer to String
int  uart_s2i(char *s);		// Convert String to Integer
void uart_put_integer(int i);	// Put Integer to UART, Require uart_i2s(),uart_put_string()
int  uart_get_integer();	// Get Integer from UART, Require uart_get_string(),uart_s2i()
void uart_put_byte(unsigned char byte_data);
void uart_put_word(unsigned int word_data);
char uart_get_nibble();
unsigned char uart_get_byte();
unsigned int uart_get_word();
__code char uart_ASCII[]="0123456789ABCDEF";

void uart_initialize(void)
{
PCON&=0x7F;		// Clear SMOD of PCON, No Double Baud Rate
TMOD&=0x2F;TMOD|=0x20;	// Set Timer1 to Mode 2 (8-bit auto reload) for Baud Rate Generation
TH1=0xFD;		// Set Baud Rate to 9600 bps for 11.0592M Hz
SM0=0;SM1=1;		// Set UART to Mode 1 (8-bit UART)
REN=1;			// Set REN of SCON to Enable UART Receive
TR1=1;			// Set TR1 of TCON to Start Timer1
TI=0;RI=0;		// Clear TI/RI of SCON to Get Ready to Send/Receive
}

void uart_put_char(char c)	// Put Character to UART
{
SBUF=c;
while(TI==0);TI=0;
}

char uart_get_char(void)	// Get Character from UART
{
while(RI==0);RI=0;
return SBUF;
}

char uart_get_char_echo(void)	// Get Character from UART with Echo, Require uart_put_char()
{
while(RI==0);RI=0;
uart_put_char(SBUF);
return SBUF;
}

void uart_put_string(char *s)	// Put String to UART, Require uart_put_char()
{
while(*s!=0){uart_put_char(*s);s++;}
}

void uart_get_string(char *s)	// Get String from UART, Require uart_get_char_echo()
{
while(((*s)=uart_get_char_echo())!=13)s++;
*s=0;
}

void uart_i2s(int i,char *s)	// Convert Integer to String
{
char sign;unsigned char len;char *p;
sign='+';len=0;p=s;
if(i<0){sign='-';i=-i;}
do{*s=(i%10)+'0';s++;len++;i/=10;}while(i!=0);
if(sign=='-'){*s='-';s++;len++;}
for(i=0;i<len/2;i++){p[len]=p[i];p[i]=p[len-1-i];p[len-1-i]=p[len];}
p[len]=0;
}

int uart_s2i(char *s)	// Convert String to Integer
{
int i=0;char sign='+';
if(*s=='-'){sign='-';s++;}
while(*s!=0){i=i*10+(*s-'0');s++;}
if(sign=='-')i=-i;
return i;
}

void uart_put_integer(int i)	// Put Integer to UART, Require uart_i2s(),uart_put_string()
{
char s[7];
uart_i2s(i,s);uart_put_string(s);
}

int uart_get_integer()		// Get Integer from UART, Require uart_get_string(),uart_s2i()
{
char s[7];
uart_get_string(s);
return uart_s2i(s);
}

void uart_put_byte(unsigned char byte_data)
{
uart_put_char(uart_ASCII[byte_data/16]);uart_put_char(uart_ASCII[byte_data%16]);
}

void uart_put_word(unsigned int word_data)
{
uart_put_byte(word_data/256);uart_put_byte(word_data%256);
}

char uart_get_nibble()
{
char c;
c=uart_get_char_echo();
if('0'<=c && c<='9')return(c-'0');
if('A'<=c && c<='F')return(10+c-'A');
if('a'<=c && c<='f')return(10+c-'a');
return(0);
}

unsigned char uart_get_byte()
{
return(16*uart_get_nibble()+uart_get_nibble());
}

unsigned int uart_get_word()
{
return(256*uart_get_byte()+uart_get_byte());
}
