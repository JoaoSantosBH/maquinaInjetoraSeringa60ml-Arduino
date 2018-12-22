//  MAQUINA INJETORA DE DIETA VIA SERINGA 60ML

// A IMPLEMENTAR 
// 
// 28-10-2017
// VERSAO 1.1.0

//Projetada por:
// João Santos      
// Edwaldo Queiroz  
// jE Maquinas Especiais Home Care

//IMPORTANDO BIBLIOTECA MOTOR PASSO
#include <AccelStepper.h>

//DECLARANDO OS COMPONENTES DA MAQUINA INJETORA
int botoes                    = A0;
int buzzer                    = 12;
int BLUE                      = 11;
int GREEN                     = 10;
int RED                       =  9;
// DEFINIDO PINO ENABLE MOTOR PASSO
int pino_enable = 5;
// DEFININDO OS PINOS STEP e DIR MOTOR PASSO
AccelStepper motorPasso(1,4,3 );

//SOBRANDO 13,8,7,6, 2

//DEFININDO QUANTIDADE GIROS DO MOTOR, 
//COMO HÁ UM FIM DE CURSO IMPLEMENTOU_SE UM NUMERO MUITO GRANDE DE VOLTAS
long passo = 1000000;

//ARRAY DE CORES  PARA LED RGB
int preto     [3]  = { 0, 0, 0 };
int branco    [3]  = { 100, 100,  100 };
int vermelho  [3]  = { 100, 0, 0 };
int verde     [3]  = { 0, 100, 0 };
int azul      [3]  = { 0, 0, 100 };
int amarelo   [3]  = { 40, 95, 0 };
int dimbranco [3]  = { 30, 30, 30};

// SETANDO CORES INICIAIS LED RGB
int valorVermelho = preto[0];
int valororVerde = preto[1]; 
int valororAzul = preto[2];
// VARIAVEIS DE CORES
int anteVermelho = valorVermelho;
int anteVerde = valororVerde;
int anteAzul = valororAzul;

//VARIAVEIS QUE VAO DETECTAR O ESTADO DE CADA BOTAO DO BARRAMENTO
int estadoBotaoBarramento = 0;

//VARIAVEIS QUE DETECTAM ESTADOS DE FUNCIONAMENTO
int estaInjetando  = 0;
int estaAguardando = 1;
int estaRecolhendo = 0;
//VARIAVEIS QUE ISOLAM COMPONENTES DO BARRAMENTO
int  botI = 1;
int  botR = 0;
int  botP = 0;
int  fcI  = 0;
int  fcR  = 0;

//DETECTA TEMPO EM QUE BOTAO FOI PRESSIONADO
unsigned long changeTime; 

//SETUP DOS COMPONENTES
void setup() {

pinMode(botoes,INPUT);
pinMode(BLUE,OUTPUT) ;                   
pinMode(GREEN,OUTPUT);
pinMode(RED, OUTPUT);
pinMode(buzzer,OUTPUT);
pinMode(pino_enable, OUTPUT);

// CONFIGURTACOES INICIAIS MOTOR PASSO - INICIAR PARADO
motorPasso.move(0);
digitalWrite(pino_enable, HIGH);

crossFade(dimbranco);
//INICIA COMUNICACAO SERIAL
Serial.begin(9600);
Serial.print("Maquina inicializada\n\n");
verificarStatus();
acenderLuzVerde();
}


void loop() {

//LER ESTADO DOS COMPONENTES 

estadoBotaoBarramento   = analogRead(botoes);

//CASO BOTAO VERDE INICIAR APERTADO
  if (estadoBotaoBarramento>=130 && estadoBotaoBarramento<150 ){
       if(estaInjetando == 0 && estaAguardando ==1 && estaRecolhendo==0 
       && botI==1 && botR==0 && botP==0 && fcI==0 && fcR==0 ){       
          iniciarInjecao();
       }
    }  
//CASO BOTAO VERMELHO PARAR APERTADO 
 else    if (estadoBotaoBarramento>=159 && estadoBotaoBarramento<200){//>=220 && estadoBotaoBarramento<240 
        if(estaInjetando == 1 && estaAguardando ==0 && estaRecolhendo== 0){
          pararMaquina();      
        }
    }
//CASO FIM DE CURSO RECOLHIMENTO COMPLETO 
  else   if (estadoBotaoBarramento >=200 &&  estadoBotaoBarramento <300){//estadoBotaoBarramento >=670
       if(estaInjetando == 0 && estaAguardando ==0 && estaRecolhendo == 1 
       && botI==0 && botR==0 && botP==0 && fcI==0 && fcR==1){
          pararMotorPassoRecolhimento();  
       }
    }  
//CASO FIM DE CURSO INJECAO COMPLETA 
  else  if (estadoBotaoBarramento >=301 && estadoBotaoBarramento<350){
       if(estaInjetando == 1 && estaAguardando ==0 && estaRecolhendo== 0 
       && botI==0 && botR==0 && botP==1 && fcI==1 && fcR==0){
          pararMotorPassoInjecao();  
       }
    }    
//CASO PRESSAO DA MAQUINA ATINJA ALTO NIVEL 
  else  if (estadoBotaoBarramento >=666){//>=330 && estadoBotaoBarramento<350
            if(estaInjetando == 1 && estaAguardando ==0 && estaRecolhendo== 0){
                pararMaquinaPressao(); 
       }
    }        
     motorPasso.run();
     
}

  
//F U N C O E S  D A   M A Q U I N A   I N J E T O R A


