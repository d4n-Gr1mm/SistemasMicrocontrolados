
//VERSION 2

unsigned short kp, kp_aux, oldstate = 99;
int ext = 0;
int duty_cicle = 0;
int number_of_digits = 0; //Porque o duty_cicle tem no max 3 digitos
char duty_aux[10];
char *string = "Duty: ";
int sentido = 0;



// Keypad module connections
char keypadPort at PORTD;
// End Keypad module connections
// LCD module connections
sbit LCD_RS at RB2_bit;
sbit LCD_EN at RB3_bit;
sbit LCD_D4 at RB4_bit;
sbit LCD_D5 at RB5_bit;
sbit LCD_D6 at RB6_bit;
sbit LCD_D7 at RB7_bit;

sbit LCD_RS_Direction at TRISB2_bit;
sbit LCD_EN_Direction at TRISB3_bit;
sbit LCD_D4_Direction at TRISB4_bit;
sbit LCD_D5_Direction at TRISB5_bit;
sbit LCD_D6_Direction at TRISB6_bit;
sbit LCD_D7_Direction at TRISB7_bit;
// End LCD module connections


void keypad_receive(){
        PORTC.F5=1;
        do
                //kp = Keypad_Key_Press(); // Store key code in kp variable
                kp = Keypad_Key_Click(); // Store key code in kp variable
        while (!kp);
        PORTC.F5=0;
        // Prepare value for output, transform key to it's ASCII value
        //No meu caso, nao tenho interesse em valores ASCII. Preferi converter com o WordToStr()
        switch (kp)
        {
                case 1:
                        //kp = 49;
                        kp_aux = 1;
                        number_of_digits++;  // para controlar o No. max de chars no duty_cicle
                        break; // 1
                case 2:
                        //kp = 50;
                        kp_aux = 2;
                        number_of_digits++;
                        break; // 2
                case 3:
                        //kp = 51;
                        kp_aux = 3;
                        number_of_digits++;
                        break; // 3
                //case 4: kp = 65; break; // A commented since 4th column is absent for 4*3 keypad
                case 5:
                        //kp = 52;
                        kp_aux = 4;
                        number_of_digits++;
                        break; // 4
                case 6:
                        //kp = 53;
                        kp_aux = 5;
                        number_of_digits++;
                        break; // 5
                case 7:
                        //kp = 54;
                        kp_aux = 6;
                        number_of_digits++;
                        break; // 6
                //case 8: kp = 66; break; // B commented since 4th column is absent for 4*3 keypad
                case 9:
                        //kp = 55;
                        kp_aux = 7;
                        number_of_digits++;
                        break; // 7
                case 10:
                        //kp = 56;
                        kp_aux = 8;
                        number_of_digits++;
                        break; // 8
                case 11:
                        //kp = 57;
                        kp_aux = 9;
                        number_of_digits++;
                        break; // 9
                //case 12: kp = 67; break; // C commented since 4th column is absent for 4*3 keypad
                case 13:
                        //kp = 42;
                        kp_aux = 10; //LIMPA
                        number_of_digits = 0;
                        break; // *
                case 14:
                        //kp = 48;
                        kp_aux = 0;
                        number_of_digits = number_of_digits; //nao muda
                        break; // 0
                case 15:
                        //kp = 35;
                        kp_aux = 11; //ENTER
                        number_of_digits = 0;
                        break; // #
                //case 16: kp = 68; break; // D
        }
}

