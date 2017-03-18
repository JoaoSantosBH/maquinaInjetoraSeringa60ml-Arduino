//  MAQUINA INJETORA DE DIETA VIA SERINGA 60ML
//  BY JOÃO SANTOS 
//  https://www.linkedin.com/in/joaomarceloms
//  https://github.com/JoaoSantosBH/
//  joaomarcelo.ms@gmail.com
//  fev/2017


//IMPORTANDO BIBLIOTECA MOTOR PASSO
#include <AccelStepper.h>

//DECLARANDO OS COMPONENTES DA MAQUINA INJETORA
int ledVerde =                      13;
int buzzer =                        12;
int botInjetar =                    11;
int botRecolher =                   10;
int fimCursoInjecaoCompleto =        9;
int fimCursoRecolhimentoCompleto =   8;
int ledVermelho =                    7;
int botParar =                       6;

// Definicao pino ENABLE MOTOR PASSO
int pino_enable = 5;

// PINOS STEP e DIR MOTOR PASSO
AccelStepper motorPasso(1,4,3 );

//Define quantidade giros do motor
long passo = 1000000;

//VARIAVEIS QUE VAO DETECTAR O ESTADO DE CADA BOTAO
int estadoBotaoInje =        0;
int estadoBotaoRecolhe =     0;
int estadoFimInjCompleto =   0;
int estadoFimRecolhimento =  0;
int estadoBotaoParar =       0;

//VARIAVEL QUE DETECTA SE A MAQUINA ESTA EM FUNCIONAMENTO
int estaInjetando  = 0;
int estaAguardando = 1;
int estaRecolhendo = 0;

//detecta o tempo desde que o botão foi apertado
unsigned long changeTime; 

//DEFININDO O SETUP DOS COMPONENTES
void setup() {

pinMode(botInjetar,INPUT);
pinMode(botParar, INPUT);
pinMode(botRecolher,INPUT);                     
pinMode(ledVerde,OUTPUT);
pinMode(ledVermelho, OUTPUT);
pinMode(buzzer,OUTPUT);
pinMode(fimCursoInjecaoCompleto, INPUT);
pinMode(pino_enable, OUTPUT);

// Configuracoes iniciais motor de passo INICIAR PARADO
motorPasso.setAcceleration(150);
motorPasso.moveTo(0);
digitalWrite(pino_enable, HIGH);

acenderLedVerde();
//INICIA COMUNICACAO SERIAL
Serial.begin(9600);
}


void loop() {

//LER ESTADO ATUA DOS COMPONENTES 
estadoFimInjCompleto = digitalRead(fimCursoInjecaoCompleto);
estadoBotaoInje = digitalRead(botInjetar);
estadoBotaoRecolhe = digitalRead(botRecolher); 
estadoBotaoParar = digitalRead(botParar);
estadoFimRecolhimento = digitalRead(fimCursoRecolhimentoCompleto);


 
  //CASO BOTAO INICIAR APERTADO
  if (estadoBotaoInje == HIGH && (millis() - changeTime)> 5000){
       if(estaInjetando == 0 && estaAguardando ==1 && estaRecolhendo== 0){
          iniciarInjecao();
       }
    } 
    
  //NO CASO DE FIM DE CURSO INJECAO COMPLETA PARAR MOTOR DE PASSO
  if (estadoFimInjCompleto == HIGH && (millis() - changeTime)> 5000){
       if(estaInjetando == 1 && estaAguardando ==0 && estaRecolhendo== 0){
          pararMotorPassoInjecao();  
       }
    }
    
 //CASO BOTAO RECOLHER APERTADO
  if (estadoBotaoRecolhe == HIGH && (millis() - changeTime)> 5000){
      if(estaInjetando == 0 && estaAguardando ==1 && estaRecolhendo== 1){
          recolherCursor();
        }
    }

 //NO CASO DE FIM DE CURSO RECOLHIMENTO COMPLETO PARAR MOTOR DE PASSO
    if (estadoFimRecolhimento == HIGH && (millis() - changeTime)> 5000){
       if(estaInjetando == 0 && estaAguardando ==0 && estaRecolhendo== 1){
          pararMotorPassoRecolhimento();  
       }
    }

 //NO CASO DE BOTAO PARAR APERTADO PARAR MOTOR DE PASSO
    if (estadoBotaoParar == HIGH && (millis() - changeTime)> 5000){
           if(estaInjetando == 1  || estaAguardando == 0 || estaRecolhendo== 0){
            Serial.println("BOTAO PARAR");
            pararMaquina(); 
               
           }
       }
   
     motorPasso.run();

//CASO DESEJE MONITORAR STAtUS descomente para ver na serial


}

  
//FUNCOES DO APARELHO
void acenderLedVerde(){
  digitalWrite(ledVerde, HIGH);
}
void apagarLedVerde(){
  digitalWrite(ledVerde,LOW);
}
void acenderLedVermelho(){
    digitalWrite(ledVermelho, HIGH);
}
void apagarLedVermelho(){
  digitalWrite(ledVermelho, LOW);
}


//METODOS DA MAQUINA

