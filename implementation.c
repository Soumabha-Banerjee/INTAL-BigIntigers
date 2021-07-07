#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *removeLeadZero(char *res)
{

    int nonz = 0, newlen = 0, i = 0;
    for (nonz = 0; nonz < strlen(res); nonz++)
    {
        if (res[nonz] != 48)
            break;
    }
    //printf("NONZ == %d\n",nonz);
    if (nonz == 0)
        return res;
    newlen = strlen(res) - nonz;
    for (i = 0; i < newlen; i++)
        res[i] = res[i + nonz];
    //res = (char*)realloc(res,sizeof(char)*(newlen+1)); //6474
    res[i] = '\0';
    if (res[0] == '\0')
    {
        free(res);
        res = (char *)calloc(2, sizeof(char));
        res[0] = 48;
        res[1] = '\0';
    }
    return res;
}

int intal_compare(const char* intal_a,const char* intal_b)
{
    int length_a = 0, length_b = 0;
    length_a = strlen(intal_a)-1;
    length_b = strlen(intal_b)-1;
    
    //When lengths are different
    if( length_a > length_b )
        return 1;
    if (length_a < length_b)
        return -1;
    
    //When lengths are same
    int i = 0;
    //PROBABLY CHANGE REQUIRED
    while( i <= length_a)
    {
        if(  intal_a[i] > intal_b[i] )
            return 1;
        if (intal_a[i] < intal_b[i])
            return -1;
        i++;
    }

    //All characters are equal
    return 0;
}

static void intal_adder(const char *intal1, const char *intal2, char *res)
{
    //printf("Reached intal_adder\n");
    int l1 = strlen(intal1) - 1;
    int l2 = strlen(intal2) - 1;
    int sum = 0, carry = 0, k = l1 + 1;
    //printf("%d %d %d\n",l1,l2,k);
    for (int i = 0; i <= k; i++)
        res[i] = '0';
    while (l2 >= 0)
    {
        sum = intal1[l1] + intal2[l2] + carry - 96;
        res[k] = 48 + sum % 10;
        carry = sum / 10;
        --l1;
        --l2;
        --k;
    }
    while (l1 >= 0)
    {
        sum = intal1[l1] + carry - 48;
        res[k] = 48 + sum % 10;
        carry = sum / 10;
        --l1;
        --k;
    }
    if (carry)
    {
        res[k] = 48 + carry;
    }
}

char* intal_add(char *intal_a, char *intal_b)
{
    //Finding which one is bigger
    int bigger = intal_compare(intal_a, intal_b);
    if( bigger == -1 )
    {
        char *result = (char *)calloc(strlen(intal_b) + 2, sizeof(char));
        intal_adder(intal_b, intal_a, result);
        return removeLeadZero(result);
    }
    char *result = (char *)calloc(strlen(intal_a) + 2, sizeof(char));
    intal_adder(intal_a, intal_b, result);
    return removeLeadZero(result);
}

static char *intal_differ(const char *intal1, const char *intal2)
{
    int l1 = strlen(intal1) - 1;
    int l2 = strlen(intal2) - 1;
    int top = 0, bottom = 0, k = l1, i;
    int taken = 0;
    char *res = (char *)calloc(k + 2, sizeof(char));
    for (i = 0; i <= k; i++)
        res[i] = 48;
    res[i] = '\0';
    while (l2 >= 0)
    {
        top = intal1[l1] - 48;
        bottom = intal2[l2] - 48;
        if (taken > 0)
        {
            if (taken == 1)
            {
                //printf("if %c\n",intal1[l1]);
                top -= 1;
            }
            else
            {
                //printf("else %c\n",intal1[l1]);
                top = 9 + intal1[l1] - 48;
            }
            //printf("updated top in if taken >0\n");
            --taken;
        }
        //printf("%d %d %d\n",top, bottom, (top-bottom));
        if (top < bottom)
        {
            //int look = 0;
            do
            {
                ++taken;
            } while (intal1[l1 - taken] == 48 && (l1 - taken) > 0);
            top += 10;
        }

        //printf("%d %d %d %d\n",top, bottom, (top-bottom), taken);
        res[k] = 48 + top - bottom;
        --l1;
        --l2;
        --k;
    }
    //printf("taken = %d\n",taken);
    while (l1 >= 0)
    {
        if (taken > 0)
        {
            res[k] = intal1[l1] - 1;
            if (intal1[l1] == 48)
                res[k] = 57;
            --taken;
        }
        else
        {
            res[k] = intal1[l1];
        }
        --l1;
        --k;
    }
    return res;
}
char *intal_diff(const char *intal1, const char *intal2)
{
    int bigger = intal_compare(intal1, intal2);
    //int i;
    //printf("bigger = %d\n",bigger);
    if (bigger == -1)
    {
        //char* res = (char*)calloc(strlen(intal2)+1,sizeof(char));
        char *res = intal_differ(intal2, intal1);
        return removeLeadZero(res);
    }
    //char* res = (char*)calloc(strlen(intal1)+1,sizeof(char));
    char *res = intal_differ(intal1, intal2);
    return removeLeadZero(res);
}

