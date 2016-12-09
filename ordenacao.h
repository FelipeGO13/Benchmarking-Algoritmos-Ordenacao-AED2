#ifndef ORDENACAO_H_INCLUDED
#define ORDENACAO_H_INCLUDED

#include <algorithm>    // std::swap
#include<iostream>
class LeonardoNumber

 /**
  **  Helper class for manipulation of Leonardo numbers
  **
  **/

  {
    public:
      /**  Default ctor.  **/
      LeonardoNumber (void) throw () : b (1), c (1)
        { return; }

      /**  Copy ctor.  **/
      LeonardoNumber (const LeonardoNumber & _l) throw () : b (_l.b), c (_l.c)
        { return; }

      /**
       **  Return the "gap" between the actual Leonardo number and the
       **  preceding one.
       **/
      unsigned gap (void) const throw ()
        { return b - c; }


      /**  Perform an "up" operation on the actual number.  **/
      LeonardoNumber & operator ++ (void) throw ()
        { unsigned s = b; b = b + c + 1; c = s; return * this; }

      /**  Perform a "down" operation on the actual number.  **/
      LeonardoNumber & operator -- (void) throw ()
        { unsigned s = c; c = b - c - 1; b = s; return * this; }

      /**  Return "companion" value.  **/
      unsigned operator ~ (void) const throw ()
        { return c; }

      /**  Return "actual" value.  **/
      operator unsigned (void) const throw ()
        { return b; }


    private:
      unsigned b;   /**  Actual number.  **/
      unsigned c;   /**  Companion number.  **/
  };


namespace ED {

    template <typename T>
    class Ordenacao{
        public:
            static void heapsort(T *vet, int n);
            static void quicks_central(T *vet, int l, int r);
            static void mergesort(T *vet, int n);
            static void shellsort_pardons(T *vet, int n);
            static void shellsort_knuth(T *vet, int n);
            static void shellsort_shell(T *vet, int n);
            static void insertionsort(T *vet, int n);
            static void smoothsort(T *vet, int n);
            static void flashsort(T *vet, int n);
        private:
            static void heapify(T *vet, int pai, int heapsize);
            static void build_heap(T *vet, int n);
            static void mergee(T *vet, T *aux, int esq, int meio, int dir);
            static void m_sort(T *vet, T *aux, int esq, int dir);
            static void semitrinkle (T *, unsigned, unsigned long long, LeonardoNumber);
            static void trinkle (T *, unsigned, unsigned long long, LeonardoNumber);
            static void sift (T *, unsigned, LeonardoNumber);
    };

    //HEAPSORT
    template <typename T>
    void Ordenacao<T>::heapify(T *vet, int pai, int heapsize)
    {
        int fl, fr, imaior;

        while(true)
        {
            fl = (pai << 1) + 1;
            fr = fl+ 1;

            if((fl < heapsize) && (vet[fl] > vet[pai])) imaior = fl;
            else imaior = pai;

            if((fr < heapsize) && (vet[fr] > vet[imaior])) imaior = fr;

            if(imaior != pai)
            {
                vet[pai] = vet[pai] + vet[imaior];
                vet[imaior] = vet[pai] - vet[imaior];
                vet[pai] = vet[pai] - vet[imaior];
                pai = imaior;
            }
            else break;
        }
    }

    template <typename T>
    void Ordenacao<T>::build_heap(T *vet, int n)
    {
        int i;
        for (i=(n>>1)-1;i>=0;i--) heapify(vet, i, n);
    }

    template <typename T>
    void Ordenacao<T>::heapsort(T *vet, int n)
    {
        build_heap(vet, n);

        int t;
        for(t=n-1;t > 0;t--)
        {
            vet[0] = vet[0] + vet[t];
            vet[t] = vet[0] - vet[t];
            vet[0] = vet[0] - vet[t];
            heapify(vet, 0, t);
        }
    }

    //QUICKSORT com piv? mediano
    template <typename T>
    void Ordenacao<T>::quicks_central(T *vet, int l, int r)
    {
        if(r <= l) return;

        int i, j;
        i= (l+r)/2;
        T pivo= vet[i];
        vet[i] = vet[l];
        vet[l] = pivo;

        i= l;
        j = r;
        while(true)
        {
            while((j > i) && (vet[j] > pivo)) j--;
            if(i==j) break;
            vet[i] = vet[j];
            i++;
            while((i< j) && (vet[i] < pivo)) i++;
            if(i==j) break;
            vet[j] = vet[i];
            j--;
        }
        vet[i] = pivo;

        quicks_central(vet, l, i-1);
        quicks_central(vet, i+1, r);
    }