void main(){
	int i;
	//cnt = 0; // Reset counter
	CMCON=0x07;
	ADCON1=0x06;
	TRISA = 0;
	PORTA = 0;
	TRISC = 0;
	TRISB = 0x03;
	PWM1_Init(2000);
	kp = 0;
	Keypad_Init(); // Initialize Keypad
	Lcd_Init(); // Initialize Lcd
	Lcd_Cmd(_LCD_CLEAR); // Clear display
	Lcd_Cmd(_LCD_CURSOR_OFF); // Cursor off
	Lcd_Out(1, 3, "MOTOR CONTROL");
	Lcd_Out(2, 2, "__Dan & Lobo__");
	delay_ms(1000);
	Lcd_Cmd(_LCD_CLEAR); // Clear displays
	delay_ms(20);
	Lcd_Out(1, 3, "### MENU ###");
	delay_ms(1000);
	//Lcd_Cmd(_LCD_CLEAR);
	//delay_ms(20);
	Lcd_Out(1, 1, "1. Clockwise");
	Lcd_Out(2, 1, "2. A_Clockwise");	
	do{
		//kp = Keypad_Key_Press(); // Store key code in kp variable
		kp = Keypad_Key_Click(); // Store key code in kp variable
		if(kp == 1 || kp == 2) ext = 1;
	}while (!ext);
	
	if(kp == 1){
		sentido = 1;
		kp = 0;			
		Lcd_Out(1, 1, "Clockwise set!");
		delay_ms(500);
		PORTA.F0 = 1;
	}
	else if(kp == 2){
		sentido = 2;
		kp = 0;
		Lcd_Out(1, 1, "A_Clockwise set!");
		delay_ms(1000);
		PORTA.F1 = 1;
	}
	else{}
	PWM1_Start();
	Lcd_Cmd(_LCD_CLEAR);
	Lcd_Out(1, 1, "Duty setting: ");
	
	do{
		
		kp = 0; // Reset key code variable
		kp_aux = 99;
		// Wait for key to be pressed and released

		keypad_receive();
	
		if(oldstate != 99){
			if(number_of_digits < 4){
				if(kp_aux == 11){ // "#" significa "enter"
					PWM1_Set_Duty(duty_cicle);
					WordToStr(duty_cicle, duty_aux);
					Lcd_Out(2, 10, duty_aux);
					delay_ms(2000);
					oldstate = 99;
					kp = 0;
					kp_aux = 99;
					duty_cicle = 0; //valor final a ir pro LCD
					PWM1_Set_Duty(duty_cicle);
					WordToStr(duty_cicle, duty_aux);
					Lcd_Out(2, 10, duty_aux);
				}
				else if(kp_aux == 10){ //limpa tudo
					oldstate = 99;
					kp = 0;
					kp_aux = 99;
					duty_cicle = 0; //valor final a ir pro LCD
					WordToStr(duty_cicle, duty_aux);
					Lcd_Out(2, 10, duty_aux);
				}
				else{
					duty_cicle = (duty_cicle*10) + kp_aux;
					if(duty_cicle < 256){
						WordToStr(duty_cicle, duty_aux);
						Lcd_Out(2, 10, duty_aux); //VALOR ATUALIZADO
					}
					else if(duty_cicle == 256){
						if(sentido == 1){
							duty_cicle = 0;
							PWM1_Set_Duty(duty_cicle);
							PORTA.F0 = 0;
							PORTA.F1 = 1;
							Lcd_Out(1, 1, "A_Clockwise set!");
							oldstate = 99;
							kp = 0;
							kp_aux = 99;
						}
						else{
							duty_cicle = 0;
							PWM1_Set_Duty(duty_cicle);
							PORTA.F1 = 0;
							PORTA.F0 = 1;
							Lcd_Out(1, 1, "Clockwise set!");
							oldstate = 99;
							kp = 0;
							kp_aux = 99;
						}
							
					}
					else{
							oldstate = 99;
							kp = 0;
							kp_aux = 99;
							duty_cicle = 0; //valor final a ir pro LCD
							Lcd_Cmd(_LCD_CLEAR);
							number_of_digits = 0;
							Lcd_Out(1, 1, "DUTY <= 255"); //VALOR ATUALIZADO
							delay_ms(1000);
							Lcd_Out(1, 1, "Duty setting: ");
							
					}
				}
			}
			else{
				oldstate = 99;
				kp = 0;
				kp_aux = 99;
				duty_cicle = 0; //valor final a ir pro LCD
				Lcd_Out(1,2, "Max 3 digitos");
				delay_ms(1000);
				Lcd_Out(1, 1, "Duty setting: ");
				WordToStr(duty_cicle, duty_aux);
				Lcd_Out(2, 10, duty_aux); //VALOR ATUALIZADO
			}
		}
		else{                                         //primeiro digito
			if(kp_aux == 11){  // # -> enter
					duty_cicle = 0; //pro LCD
					oldstate = 99;
					kp = 0;
					kp_aux = 99;
			}
			else if(kp_aux == 10){
					oldstate = 99;
					kp = 0;
					kp_aux = 99;
					duty_cicle = 0; //valor final a ir pro LCD
					WordToStr(duty_cicle, duty_aux);
					Lcd_Out(2, 10, duty_aux);
			}
			else{
					duty_cicle = kp_aux;
					WordToStr(duty_cicle, duty_aux);
					Lcd_Out(2, 10, duty_aux); //VALOR ATUALIZADO
			}
		}
		oldstate = kp_aux;

	}while(1);
}
		
		
		
		
		
		
		
		
		
		
