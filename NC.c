/*
 * This is a number convert program
 * */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<getopt.h>
#include<ctype.h>
#include<errno.h>
#include<limits.h>

/*short name of some types of integer*/
#define u8   char
#define u16  unsigned short
#define u32  unsigned int
#define u64  unsigned long long
#define s16  short
#define s32  int
#define s64  long long

/*some limit number definition*/
#define MAX16  0x7FFF
#define MIN16  0x8000
#define MAX32  0x7FFFFFFFL
#define MIN32  0x80000000L

/*bit set marco*/
#define SET_BIT(x,n) ( (x) |= (1<<(n)) )
#define GET_BIT(x,n) ( ((x)>>(n)) & 1 )
#define CLR_BIT(x,n) ( (x) &= ~(1<<(n)) )

/*some ascii value*/
#define ASCII_0_VALUE  48
#define ASCII_9_VALUE  57
#define ASCII_A_VALUE  65
#define ASCII_F_VALUE  70

#define MAP_LEN  15
#define HEX_LEN  16
#define OCT_LEN  21
#define BIN_LEN  64

/*sign bits get &set*/
#define SignBit(x) \
		(((signed char *)&(x))[sizeof(x) -1] >> 7)
#define SetSignBit(x,s)\
		(((signed char *)&(x))[sizeof(x) -1] ^= (s<<7))

#define BIT_SET(A, B) A |= (B)
#define BIT_ON(A,B) (((A) &(B)) != 0)

/*bit map for saving the flag of command parameter*/
char bit_map[MAP_LEN]; 
//int bit_map = 8;

/*use to save the result*/
typedef struct number{
	u16  b_ushortHave;
	u16  b_uintHave;
	u16  b_ulongHave;
	u16  b_sshortHave;
	u16  b_sintHave;
	u16  b_slongHave;
	u16  uShortNumber;
	u32  uIntNumber;
	u64  uLongNumber;
	s16  sShortNumber;
	s32  sIntNumber;
	s64  sLongNumber;
}ResultNum;

typedef enum flags{
	  SHOW_ALL = 1,
	  SHOW_USIGN,
	  SHOW_SSIGN,
	  SHOW_HEX,
	  SHOW_OCT,
	  SHOW_HELP,
	  SHOW_MAX=7,
}SetFlags;

enum guess {MDec,MHex,MBin, BNum};

/*global variable for save result*/
ResultNum g_res = {
	.b_ushortHave = 0,
    .b_uintHave = 0,
    .b_ulongHave = 0,
    .b_sshortHave = 0,
    .b_sintHave = 0,
    .b_slongHave = 0,
};

/*some functions difition*/
void HexConvert(char *, int);

void show_help(void)
{
	printf("Usages: NC [flag] [number]\n");
	printf("number should end with [b|h|o|d]\n");
	printf("a\t\tshow all convert type[default]\n");
	printf("u\t\tshow unsigned decimal value converted from number\n");
	printf("d\t\tshow signed decimal value conveted frome number\n");
	printf("h\t\tshow the hex format of the number\n");
	printf("o\t\tshow the octet format of the number\n");
	printf("H\t\tshow the help info\n");
}


int mystrtol(char *p, int base)
{
		char *endptr;
		int  val;
		
		errno = 0;
		val = strtol(p,&endptr,base);

		if((errno == ERANGE && (val == LONG_MIN || val == LONG_MAX)) 
						|| (errno != 0 && val == 0))
		{
				perror("strtol");
				exit(EXIT_FAILURE);
		}
		
		if(p == endptr)
		{
			fprintf(stderr,"No digit wae found\n");
			exit(EXIT_FAILURE);
		}

		return val;
}

void Print(int number)
{
	if(number == SHOW_ALL || number == SHOW_USIGN)
	{
		printf("Unsigned short: %d\n",g_res.uShortNumber);
		printf("Unsigned int:   %d\n",g_res.uIntNumber);
	}
	if(number == SHOW_ALL || number == SHOW_SSIGN)
	{
		printf("Signed short: %d\n",g_res.sShortNumber);
		printf("Signed int:   %d\n",g_res.sIntNumber);
	}
	if(number == SHOW_ALL || number == SHOW_HEX)
	{
		printf("16bit Hex with sign:    %x\n",g_res.sShortNumber);
		printf("16bit Hex without sign: %x\n",g_res.uShortNumber);
		printf("32bit Hex:              %x\n",g_res.sIntNumber);
	}

	if(number == SHOW_ALL || number == SHOW_OCT)
	{
		printf("16bit OCT:    %x\n",g_res.sShortNumber);
		printf("32bit OCT:    %x\n",g_res.sIntNumber);
	}
}


