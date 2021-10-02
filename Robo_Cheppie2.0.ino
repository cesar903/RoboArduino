#include <VarSpeedServo.h>


VarSpeedServo base;    //Faz o giro
String rec = "";   //Variavel que vai receber 
VarSpeedServo antebraco;       
VarSpeedServo pulso;       
VarSpeedServo garra;       
const int btnA = 10;
const int btnB = 11;
const int btnC = 12;
const int btnD = 13;


void setup() {
 
  base.attach(3); //saidas pwm
  antebraco.attach(5);     
  pulso.attach(6);     
  garra.attach(9);
  
  base.write(0);  //posição inicial do braço, e respectivamente    
  antebraco.write(60);
  pulso.write(60);            
  garra.write(170);

  Serial.begin(9600);

  pinMode(btnA,  INPUT_PULLUP);  //Indica ser um botão pulsante sem necessidade de resistor pullDaw
  pinMode(btnB,  INPUT_PULLUP);  //Indica ser um botão pulsante sem necessidade de resistor pullDaw
  pinMode(btnC,  INPUT_PULLUP);  //Indica ser um botão pulsante sem necessidade de resistor pullDaw
  pinMode(btnD,  INPUT_PULLUP);  //Indica ser um botão pulsante sem necessidade de resistor pullDaw
 
}

String lerserial() { //função que transforma o que e recebido pela serial em uma string
  String conteudo = ""; // armazena o frase inteira
  char carac; //armazena cada caracter
  while(Serial.available()>0) { // enquando receber caracteres
    carac=Serial.read(); //grava-lo na variavel carac
    if(carac !='/n') { //se o caracter NAO for quebra de linha
      conteudo.concat(carac); //contatenar o caracter na string conteudo
    }
    delay(10); //delay para nova leitura
  }
  Serial.print("Recebi: ");
  Serial.println(conteudo);
  return conteudo; //retorna o valor da string conteudo
}

void loop() {
  
  if(Serial.available()>0){ //se o valor recebido for maior que 0 na porta Serial, rec receb o valor de c aracter pelo metodo lerserial()
          rec = lerserial();
    }


   if((rec == "Bloco C") ||(digitalRead(btnC) == LOW)){ //se o comando recebido for bloco c
    
    Serial.println("Recebeu c"); //Avisa que este foi o comando recebido no terminal
    base.slowmove(93,30);  //slowmove é uma função do VarSpeedServo, que controla a velocidade do servo, dando mais precisão , a base faz o giro       
    antebraco.slowmove(60,30); //o ante braço o eico de decida
    delay(2000);
    pulso.slowmove(75,30); //o pulso da a precisão            
    garra.slowmove(100,30); // a garra pega a peça
    delay(1000);
    antebraco.slowmove(14,30); // antebraço volta a posição normal
    delay(1000);
    garra.write(160);
    rec = "e"; // rec recebe e para iniciar a função declarada
    
   }

   if((rec == "bloco B") || (digitalRead(btnB) == LOW)){//se o comando recebido for bloco b
    Serial.println("Recebeu b");
    base.slowmove(50,30);           //A base roda de acordo com a posição do bloco
    antebraco.slowmove(60,30);
     garra.slowmove(100,30);// O ante braço se posiciona acima da´peça para descer
    delay(2000);
    pulso.slowmove(56,30);           //O pulso desce de acorodo com o angulo pre definido
    antebraco.slowmove(16,30); //O ante braço começa a descer
    delay(2000);
    garra.write(160); //A garra pega determinada peça
    rec = "e";
    
   }

   if((rec == "bloco A" ) || (digitalRead(btnA) == LOW)){ //se o comando recebido for bloco A
    Serial.println("Recebeu a");
    base.slowmove(10,30);            //A base roda de acordo com a posição do bloco
    antebraco.slowmove(90,30);    // O ante braço se posiciona acima da´peça para descer
    delay(2000);
    pulso.slowmove(68,30);       //O pulso desce de acorodo com o angulo pre definido     
    garra.slowmove(100,30);  //A garra abre 
   delay(1000);
   antebraco.slowmove(16,30);  //O ante braço começa a descer
   delay(1000);
   garra.write(160);   //A garra pega determinada peça
   rec = "e";
   }

   if((rec == "bloco de") || (digitalRead(btnD) == LOW)){
    Serial.println("Recebeu d");
    base.slowmove(135,30);        //A base roda de acordo com a posição do bloco    
    antebraco.slowmove(60,30);  // O ante braço se posiciona acima da´peça para descer
    delay(2000);
    pulso.slowmove(63,30);     //O pulso desce de acorodo com o angulo pre definido        
    garra.slowmove(100,30);   //A garra abre 
    delay(1000);
    antebraco.slowmove(18,30);  //O ante braço começa a descer
    delay(1000);
    garra.write(160);  //A garra pega determinada peça
    rec = "e";
    }

    if(rec == "e"){
      soltar();
    }
}

  void soltar(){ // função recebida no final de cada comando, para sempre que terminar ele voltar a posição de inicio 
    
    delay(1000);
    antebraco.slowmove(60,40);
    delay(1000);
    base.slowmove(170,40);
    delay(1500);
    garra.slowmove(90,40);
    
  }
