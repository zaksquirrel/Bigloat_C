#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<ctype.h>
#include<string.h>

typedef struct bigint {
  int size; /* taille */
  unsigned int *value; /* valeur */
} bigint;

#define B 1000000000 //BASE 

int cmp(bigint a, bigint b);
bigint add(bigint a, bigint b);
bigint sub(bigint a, bigint b);
bigint product(bigint a, bigint b);
void intdiv(bigint a, bigint b, bigint *quotient, bigint *modulo);
bigint pow2n(unsigned int n);
void printbigint(bigint n);  
char* biginttostr(bigint n);
bigint *strtobigint(char *s);
char *biginttosubstr(bigint n, int first, int last);
bigint mersenne(unsigned int n);
void lehmer_test(unsigned int n);




int main()
{   
    bigint l;
    l.size = 2;
    l.value = (unsigned int *)malloc(2*sizeof(unsigned int));

    bigint l1;
    l1.size = 3;
    l1.value = (unsigned int *)malloc(3*sizeof(unsigned int));

    
    l.value[1] = 1;
    l.value[0] = 9;

    l1.value[2] = 2309;
    l1.value[1] = 292;
    l1.value[0] = 4;

    printf("p1 = %d\n",l.value[0]);
    printf("p1++ %d\n",l.value[1]);

    bigint haw;
    // printf("avant add \n");
    haw = add(l,l1);
    // printf("avant add \n");

    int a = cmp(l,l1);
    printf("a=%d\n",a);

    unsigned int *tab = haw.value;
    for(int i=0; i<4;i++){
        printf("%d\n",tab[i]);
    }

    printf("l\n");

    printbigint(l1);

    printf("\n");

    // biginttostr
    char* tabl;
    tabl = biginttostr(l1);
    while(*tabl !='\0'){
        printf("%c",*tabl);
        tabl++;
    }
    
    printf("\n");

    // product
    bigint hawhaw;
    hawhaw = product(l,l1);
    printf("produit\n");
    printbigint(hawhaw);
    // unsigned int *tabb = hawhaw.value;
    // for(int i=0; i<4;i++){
    //     printf("%d\n",tabb[i]);
    // }
    
    printf("\n");
    
    // biginttosubstr
    char* tabstr;
    tabstr = biginttosubstr(l1,2,9);
    for(int i=0; i<strlen(tabstr);i++){
        printf("%c",tabstr[i]);
    }

    printf("\n");
    printf("Quotient: ");
    printf("\n");
    free(tabstr);
    // free(tab);
    // free(tabb);
    // free(tabl);
    free(haw.value);
    free(hawhaw.value);
    free(l.value);
    free(l1.value);

    printf("Quotient: ");
    printf("\n");

//////////////////////////////////////////////
    
    printf("Quotient: ");
    bigint dividend;
    dividend.size = 3;
    dividend.value = (unsigned int*)malloc(dividend.size * sizeof(unsigned int));
    dividend.value[0] = 0;
    dividend.value[1] = 1;
    dividend.value[2] = 3;
    // dividend.value[3] = 232;

    printf("\n");

    bigint divisor;
    divisor.size = 2;
    divisor.value = (unsigned int*)malloc(divisor.size * sizeof(unsigned int));
    divisor.value[0] = 999999;
    divisor.value[1] = 23;

    printf("\n");

    bigint result_quotient, result_modulo;

    printf("Quotient: pre int div");
    printf("\n");

    // Call the intdiv function
    intdiv(dividend, divisor, &result_quotient, &result_modulo);

    printf("\n");

    // Print the quotient
    printf("Quotient: after intdiv\n");
    printbigint(dividend);
    printf("\n");
    printbigint(divisor);
    printf("\n");
    printf("quotient: ");
    printbigint(result_quotient);
    
    printf("\n");

    // Print the modulo
    printf("Modulo: ");
    printbigint(result_modulo);
    
    printf("\n");

    // Free allocated memory (assuming a proper implementation for freeing memory)
    free(result_quotient.value);
    free(result_modulo.value);
    printf("\n");

/////////////////////////////////////////////

printf("\n");

// test de sub 
    bigint x = { .size = 4, .value = (unsigned int[]){ 5, 4, 3, 2 } };
    bigint b = { .size = 3, .value = (unsigned int[]){ 2, 1, 1 } };

    bigint result = sub(x, b);
    printf("\n");
    printbigint(x);
    printf("\n");
    printbigint(b);
    printf("\n");
    printf("Result: \n");
    printbigint(result);
    printf("\n");

//////////////////////////////////////////////
    return 0;

}


