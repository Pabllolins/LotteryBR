#include "LotteryBR.h"
#include "Arduino.h"


void LotteryBR::game(int GameType, int BetQuantityNumbers){
    switch (GameType){
      case 60: if((BetQuantityNumbers>5) && (BetQuantityNumbers<16)){
                  Megasena(BetQuantityNumbers); break;  
                }else{break;} 
      case 80: if((BetQuantityNumbers>5) && (BetQuantityNumbers<16)){
                  Quina(BetQuantityNumbers); break;  
                }else{break;} 
      case 25: if((BetQuantityNumbers>5) && (BetQuantityNumbers<20)){
                  Lotofacil(BetQuantityNumbers); break;  
                }else{break;} 
      case 99: if((BetQuantityNumbers>0) && (BetQuantityNumbers<51)){
                  Lotomania(BetQuantityNumbers); break;  
                }else{break;} 
      default:
          break;
    }
}


void LotteryBR::Megasena(int quant){
    Serial.println();
    Serial.printf("The %d random numbers of MEGA SENA are:\n",quant);
    RandonMax = 60;
    quantity = quant;    
    RandomNumbers();
}

void LotteryBR::Quina(int quant){
    Serial.println();
    Serial.printf("The %d random numbers of QUINA are:\n",quant);
    RandonMax = 80;
    quantity = quant;    
    RandomNumbers();
}

void LotteryBR::Lotofacil(int quant){
    Serial.println();
    Serial.printf("The %d random numbers of LOTOFACIL are:\n",quant);
    RandonMax = 25;
    quantity = quant;    
    RandomNumbers();
}

void LotteryBR::Lotomania(int quant){
    Serial.println();
    Serial.printf("The %d random numbers of LOTOMANIA are:\n",quant);  
    RandonMax = 99;
    quantity = quant;    
    RandomNumbers();
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