//INICIA A INJECAO
void iniciarInjecao(){
  estaInjetando  = 1;
  estaAguardando = 0; 
  estaRecolhendo = 0;
  botI = 0;
  botR = 0;
  botP = 1;
  fcI  = 1;
  fcR  = 0;
  Serial.println("INICIANDO INJECAO");
  acenderLuzAzul();
  motorPasso.setMaxSpeed(150);
  motorPasso.setSpeed(150); 
  motorPasso.setAcceleration(150);//Novo
  digitalWrite(pino_enable, LOW);
  motorPasso.move(-passo);
  verificarStatus();
}

//INICIAR O RECOLHIMENTO DO TRIlHO
void recolherCursor(){
  estaInjetando  = 0;
  estaAguardando = 0; 
  estaRecolhendo = 1;
  botI = 0;
  botR = 0;
  botP = 0;
  fcI  = 0;
  fcR  = 1; 
  acenderLuzBranca();
  Serial.println("RECOLHENDO CURSOR");
  digitalWrite(pino_enable, LOW);   
  motorPasso.setMaxSpeed(2000);
  motorPasso.setSpeed(2000);
  motorPasso.setAcceleration(2000);//Novo
  motorPasso.move(passo);
  verificarStatus();
}

//PARAR INJECAO E RECOLHE MEMBOLO
void pararMotorPassoInjecao(){
  Serial.println("A INJECAO ACABOU");
  acenderLuzMagenta();
  estaInjetando  = 0;
  estaAguardando = 1; 
  estaRecolhendo = 0;
  botI = 0;
  botR = 1;
  botP = 0;
  fcI  = 0;
  fcR  = 1;
  motorPasso.move(0);
  digitalWrite(pino_enable, HIGH);
  verificarStatus();
  recolherCursor();
}

//PARAR MAQUINA
void pararMaquina(){
  Serial.println(" MAQUINA PAUSADA");
  acenderLuzVermelha();
  estaInjetando  = 0;
  estaAguardando = 1; 
  estaRecolhendo = 0;
  botI = 1;
  botR = 0;
  botP = 0;
  fcI  = 0;
  fcR  = 0;
  motorPasso.move(0);
  digitalWrite(pino_enable, HIGH);
  verificarStatus();
}

//PARAR MAQUINA CASO ENTUPIMENTO
void pararMaquinaPressao(){
  Serial.println(" MAQUINA PAUSADA");
  Serial.println("a pressão atingiu niveis alarmantes"); 
  acenderLuzVermelha();
  estaInjetando  = 0;
  estaAguardando = 1; 
  estaRecolhendo = 0;
  botI = 1;
  botR = 0;
  botP = 0;
  fcI  = 0;
  fcR  = 0;
  motorPasso.move(0);
  digitalWrite(pino_enable, HIGH);
  tocarMarchaImperial();
  verificarStatus();
}

// QUANDO ATINGE O FDC - PARAR RECOLHIMENTO E EMITE ALERTA SONORO
void pararMotorPassoRecolhimento(){
  Serial.println("O RECOLHIMENTO CHEGOU AO FIM");
  acenderLuzBranca();
  tocarArpejoFeliz();
  motorPasso.move(0);
  digitalWrite(pino_enable, HIGH);
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
  botI = 1;
  botR = 0;
  botP = 0;
  fcI  = 0;
  fcR  = 0;
  acenderLuzVerde();
  verificarStatus();
 
}

