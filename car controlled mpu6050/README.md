# Car Controlled by MPU6050

Esse projeto é composto de 2 sub-projetos:

## Car

Nessa 1ª parte, foi desenvolvido uma PCB e código simples para apenas receber as informações do controle via ESP-NOW e acionar os motores de acordo com o ângulo.

A placa foi feito no Altium Designer e o código na Arduino IDE.

Foram utilizados os seguintes componentes:

- 1PLACA FENOLITE FACE SIMPLES
- 1 ESP32
- 1 TB6612FNG
- 1 MINI-360
- 1 CHAVE ON/OFF SS12D00G4
- 3 BORNE 2 VIAS 

## Controller

Na 2ª parte, foi feito uma placa e código mais simples ainda, que apenas pega os valores do sensor MPU6050 e envia via ESP-NOW para o robô.

A placa foi feito no Fritzing e o código na Arduino IDE.

Foram utilizados os seguintes componentes:

- 1 PLACA FENOLITE SIMPLES FURADA 5X7
- 1 ESP32
- 1 MPU6050
- 1 CHAVE ON/OFF
- 1 BORNE 2 VIAS

![](altium_car_mpu6050.png)