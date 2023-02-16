# Car Controlled by MPU6050

Esse projeto é composto de 2 sub-projetos:

## CaR

Nessa 1ª parte, foi desenvolvido uma placa e código simples para apenas receber as informações do controle via ESP-NOW e acionar os motores de acordo com o ângulo.

Foram utilizados os seguintes componentes:

- PLACA FENOLITE FACE SIMPLES
- ESP32
- TB6612FNG
- MINI-360
- CHAVE ON/OFF
- 3 BORNE 2 VIAS 

## Controller

Na 2ª parte, foi feito uma placa e código mais simples ainda, que apenas pega os valores do sensor MPU6050 e envia via ESP-NOW para o robô.

Foram utilizados os seguintes componentes:

- PLACA FENOLITE SIMPLES FURADA 5X7
- ESP32
- MPU6050
- CHAVE ON/OFF
- BORNE 2 VIAS