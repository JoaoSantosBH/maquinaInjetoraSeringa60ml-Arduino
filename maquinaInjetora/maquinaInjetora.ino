//  MAQUINA INJETORA DE DIETA VIA SERINGA 60ML
//  BY JOÃO SANTOS 
//  https://www.linkedin.com/in/joaomarceloms
//  https://github.com/JoaoSantosBH/
//  joaomarcelo.ms@gmail.com
//  fev/2017
// A IMPLEMENTAR:
// 01- detectar forca de giro para possivel entupimento do sistema E PAUSAR A MAQUINA

// VERSAO 1.0.0

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
int botParar =                       2;

// Definicao pino ENABLE MOTOR PASSO
int pino_enable = 5;

// PINOS STEP e DIR MOTOR PASSO
AccelStepper motorPasso(1,4,3 );

//DEFINE QUANTIDADE GIROS DO MOTOR, 
//COMO TEMOS UM FIM DE CURSO IMPLEMENTEI UM NUMERO MUITO GRANDE DE VOLTAS
long passo = 1000000;

//VARIAVEIS QUE VAO DETECTAR O ESTADO DE CADA BOTAO
int estadoBotaoInje =        0;
int estadoBotaoRecolhe =     0;
int estadoBotaoParar =       0;

//VARIAVEIS QUE VAO DETECTAR O ESTADO DE CADA FIM DE CURSO
int estadoFimInjCompleto =   0;
int estadoFimRecolhimento =  0;

//VARIAVEL QUE DETECTA SE A MAQUINA ESTA EM FUNCIONAMENTO
int estaInjetando  = 0;
int estaAguardando = 1;
int estaRecolhendo = 0;

//detecta o tempo desde que o botão foi apertado
unsigned long changeTime; 

//DEFININDO O SETUP DOS COMPONENTES
void setup() {

pinMode(botInjetar,INPUT);
pinMode(botRecolher,INPUT);
pinMode(botParar, INPUT);
pinMode(fimCursoInjecaoCompleto, INPUT);
pinMode(fimCursoRecolhimentoCompleto,INPUT);                     
pinMode(ledVerde,OUTPUT);
pinMode(ledVermelho, OUTPUT);
pinMode(buzzer,OUTPUT);
pinMode(pino_enable, OUTPUT);

// Configuracoes iniciais motor de passo INICIAR PARADO
motorPasso.move(0);
digitalWrite(pino_enable, HIGH);

apagarLedVermelho();
acenderLedVerde();
//INICIA COMUNICACAO SERIAL
Serial.begin(9600);
Serial.print("Maquina inicializada");
}


void loop() {

//LER ESTADO ATUA DOS COMPONENTES 
estadoBotaoInje         = digitalRead(botInjetar);
estadoBotaoRecolhe      = digitalRead(botRecolher); 
estadoBotaoParar        = digitalRead(botParar);
estadoFimInjCompleto    = digitalRead(fimCursoInjecaoCompleto);
estadoFimRecolhimento   = digitalRead(fimCursoRecolhimentoCompleto);


  //CASO BOTAO VERDE INICIAR APERTADO
  if (estadoBotaoInje == HIGH && (millis() - changeTime)> 5000){
       if(estaInjetando == 0 && estaAguardando ==1 && estaRecolhendo== 0){
          iniciarInjecao();
       }
    } 
  //CASO FIM DE CURSO INJECAO COMPLETA 
   if (estadoFimInjCompleto == HIGH && (millis() - changeTime)> 5000){
       if(estaInjetando == 1 && estaAguardando ==0 && estaRecolhendo== 0){
          pararMotorPassoInjecao();  
       }
    } 
 //CASO BOTAO AZUL RECOLHER APERTADO
   if (estadoBotaoRecolhe == HIGH && (millis() - changeTime)> 5000){
      if(estaInjetando == 0 && estaAguardando ==1 && estaRecolhendo== 0){
          recolherCursor();
        }
    }
 //CASO FIM DE CURSO RECOLHIMENTO COMPLETO 
    if (estadoFimRecolhimento == HIGH && (millis() - changeTime)> 5000){
       if(estaInjetando == 0 && estaAguardando ==0 && estaRecolhendo== 1){
          pararMotorPassoRecolhimento();  
       }
    }
 //CASO BOTAO VERMELHO PARAR APERTADO 
    if (estadoBotaoParar == HIGH && (millis() - changeTime)> 5000){
        if(estaInjetando == 1 && estaAguardando ==0 && estaRecolhendo== 0){
             pararMaquina();
                 
        }
    }

       
     motorPasso.run();

     
}

  
//FUNCOES DA MAQUINA INJETORA
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


//M E T O D O S  D  A   M A Q U I N A

