unsigned short valor = 0;

void main() {

TRISB.RB0 = 1;  //BOTÃO DE INCREMENTO do PWM
TRISB.RB1 = 1;  //BOTÃO DE INCREMENTO do PWM

TRISC.RC3 = 0;  //SAIDA DO PWM
PORTB.RC3 = 0;

PWM1_Init(5000);
PWM1_Set_Duty(0);
PWM1_Start();
TMR2=0;

while(1)
{
        if (PORTB.RB0==1 && valor < 255){
        delay_ms(200);
        valor = valor + 5;
        PWM1_Set_Duty(valor);
        TMR2=0;
        }

        if (PORTB.RB1==1 && valor >= 5){
        delay_ms(200);
        valor = valor - 5;
        PWM1_Set_Duty(valor);
        TMR2=0;
        }
}
}