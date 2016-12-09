#ifndef RANDOMCL_H_INCLUDED
#define RANDOMCL_H_INCLUDED


template<typename Tipo> // ClasseTemplate parao gerador
class RandomCL{
        private:
            Tipo r; // Atributoparageraçãodasequência
            unsigned char i;
        public:
            RandomCL(unsigned char i) { // Construtor
                this->i= i;
                reset();
            }
            Tipo nextr() { // Métododacongruêncialinear: a=17, b=23
                r = 17*r + 23;
                return(r);
            }

            void reset() { // Iniciaa sequenciacom a semente
                unsigned short seeds[6] = {4, 81, 151, 1601, 2307, 4207};
                r = seeds[i%6];
            }
};



#endif // RANDOMCL_H_INCLUDED