    //MERGESORT
    template <typename T>
    void Ordenacao<T>::mergee(T *vet, T *aux, int esq, int meio, int dir)
    {
        int i, j, k;
        i = k = esq;
        j = meio + 1;

        while((i <= meio) && (j <= dir))
        {
            if(vet[i] < vet[j]) aux[k++] = vet[i++];
            else aux[k++] = vet[j++];
        }
        while(i<= meio) aux[k++] = vet[i++];
        while(j <= dir) aux[k++] = vet[j++];
        while(esq<=dir) vet[esq] = aux[esq++];
    }

    template <typename T>
    void Ordenacao<T>::m_sort(T *vet, T *aux, int esq, int dir)
    {
        if(dir <= esq) return;
        int meio= (dir + esq) >> 1;

        m_sort(vet, aux, esq, meio);
        m_sort(vet, aux, meio+1, dir);

        if(vet[meio]<=vet[meio+1]) return;

        mergee(vet, aux, esq, meio, dir);
    }

    template <typename T>
    void Ordenacao<T>::mergesort(T *vet, int n)
    {
        T *aux = new T[n];

        m_sort(vet, aux , 0, n-1);

        delete aux;
    }

    //SHELLSORT Pardons
    template <typename T>
    void Ordenacao<T>::shellsort_pardons(T *vet, int n)
    {
        int i,j,h,k = 0;
        T aux;
        int increments[] = {217378076, 45806244, 9651787, 2034035, 428481, 90358, 19001, 4025, 836, 182, 34, 9, 1};

        while(increments[k]>n) k++;

        do{
            h = increments[k++] ;
            for(i = h; i < n; i++)
            {
                aux = vet[i];
                j = i-h;

                while((j >= 0) && (aux < vet[j]))
                {
                    vet[j+h] = vet[j];
                    j -= h;
                }

                vet[j+h] = aux;
            }
        } while(h!=1);
    }

    //SHELLSORT Knuth
    template <typename T>
    void Ordenacao<T>::shellsort_knuth(T *vet, int n)
    {
        int i, j, h;
        T aux;
        h = 1;

        do{ h = 3 * h + 1; } while (h < n);
        do{
            h /= 3;
            for(i=h;i<n;i++)
            {
                aux = vet[i];
                j = i - h;
                while((j >= 0) && (aux < vet[j]))
                {
                    vet[j+h] = vet[j];
                    j -= h;
                }
                vet[j+h] = aux;
            }
        } while(h != 1);
    }

    //SHELLSORT Shell
    template <typename T>
    void Ordenacao<T>::shellsort_shell(T *vet, int n)
    {
        int i,j,h;
        T aux;
        h = n;

        do{
            h /= 2;
            for(i=h;i<n;i++)
            {
                aux = vet[i];
                j = i - h;

                while((j >= 0) && (aux < vet[j]))
                {
                    vet[j+h] = vet[j];
                    j -= h;
                }
                vet[j+h] = aux;
            }
        } while(h != 1);
    }

    //INSERTIONSORT
    template <typename T>
   
    void Ordenacao<T>::insertionsort(T *vet, int n)
    {
       int i, j;
       T key;
       for (i = 1; i < n; i++)
       {
           key = vet[i];
           j = i-1;

           while (j >= 0 && vet[j] > key)
           {
               vet[j+1] = vet[j];
               j = j-1;
           }
           vet[j+1] = key;
       }
    }

	//SMOOTHSORT
    template <typename T>
        void Ordenacao<T>::sift (T * _m, unsigned _r, LeonardoNumber _b)

           {
             unsigned r2;

             while (_b >= 3)
               {
                 if (_m [_r - _b.gap ()] >= _m [_r - 1])
                   r2 = _r - _b.gap ();
                 else
                   { r2 = _r - 1; --_b; }

                 if (_m [_r] >= _m [r2])  break;
                 else
                   { std::swap(_m [_r], _m [r2]); _r = r2; --_b; }
               }


             return;
           }


         template <typename T>
         void Ordenacao<T>::semitrinkle (T * _m, unsigned _r, unsigned long long _p,
                                                  LeonardoNumber _b)

           {
             if (_m [_r - ~_b] >= _m [_r])
               {
                 std::swap(_m [_r], _m [_r - ~_b]);
                 Ordenacao<T>::trinkle (_m, _r - ~_b, _p, _b);
               }


             return;
           }


         template <typename T>
         void Ordenacao<T>::trinkle (T * _m, unsigned _r, unsigned long long _p,
                                               LeonardoNumber _b)