//INICIA A INJECAO
void iniciarInjecao(){
  estaInjetando  = 1;
  estaAguardando = 0; 
  estaRecolhendo = 0;
  Serial.println("INICIANDO INJECAO");
  apagarLedVerde();
  acenderLedVermelho();
  motorPasso.setMaxSpeed(150);
  motorPasso.setSpeed(150); 
  motorPasso.setAcceleration(150);//Novo
  digitalWrite(pino_enable, LOW);
  motorPasso.move(-passo);
  verificarStatus();
}

//INICIA O RECOLHIMENTO DO trilHO
void recolherCursor(){
  estaInjetando  = 0;
  estaAguardando = 0; 
  estaRecolhendo = 1;
  acenderLedVermelho();
  apagarLedVerde();
  Serial.println("RECOLHENDO CURSOR");
  digitalWrite(pino_enable, LOW);   
  motorPasso.setMaxSpeed(2000);
  motorPasso.setSpeed(2000);
  motorPasso.setAcceleration(2000);//Novo
  motorPasso.move(passo);
  verificarStatus();
}

//PARA INJECAO E EMITE ALERTA SONORO
void pararMotorPassoInjecao(){
  Serial.println("A INJECAO ACABOU");
  estaInjetando  = 0;
  estaAguardando = 1; 
  estaRecolhendo = 0;
  motorPasso.move(0);
  digitalWrite(pino_enable, HIGH);
  tocarBuz();
  acenderLedVerde();
  apagarLedVermelho();
  verificarStatus();
}

//PARA MAQUINA
void pararMaquina(){
  Serial.println(" MAQUINA PAUSADA");
  estaInjetando  = 0;
  estaAguardando = 1; 
  estaRecolhendo = 0;
  motorPasso.move(0);
  digitalWrite(pino_enable, HIGH);
  acenderLedVermelho();
  apagarLedVerde();
  verificarStatus();
}

// QUANDO ATINGE O FDC - PARA RECOLHIMENTO E EMITE ALERTA SONORO
void pararMotorPassoRecolhimento(){
  Serial.println("O RECOLHIMENTO CHEGOU AO FIM");
  tocarBuz();
  motorPasso.move(0);
  digitalWrite(pino_enable, HIGH);
  acenderLedVermelho();
  apagarLedVerde();
  delay(500);
  voltarUmPoquinho();
}

//FUNCAO QUE RECOLHE EMBOLO PARA NAO COLIDIR COM MOLA DO FIM DE CURSO
void voltarUmPoquinho(){
  Serial.println("INICIANDO RETORNO POSICAO ZERO");
  digitalWrite(pino_enable, LOW);
  motorPasso.move(-1000);
  estaInjetando  = 0;
  estaAguardando = 1; 
  estaRecolhendo = 0;
  apagarLedVermelho();
  acenderLedVerde();
  verificarStatus();
}

//VERIFICA STATUS CORRENTE DA MAQUINA
void verificarStatus(){
     if(estaRecolhendo == 1){
    Serial.println("Maquina esta Recolhendo");
    String message = (String) "BP = " + estadoBotaoParar +  ", EI = " + estaInjetando + ", EA = " + estaAguardando + ", ER = " + estaRecolhendo + " .";
    Serial.println(message );
     }
   if(estaInjetando == 1){
    Serial.println("Maquina esta Injetando");
    String message = (String) "BP = " + estadoBotaoParar +  ", EI = " + estaInjetando + ", EA = " + estaAguardando + ", ER = " + estaRecolhendo + " .";
    Serial.println(message );
   }
   if(estaAguardando == 1){
    Serial.println("Maquina esta Aguardando");
    String message = (String) "BP = " + estadoBotaoParar +  ", EI = " + estaInjetando + ", EA = " + estaAguardando + ", ER = " + estaRecolhendo + " .";
    Serial.println(message );
   }
}
// A  L E R T A   S O N O R O
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
//    T A B E L A   V E R D A D E   d o  S T A T U S da maquina
//
//  LEGENDA : Esta Injetando = EI  Esta Aguardando = EA   Esta Recolhendo = ER
//
// _______________________________  EI  | EA  | ER
// (00) ESTADO INICIAL DA MAQUINA |  0  |  1  |  0  |
//__________________________________________________|
// (01) INICIAR INJECAO           |  1  |  0  |  0  |
//__________________________________________________|
// (02) FIM CURSO ACABOU INJECAO  |  0  |  1  |  0  |
//__________________________________________________|
// (03) RECOLHER CURSOR           |  0  |  0  |  1  |
//__________________________________________________|
// (04) FIM CURSO RECOLHIMENTO    |  0  |  1  |  0  |
//__________________________________________________|
// (05) PAUSAR MAQUINA            |  0  |  1  |  0  |
//__________________________________________________|

