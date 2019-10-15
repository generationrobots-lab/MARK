
/*
Connect with a PC to the network ESP_XXXX and open a web browser at this address : http://192.168.4.1
*/
    #define DEBUG true

    void setup()
    {
      Serial.begin(9600);  // com serie a 9600 bauds
      Serial3.begin(115200); // ESP8266 a 9600 bauds         
      sendData("AT+RST\r\n",2000,DEBUG); // reinitialise le module ESP8266
      sendData("AT+CWMODE=2\r\n",1000,DEBUG); // configure en TCP
      sendData("AT+CWSAP?\r\n",2000,DEBUG); // recupere nom et mot de passe
      sendData("AT+CIFSR\r\n",1000,DEBUG); // recupere l'adresse IP
      sendData("AT+CIPMUX=1\r\n",1000,DEBUG); // configure en connexion multiple 
      sendData("AT+CIPSERVER=1,80\r\n",1000,DEBUG); // ouvre le serveur sur le port 80
    }
     
    void loop()
    {
      if(Serial3.available()) // teste si l'ESP envoi un message  
      {
        if(Serial3.find("+IPD,"))
        {
         delay(1000);     
         int connectionId = Serial3.read()-48;
         // soustrait 48 parceque la fonction read() retourne la valeur ASCII decimal et O 
         // la premiere valeur decimale commence a 48                                        
         
         String webpage = "<h1>HELLO FROM MARK ROBOT :)</h1>";     
         String cipSend = "AT+CIPSEND=";
         cipSend += connectionId;
         cipSend += ",";
         cipSend +=webpage.length();
         cipSend +="\r\n";         
         sendData(cipSend,1000,DEBUG);
         sendData(webpage,1000,DEBUG);                
         String closeCommand = "AT+CIPCLOSE="; 
         closeCommand+=connectionId; // fermer la connexion
         closeCommand+="\r\n";         
         sendData(closeCommand,3000,DEBUG);
        }
      }
    }          
    String sendData(String command, const int timeout, boolean debug)
    {
        String response = "";        
        Serial3.print(command); // envoi le caractere a l' esp8266        
        long int time = millis();        
        while( (time+timeout) > millis())
        {
          while(Serial3.available())
          {          
            char c = Serial3.read(); // lit le caracter suivant
            response+=c;
          }  
        }        
        if(debug)
        {
          Serial.print(response);
        }        
        return response;
    }