int cmp(bigint a, bigint b){

    int min_size;
        if(a.size > b.size){
            min_size=b.size;
        }
        else {
            min_size=a.size;
        }

    if(a.size == b.size){
        for(int i=a.size-1; i >0 ; i--){
            if (a.value[i] != b.value[i]) {
                
                if (a.value[i] > b.value[i]) {
                    return 1;  // a > b
                } 
                
                else {
                    return -1; // a < b
                }
            }
        }
    }

    else if (a.size>b.size)
    {
        return 1;
    }
    

    else {
        return -1;
    }

}

// IDEA addition elementaire
// FIXED
bigint add(bigint a, bigint b){

    bigint result;
    int max;
    if(a.size > b.size){
        max = a.size+1;
    }
    else {
        max = b.size+1;
    }
    // i should have done this with the short version with the " p ? a:b", i gotta do it later on

    // printf("%d\n",max);
    result.value = (unsigned int *)malloc(max*sizeof(unsigned int));
    result.size = max;


    unsigned int r = B;
    unsigned int accumulation = 0;

    for(int i = 0 ; i<max; i++){
        // 
        if(i<a.size)
            accumulation+=a.value[i];
        
        if(i<b.size)
            accumulation+=b.value[i];
        
        result.value[i] = accumulation%r;
        accumulation = accumulation/r;
        // r*=B;
    }

    if(accumulation!=0){
       result.value[max] = accumulation; 
    }

    // adjust the size of our bigint, ca marche pas, aucune idee pourquoi
    if(result.value[max] != 0){
        result.size = max-1;
        result.value = realloc(result.value,result.size-1);
    }

    return result;

}


// il faut que je revisite celle la avant de deposer 
// il faut que je refais de nombreux test
// NEEDS FIXING
// FIXED
bigint sub(bigint a, bigint b){

    bigint result1;
    result1.value = (unsigned int*)malloc(a.size*sizeof(unsigned int));
    result1.size = a.size;

    int s = (a.size > b.size) ? a.size : b.size;
    int accumulation = 0;

    int temp = 0;
    for(int i = 0 ; i<s; i++){
        accumulation = a.value[i];

        if(i<b.size)
            accumulation -= b.value[i] + temp;

        if(a.value[i]<b.value[i] && i != s-1){
            result1.value[i] = accumulation + B;
            a.value[i+1] -= 1;
            temp = 1;
        }
        else{
            result1.value[i] = accumulation;
            temp = 0;
        }
    }
    
    return result1;
}


// IDEA : produit elementaire, comme on a fait pour addition elementaire
// j ai un probleme avec le decalage shifting, fonction ?? refais ca
// shifting avec une fonction est compliqué, et shifting with result.value[i], result.value[i+1] is problematic and doesn't do the job, the indices should move to the next one eaxh time
// what should i dooooooo
// FIXED i+j ********************************
bigint product(bigint a, bigint b){
    
    bigint result;
    result.size = a.size+b.size;
    result.value = calloc(result.size,sizeof(unsigned int)); // initialisation 0

    unsigned int accumulation = 0;

    for(int i=0; i < a.size ; i++){
        accumulation = 0;
        for(int j=0 ; j < b.size ; j++){
        accumulation += a.value[i]*b.value[j] + result.value[i+j];
        result.value[i+j] = accumulation%B; 
        accumulation /= B;   
        } 
        result.value[i+b.size] +=accumulation;

    }
    return result;
}


