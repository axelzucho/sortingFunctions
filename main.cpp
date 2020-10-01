#include <iostream>
#include <vector>
#include <chrono>
#include <math.h>
#include <fstream>

using namespace std;

int range = 10000;
int binaryIndex;
class Nodo{
public:
    int d;
    Nodo * izq;
    Nodo * der;
    Nodo(int dato){
        d = dato;
        izq = NULL;
        der = NULL;
    }

};

class BST{
public:
    Nodo * raiz = NULL;
    void insertar(Nodo ** p, int d){
        if(*p == NULL){
            Nodo * n = new Nodo(d);
            *p = n;
            return;
        }
        if((*p)->d >= d)
            insertar(&((*p)->izq),d);
        else insertar(&((*p)->der),d);
    }
    void inOrden(Nodo * p, int **a){ //Imprime los elementos en inOrden
        if(p==NULL) //Si el apuntador es nulo, regresa.
            return;
        inOrden(p->izq, a); //primero entra a la función del lado izquierdo
        (*a)[binaryIndex] =  p->d; //Imprime el elemento
        ++binaryIndex;
        inOrden(p->der, a); //Entra a la función del lado derecho
    }
};


void swap(int * a, int * b){
    int pass;
    pass = *a;
    *a = *b;
    *b = pass;
}

void bubbleSort(int ** a, int size){
    bool flag;
    int pass;
    for(int i = 0; i < size; ++i){
        flag = true;
        for(int x = 0; x < size-i-1; ++x){
            if((*a)[x] > (*a)[x+1]){
                swap((*a)[x], (*a)[x+1]);
                flag = false;
            }
        }
        if(flag) return;
    }

}

void cocktailSort(int ** a, int size){
    bool check = true;
    int start = 0;
    int end = size-1;
    while(check){
        check = false;
        for(int i = start; i < end; ++i){
            if((*a)[i] > (*a)[i+1]){
                swap((*a)[i],(*a)[i+1]);
                check = true;
            }
        }
        --end;
        for (int i = end - 1; i >= start; --i)
        {
            if ((*a)[i] > (*a)[i + 1])
            {
                swap((*a)[i],(*a)[i+1]);
                check = true;
            }
        }
    }

}

void insertionSort(int ** a, int size){
    int x;
    for(int i = 1; i < size; i++){
        x = i;
        while(x > 0 && (*a)[x] < (*a)[x-1]){
            swap((*a)[x], (*a)[x-1]);
            x -= 1;
        }
    }
}

void selectionSort(int **a, int size){
    int minimo;
    int pass;
    for(int i = 0; i < size-1; i++){
        minimo = i;
        for(int x = i+1; x < size; x++){
            if((*a)[minimo] > (*a)[x])
                minimo = x;
        }
        swap((*a)[i], (*a)[minimo]);
    }
}

int particion(int ** a, int lo, int hi){ //Funcion que regresa el indice que indica el punto donde está el pivote (a la izquierda los menores al pivote y a la derecha los mayores al pivote)
    int i = lo+1; //Esta variable nos ayudará a ir recorreindo los elementos de izquierda a derecha, comparándolos con el pivote
    int j = hi; //Esta variable nos ayudará a ir recorreindo los elementos de derecha a izquierda, comparándolos con el pivote
    int pivot = (*a)[lo]; //Define el pivote, la variable que se utilizará para comparar todos los elementos y acomodarlos con respecto de éste
    while(true){ //Loop hasta que se acceda al break
        while((*a)[i] <= pivot) //Mientras el valor del lado izquierdo sea más chico, se recorre el índice de la izquierda.
            i++;
        while((*a)[j] > pivot) //Mientras el valor del lado derecho sea más grande, se recorre el índice de la derecha.
            j--;
        if(i > j) //Si se entrelazan los índices, significa que ya sólo falta acomodar el pivote.
            break;
        swap((*a)[i],(*a)[j]); //Esta función se accede cuando aún no se entrelazan los índices, por lo que intercambia los valores en i y j para poder seguir acomodándolos
    }
    swap((*a)[lo],(*a)[j]); //intercambia el valor del pivote por el número que ocupa su lugar, dejando los menores a la izquierda y los mayores a la derecha
    return j; //Regresa el índice del pivote.
}