void PrintAssume(u16 flag)
{

}


void ResultSet(int result)
{

	g_res.b_ushortHave = 1;
	g_res.uShortNumber = (unsigned short)result;
	g_res.b_uintHave = 1;
	g_res.uIntNumber = (unsigned int)result;
	g_res.b_sshortHave = 1;
	g_res.sShortNumber = (short)result;
	g_res.b_sintHave = 1;
	g_res.sIntNumber = result;

}


void DecConvert(char *raw, int len)
{
	int result = 0;
	char *p;

	p = raw;
	p[len - 1] = '\0';

	result = mystrtol(p,10);

	ResultSet(result);

}


void OctConvert(char *raw, int len)
{
	int result = 0;
	char *p;

	if(raw[0] == '0' && (raw[1] >= '0' && raw[1] <= '7'))
	{
		p = &raw[1];
	}else
	{
		p = raw;
		p[len - 1] = '\0';
	}
    
	result = mystrtol(p,8);
	
	ResultSet(result);

	printf("%d\n",g_res.uShortNumber);
	printf("%d\n",g_res.sShortNumber);

}

void BinConvert(char *raw, int len)
{
	int result = 0;
	char *p;

	p = raw;
	p[len -1] = '\0';

	result = mystrtol(p,2);

	ResultSet(result);
		
	printf("%#x\n",g_res.sIntNumber);
	printf("%#x\n",g_res.uIntNumber);


}

u16 Make_Assume(char *raw,int len)
{
	u16  MayHex = 0;
	u16  MayBin = 0;
	u16  BadNumber = 0;
	u16  ZoO_Num = 0;
	char ch;
	char *p;

	p = raw;

	while(ch = *p)
	{
		/*only if this number has the A-F or a-f character
		 * ,we can assume it is a hex*/
		if((ch >= 'A' && ch <= 'F') || (ch >= 'a' && ch <= 'f'))
		{	
			MayHex = MHex;
		}
		if((ch >= '0' && ch <= '1'))
		{
			ZoO_Num++;
		}

		if(ch >= 'F' || ch >= 'f')
		{
			BadNumber = BNum;
		}

		++p;
	}

	/*only all of the number have the 0 or 1 number
	 * that we can assume this number is a binary number*/
	if(ZoO_Num == len)
			MayBin = MBin;

	if(MayHex == MHex){
			HexConvert(raw,len);
			return MayHex;
	}else if(MayBin == MBin){
			BinConvert(raw,len);
			return MayBin;
	}else if(BadNumber == BNum){
			return BadNumber;
	}else{
			DecConvert(raw,len);
			return MDec;
	}

}


/*
 * if the argument has no sign flag,like:
 * 'b'/'h'/'0'/'d' so i will make a assume of
 * that
 * 
 * */
u16 AssumeConvert(char *raw, int len)
{
	 int result = 0;
 	 u16 guessRes = 0;
	 
	 /*because of the raw have no prefix or suffix, 
	  * so just need to travel p, test whether it has
	  * the some special character*/
	 guessRes = Make_Assume(raw,len);
	 
	 switch(guessRes)
	 {
			case MDec:
				printf("The %s is treated as Decimal number\n",raw);
				break;
			case MHex:
				printf("The %s is treated as Hexium number\n",raw);
				break;
			case MBin:
				printf("The %s is treated as Binary number\n",raw);
				break;
			case BNum:
				printf("The %s is a bad number, Please check it again\n",raw);
				break;
	 }

	 return guessRes;
}