// // IDEA 1 intdiv : long division, but i don't know where to start
// // division entiere du plus important nombre du dividend par le plus important nombre du diviseur A = a b c B = d e (a/d b/d c/e), plus manipulation du reste a chaque fois
// // PROBLEM 1 : loop control, PROBLEM 2 : size du quotient et du modulo et affectation (utilisation dune variable pour accumuler puis faire modulo avec base 10^9 puis affecter)
// // PROBLEM 2 : manageavle, think of problem 1 first 
// // je suis un peu perdu sur celle la,

// void intdiv(bigint a, bigint b, bigint *quotient, bigint *modulo){    
//     // a doit etre plus grand que b 
//     if(a.size<b.size){
//         printf("ERREUR");
//     }
//     // b doit etre non null 
//     if(b.size == 1 && b.value[0] == 0){
//         printf("ERREUR, diviseur nul");
//     }
//     unsigned int accumulation_quotient = 0;
//     unsigned int accumulation_modulo = 0;   
//     unsigned int temp1; 
//     unsigned int temp2; 
//     int k = a.size-1;
//     while(k>=0){    
//         while(k>=b.size){
//             temp1 = a.value[k] / b.value[b.size-1];
//             temp2 = a.value[k] % b.value[b.size-1];
//             accumulation_quotient += temp1;
//             accumulation_modulo += temp2;
//             accumulation_quotient += accumulation_modulo/b.value[b.size-1];
//             // accumulation_modulo /= b.value[b.size-2];
//             accumulation_modulo %= b.value[b.size-1];
//             k--;
//             continue;
//         }
//         temp1 = a.value[k] / b.value[b.size-1];
//         temp2 = a.value[k] % b.value[b.size-1];
//         accumulation_quotient += temp1;
//         accumulation_modulo += temp2;
//         accumulation_quotient += accumulation_modulo/b.value[b.size-1];
//         // accumulation_modulo /= b.value[b.size-2];
//         accumulation_modulo %= b.value[b.size-1];
//         k--;
//     }
//     // remplissage des bigints quoient et modulo
// }



// IDEA 2 : we will caculate how many b is in a by successive substractions, that's our quotient, then quotien*b from a and that would our remainder
// this one seemes easier, as we will use the prevsious sub and product functions, IDEA 1 is complex (it took me so much time) 
// // j'utilise sub ici, il faut que je teste sub avant de tester intdiv
// SUB marche bien, mais j ai un pb ici en l utilisant

void intdiv(bigint a, bigint b, bigint *quotient, bigint *modulo) {
    // a doit etre plus grand que b 
    // printf("hwhwhwhwhwh\n");
    if (cmp(a, b) < 0) {
        printf("ERROR: Dividend is smaller than divisor\n");
        return;
    }
    printf("Quotient: ");
    if (b.size == 1 && b.value[0] == 0) {
        printf("ERROR: Division by zero\n");
        return;
    }
    printf("nn");
    printf("Quotient: 2");

    // Initialize variables
    bigint zero;
    zero.size = 1;
    zero.value = calloc(zero.size, sizeof(unsigned int));
    zero.value[0] = 0;

    bigint our_base;
    our_base.size = 1;
    our_base.value = calloc(our_base.size, sizeof(unsigned int));
    our_base.value[0] = B;

    bigint temp;
    temp.size = 1;
    temp.value = calloc(zero.size, sizeof(unsigned int));

    bigint init_quotient;
    init_quotient.size = 1;
    init_quotient.value = calloc(init_quotient.size, sizeof(unsigned int));
    init_quotient.value[0] = 0;

    // bigint temp2;
    
    // printf("\n");
    for (int i = a.size - 1; i >= 0; i--) {
        // temp.value[0] = 0;
        // temp = product(temp, our_base);
        temp.value[0] = a.value[i]*B; // notre a.value[i]*B
        printf("Quotient: before while ");

        int compteur = 0;
        // on compare temp et b, puisque temp>b y aura encore des b.value[i] dans a.value[i]
        while (cmp(temp, b) >= 0) {
            compteur++;
            temp = sub(temp, b);
        } 
        printf("\n");
        printf("Quotient: after while ");

        init_quotient = product(init_quotient, our_base);
        init_quotient.value[0] = compteur;
    }

    *quotient = init_quotient;
    *modulo = temp; // le reste

    free(zero.value);
    free(our_base.value);
}


