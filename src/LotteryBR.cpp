#include "LotteryBR.h"
#include "Arduino.h"
//#include "Esp.h"


void LotteryBR::game(int GameName, int QuantityNumbers){
    switch (GameName){
      case 60: if((QuantityNumbers>5) && (QuantityNumbers<16)){
                  Megasena(QuantityNumbers); break;  
                }else{break;} 
      case 80: if((QuantityNumbers>5) && (QuantityNumbers<16)){
                  Quina(QuantityNumbers); break;  
                }else{break;} 
      case 25: if((QuantityNumbers>14) && (QuantityNumbers<21)){
                  Lotofacil(QuantityNumbers); break;  
                }else{break;} 
      case 99: if((QuantityNumbers>0) && (QuantityNumbers<51)){
                  Lotomania(QuantityNumbers); break;  
                }else{break;} 
      default:
          break;
    }
}


void LotteryBR::Megasena(int quant){
  RandonMax = 60;
  BetMin = 6;
  BetMax = 15;
  quantity = quant;

  if((quantity <= BetMax) && (quantity >= BetMin)){
    Serial.printf("The %d numbers for MEGA SENA's prize maybe:\n",quant);    
    RandomNumbers();
  }else if((quantity > BetMax) || (quantity < BetMin)){
    delay(100);
    Serial.println();
    Serial.println("ERROR: Invalid quantity!");
    delay(100);
  }
}

void LotteryBR::Quina(int quant){
  RandonMax = 80;
  BetMin = 5;
  BetMax = 15;
  quantity = quant;    

  if((quantity <= BetMax) && (quantity >= BetMin)){
    Serial.printf("The %d numbers for QUINA's prize maybe:\n",quant);    
    RandomNumbers();
  }else if((quantity > BetMax) || (quantity < BetMin)){
    delay(100);
    Serial.println();
    Serial.println("ERROR: Invalid quantity!");
    delay(100);
  }
}

void LotteryBR::Lotofacil(int quant){
  RandonMax = 25;
  BetMin = 15;
  BetMax = 20;
  quantity = quant;    
  
  if((quantity <= BetMax) && (quantity >= BetMin)){
    Serial.printf("The %d numbers for LOTOFACIL's prize maybe:\n",quant);   
    RandomNumbers();
  }else if((quantity > BetMax) || (quantity < BetMin)){
    delay(100);
    Serial.println();
    Serial.println("ERROR: Invalid quantity!");
    delay(100);
  }
}

void LotteryBR::Lotomania(int quant){  
  RandonMax = 99;
  BetMin = 1;
  BetMax = 50;
  quantity = quant;    
  
  if((quantity <= BetMax) && (quantity >= BetMin)){
    Serial.printf("The %d numbers for LOTOMANIA's prize maybe:\n",quant);   
    RandomNumbers();
  }else if((quantity > BetMax) || (quantity < BetMin)){
    delay(100);
    Serial.println();
    Serial.println("ERROR: Invalid quantity!");
    delay(100);
  }
}


void LotteryBR::RandomNumbers(){
    //Serial.println("Test");
    //Serial.printf("quantity: %d\n", quantity);
    //Serial.printf("RandonMax: %d\n", RandonMax);
    //delay(100);

    for(index = 0; index < quantity; index++){
      RandomNumber = random(1, RandonMax); //a variaável recebe umnumero randomico
      if(index > 0){
        for(counter = 0; counter < quantity; counter++){//Laço para varrer e comparar se já existe o numero na lista      
          while(RandomNumber == Numbers[counter]){
            RandomNumber = random(1, RandonMax); //a variaável recebe umnumero randomico
            counter = 0;
          }
        }
      }
      //Serial.printf("Numbers[%d] = %d \n", index, RandomNumber);
      Numbers[index] = RandomNumber; //salva o novo numero aleatório no array
    } 

    /*
    Serial.println("Random numbers generated: ");   
    for(index = 0; index < quantity; index++){
      if(index > 0){
        if((index%10) == 0){
          Serial.println();
        }
      }
      Serial.print(Numbers[index]);
      Serial.print(" ");
    }
    */

    NumbersOrderer();
 }