//VERIFICA STATUS CORRENTE DA MAQUINA - IMPRESSAO NA SERIAL PARA MONITORAMENTO DO FUNCIONAMENTO
//PODE SER SUPRIMIDA CASO DESEJADO
void verificarStatus(){
     if(estaRecolhendo == 1){
    Serial.println("Maquina esta Recolhendo");
    String message = (String)  "EI=" + estaInjetando + " EA=" + estaAguardando + " ER=" + estaRecolhendo + " BI=" + botI + " bR=" + botR + " bP=" + botP + " FCI=" + fcI + " FCR=" + fcR;
    Serial.println(message );
     }
   if(estaInjetando == 1){
    Serial.println("Maquina esta Injetando");
    String message = (String) "EI=" + estaInjetando + " EA=" + estaAguardando + " ER=" + estaRecolhendo + " BI=" + botI + " bR=" + botR + " bP=" + botP + " FCI=" + fcI + " FCR=" + fcR;
    Serial.println(message );
   }
   if(estaAguardando == 1){
    Serial.println("Maquina esta Aguardando");
    String message = (String)  "EI=" + estaInjetando + " EA=" + estaAguardando + " ER=" + estaRecolhendo + " BI=" + botI + " bR=" + botR + " bP=" + botP + " FCI=" + fcI + " FCR=" + fcR;
    Serial.println(message );
   }
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//realiza corsfade de luz
void crossFade(int cor[3]) {
  // Convert to 0-255
  int R = (cor[0] * 255) / 100;
  int G = (cor[1] * 255) / 100;
  int B = (cor[2] * 255) / 100;

  int passoSweepR = calcularPasso(anteVermelho, R);
  int passoSweepG = calcularPasso(anteVerde, G); 
  int passoSweepB = calcularPasso(anteAzul, B);

  for (int i = 0; i <= 1020; i++) {
    valorVermelho = calcularValor(passoSweepR, valorVermelho, i);
    valororVerde = calcularValor(passoSweepG, valororVerde, i);
    valororAzul = calcularValor(passoSweepB, valororAzul, i);

    analogWrite(RED, valorVermelho);   // Write current valorues to LED pins
    analogWrite(GREEN, valororVerde);      
    analogWrite(BLUE, valororAzul); 

    delay(10); 
  }
  anteVermelho = valorVermelho; 
  anteVerde = valororVerde; 
  anteAzul = valororAzul;
  delay(0); 
}


int calcularPasso(int valororAnterior, int valororFinal) {
  int passoSweep = valororFinal - valororAnterior; 
  if (passoSweep) {                      
    passoSweep = 1020/passoSweep;              
  } 
  return passoSweep;
}

int calcularValor(int passoSweep, int valor, int i) {

  if ((passoSweep) && i % passoSweep == 0) { 
    if (passoSweep > 0) {             
      valor += 1;           
    } 
    else if (passoSweep < 0) {         
      valor -= 1;
    } 
  }
  
  if (valor > 255) {
    valor = 255;
  } 
  else if (valor < 0) {
    valor = 0;
  }
  return valor;
}

void acenderLuzVerde(){
  for(int i =0; i<256; i++){
    digitalWrite(GREEN, i);
    digitalWrite(RED, 0);
    digitalWrite(BLUE, 0);
  }
}
void acenderLuzVermelha(){
  for(int i =0; i<256; i++){
    digitalWrite(GREEN, 0);
    digitalWrite(RED, 255);
    digitalWrite(BLUE, 0);
  }
}
void acenderLuzAzul(){
  for(int i =0; i<256; i++){
    digitalWrite(GREEN, 0);
    digitalWrite(RED, 0);
    digitalWrite(BLUE, i);
  }
}

void acenderLuzMagenta(){
  for(int i =0; i<256; i++){
    digitalWrite(GREEN, 0);
    digitalWrite(RED, i);
    digitalWrite(BLUE, i);
  }
}

void acenderLuzBranca(){
  for(int i =0; i<256; i++){
    digitalWrite(GREEN, i);
    digitalWrite(RED, i);
    digitalWrite(BLUE, i);
  }
}

// A L E R T A s  S O N O R Os
// THE IMPERIAL MARCH - John Williams
void tocarMarchaImperial(){   
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
void tocarArpejoFeliz(){
  tone(buzzer,1046);   
  delay(125);
  noTone(buzzer);
  delay(50);
  tone(buzzer,1318);   
  delay(125);
  noTone(buzzer);
  delay(50);
  tone(buzzer,1567);   
  delay(125);
  noTone(buzzer);
  delay(50);
  tone(buzzer,2093);   
  delay(125);
  noTone(buzzer);
  delay(50);
  tone(buzzer,2637);   
  delay(125);
  noTone(buzzer);
  delay(50);
  tone(buzzer,1046);   
  delay(125);
  noTone(buzzer);
  delay(50);
  tone(buzzer,1567);   
  delay(125);
  noTone(buzzer);
  delay(50);
  tone(buzzer,2637);   
  delay(125);
  noTone(buzzer);
  delay(50);
  tone(buzzer,2093);   
  delay(250);
  noTone(buzzer);
  delay(50);
}


//SUPRIMIDOS
 //CASO BOTAO AZUL RECOLHER APERTADO 
//  else if (estadoBotaoBarramento >=160 && estadoBotaoBarramento<170){ >=160 && estadoBotaoBarramento<170
//      if(estaInjetando == 0 && estaAguardando ==1 && estaRecolhendo== 0 
//      && botI==0 && botR==1 && botP==0 && fcI==0 && fcR==1){
//          recolherCursor();
//        }
//    }


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
// (05) PARAR MAQUINA            |  0  |  1  |  0  |
//__________________________________________________|

