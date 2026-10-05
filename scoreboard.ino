**- CODE - COPY AND PASTE TO PROGRAM YOUR ESP32 DEVKIT V1 30 PIN VERSION -**
/* 
  * HYPSEUS COMMUNICATION DEFINITIVE SKETCH (2 MODULES MAX7219 - FIXED MAPPING & CUSTOM WELCOME)   
 * Used to verify that the serial connection is working and that the game is communicating.
 * 
 * WAIT STATE: Displays first max7219 module0 "Gian  DJ-" second max7219 - module1 "Dlair S.B." .
 * GAME STATE: Displays the Player number, 'P', Score, and Lives on Digit 0
 /*   

#include <LedControl.h>  

#define NUM_DEVICES 2  // 2 Moduli MAX7219 in cascata - (2 MAX7219 in Daisy Chain)

typedef enum {       
    PLAYER1_0 = 0, PLAYER1_1, PLAYER1_2, PLAYER1_3, PLAYER1_4, PLAYER1_5,     
    PLAYER2_0, PLAYER2_1, PLAYER2_2, PLAYER2_3, PLAYER2_4, PLAYER2_5,     
    LIVES0, LIVES1, CREDITS1_0, CREDITS1_1, DIGIT_COUNT 
} WhichDigit;  

#pragma pack(push, 1) 
typedef struct {    
    char unit;    
    char digit;    
    char value; 
} DigitStruct; 
#pragma pack(pop)  

LedControl lc = LedControl(23, 18, 5, NUM_DEVICES);  
bool giocoAvviato = false;  

// Tabella di decodifica per i display a 7 segmenti
uint8_t decodificaHypseus(uint8_t rawValue) {
    static const uint8_t mappaNumeri[] = {
        0x7E, // 0
        0x30, // 1
        0x6D, // 2
        0x79, // 3
        0x33, // 4
        0x5B, // 5
        0x5F, // 6
        0x70, // 7
        0x7F, // 8
        0x7B  // 9
    };

    uint8_t valoreNumerico = rawValue & 0x0F; 

    if (valoreNumerico <= 9) {
        return mappaNumeri[valoreNumerico];
    }
    return rawValue; 
}

// Nuova scritta iniziale configurata esattamente come da schema immagine
void mostraScrittaBenvenuto() {     
    lc.clearDisplay(0);     
    lc.clearDisplay(1);          
    
    // =================================================================
    // MODULO 0 (SINISTRA) -> "Gian  DJ-"
    // =================================================================
    lc.setRow(0, 7, 0x5E); // 'G'     
    lc.setRow(0, 6, 0x10); // 'i'     
    lc.setRow(0, 5, 0x77); // 'a'     
    lc.setRow(0, 4, 0x15); // 'n'          
    lc.setRow(0, 3, 0x00); // Spazio vuoto
    lc.setRow(0, 2, 0x7E); // 'O'     
    lc.setRow(0, 1, 0x38); // 'J' 
    lc.setRow(0, 0, 0x01); // '-' (Trattino)
    
    // =================================================================
    // MODULO 1 (DESTRA) -> "OLair  5.8." - trick to write DLair S.B. - (means Score Board)
    // =================================================================
    lc.setRow(1, 7, 0x7E); // 'O'
    lc.setRow(1, 6, 0x0E); // 'L'
    lc.setRow(1, 5, 0x77); // 'a'
    lc.setRow(1, 4, 0x10); // 'i'
    lc.setRow(1, 3, 0x05); // 'r' (Forma minuscola a 7 segmenti)
    lc.setRow(1, 2, 0x00); // Spazio vuoto
    lc.setDigit(1, 1, 5, true);  // '5.' (Numero 5 con punto decimale attivo)
    lc.setDigit(1, 0, 8, true);  // '8.' (Numero 8 con punto decimale attivo)
}  

void avviaGraficaGioco() {     
    lc.clearDisplay(0);     
    lc.clearDisplay(1);          
    
    // Modulo 0 iniziale (Player 1 attivo)     
    lc.setDigit(0, 7, 1, false);       
    lc.setRow(0, 6, 0x67);        // 'P'          
    
    // Modulo 1 fisso (Crediti e Vite)     
    lc.setRow(1, 6, 0x4E);        // 'C'     
    lc.setRow(1, 5, 0x01);        // '-'     
    lc.setRow(1, 4, 0x0E);        // 'L'     
    lc.setRow(1, 3, 0x10);        // 'i'     
    lc.setRow(1, 2, 0x1C);        // 'v'     
    lc.setRow(1, 1, 0x4F);        // 'e' 
}  

void setup() {     
    pinMode(2, OUTPUT);     
    digitalWrite(2, HIGH); 

    for(int i=0; i<NUM_DEVICES; i++) {         
        lc.shutdown(i, false);         
        lc.setIntensity(i, 8);         
        lc.clearDisplay(i);     
    }          
    
    delay(100);     
    mostraScrittaBenvenuto();      

    Serial.begin(115200);     
    while (!Serial) { ; }          
    
    digitalWrite(2, LOW); 
}  

void loop() {     
    if (Serial.available() >= 3) {                  
        if (Serial.peek() > 0x05) {              
            Serial.read();             
            return;         
        }          

        DigitStruct ds;         
        Serial.readBytes((char*)&ds, 3);                  
        
        digitalWrite(2, HIGH);           

        if (ds.unit == 0) {             
            if (!giocoAvviato) {                 
                giocoAvviato = true;                 
                avviaGraficaGioco();             
            }              

            uint8_t segmentoCorretto = decodificaHypseus((uint8_t)ds.value);              

            switch ((WhichDigit)(uint8_t)ds.digit) {                                  
                // MODULO 0 - PUNTEGGIO GIOCATORE 1                 
                case PLAYER1_0: lc.setRow(0, 5, segmentoCorretto); break;                  
                case PLAYER1_1: lc.setRow(0, 4, segmentoCorretto); break;                  
                case PLAYER1_2: lc.setRow(0, 3, segmentoCorretto); break;                  
                case PLAYER1_3: lc.setRow(0, 2, segmentoCorretto); break;                  
                case PLAYER1_4: lc.setRow(0, 1, segmentoCorretto); break;                  
                case PLAYER1_5: lc.setRow(0, 0, segmentoCorretto); break;                                   
                
                case LIVES0:                     
                    lc.setDigit(0, 7, 1, false);                          
                    lc.setRow(1, 0, segmentoCorretto);                      
                    break;                  

                // MODULO 0 - PUNTEGGIO GIOCATORE 2                 
                case PLAYER2_0: lc.setRow(0, 5, segmentoCorretto); break;                  
                case PLAYER2_1: lc.setRow(0, 4, segmentoCorretto); break;                  
                case PLAYER2_2: lc.setRow(0, 3, segmentoCorretto); break;                  
                case PLAYER2_3: lc.setRow(0, 2, segmentoCorretto); break;                  
                case PLAYER2_4: lc.setRow(0, 1, segmentoCorretto); break;                  
                case PLAYER2_5: lc.setRow(0, 0, segmentoCorretto); break;                                   
                
                case LIVES1:                     
                    lc.setDigit(0, 7, 2, false);                          
                    lc.setRow(1, 0, segmentoCorretto);                      
                    break;                  

                // MODULO 1 - CREDITI DI GIOCO                 
                case CREDITS1_0:                      
                    break;                  
                case CREDITS1_1:                      
                    lc.setRow(1, 7, segmentoCorretto);                      
                    break;                  
                
                default:                     
                    break;             
            }         
        }         
        digitalWrite(2, LOW);     
    } 
}