//INICIA A INJECAO
void iniciarInjecao(){
  estaInjetando  = 1;
  estaAguardando = 0; 
  estaRecolhendo = 0;
  Serial.println("INICIANDO INJECAO");
  apagarLedVerde();
  acenderLedVermelho();
  digitalWrite(pino_enable, LOW);
  motorPasso.setMaxSpeed(150);
  motorPasso.setSpeed(150); 
  motorPasso.moveTo(-passo);
  verificarStatus();
}

//INICIA O RECOLHIMENTO DO trilHO
void recolherCursor(){
  estaInjetando  = 0;
  estaAguardando = 0; 
  estaRecolhendo = 1;
  noTone(buzzer);
  acenderLedVermelho();
  apagarLedVerde();
  Serial.println("RECOLHENDO CURSOR");
  digitalWrite(pino_enable, LOW);   
  motorPasso.setMaxSpeed(500);
  motorPasso.setSpeed(500);
  motorPasso.moveTo(passo);
  verificarStatus();
}

//PARA INJECAO E EMITE ALERTA SONORO
void pararMotorPassoInjecao(){
  Serial.println("A INJECAO ACABOU");
  estaInjetando  = 0;
  estaAguardando = 1; 
  estaRecolhendo = 1;
  motorPasso.moveTo(0);
  digitalWrite(pino_enable, HIGH);
  motorPasso.setMaxSpeed(150);
  motorPasso.setSpeed(150);
  tocarBuz();
  delay(500);
  acenderLedVerde();
  apagarLedVermelho();
  verificarStatus();
}

//PARA RECOLHIMENTO E EMITE ALERTA SONORO
void pararMotorPassoRecolhimento(){
  Serial.println("A POSICAO CHGOU AO FIm");
  estaInjetando  = 0;
  estaAguardando = 1; 
  estaRecolhendo = 0;
  motorPasso.moveTo(0);
  digitalWrite(pino_enable, HIGH);
  motorPasso.setMaxSpeed(150);
  motorPasso.setSpeed(150);
  tocarBuz();
  motorPasso.moveTo(0);
  delay(500);
  acenderLedVerde();
  apagarLedVermelho();
  voltarUmPoquinho();
  verificarStatus();
}

//PARA MAQUINA
void pararMaquina(){
  Serial.println("PARANDO MAQUINA");
  estaInjetando  = 0;
  estaAguardando = 1; 
  estaRecolhendo = 0;
  motorPasso.moveTo(0);
  digitalWrite(pino_enable, HIGH);
  motorPasso.setMaxSpeed(150);
  motorPasso.setSpeed(150);
  acenderLedVerde();
  apagarLedVermelho();
  verificarStatus();  
}

//FUNCAO QUE RECOLHE EMBOLO PARA NAO COLIDIR COM FIM DE CURSO
void voltarUmPoquinho(){
   Serial.println("INICIANDO RETORNO ESPACO");
  apagarLedVerde();
  acenderLedVermelho();
  digitalWrite(pino_enable, LOW);
  motorPasso.setMaxSpeed(150);
  motorPasso.setSpeed(100); 
  motorPasso.moveTo(-5);
  apagarLedVermelho();
  acenderLedVerde();
  
  verificarStatus();
}
//VERIFICA STATUS CORRENTE DA MAQUINA
void verificarStatus(){
     if(estaRecolhendo == 1){
    Serial.println("Status esta Recolhendo");
   }
   if(estaInjetando == 1){
    Serial.println("Status esta Injetando");
   }
   if(estaAguardando == 1){
    Serial.println("Status esta Aguardando");
   }
}

// THE IMPERIAL MARCH - John Williams
void tocarBuz(){   
  tone(buzzer,1500);   
  delay(500);
  noTone(buzzer);
  delay(50);
  tone(buzzer,1500);   
  delay(500);
  noTone(buzzer);
  delay(50);
  tone(buzzer,1500);   
  delay(500);
  noTone(buzzer);
  delay(50);
  tone(buzzer,1200);   
  delay(250);
  tone(buzzer,1850);   
  delay(250);
  noTone(buzzer);
  delay(50);
  tone(buzzer,1500);   
  delay(500);
  noTone(buzzer);
  delay(50);
  tone(buzzer,1200);   
  delay(250);
  tone(buzzer,1850);   
  delay(250);
  tone(buzzer,1500);   
  delay(500);
  noTone(buzzer);
  delay(500);
  ///////////////////
  tone(buzzer,2220);   
  delay(500);
  noTone(buzzer);
  delay(50);
  tone(buzzer,2220);   
  delay(500);
  noTone(buzzer);
  delay(50);
  tone(buzzer,2220);   
  delay(500);
  tone(buzzer,2369);   
  delay(250);
  tone(buzzer,1850);   
  delay(250);
  noTone(buzzer);
  delay(50);
  tone(buzzer,1500);   
  delay(500);
  noTone(buzzer);
  delay(50);
  tone(buzzer,1200);   
  delay(250);
  tone(buzzer,1850);   
  delay(250);
  tone(buzzer,1500);   
  delay(500);
  noTone(buzzer);
}