static int isZero(const char *intal)
{
    int i = 0, len = strlen(intal);
    while (i < len)
    {
        if (intal[i] == 48)
            ++i;
        else
            break;
    }
    //printf("values of i%d, strlen = %d\n",i,len);
    if (intal[i] == '\0')
        return 1;
    //printf("Returning zero\n");
    return 0;
}

static void intal_multy(const char *intal1, const char *intal2, char *res)
{
    int l1 = strlen(intal1);
    int l2 = strlen(intal2);
    int sum = 0, carry = 0;
    int l3 = l1 + l2;
    int ptr1 = 1;
    int ptr2;
    int i;
    //res = (char*)realloc(res,l3*sizeof(char));
    //printf("strlen before%d\n",strlen(res));
    for (i = 0; i < l3; i++)
    {
        res[i] = '0';
    }
    for (i = l2 - 1; i >= 0; i--)
    {
        sum = 0;
        carry = 0;
        ptr2 = l3 - ptr1;
        for (int j = l1 - 1; j >= 0; j--)
        {
            //printf("%c %c\n",intal1[j], intal2[i]);
            sum = (intal1[j] - '0') * (intal2[i] - '0') + (res[ptr2] - '0') + carry;
            //printf("%c %c %d\n",intal1[j], intal2[i],sum);
            res[ptr2] = 48 + sum % 10;
            carry = sum / 10;
            --ptr2;
            //printf("%d %d\n",ptr1,ptr2);
        }
        if (carry)
        {
            res[ptr2] += carry;
        }
        ++ptr1;
    }
}

char *intal_multiply(const char *intal1, const char *intal2)
{
    //printf("%d %d\n",isZero(intal1),isZero(intal2));

    if (!isZero(intal1) && !isZero(intal2))
    {
        int bigger = intal_compare(intal1, intal2);
        //int i;
        char *res = (char *)calloc(strlen(intal1) + strlen(intal2) + 1, sizeof(char));
        if (bigger >= 0)
        {
            intal_multy(intal1, intal2, res);
        }
        else
        {
            intal_multy(intal2, intal1, res);
        }
        return removeLeadZero(res);
    }
    char *res = (char *)malloc(2 * sizeof(char));
    strcpy(res, "0");
    return res;
}

char *intal_factorial(unsigned int n)
{
    char *res = (char *)calloc(2, sizeof(char));
    strcpy(res, "1");
    if (n == 0 || n == 1)
    {
        return res;
    }
    char *num = (char *)calloc(2, sizeof(char));
    char *copy = NULL;
    strcpy(num, "1");
    unsigned int i = 2;
    while (i <= n)
    {
        copy = intal_add(num, "1");
        free(num);
        num = copy;
        copy = intal_multiply(num, res);
        free(res);
        res = copy;
        ++i;
    }
    //free(copy);
    free(num);
    return removeLeadZero(res);
}

char *intal_pow(const char *intal1, unsigned int n)
{
    if (isZero(intal1))
    {
        char *res = (char *)malloc(sizeof(char) * 2);
        strcpy(res, "0");
        return res;
    }
    char *res = (char *)malloc(sizeof(char) * 2);
    strcpy(res, "1");
    char *x = (char *)malloc(sizeof(char) * (strlen(intal1) + 1));
    strcpy(x, intal1);
    char *temp;
    while (n > 0)
    {
        if (n & 1)
        {
            temp = intal_multiply(res, x);
            free(res);
            res = temp;
        }
        n = n >> 1;
        temp = intal_multiply(x, x);
        free(x);
        x = temp;
    }
    free(x);
    return res;
}

