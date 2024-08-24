<h1 align="center"> 
    <p>Análise e Processamento de Dados MQTT</p>
</h1>

## 📚Sobre
Este repositório é o resultado de um trabalho em dupla realizado durante nosso curso no Senai. Eu fui responsável pelos cálculos no código e pela organização dos dados no Broker MQTT (Shiftr), enquanto meu colega ficou encarregado da montagem dos circuitos físicos, da lógica dos LEDs e do desenvolvimento e personalização do aplicativo. O projeto demonstra nossa habilidade em desenvolver aplicações IoT úteis e interessantes para diversos contextos.

Fique à vontade para explorar o código-fonte e contribuir com melhorias. Estamos abertos a sugestões e colaborações que possam aprimorar ainda mais este projeto.

## 💻Funcionalidades
O código implementa uma interface de visualização de dados em um aplicativo. Ele realiza leituras de temperatura e umidade usando um sensor DHT11, enviando esses dados para um broker MQTT, de onde podem ser acessados por inscritos no tópico. A ideia inicial é que empresas ou instituições utilizem a aplicação para monitorar a temperatura e umidade de uma sala, mas o projeto pode ser facilmente adaptado para outros contextos. As funcionalidades principais incluem:
- Processamento de Dados
    - Temperatura atual
    - Umidade atual
    - Número de dados recebidos
    - Temperatura Média
    - Umidade média
    - Temperatura máxima
    - Umidade máxima
    - Temperatura mínima
    - Umidade mínima
- Aplicativo Móvel
    - Possibilita a visualização de todos os dados do Broker MQTT
- Esquema de Led´s no circuito
    - Um LED sinaliza a conexão do ESP32 com a rede Wi-Fi (O LED permanece ligado enquanto estiver conectado). 
    - Um LED sinalize sempre que uma publicação for feita (LED pisca quando for feita uma publicação).
    - Um LED sinalize sempre que uma mensagem de um tópico assinado chegar. 

 Toda a lógica para o cálculo de médias, contagem de dados enviados, etc., está no código que é inserido no ESP32 por meio do Arduino IDE. O código também permite a fácil visualização dos dados em aplicativos de dashboard para desktop, como o Node-RED.

### Vídeo do código em execução
[Assista ao vídeo](https://www.youtube.com/shorts/TiHe-JN9a4s)

Abaixo, uma foto do aplicativo funcionando recebendo os dados do Broker e imprimindo na tela:
<img src="apkDadosKodular.png"/>

## 🔨Ferramentas

- [ESP32](https://www.espressif.com/en/products/socs/esp32)
- [Arduino IDE](https://www.arduino.cc)
- [Shiftr](https://www.shiftr.io)

## 👨🏾‍🏫Requisitos de Pré-instalação

- Circuito com ESP32
- Shiftr (ou outro broker compatível)
- Arduino IDE (ou outra IDE compatível)
- Placa ESP32 DEVKIT V1

## 🏹Instalação

1. Clone este repositório:

```bash
    $ git clone https://github.com/natan3LiR/Processamento-de-Dados-Sensor--MQTT.git
```
2. Entre no diretório
```bash
    $ Processamento-de-Dados-Sensor--MQTT
```
