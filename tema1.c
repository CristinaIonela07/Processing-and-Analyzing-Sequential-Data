#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct node{
    int timestamp;
    double value;
    struct node *next;
    struct node *prev;
} node;

typedef struct DList{
    node *head;
    node *tail;
    int numarPerechi;
} DList;

//functie de initializare a listei
void init(DList **list){
    *list = (DList *)calloc(1, sizeof(DList));
    if (*list == NULL){
        printf("Lista nu a putut fi creata");
        return;
    }

    (*list)->numarPerechi = 0;
    (*list)->head = NULL;
    (*list)->tail = NULL;

}

//functie de adaugare nod nou la lista
void add(DList *list, int n, int ts, double vr){
    node *nod_nou = (node*) calloc(1, sizeof(node));
    nod_nou->timestamp = ts;
    
    nod_nou->value = vr;

    if (n == 0){
        list->head = nod_nou;
        list->tail = nod_nou;
        list->head->prev = NULL;
        list->tail->next = NULL;
   }

    else {
        node *nod_curent = list->head;

        for (int i=0; i< n-1; i++)
            nod_curent = nod_curent->next;
             
        if (nod_curent->next !=NULL){
            nod_nou->prev = nod_curent;
            nod_nou->next = nod_curent->next;
            nod_curent->next = nod_nou;
            nod_nou->next->prev = nod_nou;
        }
            
        else{
            nod_nou->prev = list->tail;
            nod_nou->next = NULL;
            nod_nou->prev->next = nod_nou;
            list->tail = nod_nou;
        }
   }
}

//functie de aproximare a valorilor reale
double convert (double n){
    double m = n * 100;
    int aux = (int)m;
    if (n < 0.00 && n > -0.05)
        return -0.00;

    if (n == 0)
        return n;

    else if (n > 0){
        if (m - aux < 0.5)
            n = (double)aux / 100;
        else n = (double)aux / 100 + 0.01;
    }
     
    else {
        if (m - aux < -0.5)
            n = (double)aux / 100 - 0.01;
        else n = (double)aux / 100;
    }
    
    return n;
}

//functie de afisare lista
void print_list(DList *list){
    node *nod_curent = list->head;

    if (nod_curent == NULL) printf("lista e vida\n"); 
    else {
        printf("%d\n", list->numarPerechi);

        while (nod_curent != list->tail) {
            printf("%d %0.2lf\n", nod_curent->timestamp, convert(nod_curent->value));
            nod_curent = nod_curent->next;
        }
    }
    printf("%d %0.2lf\n", nod_curent->timestamp, convert(nod_curent->value));
}

//functie de stergere nodul de pe pozitia n din lista
void rremove(DList *list, int n){
    node *nod_curent = list->head;

    for (int i = 0; i < (n - 1); i++){
        nod_curent = nod_curent->next;
    }

    node *nod_sters = nod_curent->next;
    node *nod_urmator = nod_curent->next->next;
    nod_urmator->prev = nod_curent;
    nod_curent->next = nod_urmator;

    list->numarPerechi--;
    
    free(nod_sters);
}

//functie pentru eliberarea memoriei alocate listei
void free_list(DList **list){

    node *nod_curent = (*list)->head;
    for (int i = 0; i < (*list)->numarPerechi; i++){
        node *nod_urmator = nod_curent->next;
        free(nod_curent);
        nod_curent = nod_urmator;        
    }
    
    (*list)->numarPerechi = 0;
    free(*list); 
    *list = NULL;  
}

//functie pentru calculul mediei valorilor numerice din fereastra de 5 elemente
double medie_fereastra (node *nod_curent){
    double x = (nod_curent->prev->prev->value + nod_curent->prev->value + nod_curent->value + nod_curent->next->value + nod_curent->next->next->value) / 5;
    return x;
}

//functie pentru calculul deviatiei standard a valoriilor din fereastra de 5 elemente
double deviatie ( node *nod_curent, double x){
    double s = (nod_curent->prev->prev->value - x)*(nod_curent->prev->prev->value - x) + (nod_curent->prev->value - x)*(nod_curent->prev->value - x) + (nod_curent->value - x)*(nod_curent->value - x) +(nod_curent->next->value - x)*(nod_curent->next->value - x) + (nod_curent->next->next->value - x)*(nod_curent->next->next->value - x);
    s = s / 5;
    return sqrt(s);
}

//functie de copiere a unei liste in alta lista
void coppy_list(DList *list1, DList *list2){
    list2->numarPerechi = list1->numarPerechi;
    node *nod_lista1 = list1->head;
    int i = 0;
    while (i < list2->numarPerechi){
        add(list2, i, nod_lista1->timestamp, nod_lista1->value);
        i++;
        nod_lista1 = nod_lista1->next;
    }
}

//functie pentru implementarea cerintei 1
void eliminare_exceptii(DList *list){
    DList *list_aux;
    init(&list_aux);
    coppy_list(list, list_aux);
   
    node *nod_curent = list_aux->head->next->next;
    int i = 2;
    double x, dev, dif, sum;
    while (nod_curent->next->next != NULL){
        x = medie_fereastra(nod_curent);
        dev = deviatie(nod_curent, x);
        dif = x - dev;
        sum = x+ dev;
           
        if (nod_curent->value <= dif || nod_curent->value >= sum){
            rremove(list, i);
            i--;
        }
                
        nod_curent =  nod_curent->next;
        i++;
    } 

    free_list(&list_aux);
}

