#include <LiquidCrystal.h>
#include <IRremote.h>

#define pinoIR  1

IRrecv receptor(pinoIR);   
decode_results resultados; 

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int sensorTemp = 0;
int tempBaixa = 18;
int tempAlta = 22;


int sensorPresenca = 7;               
int estadoPresenca = LOW;   
int val = 0;     
int pessoasDia = 0;


int valLuminosidade = 0;
int sensorLuminosidade = A1;



void setup()
{
  
    pinMode(sensorLuminosidade, INPUT);
   	
    pinMode(sensorPresenca, INPUT); 
    Serial.println(pessoasDia);    

    receptor.enableIRIn();  

    lcd.begin (16,2);
    lcd.setCursor (3,0);
    lcd.print ("Aguarde um");
    lcd.setCursor (4,1);
    lcd.print ("momento");
    delay (2000);
    lcd.clear ();

    lcd.setCursor (2,0);
    lcd.print ("Clique em um");
    lcd.setCursor (1,1);
    lcd.print ("botao: 1, 2, 3");
    delay (2000);
    lcd.clear ();
    delay (250);

}



void loop() 
{
  	
	valLuminosidade = analogRead(sensorLuminosidade);

    val = digitalRead(sensorPresenca); 
  
  	while(val)
    {
    	val = digitalRead(sensorPresenca);
        if(val == LOW)
        { 
            pessoasDia = pessoasDia + 1;  
            break;
        }
    }
  
  
	if(receptor.decode(&resultados)) 
    {      

        if(resultados.value == 16582903)//botao 1
        {

            lcd.setCursor (4,0);
            lcd.print ("Botao 1");
            lcd.setCursor (2,1);
            lcd.print ("Temperatura");
            delay (2000);
            lcd.clear ();
        
            // Pegando a leitura do sensor de temperatura
	        int tempTensao = analogRead(sensorTemp);

            // Converte a temperatura lida
            float temp=tempTensao*5;
            temp/=1024;

            // Converte a temperatura lida em em celsius
            float temperaturaC=(temp-0.5)*100;

            // Temperatura dentro do aceito
            if (temperaturaC >= 18 && temperaturaC <= 22)
            {
                lcd.setCursor (0,0);
                lcd.print (" Temperatura:");
                lcd.setCursor (4,1);
                lcd.print (temperaturaC);
                lcd.print (" C");
            }

            // Temperatura alta
            if (temperaturaC >= 23) 
            {
                lcd.setCursor (3,0);
                lcd.print ("Temp alta:");
                lcd.setCursor (4,1);
                lcd.print (temperaturaC);
                lcd.print (" C");
            }

            // Temperatura baixa
           if (temperaturaC <= 17) 
            { 
                lcd.setCursor (3,0);
                lcd.print ("Temp baixa:");
                lcd.setCursor (4,1);
                lcd.print (temperaturaC);
                lcd.print (" C");
            }

            delay (5000);
            lcd.clear ();

        } //fecha if botao 1

        // luminosidade 
        if(resultados.value == 16615543)//botao 2
        {   
          
            lcd.setCursor (4,0);
            lcd.print ("Botao 2");
            lcd.setCursor (2,1);
            lcd.print ("Luminosidade");
            delay (2000);
            lcd.clear ();

            lcd.setCursor(0,0);
            lcd.print("Luminosidade em: ");
            lcd.setCursor (7,1);
            lcd.print(valLuminosidade);
            delay (5000);
    		lcd.clear ();

        }//fecha if botao 2

		// contagem de pessoas
        if(resultados.value == 16599223)//botao 3
        {   
            lcd.setCursor (4,0);
            lcd.print ("Botao 3");
            lcd.setCursor (4,1);
            lcd.print ("Pessoas");
            delay (2000);
            lcd.clear ();

          	lcd.setCursor (5,0);
            lcd.print("Teve "); 
            lcd.print(pessoasDia);
            lcd.setCursor (2,1);
            lcd.print ("pessoas hoje");
          	delay (5000);
    		lcd.clear ();
        }//fecha if botao 3
      
      	receptor.resume(); 

    } //Fecha if controle principal
  	
}//Fecha loop


  