void LotteryBR::NumbersOrderer(){
  int ordenator[quantity];
  int lower = RandonMax+1;
  int lowerPosition = RandonMax+1;
  int first = Numbers[0];   
  LowerNumberPosition = 0;

  /*  This loop find the minor number and its position in the array */
  for(index = 0; index < quantity; index++){   
    if(lower > Numbers[index]){                                                                                                                                                                                                             
      lower = Numbers[index];
      lowerPosition = index;         
    }
  }

  /*  replace some elements on the array  */
  Numbers[lowerPosition] = first;
  Numbers[0] = lower;
  //Serial.printf("first: %d   -   lower: %d\n", first, lower);
  //Serial.printf("\nNumbers[%d]: %d\n", 0, lower);
  /*
  Serial.println("Randons received and pre-organized: "); 
  for(index = 0; index < quantity; index++){
    if(index > 0){
      if((index%10) == 0){
        Serial.println();
      }
    }
    Serial.print(Numbers[index]);
    Serial.print(" ");
  }
  */

  for(counter = 0; counter < quantity; counter++){                 
    for(index = 0; index < quantity; index++){   
      if((LowestNumber > Numbers[index])){                                                                                                                                          
        if(Numbers[index] != Numbers[LowerNumberPosition]){                                                                                                                                       
          if((index != 0) && (counter != 0)){
            LowestNumber = Numbers[index];
            LowerNumberPosition = index;       
          }     
        }
      }
    }

    if(counter == 0){LowestNumber = lower;} 
    //Serial.print("LowerNumberPosition: ");
    //Serial.println(LowerNumberPosition);
    //Serial.print("LowestNumber: ");
    //Serial.println(LowestNumber);

    ordenator[counter] = LowestNumber;
    Numbers[LowerNumberPosition] = RandonMax+1;
    LowestNumber = RandonMax+1;
  }

  //This part of the code, makes the reverse filling to the main array, but with the numbers organized
  for(index = 0; index < quantity; index++){ 
      Numbers[index] = ordenator[index];
  }
  ImprimeSerial();
}



void LotteryBR::ImprimeSerial(){
  //Serial.println("Ordered array mounted: "); 
  for(index = 0; index < quantity; index++){
    if(index > 0){
      if((index%10) == 0){
        Serial.println();
      }
    }
    Serial.print(Numbers[index]);
    Serial.print(" ");
  }
  Serial.println();
}



void LotteryBR:: InitialPresentation(){
  count = 0;
  Serial.println();
  Serial.println(" ______________________________________________________");
  Serial.println("|___________BRAZIL_LOTTERY_NUMBERS_GENERATOR___________|");    
  Serial.println("|Press the game letter(keyboard), and after press enter|");
  Serial.println("|                                                      |");
  Serial.println("| C --> Lotofacil                                      |");
  Serial.println("| E --> MegaSena                                       |");                     
  Serial.println("| D --> Quina                                          |");
  Serial.println("| B --> Lotomania                                      |");
  Serial.println("|______________________________________________________|");
  Serial.println();
  delay(200);
}





//________________
char LotteryBR:: GameInputOption(){
  if(count == 100){
    Serial.println("Entrando em deepsleep");
    ESP.deepSleep(5000);
  }
  if(Serial.available() == false){
    Serial.begin(BaudRateValue);
    //Serial.updateBaudRate(BaudRateValue);
  }

  ReceivedChar = Serial.read();    
  delay(500);

  while (ReceivedChar != '\r'){  
    if(ReceivedChar == 'D'){ MenuOption = 'D'; break;}
    else if(ReceivedChar == 'C'){ MenuOption = 'C'; break;}
    else if(ReceivedChar == 'B'){ MenuOption = 'B'; break;}
    else if(ReceivedChar == 'E'){ MenuOption = 'E'; break;}
    else {ReceivedChar = '\r'; MenuOption = ' '; break; }
    delay(50);
  }

  if(MenuOption == ' '){ 
    GameInputOption(); 
  }else if(MenuOption != ' '){
      return MenuOption;
  }
  count++;
}


int LotteryBR:: NumberQuantity(){ 
  String MountedText;
  int IntVar;
  Serial.print("Digite a quantidade desejada, ESPAÇO, depois ENTER: ");
  
  ReceivedChar = '\r';

  while (ReceivedChar == '\r'){    
    ReceivedChar = Serial.read();
    delay(5);

    if (ReceivedChar == '0' || ReceivedChar == '1' || ReceivedChar == '2' || ReceivedChar == '3' || ReceivedChar == '4' || ReceivedChar == '5' || ReceivedChar == '6' || ReceivedChar == '7' || ReceivedChar == '8' || ReceivedChar == '9' ){                
      MountedText += ReceivedChar;
      ReceivedChar = '\r';               
    }
    else if(ReceivedChar == ' '){        
            break;
          }
          else{
            ReceivedChar = '\r'; 
          }
  }

  IntVar = (int)atoi(MountedText.c_str());
  MountedText = "";

  return IntVar;
}