//functie de sortare a valorilor reale intr-o lista
void sort(DList *list){
    node *nod1 = list->head;
    node *nod2 = list->head->next;
    while (nod1 != list->tail){
        while (nod2 != NULL){
            if (nod2->value < nod1->value){
                double aux = nod2->value;
                nod2->value = nod1->value;
                nod1->value = aux;
            }
            nod2 = nod2->next;
        } 
        nod1 = nod1->next;
        nod2 = nod1->next;
    }
}

//functie pentru implementarea cerintei 2.1
void filtrare_mediana (DList *list, DList *list_median){
    list_median->numarPerechi = list->numarPerechi - 4;
    int med = 0;

    node *nod_curent = list->head;
    int i, j;
    
    node *nod_start = list->head;
    for (i = 0; i < list->numarPerechi - 4; i++){ 
        DList *list_aux;
        init(&list_aux);
        list_aux->numarPerechi = 5;
        for (j = 0; j < 5; j++){
            add(list_aux, j, nod_curent->timestamp, nod_curent->value);
            nod_curent = nod_curent->next;
        }
    
        sort(list_aux);
        add(list_median, med, list_aux->head->next->next->timestamp, list_aux->head->next->next->value);
        med ++;
  
        free_list(&list_aux);
        nod_start = nod_start->next;
        nod_curent = nod_start;
    }
}

//functie pentru implementarea cerintei 2.2
void filtrare_aritmetica (DList *list, DList *list_aritm){
    list_aritm->numarPerechi = list->numarPerechi - 4;
    int aritm = 0;
    
    node *nod_curent = list->head;
    int i, j;
    
    node *nod_start = list->head;
    for (i = 0; i < list->numarPerechi - 4; i++){ 
        double ma = 0;
        double s = 0;
        for (j = 0; j < 5; j++){
            s = s + nod_curent->value;
            nod_curent = nod_curent->next;
        }
        ma = s / 5;
        add(list_aritm, aritm, nod_start->next->next->timestamp, ma);
        aritm ++;
  
        nod_start = nod_start->next;
        nod_curent = nod_start;
    }
}

//functie pentru implementarea cerintei 3
void uniformizare (DList *list){
    node *nod_curent = list->head;
    int i;
    for (i = 0; i < list->numarPerechi - 1; i++){
        if (nod_curent->next->timestamp - nod_curent->timestamp >= 100 && nod_curent->next->timestamp - nod_curent->timestamp <=1000){
            nod_curent->next->timestamp = (nod_curent->timestamp + nod_curent->next->timestamp) / 2;
            nod_curent->next->value = (double)(nod_curent->value + nod_curent->next->value) / 2;
        }
        nod_curent = nod_curent->next;
    }
}

//functie pentru calculul valorilor omega
double calcul_w(int i){
    double numarator = (double)i * i * 0.9 / 4 + 0.1;
    double numitor = 0;
    for (int j = 0; j < 3; j++){
        numitor = numitor + (double)j * j * 0.9 / 4 + 0.1;
    }
    return numarator / numitor;
}

//functie pentru implementarea cerintei 4
void completare_date (DList *list){
    node *nod_list = list->head->next->next;
    int poz = 3;
    double w1, w2, w3;
    w1 = calcul_w(0);
    w2 = calcul_w(1);
    w3 = calcul_w(2);

    while (nod_list->next->next->next != NULL){
        if (nod_list->next->timestamp - nod_list->timestamp >= 1000){
            int nod_ts = nod_list->timestamp + 200;
           
            int ts = nod_list->timestamp;
            int next_ts = nod_list->next->timestamp;
            double ppv = nod_list->prev->prev->value, pv = nod_list->prev->value, v = nod_list->value;
            double nnnv = nod_list->next->next->next->value, nnv = nod_list->next->next->value, nv = nod_list->next->value;
            int i = 1;

            while (nod_ts < next_ts){
                double c = i * 200 / (double)( next_ts - ts);
                double f = (1 - c) * (w1 * ppv + w2 * pv + w3 * v) + c * (w3 * nv + w2 * nnv + w1 * nnnv);
                add(list, poz, nod_ts, f);
                list->numarPerechi++;
                nod_ts = nod_ts + 200;
                poz++;
                i++;
                nod_list = nod_list->next;
            }
        }
        else {
            poz++;
            nod_list = nod_list->next;
        }
    }
}

//functie pentru calculul celei mai mari valori intregi 
//mai mica decat prima valoare reala din lista
int smallest (double a){
    if (a >= 0 )
        a = (int)a;
    else
        a = (int)a -1;

    return a;
}

