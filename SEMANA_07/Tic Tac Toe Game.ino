// Import das bibliotecas necessárias
#include <WiFi.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

// Credenciais para conexão wifi
const char* ssid = "SHARE-RESIDENTE";
const char* password = "Share@residente";

// Defini o led como output
const int output2 = 2;

String roundWon = "0";

const char* PARAM_INPUT = "value";

// Cria objeto AsyncWebServer na porta 80
AsyncWebServer server(80);

//Página HTML com style e javascript
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html><head>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <title>Document</title>
  <link rel="stylesheet" href="style.css"
  </head><body onload="restartGame()">
    <style>
    .cell{
        width: 75px;
        height: 75px;
        border: 2px solid;
        box-shadow: 0 0 0 2px;
        line-height: 75px;
        font-size: 50px;
        cursor: pointer;
    }
    #gameContainer{
        font-family: "Permanent Marker", cursive;
        text-align: center;
    }
    #cellContainer{
        display: grid;
        grid-template-columns: repeat(3, auto);
        width: 225px;
        margin: auto;
    }
    </style>
        <div id="gameContainer">
            <h1>Tic Tac Toe</h1>
            <div id="cellContainer">
                <div cellIndex="0" class="cell"></div>
                <div cellIndex="1" class="cell"></div>
                <div cellIndex="2" class="cell"></div>
                <div cellIndex="3" class="cell"></div>
                <div cellIndex="4" class="cell"></div>
                <div cellIndex="5" class="cell"></div>
                <div cellIndex="6" class="cell"></div>
                <div cellIndex="7" class="cell"></div>
                <div cellIndex="8" class="cell"></div>
            </div>
            <h2 id="statusText"></h2>
            <button id="restartBtn">Restart</button>
        </div>
    </body>
    </html>
    <script>
      const cells = document.querySelectorAll(".cell");
      const statusText = document.querySelector("#statusText");
      const restartBtn = document.querySelector("#restartBtn");
      const winConditions = [
          [0, 1, 2],
          [3, 4, 5],
          [6, 7, 8],
          [0, 3, 6],
          [1, 4, 7],
          [2, 5, 8],
          [0, 4, 8],
          [2, 4, 6]
      ];
      let options = ["", "", "", "", "", "", "", "", ""];
      let currentPlayer = "X";
      let running = false;
      initializeGame();
      function initializeGame(){
          cells.forEach(cell => cell.addEventListener("click", cellClicked));
          restartBtn.addEventListener("click", restartGame);
          statusText.textContent = `${currentPlayer}'s turn`;
          running = true;
      }
      function cellClicked(){
          const cellIndex = this.getAttribute("cellIndex");
          if(options[cellIndex] != "" || !running){
              return;
          }
          updateCell(this, cellIndex);
          checkWinner();
      }
      function updateCell(cell, index){
          options[index] = currentPlayer;
          cell.textContent = currentPlayer;
      }
      function changePlayer(){
          currentPlayer = (currentPlayer == "X") ? "O" : "X";
          statusText.textContent = `${currentPlayer}'s turn`;
      }
      function checkWinner(){
          let roundWon = false;

          for(let i = 0; i < winConditions.length; i++){
              const condition = winConditions[i];
              const cellA = options[condition[0]];
              const cellB = options[condition[1]];
              const cellC = options[condition[2]];

              if(cellA == "" || cellB == "" || cellC == ""){
                  continue;
              }
              if(cellA == cellB && cellB == cellC){
                  roundWon = true;
                  break;
              }
          }

          if(roundWon){
              statusText.textContent = `${currentPlayer} wins!`;
              running = false;
              var xhr = new XMLHttpRequest();
              xhr.open("GET", "/roundWon?value="+currentPlayer, true);
              xhr.send();
          }
          else if(!options.includes("")){
              statusText.textContent = `Draw!`;
              running = false;
          }
          else{
              changePlayer();
          }
      }
      function restartGame(){
          currentPlayer = "X";
          options = ["", "", "", "", "", "", "", "", ""];
          statusText.textContent = `${currentPlayer}'s turn`;
          cells.forEach(cell => cell.textContent = "");
          running = true;
      }
    </script>  
</body></html>
)rawliteral";

void setup(){
  // Serial port delimitada para debug do código
  Serial.begin(115200);

  //Configura funcionalidade do led
  pinMode(output2, OUTPUT);
  
  // Conecta ao wi-fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }

  //  Print do endereço IP local do ESP
  Serial.println(WiFi.localIP());

  //O ESP32 é programado para criar uma página de servidor Web que irá mostrar a página web com o jogo.
  // Na função, if(roundWon) do script é criado uma variável para o método XMLHttpRequest, que acenderá o atuador led quando o jogador vencer. 

  // Rota para a página web
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });

  // Envia uma requisição GET para <ESP_IP>/roundWon?value=<inputMessage>
  server.on("/roundWon", HTTP_GET, [] (AsyncWebServerRequest *request) {
    String inputMessage;
    // GET valor do input em <ESP_IP>/roundWon?value=<inputMessage>
    if (request->hasParam(PARAM_INPUT)) {
      inputMessage = request->getParam(PARAM_INPUT)->value();
      roundWon = inputMessage;
      digitalWrite(output2, HIGH);
    // Se o GET estiver de acordo com o delimitado, o LED acende 
    }
    else {
    inputMessage = "No message sent";
    }
    Serial.println(inputMessage);
    request->send(200, "text/plain", "OK");

  });

    // Inicia servidor 
  server.begin();
}

void loop() {
  
}