void quickSort2(int ** a, int lo, int hi){ //Ordena los elementos del vector utilizando quickSort
    if(hi <= lo) //Si el hi es menor o igual al lo, significa que esa parte del vector ya está acomodada y regresa.
        return;
    int j = particion(a,lo,hi); //Se iguala la variable j a lo que regresa la funcion particion que es enviada con los parametros de lo y hi.
    quickSort2(a,lo,j-1); //Accede nuevamente a la funcion quicksort ahora acomodando los elementos de la izquierda y de la derecha de la variable ya acomodadada
    quickSort2(a,j+1,hi);
}

void quickSort(int ** a, int size){
    quickSort2(a,0,size-1);
}

void merge(int ** a, int lo, int mid, int hi){  //Metodo que une dos segmentos ordenados
    vector <int> aux; //El vector donde se van a copiar los datos antes de ordenarlos
    int left = lo; //Variable que indicará el siguiente elemento a agregar del primer segmento
    int beg = lo; //variable que ayuda a no tener que copiar too el arreglo, sino que indica que posición del vector original es la primera del vector auxiliar.
    int right = mid+1; //Variable que indicará el siguiente elemento a agregar del segundo segmento
    for(int i = lo; i<=hi; i++) //Copia el segmento necesitado al vector auxiliar
        aux.push_back((*a)[i]);
    while(left <= mid && right <= hi){ //mientras siga habiendo elementos que ordenar de ambos segmentos
        if(aux[left-beg] < aux[right-beg]){ //Si el elemento de la izquierda es menor que el de la derecha, acomoda ese elemento y se aumentan los índices del primer segmento y del vector original
            (*a)[lo] = aux[left-beg];
            ++left;
            ++lo;
        }
        else{ //Si no es menor, acomoda el elemento del segundo segmento y se aumentan los índices del segundo segmento y del vector original
            (*a)[lo] = aux[right-beg];
            ++right;
            ++lo;
        }
    }
    if(left == mid+1){ //Si el segmento ya no tiene elementos que acomodar, copia todos los restantes del segundo segmento en el vector original.
        while(right <= hi){
            (*a)[lo] = aux[right-beg];
            ++right;
            ++lo;
        }
    }
    else{ //Si no, copia todos los elementos restantes del primer segmento en el vector original
        while(left <= mid){
            (*a)[lo] = aux[left-beg];
            ++left;
            ++lo;
        }
    }
}

void mergeSort2(int ** a, int lo, int hi){ //Ordena los elementos del vector utilizando mergeSort
    if(hi <= lo) //Si el hi es igual o menor al lo, significa que ya no se puede seguir partiendo por lo que ya está ordenado
        return;
    int mid = lo + (hi - lo)/2; //Define la variable mid
    mergeSort2(a,lo,mid); //Accede al metodo mergeSort pasando como parametros la primera mitad
    mergeSort2(a,mid+1,hi); //Accede al metodo mergeSort pasando como parametros la primera mitad
    merge(a,lo,mid,hi); //Accede al metodo merge con los paramétros de las posiciones donde se quieren juntar las dos segementos ya ordenados.
}

void mergeSort(int ** a, int size){
    mergeSort2(a, 0, size-1);
}

void countingSort(int **a, int size){
    int * sorted = new int[size];
    int * count;
    count = new int [range];
    for(int i = 0; i < range;++i){
        count[i] = 0;
    }
    for(int i = 0; i < size; ++i){
        ++count[(*a)[i]];
    }
    for(int i = 1; i < range;++i){
        count[i] += count[i-1];
    }
    for(int i = size-1; i >= 0; --i){
        sorted[(count[(*a)[i]]--)-1] = (*a)[i];
    }
    (*a) = sorted;
}

int getMax(int ** a, int size){
    int max = INT32_MIN;
    for(int i = 0; i < size; ++i){
        if((*a)[i] > max)
            max = (*a)[i];
    }
    return max;
}

int getMin(int ** a, int size){
    int min = INT32_MAX;
    for(int i = 0; i < size; ++i){
        if((*a)[i] < min)
            min = (*a)[i];
    }
    return min;
}


void countingRadixSort(int **a, int size, int exp){
    int * sorted = new int[size];
    int count[10] = {0};
    for(int i = 0; i < size; ++i){
        ++count[((*a)[i]/exp)%10];
    }
    for(int i = 1; i < 10;++i){
        count[i] += count[i-1];
    }
    for(int i = size-1; i >= 0; --i){
        sorted[(count[((*a)[i]/exp)%10]--)-1] = (*a)[i];
    }
    (*a) = sorted;
}

