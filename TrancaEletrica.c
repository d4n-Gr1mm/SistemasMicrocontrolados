// LCD module connections
sbit LCD_RS at RA0_bit;
sbit LCD_EN at RA1_bit;
sbit LCD_D4 at RA2_bit;
sbit LCD_D5 at RA3_bit;
sbit LCD_D6 at RA4_bit;
sbit LCD_D7 at RA5_bit;

sbit LCD_RS_Direction at TRISA0_bit;
sbit LCD_EN_Direction at TRISA1_bit;
sbit LCD_D4_Direction at TRISA2_bit;
sbit LCD_D5_Direction at TRISA3_bit;
sbit LCD_D6_Direction at TRISA4_bit;
sbit LCD_D7_Direction at TRISA5_bit;
// End LCD module connections

// Keypad module connections
char  keypadPort at PORTD;
// End Keypad module connections

//LED definitions

#define led1a   RE0_bit
#define led1b   RE1_bit
#define led2a   RC0_bit
#define led2b   RC1_bit
#define led3a   RC2_bit
#define led3b   RC3_bit
#define led4a   RC4_bit
#define led4b   RC5_bit
#define led5a   RC6_bit
#define led5b   RC7_bit
#define led6a   RB0_bit
#define led6b   RB1_bit
#define led7a   RB2_bit
#define led7b   RB3_bit
#define led8a   RB4_bit
#define led8b   RB5_bit
#define led9a   RB6_bit
#define led9b   RB7_bit

//end of LED definitions

char player;

void interpretadorKP(char kp){
	if(kp){
		if(kp % 4 == 0 || kp == 13 || kp == 15 || kp == 14){
			/*não faz nada pois estes valores
			não estão presentes no teclado ou não são usados. 
			*/
        }
		else{
			switch(kp){
				case 1: kp = 49; break; //1
				case 2: kp = 50; break; //2
				case 3: kp = 51; break; //3
				case 5: kp = 52; break; //4
				case 6: kp = 53; break; //5
				case 7: kp = 54; break; //6
				case 9: kp = 55; break; //7
				case 10: kp = 56; break;//8
				case 11: kp = 57; break;//9
				case 14: kp = 48; break;//0
			}
			if(kp == 49){
				if(player == 1 && led1a==0 && led1b==0){
					led1a = 1;
					player = 2;
				}
				else if(player == 2 && led1a==0 && led1b==0){
					led1b = 1;
					player = 1;
				}
				else{
					Lcd_Out(1, 1, "Jogada incorreta");
				}
			}
			else if(kp == 50){
				if(player == 1 && led2a==0 && led2b==0){
					led2a = 1;
					player = 2;
				}
				else if(player == 2 && led2a==0 && led2b==0){
					led2b = 1;
					player = 1;
				}
				else{
					Lcd_Out(1, 1, "Jogada incorreta");
				}
			}
			else if(kp == 51){
				if(player == 1 && led3a==0 && led3b==0){
					led3a = 1;
					player = 2;
				}
				else if(player == 2 && led3a==0 && led3b==0){
					led3b = 1;
					player = 1;
				}
				else{
					Lcd_Out(1, 1, "Jogada incorreta");
				}
			}
			else if(kp == 52){
				if(player == 1 && led4a==0 && led4b==0){
					led4a = 1;
					player = 2;
				}
				else if(player == 2 && led4a==0 && led4b==0){
					led4b = 1;
					player = 1;
				}
				else{
					Lcd_Out(1, 1, "Jogada incorreta");
				}
			}
			else if(kp == 53){
				if(player == 1 && led5a==0 && led5b==0){
					led5a = 1;
					player = 2;
				}
				else if(player == 2 && led5a==0 && led5b==0){
					led5b = 1;
					player = 1;
				}
				else{
					Lcd_Out(1, 1, "Jogada incorreta");
				}
			}
			else if(kp == 54){
				if(player == 1 && led6a==0 && led6b==0){
					led6a = 1;
					player = 2;
				}
				else if(player == 2 && led6a==0 && led6b==0){
					led6b = 1;
					player = 1;
				}
				else{
					Lcd_Out(1, 1, "Jogada incorreta");
				}
			}
			else if(kp == 55){
				if(player == 1 && led7a==0 && led7b==0){
					led7a = 1;
					player = 2;
				}
				else if(player == 2 && led7a==0 && led7b==0){
					led7b = 1;
					player = 1;
				}
				else{
					Lcd_Out(1, 1, "Jogada incorreta");
				}
			}
			else if(kp == 56){
				if(player == 1 && led8a==0 && led8b==0){
					led8a = 1;
					player = 2;
				}
				else if(player == 2 && led8a==0 && led8b==0){
					led8b = 1;
					player = 1;
				}
				else{
					Lcd_Out(1, 1, "Jogada incorreta");
				}
			}
			else if(kp == 57){
				if(player == 1 && led9a==0 && led9b==0){
					led9a = 1;
					player = 2;
				}
				else if(player == 2 && led9a==0 && led9b==0){
					led9b = 1;
					player = 1;
				}
				else{
					Lcd_Out(1, 1, "Jogada incorreta");
				}
			}
			else Lcd_Out(1, 1, "Algo errado na leitura");
		}
	}
}

void main(){
	
	char kp;
	ADCON1=0x06;
	TRISA=0;
	TRISC=0;
	TRISE=0;
	PORTE=0;
	PORTC=0;
	Keypad_Init();
	Lcd_Init();
    Lcd_Cmd(_LCD_CLEAR);
    Lcd_Cmd(_LCD_CURSOR_OFF);
	
	Lcd_Out(1, 1, "Key  :");
	Lcd_Out(2, 1, "Times:");
	
	player = 1;
	
	while(1){
		kp = Keypad_Key_Click();
		interpretadorKP(kp);
	}
	
}