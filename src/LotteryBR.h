#ifndef LOTTERYBR_H
#define LOTTERYBR_H

#define MEGASENA 60
#define LOTOFACIL 25
#define LOTOMANIA 99
#define QUINA 80
#define SampleMax 50


class LotteryBR {
    public:
        /*  Constructor Method   */
        //LotteryBR();

        /* Variaveis da classe  */
        int LowerNumberPosition;
        int RandomNumber;
        int index = 0;
        int counter = 0;
        int RandonMax;

        int quantity = 5;
        int Numbers[SampleMax];
        int LowestNumber;//*


        /* Método da classe */
        void game(int jogo, int QuantidadeAposta);        

        void ImprimeSerial();
        void ImprimeLCD();       

    private:
        /* Método da classe */
        void Megasena(int quant);
        void Quina(int quant);
        void Lotofacil(int quant);
        void Lotomania(int quant); 
        void RandomNumbers();

        void NumbersOrderer();
};

#endif