void HexConvert(char *raw, int len)
{
	 int  result = 0;
	 int  temp;
	 s16  shortTemp;
	 u16  NumberLen;
	 s16  sign_flag =0;
	 char *p;
	 char ch;

	 /*judgement the prefix*/
	 if(raw[0] == '0' && (raw[1] == 'x'|| raw[1] == 'X')){
		  p = &(raw[2]);
		  NumberLen = len - 2; /*minus the prefix's length*/
	 }else if(raw[len - 1] == 'h'){
		  p = raw;
		  p[len-1] = '\0'; /*remove the number signed(h)*/
		  NumberLen = len - 1; /*remove the length of number signed*/
	 }else{
	 	  p = raw;
		  NumberLen = len;
	 }
	
	/*convert hex to decimal*/
	while(ch = *p)
	{
		ch = toupper(ch);
		result <<= 4;

		if(ch >= ASCII_0_VALUE && ch <= ASCII_9_VALUE)
			temp = ch - ASCII_0_VALUE;
		else if(ch >= ASCII_A_VALUE && ch <= ASCII_F_VALUE)
			temp = ch - ASCII_A_VALUE + 10;
		else{
			fprintf(stderr,"Unkonw hex token %c, drop it!\n",*p);
			break;
		}
		
		result += temp;
		++p;	
	}
	


	/*if the result is 16bit, it will be converted to 
	 * singned number, e.g.  0x8765 ==> -30875*/
	if(NumberLen < 5)
	{
		shortTemp = (short)result;
    	sign_flag = SignBit(shortTemp);
		g_res.b_sshortHave = 1;
		if(sign_flag == -1){
			g_res.sShortNumber = (short)result - 1;
			g_res.sShortNumber = ~g_res.sShortNumber;	
			SetSignBit(g_res.sShortNumber,0);
			if(sign_flag == -1)
				g_res.sShortNumber *= -1;
		}else{
			   g_res.sShortNumber = (short)result;
		}	   
		g_res.b_ushortHave = 1;
		g_res.uShortNumber =(u16)result; /*the type convert is must*/
	}else{
		sign_flag = SignBit(g_res.sIntNumber);
		g_res.b_sintHave= 1;
		if(sign_flag == -1){
			g_res.sIntNumber = result - 1;
			g_res.sIntNumber = ~g_res.sIntNumber;
			SetSignBit(g_res.sIntNumber,0);
			if(sign_flag == -1)
			 	 g_res.sIntNumber *= -1;
		}else{
			g_res.sIntNumber = result;
		}
		g_res.b_uintHave = 1;
		g_res.uIntNumber = (u32)result;  /*the type convert is must */
	}	


}



int ConvertNumber(char *raw, int len)
{
	int ch;	
	int ret = 0;
	ch = raw[len-1];

	switch(ch)
	{
		case 'd':
			/*decimal number, so it should be converted
			 *to hex/binary/octet/unsigned
			*/
			DecConvert(raw,len);
			break;
		case 'h':
			/*hex number, so it should be converted to 
			 * decimal/signed/unsigned/binary/octet etc*/
			HexConvert(raw,len);
			break;
		case 'o':
			/*octet number, so it should be converted to 
			 * signed/unsigned/binary/octet etc.*/
			OctConvert(raw,len);
			break;
		case 'b':
			/*binary number. so it should be converted to
			 * signde/unsigned/hex/octet etc.*/
			BinConvert(raw,len);
			break;
		default:
			if(raw[0] == '0' && (raw[1] == 'x'|| raw[1] == 'X'))
					HexConvert(raw,len);
			else if(raw[0] == '0' && (raw[1] < '8'))
					OctConvert(raw,len);
			else{
				fprintf(stderr,"Unkonw character for number! act the default option!\n");
				ret = 1;
			}
			break;
	}

	return ret;
}


void ShowResult(char * bitmap, char *Rnumber, int len)
{
	int i = 0;
	int isassume = 0;
	u16  index, val;

	isassume = ConvertNumber(Rnumber,len);
	
	if(isassume == 0)
	{
		printf("Convert complete!\n");
		printf("===== The result =====\n");
		for( i = 1;i < 8;i++)
		{
			index = i >> 3;
			val = i & 7;
			if(GET_BIT(bit_map[index],val) == 1)
			{
				Print(i);
			}
		}
	}else{
		printf("Convert complete! but the result is assumed\n");
	    PrintAssume(AssumeConvert(Rnumber,len));
	}
}


int main(int argc, char **argv)
{
	s32  ch;   /*save getopt's return value*/
	char *raw = NULL;/*save the optarg*/
	u16  index,val,flag; /*index and value of bit_map*/
	
	
	if(argc < 2)
	{
		show_help();
		exit(1);
	}

	while((ch = getopt(argc,argv,"audhoH")) != -1)
	{
		switch(ch)
		{
			case 'a':
				flag = SHOW_ALL;
				break;
			case 'u':
				flag = SHOW_USIGN;
				break;
			case 'd':
				flag = SHOW_SSIGN;
				break;
			case 'h':
				flag = SHOW_HEX;
				break;
			case 'o':
				flag = SHOW_OCT;
				break;
			case 'H':
				flag = SHOW_HELP;
				break;
			default:
				flag = SHOW_MAX;
				break;						
		}
	    if(flag != SHOW_MAX)
		{
			index = flag >> 3;
			val = flag & 7;
			SET_BIT(bit_map[index],val);

		}else{
			show_help();
			exit(1);
		}
	}

	ShowResult(bit_map, argv[argc-1], strlen(argv[argc-1]));
}

