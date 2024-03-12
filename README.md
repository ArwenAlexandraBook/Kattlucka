
Jag arbetar för närvarande på ett projekt som involverar utveckling av en smart kattlucka. Denna kattlucka är utrustad med en ESP32 mikrokontroller och en MFRC522 RFID-läsare. Kattluckan är designad för att endast tillåta katter med registrerade RFID-taggar att passera genom den, vilket ger en extra nivå av säkerhet och bekvämlighet.

Kommunikationen mellan ESP32 och kattluckan sker via SPI (Serial Peripheral Interface). I mina kodfiler 'rfid_reader.h' och 'rfid_reader.cpp' har jag implementerat en klass MFRC522RFIDReader som använder SPI för att läsa data från RFID-läsaren. Klassen innehåller metoden 'readData' som läser in RFID-data om ett nytt ID är närvarande och läser av serienumret.

Kattluckan har också flera olika funktioner. Den har en batterinivåsensor som övervakar strömförsörjningen och säkerställer att systemet alltid fungerar korrekt. Den har också en funktion som automatiskt håller luckan stängd mellan 22:00 och 06:00 för att förhindra att katterna går ut på nätterna. Systemet använder sig av WiFi för att koppla upp till nätet och hämtar där sin tid från NTP servern.  Dessutom är luckan utrustad med LED-lampor som ger visuell feedback om systemets status. Vid grön LED har ett giltligt ID kommit i kontakt med RFID-läsaren och luckan öppnas som den ska. Luckan är öppen i 20 sekunder för att se till att katten kan gå in eller ut utan problem. Röd LED innebär att ett ID som inte är registerat kommit i kontakt med RFID-läsaren och luckan öppnas inte. Även om RFID läsaren misslyckas med att läsa av ID;n visualiseras detta av en röd LED. Vid gul LED visualiseras en låg batterinivå vilket jag i detta projekt har satt till 10 %. 

För att utveckla detta projekt använder jag PlatformIO, en kraftfull open-source utvecklingsmiljö som stöder flera olika plattformar och ramverk, inklusive ESP32 och Arduino. PlatformIO ger mig möjlighet att skriva, kompilera, ladda upp och testa min kod på ett effektivt och organiserat sätt.

Jag utför också enhetstester för att säkerställa att min kod fungerar som förväntat. 
Tyvärr lyckas jag inte helt att få enhetstesterna att fungera helt som planerat eftersom att delar av koden fortfarande verkar vara hårdvaruberoende eller ett och annat whitespace som i Makefilen som stör. Kör Google test med MSYS2 MINGW64 och Pytest. 

## Referenser 

- [RC522 RFID Datasheet](https://www.electronicwings.com/components/rc522-rfid/2/datasheet)
- https://www.instructables.com/ESP32-With-RFID-Access-Control/
- [ESP32-WROOM-32](https://www.espressif.com/sites/default/files/documentation/esp32-wroom-32_datasheet_en.pdf)
- [MFRC522 biblioteket] https://github.com/miguelbalboa/rfid

  ## Sammanfattning om arbetet.
Det har varit väldigt utmanande eftersom att jag inte har större erfarenhet av att arbeta från scratch och eftersom att jag inte har en fysisk RFID tag att testa med. Tyckte att det verkade vara ett roligt och utmanande projekt men det har tagit sin långa tid framförallt med enhetstesterna. Jag har gjort enhetstester innan utan problem men på mindre avancerande projekt utan större avancerad funktionalitet. Att testerna ska kunna göras utan fysisk hårdvara närvarande har varit en utmaning och är fortfarande ett work in progess. Jag började med att sätta upp den funktionalitet som kattluckan skulle ha i catflap.h och catflap.cpp och sedan hur jag skulle få rfid läsaren att läsa av ID;n och att kommunicera med ESP32. Jag implementerade sedan WiFi och möjligheten för användarinput som att användaren ska kunna registerera giltliga ID;n. LED lamporna lade var bland det sista jag implementerade för visualisering. Sedan dess har renskrivning varit i fokus när jag arbetat med detta parallelt med andra projekt och samtidigt försökt beta av problemen som uppstår under unittesting. Känner nu i efterhand att det varit tungt arbete att köra själv med min kunskapsnivå. Men tror att de problem som uppstått på vägen och som jag lyckats lösa bara bidragit till mina kunskaper. Önskar att jag fått testa koden med en RFID-tag då jag har en ESP32 hemma. Att bygga vidare och utveckla detta projekt är något jag definitivt kommer jobba vidare på längre fram. 