void main()
{
    int n = 12;
    char **a = (char **)malloc(n * sizeof(char *));
    for (int i = 0; i < n; i++)
    {
        a[i] = (char *)malloc(1001 * sizeof(char));
    }

    strcpy(a[0], "1234512345123451234512345");
    strcpy(a[1], "543215432154321543215432154321");
    strcpy(a[2], "0");
    strcpy(a[3], "1234512345123451234512345");
    strcpy(a[4], "1234512345123451234512344");
    strcpy(a[5], "12");
    strcpy(a[6], "265252859812191058636308480000000");
    strcpy(a[7], "265252859812191058636308480000000");
    strcpy(a[8], "5432154321543215432154321");
    strcpy(a[9], "3");
    strcpy(a[10], "1000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000");
    strcpy(a[11], "1230231922161117176931558813276752514640713895736833715766118029160058800614672948775360067838593459582429649254051804908512884180898236823585082482065348331234959350355845017413023320111360666922624728239756880416434478315693675013413090757208690376793296658810662941824493488451726505303712916005346747908623702673480919353936813105736620402352744776903840477883651100322409301983488363802930540482487909763484098253940728685132044408863734754271212592471778643949486688511721051561970432780747454823776808464180697103083861812184348565522740195796682622205511845512080552010310050255801589349645928001133745474220715013683413907542779063759833876101354235184245096670042160720629411581502371248008430447184842098610320580417992206662247328722122088513643683907670360209162653670641130936997002170500675501374723998766005827579300723253474890612250135171889174899079911291512399773872178519018229989376");
    char *result1;
    int index1;

    result1 = intal_add(a[0], a[1]);
    if (!result1)
    {
        printf("Test intal_add FAILED.\n");
    }
    else
    {
        if (0 == strcmp(result1, "543216666666666666666666666666"))
        {
            printf("Test intal_add PASSED\n");
        }
        else
        {
            printf("Test intal_add FAILED.\nYour answer: %s\nExpected answer: %s\n", result1, "543216666666666666666666666666");
        }
        free(result1);
    }

    index1 = intal_compare(a[0], a[1]);
    if (-1 == index1)
    {
        printf("Test intal_compare PASSED\n");
    }
    else
    {
        printf("Test intal_compare FAILED.\nYour answer: %d\nExpected answer: %d\n", index1, -1);
    }
    index1 = intal_compare("99999999999999999999999999999", "99999999999999999999999999999");
    if (0 == index1)
    {
        printf("Test intal_compare PASSED\n");
    }
    else
    {
        printf("Test intal_compare FAILED.\nYour answer: %d\nExpected answer: %d\n", index1, 0);
    }

    result1 = intal_diff("99999999999999999999999999999", "99999999999999999999999999999");
    if (!result1)
    {
        printf("Test intal_diff FAILED.\n");
    }
    else
    {
        if (0 == strcmp(result1, "0"))
        {
            printf("Test intal_diff PASSED\n");
        }
        else
        {
            printf("Test intal_diff FAILED.\nYour answer: %s\nExpected answer: %s\n", result1, "0");
        }
        free(result1);
    }

    result1 = intal_multiply(a[8], a[5]);
    if (!result1)
    {
        printf("Test intal_multiply FAILED.\n");
    }
    else
    {
        if (0 == strcmp(result1, "65185851858518585185851852"))
        {
            printf("Test intal_multiply PASSED\n");
        }
        else
        {
            printf("Test intal_multiply FAILED.\n.Your answer: %s\nExpected answer: %s\n", result1, "65185851858518585185851852");
        }
        free(result1);
    }

    result1 = intal_factorial(100);
    if (!result1)
    {
        printf("Test intal_factorial FAILED.\n");
    }
    else
    {
        if (0 == strcmp(result1, "93326215443944152681699238856266700490715968264381621468592963895217599993229915608941463976156518286253697920827223758251185210916864000000000000000000000000"))
        {
            printf("Test intal_factorial PASSED\n");
        }
        else
        {
            printf("Test intal_factorial FAILED.\nYour answer: %s\nExpected answer: %s\n", result1, "93326215443944152681699238856266700490715968264381621468592963895217599993229915608941463976156518286253697920827223758251185210916864000000000000000000000000");
        }
        free(result1);
    }
    result1 = intal_pow("2", 3000);
    if (!result1)
    {
        printf("Test intal_pow FAILED.\n");
    }
    else
    {
        if (0 == strcmp(result1, a[11]))
        {
            printf("Test intal_pow PASSED\n");
        }
        else
        {
            printf("Test intal_pow FAILED.\nYour answer: %s\nExpected answer: %s\n", result1, a[11]);
        }
        free(result1);
    }
}   
