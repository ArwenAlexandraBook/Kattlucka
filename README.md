
Jag arbetar för närvarande på ett projekt som involverar utveckling av en smart kattlucka. Denna kattlucka är utrustad med en ESP32 mikrokontroller och en MFRC522 RFID-läsare. Kattluckan är designad för att endast tillåta katter med registrerade RFID-taggar att passera genom den, vilket ger en extra nivå av säkerhet och bekvämlighet.

Kattluckan har också flera olika funktioner. Den har en batterinivåsensor som övervakar strömförsörjningen och säkerställer att systemet alltid fungerar korrekt. Den har också en funktion som automatiskt håller luckan stängd mellan 22:00 och 06:00 för att förhindra att katterna går ut på nätterna. Dessutom är luckan utrustad med LED-lampor som ger visuell feedback om systemets status. Vid grön LED har ett giltligt ID kommit i kontakt med RFID-läsaren och luckan öppnas som den ska. Luckan är öppen i 20 sekunder för att se till att katten kan gå in eller ut utan problem. Röd LED innebär att ett ID som inte är registerat kommit i kontakt med RFID-läsaren och luckan öppnas inte. Även om RFID läsaren misslyckas med att läsa av ID;n visualiseras detta av en röd LED. Vid gul LED visualiseras en låg batteri nivå vilket jag i detta projekt har satt till 10 %. 

För att utveckla detta projekt använder jag PlatformIO, en kraftfull open-source utvecklingsmiljö som stöder flera olika plattformar och ramverk, inklusive ESP32 och Arduino. PlatformIO ger mig möjlighet att skriva, kompilera, ladda upp och testa min kod på ett effektivt och organiserat sätt.

Jag utför också enhetstester för att säkerställa att min kod fungerar som förväntat. 
Tyvärr lyckas jag inte helt att få enhetstesterna att fungera helt som planerat vilket är ett work in progress. 

