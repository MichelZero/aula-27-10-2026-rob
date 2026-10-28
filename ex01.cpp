// C++ code
//

// definições dos pinos
int PinTrigger = 6; // pino de trigger do sensor ultrassônico
int PinEcho = 5; // pino de echo do sensor ultrassônico
int vermelho = 12; // pino do LED vermelho
int amarelo = 11; // pino do LED amarelo
int verde = 10; // pino do LED verde

// variáveis globais 
long duracaoPulso, distancia_hc;




void setup()
{
  Serial.begin(9600);
  pinMode(PinTrigger, OUTPUT);
  pinMode(PinEcho, INPUT); // pino de echo do sensor ultrassônico deve ser configurado como entrada
  pinMode(vermelho, OUTPUT);
  pinMode(amarelo, OUTPUT);
  pinMode(verde, OUTPUT);
}


/*
a logica do programa é simples: o sensor ultrassônico mede
 a distância de um objeto e, dependendo da distância, acende 
 um LED correspondente. Se a distância for maior que 150 cm, 
 o LED verde acende; se estiver entre 40 e 150 cm, o LED amarelo 
 acende; se for menor que 30 cm, o LED vermelho acende. 
 Caso contrário, todos os LEDs permanecem apagados.
*/
void loop()
{
  medirDistancia();
  Serial.print("Distancia ");
  Serial.print(distancia_hc);
  Serial.println(" cm ");
  
  if (distancia_hc > 150){
    digitalWrite(vermelho, LOW);
    digitalWrite(amarelo, LOW);
    digitalWrite(verde, HIGH);
  } else if (distancia_hc < 150 and distancia_hc > 40){
    digitalWrite(vermelho, LOW);
    digitalWrite(amarelo, HIGH);
    digitalWrite(verde, LOW);
  } else if (distancia_hc < 30){
    digitalWrite(vermelho, HIGH);
    digitalWrite(amarelo, LOW);
    digitalWrite(verde, LOW);
  } else {
    digitalWrite(vermelho, LOW);
    digitalWrite(amarelo, LOW);
    digitalWrite(verde, LOW);
  }
}


/*
a função medirDistancia() envia um pulso de trigger para 
o sensor ultrassônico, aguarda o retorno do pulso de
 echo e calcula a distância com base no tempo de duração 
 do pulso. A distância é então armazenada 
 na variável distancia_hc e impressa no monitor serial
*/
void medirDistancia(){
  digitalWrite(PinTrigger, LOW);
  delayMicroseconds(2);
  digitalWrite(PinTrigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(PinTrigger, LOW);
  duracaoPulso = pulseIn(PinEcho, HIGH);
  Serial.println(duracaoPulso);
  distancia_hc = duracaoPulso / 58;
}

/*
O som leva cerca de 58 microssegundos para 
percorrer um total de 2 centímetros (1 cm de ida e 1 cm de volta).
Dividindo o tempo total por 58, você obtém a 
distância exata em centímetros.
*/