// IDEA 3: utilisation du KNUTH ALORITHM, je dois essayer cella la
// 
// 

// void intdiv(bigint a, bigint b, bigint *quotient, bigint *modulo) {
//     if (b.size == 1 && b.value[0] == 0) {
//         printf("ERROR: Division by zero\n");
//         return;
//     }
//     bigint q = { .size = a.size, .value = calloc(a.size, sizeof(unsigned int)) };
//     // my_quotient.size = a.size;
//     // my_quotient.value = calloc(a.size,sizeof(unsigned int));
//     bigint r = { .size = b.size, .value = calloc(b.size, sizeof(unsigned int)) };
//     bigint v = { .size = b.size + 1, .value = calloc(b.size + 1, sizeof(unsigned int)) };
//     // Initialize values
//     for (int i = 0; i < b.size; i++) {
//         r.value[i] = a.value[a.size - b.size + i];
//         v.value[i + 1] = b.value[i];
//     }
//     for (int j = a.size - b.size; j >= 0; j--) {
//         int qhat = (r.value[b.size - 1] == v.value[b.size]) ? B - 1 : r.value[b.size - 1] * B + r.value[b.size - 2] / v.value[b.size];
//         int rhat = qhat * v.value[b.size - 1];
//         while (rhat > r.value[b.size - 2] * B + r.value[b.size - 3]) {
//             qhat--;
//             rhat -= v.value[b.size - 1];
//         }
//         // Multiply and subtract
//         bigint u = { .size = b.size, .value = calloc(b.size, sizeof(unsigned int)) };
//         for (int i = 0; i < b.size; i++) {
//             u.value[i] = qhat * v.value[i];
//         }
//         while (sub(r, u).value[0] < 0) {
//             qhat--;
//             for (int i = 0; i < b.size; i++) {
//                 u.value[i] -= v.value[i];
//             }
//         }
//         q.value[j] = qhat;
//         r = sub(r, u);
//         if (j > 0) {
//             r.value[b.size - 1] = a.value[j - 1];
//         }
//         free(u.value);
//     }
//     *quotient = q;
//     *modulo = r;
//     free(v.value);
// }


// j'utilise product() ici, il faut que product marche 
// IMPORTANT ********* FIX PRODUCT BEFORE SUBMETTING THIS ASSIGNMENT
// FIXED **********************
bigint pow2n(unsigned int n){

    bigint two,power;
    two.size = 1;
    two.value = (unsigned int*)malloc(sizeof(unsigned int));
    two.value[0] = 2;

    power.size = 1;
    power.value = (unsigned int*)malloc(sizeof(unsigned int));
    power.value[0]=1;

    
    for(int i=0;i<n;i++){
        power = product(two,power);
    }

    free(two.value);
    return power;
}

/// redo this, il faut que je refais celle la 
/// how to eliminate the zeros i get at the beinning of the list ???
/// done with a simple if
// FIXED **********************
void printbigint(bigint n){

    int base;
    for(int i=n.size-1;i>=0;i--){
        base = B; 
        unsigned int temp = n.value[i];
        // eliminer les zeros au debut 00000099 999999999
        while(base>1){
                base /= 10;
                if (i == n.size-1 && temp/base == 0) 
                    {
                        temp %= base;
                    }
                else{
                    printf("%d",temp/base);
                    temp %= base;
                }
            
            // bb /= 10;
            
        }
    }
}