           {
             while (_p)
               {
                 for ( ; !(_p % 2); _p >>= 1)  ++_b;

                 if (!--_p || (_m [_r] >= _m [_r - _b]))  break;
                 else
                   if (_b == 1)
                     { std::swap(_m [_r], _m [_r - _b]); _r -= _b; }

                   else if (_b >= 3)
                     {
                       unsigned r2 = _r - _b.gap (), r3 = _r - _b;

                       if (_m [_r - 1] >= _m [r2])
                         { r2 = _r - 1; _p <<= 1; --_b; }

                       if (_m [r3] >= _m [r2])
                         { std::swap(_m [_r], _m [r3]); _r = r3; }

                       else
                         { std::swap(_m [_r], _m [r2]); _r = r2; --_b; break; }
                     }
               }

            Ordenacao<T>:: sift (_m, _r, _b);


             return;
           }

         template <typename T>
         void Ordenacao<T>::smoothsort (T * _m, int _n)

           {
             if (!(_m && _n)) return;

             unsigned long long p = 1;
             LeonardoNumber b;

             for (unsigned q = 0; ++q < _n ; ++p)
               if (p % 8 == 3)
                 {
                  Ordenacao<T>:: sift (_m, q - 1, b);

                   ++++b; p >>= 2;
                 }

               else if (p % 4 == 1)
                 {
                   if (q + ~b < _n)  Ordenacao<T>::sift (_m, q - 1, b);
                   else Ordenacao<T>:: trinkle (_m, q - 1, p, b);

                   for (p <<= 1; --b > 1; p <<= 1)  ;
                 }

            Ordenacao<T>:: trinkle (_m, _n - 1, p, b);

             for (--p; _n-- > 1; --p)
               if (b == 1)
                 for ( ; !(p % 2); p >>= 1)  ++b;

               else if (b >= 3)
                 {
                   if (p)  Ordenacao<T>::semitrinkle (_m, _n - b.gap (), p, b);

                   --b; p <<= 1; ++p;
                   Ordenacao<T>::semitrinkle (_m, _n - 1, p, b);
                   --b; p <<= 1; ++p;
                 }


             return;
           }





    //FLASHSORT
    template <typename T>
	void Ordenacao<T>::flashsort(T *vet, int n)
	{

		if(n == 0) return;

		int m = (int)((0.2 * n) + 2);

 
		T min, max, maxIndex;
		min = max = vet[0];
		maxIndex = 0;

		for(int i = 1; i < n - 1; i += 2)
		{
			T small;
			T big;
			T bigIndex;

			if(vet[i] < vet[i + 1])
			{
				small = vet[i];
				big = vet[i + 1];
				bigIndex = i + 1;
			}
			else
			{
				big = vet[i];
				bigIndex = i;
				small = vet[i + 1];
			}

			if(big > max)
			{
				max = big;
				maxIndex = bigIndex;
			}

			if(small < min)
			{
				min = small;
			}
		}

		if(vet[n - 1] < min)
		{
			min = vet[n - 1];
		}
		else if(vet[n - 1] > max)
		{
			max = vet[n - 1];
			maxIndex = n - 1;
		}

		if(max == min)
		{
			return;
		}

		int* L = new int[m + 1];

		for(int t = 1; t <= m; t++)
		{
			L[t] = 0;
		}

		double c = (m - 1.0) / (max - min);
		T K;
		for(int h = 0; h < n; h++)
		{
			K = ((T)((vet[h] - min) * c)) + 1;

			L[K] += 1;
		}

		for(K = 2; K <= m; K++)
		{
			L[K] = L[K] + L[K - 1];
		}

		T temp = vet[maxIndex];
		vet[maxIndex] = vet[0];
		vet[0] = temp;

		int j = 0;

		K = m;

		int numMoves = 0;

		while(numMoves < n)
		{

			while(j >= L[K])
			{
				j++;
				K = ((T)((vet[j] - min) * c)) + 1;
			}

			T evicted = vet[j];

			while(j < L[K])
			{
				K = ((T)((evicted - min) * c)) + 1;

				int location = L[K] - 1;

				T temp = vet[location];
				vet[location] = evicted;
				evicted = temp;

				L[K] -= 1;

				numMoves++;
			}
		}

  
		int threshold = (int)(1.25 * ((n / m) + 1));
		const int minElements = 30;

		for(K = m - 1; K >= 1; K--)
		{
      
			int classSize = L[K + 1] - L[K];

			if(classSize > threshold && classSize > minElements)
			{
            
				flashsort(&vet[L[K]], classSize);
			}
			else 
			{
				if(classSize > 1)
				{
					Ordenacao<T>::insertionsort(&vet[L[K]], classSize);
				}
			}
		}

			delete [] L;
		}

	}

#endif // ORDENACAO_H_INCLUDED
