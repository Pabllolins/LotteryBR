#ifndef LOTTERYBR_H
#define LOTTERYBR_H

#define MEGASENA 60
#define LOTOFACIL 25
#define LOTOMANIA 99
#define QUINA 80
#define SampleMax 50

#define BaudRateValue 9600


class LotteryBR {
    public:
        /*  Constructor Method   */
        //LotteryBR();

        /* Class's public Methods */
        void game(int GameName, int QuantityNumbers);
        char GameInputOption(); 
        int NumberQuantity();
        void InitialPresentation();
        char ReceivedChar;
        char MenuOption; 
     

    private:
        /* Variaveis da classe  */
        int LowerNumberPosition;
        int RandomNumber;
        int index = 0;
        int counter = 0;
        int RandonMax;
        int BetMin;
        int BetMax;
        int count = 0;

        int quantity = 5;
        int Numbers[SampleMax];
        int LowestNumber;//*

        /* Class's public Methods */
        void Megasena(int quant);
        void Quina(int quant);
        void Lotofacil(int quant);
        void Lotomania(int quant); 
        void RandomNumbers();

        void NumbersOrderer();        
        void ImprimeSerial();
        void ImprimeLCD();  
};

#endif