// IDEA : store digits in an int table, then turn each one into a char, i found this way way easier, i tried to implement other methods, but i couldn;t get the -->
// desired results
// FIXED
char* biginttostr(bigint n) {
    char* tab = (char*)malloc((n.size * 9 + 1) * sizeof(char));
    int* tab1 = (int*)malloc((n.size * 9 + 1) * sizeof(int));

    int j = 0;
    int l = 0;

    // fetch digits as ints
    int base;
    for(int i=n.size-1;i>=0;i--){
        base = B; 
        unsigned int temp = n.value[i];
        while(base>1){
                base /= 10;
                if (i == n.size-1 && temp/base == 0)
                    {
                        temp %= base;
                        continue;
                    }
                else{
                    tab1[j] = temp/base;
                    temp %= base;  
                } 
                j++;
        }
    }

    // turn them into chars
    for(int i=0;i<j; i++){
        tab[l] = tab1[i] + '0';
        l++;
    }
    tab[l] = '\0'; 

    free(tab1);
    return tab;
}

// THIS NEEDS ADJUSTMENTS, il faut que refais ca ************** IMPORTANT
// the idea seems right, string to int tab, int tab into bigint
bigint *strtobigint(char *s){
    int len = strlen(s); 
    int size_bigint = (len+8)/9; // i used len.9 but it didn;t give me enough space, j ai du la changer 

    bigint *result;
    result = (bigint *)malloc(sizeof(bigint));

    result->size = size_bigint;
    result->value = (unsigned int*)malloc(size_bigint*sizeof(unsigned int)); 

    // IDEA : turn chars into ints
    int *tab = (int *)malloc(len*sizeof(int));
    int k=0;
    int j=0;
    for(int i=len-1;i>=0;i--){
        tab[j] = s[i] - '0';
        j++;
    }
    
    // IDEA : store in bigint, the idea is to multiply successive ints by multiple of 10 untill we get to base 10**9 , store in bigint, then move to the next xhunk of ints and do the same 
    // all over again 
    for(int j=0;j<len;j+=9){
        int accumulator = 0;
        int sub_base = 10;
        for(int i=j; i<len; i++){
            accumulator += tab[i]*sub_base;
            sub_base *=10;
        }
        result->value[k]=accumulator;
        k++;
    }

    free(tab);
    return result;
}

// IDEA: convertir turn bigint into a string using our function biginttostr, then extract str between first and last
// idea implemented, faut que je compile/test demain
char *biginttosubstr(bigint n, int first, int last){
    char *tab;
    char * tab1;
    int len = last-first +1;
    tab1 = (char *)malloc(len*sizeof(char));

    tab = biginttostr(n);
    int j = 0;
    for(int i = first;i<=last;i++){
        tab1[j] = tab[i];
        j++;
    }

    // terminaison du string 
    tab1[len]='\0';

    free(tab);
    return tab1;
}


bigint mersenne(unsigned int n){

    bigint mersenne_number, one, two;
    one.size = 1;
    one.value = (unsigned int *)malloc(one.size*sizeof(unsigned int));
    one.value[0] = 1;

    mersenne_number = sub(pow2n(n),one);

    free(one.value);
    free(two.value);

    return mersenne_number;
}

void lehmer_test(unsigned int n){

    bigint s;
    s.size = 1;
    s.value = (unsigned int *)malloc(s.size*sizeof(unsigned int));
    s.value[0] = 1;

    bigint two;
    two.size = 1;
    two.value = (unsigned int *)malloc(two.size*sizeof(unsigned int));
    two.value[0] = 2;

    bigint modulo_mersenne, quotient_mersenne;

    for(int i=0; i<n;i++){
        s = sub(product(s,two),two);
        intdiv(mersenne(n),s,&quotient_mersenne,&modulo_mersenne);
    }
    
    // test S(2^n-1)%Mn
    bigint zero;
    zero.size =1;
    zero.value = (unsigned int *)malloc(zero.size*sizeof(unsigned int));
    zero.value[0] = 0;

    int comparateur = cmp(modulo_mersenne,zero);

    if(comparateur == 0){
        printf("Mn is indeed a prime mersenne number, est premier");
    }

    free(zero.value);
    free(two.value);
    free(s.value);
    free(modulo_mersenne.value);
    free(quotient_mersenne.value);

}