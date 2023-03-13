# Processing-and-Analyzing-Sequential-Data

Am creat functiile specifice listelor dublu inlantuite: functiile de init, add, remove, free si print. 

Am folosit o lista auxiliara in care am copiat lista initiala, 
pentru ca aveam nevoie pentru calculul deviatiei de toate nodurile, inclusiv de cele 
sterse ulterior.

Pentru eliminare de exceptii folosind metode statistice, am folosit 3 liste: lista 
initiala (list), lista finala (list_median) si o lista auxiliara (list_aux). In lista 
auxiliara am copiat pe rand cate 5 noduri din lista initiala, apoi am sortat valorile 
reale ale respectivelor 5 noduri, urmand ca in lista finala sa adaug nodul 3 (nodul din mijloc) 
al listei auxiliare sortate.

Pentru eliminare de zgomot folosind filtre, am folosit 2 liste: lista initiala (list), 
lista finala (list_aritm). Am luat pe rand cate 5 noduri din lista initiala, am aflat media 
aritmetica a valorilor reale din respectivele noduri, urmand ca in lista finala sa adaug aceasta 
medie.

Pentru uniformizarea frecventei in timp a datelor am urmarit doar indicatiile din cerinta: 
daca diferenta temporala dintre 2 noduri era mai mare decat 100 si mai mica decat 1000, valoarea 
reala devenea egala cu media aritmetica dintre valorile reale, iar timestamp-ul din nodul curent 
devenea egal cu media dintre timestamp-ul din nodul anterior si timestamp-ul din nodul curent.

Similar, pentru completarea datelor am urmarit indicatiile din cerinta. Am implementat o functie 
pentru calculul celor 3 valori omega, apoi am parcurs lista, iar in cazul in care diferenta 
temporala dintre doua noduri era mai mare decat 1000, s-au adaugat noduri noi in lista: 
timestamp-ul creste din 200 in 200, iar valoarea reala a fiecarui nou nod a fost calculata 
conform specificatiilor si formulelor din enunt.

Pentru calcularea statisticilor, in primul rand, am sortat lista in functie de valorile reale, 
am apelat functia "smallest" pentru a gasi cel mai mare intreg mai mic decat primul element din 
lista (capatul inferior al primului interval), apoi am parcurs lista o singura data, pentru 
fiecare interval "sigma" numarand cate valori se incadreaza in acesta.

In main am initializat cele 3 liste folosite in task-uri, am apelat functiile in functie 
de argumentele primite in linia de comanda si am afisat lista finala, urmand eliberarea 
memoriei.