//functie pentru implementarea cerintei 5
void statistici (DList *list, int sigma){
    sort(list);
    node *nod_curent = list->head;
    int val1 = smallest(nod_curent->value);

   int nr;
    while (nod_curent->next != NULL && val1 < list->tail->value){ 
        val1 = val1 + sigma;
         nr = 0;
        while (nod_curent->value <= val1 && nod_curent->value >= val1 - sigma){
            nr++;
            nod_curent = nod_curent->next;
        }
        if (nr !=0) 
            printf("[%d, %d] %d\n", val1 - sigma, val1, nr);
    }

    while (val1 < list->tail->value)
        val1 = val1 + sigma;
    printf("[%d, %d] 1\n", val1 - sigma, val1);
}

int main (int argc, char *argv[] ){
    DList *list;
    init(&list);
    scanf("%d", &list->numarPerechi);

    long int j = 0;
    int ts;
    double vr;
 
    while (j < list->numarPerechi){
        scanf("%d%lf", &ts, &vr);
        add(list, j, ts, vr);
        j++;
    }
    
    DList *lista_mediana;
    init(&lista_mediana);

    DList *lista_aritmetica;
    init(&lista_aritmetica);
 
 //apelare functii si afisare
    if (strcmp(argv[1], "--e1") == 0 && argc == 2){
        eliminare_exceptii(list);
        print_list(list);
    }

    else if (strstr(argv[1], "--st")){
        int c = atoi(strcpy(argv[1], argv[1] + 4));
        statistici(list, c);
    }

    else if (strcmp(argv[1], "--e2") == 0 && argc == 2){
        filtrare_mediana(list, lista_mediana);
        print_list(lista_mediana);
    }

    else if (strcmp(argv[1], "--e3") == 0 && argc== 2){
        filtrare_aritmetica(list, lista_aritmetica);
        print_list(lista_aritmetica);
    }

    else if (strcmp(argv[1], "--u") == 0 && argc == 2){
        uniformizare(list);
        print_list(list);
    }

    else if (strcmp(argv[1], "--c") == 0 && argc == 2){
        completare_date(list);
        print_list(list);
    }

    else if (strcmp(argv[1], "--u") == 0 && strcmp(argv[2], "--c") == 0 && argc == 3){
        uniformizare(list);
        completare_date(list);
        print_list(list);
    }

    else if (strcmp(argv[1], "--u") == 0 && strcmp(argv[2], "--c") == 0 && strcmp(argv[3], "--e3") == 0){
        uniformizare(list);
        completare_date(list);
        filtrare_aritmetica(list, lista_aritmetica);
        print_list(lista_aritmetica);
    }

    else if (strcmp(argv[1], "--e3") == 0 && strcmp(argv[2], "--u") == 0 && strcmp(argv[3], "--u") == 0){
        filtrare_aritmetica(list, lista_aritmetica);
        uniformizare(lista_aritmetica);
        uniformizare(lista_aritmetica);
        print_list(lista_aritmetica);
    }

    else if (strcmp(argv[1], "--e2") == 0 && strcmp(argv[2], "--u") == 0 && strcmp(argv[3], "--u") == 0){
        filtrare_mediana(list, lista_mediana);
        uniformizare(lista_mediana);
        uniformizare(lista_mediana);
        print_list(lista_mediana);
    }

    else if (strcmp(argv[1], "--e1") == 0 && strcmp(argv[2], "--e2") ==0 && argc== 3){
        eliminare_exceptii(list);
        filtrare_mediana(list, lista_mediana);
        print_list(lista_mediana);
    }
    
    else if (strcmp(argv[1], "--e1") == 0 && strcmp(argv[2], "--e3") ==0 && argc == 3){
        eliminare_exceptii(list);
        filtrare_aritmetica(list, lista_aritmetica);
        print_list(lista_aritmetica);
    }
    
    else if (strcmp(argv[1], "--e1") == 0 && strcmp(argv[2], "--e2") == 0 && strcmp(argv[3], "--e3") == 0 && argc == 4){
        eliminare_exceptii(list);
        filtrare_mediana(list, lista_mediana);
        filtrare_aritmetica(lista_mediana, lista_aritmetica);
        print_list(lista_aritmetica);
    }
    
    else if (strcmp(argv[1], "--e2") == 0 && strcmp(argv[2], "--e3") == 0 && strcmp(argv[3], "--e1") == 0 && strcmp(argv[4], "--u") == 0){
        filtrare_mediana(list, lista_mediana);
        filtrare_aritmetica(lista_mediana, lista_aritmetica);
        eliminare_exceptii(lista_aritmetica);
        uniformizare(lista_aritmetica);
        print_list(lista_aritmetica);
    }
    
    else if (strcmp(argv[1], "--e1") == 0 && strcmp(argv[2], "--e2") == 0 && strcmp(argv[3], "--e3") == 0 && strcmp(argv[4], "--u") == 0 && strcmp(argv[5], "--c") == 0){
        eliminare_exceptii(list);
        filtrare_mediana(list, lista_mediana);
        filtrare_aritmetica(lista_mediana, lista_aritmetica);
        uniformizare(lista_aritmetica);
        completare_date(lista_aritmetica);
        print_list(lista_aritmetica);
    }

//eliberare memorie
    free_list(&lista_aritmetica);
    free_list(&lista_mediana);
    free_list(&list);

    return 0;
}