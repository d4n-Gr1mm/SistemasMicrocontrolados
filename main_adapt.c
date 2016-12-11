
//LCD
sbit LCD_RS at RC4_bit;
sbit LCD_EN at RC5_bit;
sbit LCD_D4 at RC0_bit;
sbit LCD_D5 at RC1_bit;
sbit LCD_D6 at RC2_bit;
sbit LCD_D7 at RC3_bit;
sbit LCD_RS_Direction at TRISC4_bit;
sbit LCD_EN_Direction at TRISC5_bit;
sbit LCD_D4_Direction at TRISC0_bit;
sbit LCD_D5_Direction at TRISC1_bit;
sbit LCD_D6_Direction at TRISC2_bit;
sbit LCD_D7_Direction at TRISC3_bit;

int botao = 0;
char keypadPort at PORTD;
char cliques = 0;
char tentativas = 0;
char *senha = "000000";
char *textos[6] = {"      Senha OK      ",
                   "    Senha Errada    ",
                   "   Nova Senha OK    ",
                   "   Digite a senha   ",
                   " Digite a nova senha",
                   "         Fim        "};

char *Ptr1, *Ptr2;

char CompararSenha(){
	char i;
	for(i=0; i < 6; i++){
		if(senha[i] != Eeprom_Read(i)) return(0);
	}
	return(1);
}

void GravarSenhaNaEeprom(){
	char i;
	for(i=0; i < 6; i++) Eeprom_Write(i, senha[i]);
}

void LimparSenha(){
	char i;
	for(i=0; i < 6; i++) senha[i] = '0';
}

void doDaMagic(char kp){
	//ESTA BELEZINHA AQUI LÊ O TECLADO E FAZ TODA A LÓGICA (A MÁGICA)
    if(kp){
		if(kp == 0 || kp == 8){
			  /*não faz nada pois estes valores
			  não estão presentes no teclado. (não, não são
			  as teclas 4 e 8, caso tenha cogitado)
			  */
		}
		else if(kp == 4){		//AQUI JACQUE... 
			Ptr1 = textos[4];
			botao = 1;
		}
		else if(kp == 13){
			 LimpaSenha();
			 cliques = 0;
		}
		else if(kp == 15){
			cliques = 0;
			if(PORTB.F7 == 1){
				if(botao == 1){
					GravarSenhaNaEeprom();
					Ptr1 = textos[2];
					LimparSenha();
				}
				else{
					if(CompararSenha()){
						PORTB.F0 = ~PORTB.F0;	//abre a porra da tranca
						Ptr1 = textos[0];
						LimparSenha();
					}
					else{
						tentativas++;
						Ptr1 = textos[1];
						LimparSenha();
					}
				}
			}
			else{
				GravarSenhaNaEeprom();
				Ptr1 = textos[2];
				LimparSenha();
			}
			Lcd_Out(1, 1, Ptr1);
			Delay_ms(2000);
			botao = 0;
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
			if(cliques < 6){    		//Aqui, a lógica é sempre guardar os 6 ultimos valores digitados e foda-se sua opinião
				for(i=0; i < 5; i++){
					senha[i] = senha[i+1];
				}
				senha[5] = kp;
			}
		}
	}
	else{
		if(PORTB.F7) Ptr2 = textos[3];
		else{
			Ptr1 = textos[4];
			botao = 1;
		}
	}
}

void checa_botao(int bt){
	if(bt == 1) Lcd_Out(1,1, Ptr1);
	else Lcd_Out(1,1, Ptr2);
}


void main(){
    
	char kp;
    TRISB = 0b10000000;
    PORTB=0;
    Keypad_Init();
    Lcd_Init();
    Lcd_Cmd(_LCD_CLEAR);
    Lcd_Cmd(_LCD_CURSOR_OFF);
    Ptr2 = textos[3];          //INICIALIZAR DISPLAY COM "DIGITE A SENHA"
    Lcd_Out(1, 1, Ptr2);
     
    while(true){

		if(tentativas < 3){
			kp = Keypad_Key_Click();
			doDaMagic(kp);
		}
		else{
			Ptr2 = textos[5];
			PORTB.F1 = 1;
		}
		
		checa_botao(botao); 	//CHECA O ESTADO DO BOTAO PARA, SE ELE TIVER SIDO PRESSIONADO (E SOLTO),
								//EXECUTE UM RESET DA SENHA MEMO ASSIM.
		Lcd_Out(2,8, senha);
		Delay_ms(100);
	}
}