void radixSort(int ** a, int size){
    int max;
    max = getMax(a,size);
    for(int i = 1; max/i > 0; i*=10)
        countingRadixSort(a,size,i);
}


void shellSortGaps(int ** a ,int size, int gap){
    for(int i = gap; i < size; ++i){
        if((*a)[i-gap] > (*a)[i]){
            swap((*a)[i], (*a)[i-gap]);
            for(int j = i-gap; j >=gap; j-=gap){
                if((*a)[j-gap] > (*a)[j])
                    swap((*a)[j], (*a)[j-gap]);
                else break;
            }
        }
    }

}
void shellSort(int ** a, int size){
    shellSortGaps(a, size, 5);
    shellSortGaps(a, size, 2);
    shellSortGaps(a, size, 1);
}

void brickSort(int ** a, int size){
    for(int i = 0; i < size; ++i){
        if(i&1)
            for(int j = 1; j < size-2; j+=2)
                if((*a)[j] < (*a)[j-1]) swap((*a)[j],(*a)[j-1]);
        else
            for(int j = 2; j < size-2; j+=2)
                if((*a)[j] < (*a)[j-1]) swap((*a)[j],(*a)[j-1]);

    }
}

void timeCheck(void (*sort)(int**, int), int ** a, int size){
    chrono::high_resolution_clock::time_point t1 = chrono::high_resolution_clock::now();
    sort(a,size);
    chrono::high_resolution_clock::time_point t2 = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::microseconds>(t2-t1).count();
    cout << "Time for " << size << " is: " << duration << "ms" << "\n";
}

void allTimes(void(*sort)(int**, int), int **a, int x){
    for(int i = x; i < x+1; ++i){
        timeCheck(sort,a,pow(10,i));

    }
}

void binaryTreeSort(int ** a, int size){
    BST bt;
    bt.raiz = new Nodo ((*a)[0]);
    for(int i = 1; i < size; ++i){
        bt.insertar(&bt.raiz,(*a)[i]);
    }
    binaryIndex = 0;
    bt.inOrden(bt.raiz,a);

}

void heapify(int ** a, int size, int x){
    int largest = x;
    int left = 2*x + 1;
    int right = 2*x + 2;
    if(left < size && (*a)[left] > (*a)[largest])
        largest = left;
    if (right < size && (*a)[right] > (*a)[largest])
        largest = right;
    if(largest != x){
        swap((*a)[x], (*a)[largest]);
        heapify(a,size,largest);
    }
}

void heapSort(int ** a, int size){
    for(int i = (size/2) - 1; i >= 0; --i)
        heapify(a,size,i); //The biggest are the roots

    for(int i = size-1; i>= 0; --i){
        swap((*a)[0], (*a)[i]); //Puts the largest element at the end
        heapify(a,i,0); //Rearranges it
    }

}

void bucketSort(int ** a, int size){
    int max = getMax(a,size);
    int min = getMin(a,size);
    int divider = (int) ceil((max+1) / 49);
    vector < vector <int>> buckets;
    buckets.resize(50);
    for(int i = 0; i < size; ++i){
        buckets[(int)floor((*a)[i])/divider].push_back((*a)[i]);
    }
    for (int i = 0; i < 50; ++i)
        mergeSort((int **) &(buckets[i]), buckets[i].size());
    int x = 0;
    for(int i = 0; i < 50; ++i){
        for(int j = 0; j < buckets[i].size();++j){
            (*a)[x] = buckets[i][j];
            ++x;
        }
    }
}


int shellSort(int arr[], int N)
{
for (int gap = N/2; gap > 0; gap /= 2) {
 for (int i = gap; i < N; i += 1) {
      //sort sub lists created by applying gap
int temp = arr[i];
int j;
for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
arr[j] = arr[j - gap];
   
      arr[j] = temp;
   }
}
return 0;
}

int main() {
    ifstream myfile;
    myfile.open("numbers.txt");
    int  * arr = new int [1000000];
    for(int i = 0; i < 1000000; i ++){
        myfile >> arr[i];
    }
    myfile.seekg(0,ios::beg);
    allTimes(bucketSort,&arr,2);
    cout << "\n";
    myfile.close();

}
