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

int intal_compare(const char *intal_a, const char *intal_b)
{
    int length_a = 0, length_b = 0;
    length_a = strlen(intal_a) - 1;
    length_b = strlen(intal_b) - 1;

    //When lengths are different
    if (length_a > length_b)
        return 1;
    if (length_a < length_b)
        return -1;

    //When lengths are same
    int i = 0;
    //PROBABLY CHANGE REQUIRED
    while (i <= length_a)
    {
        if (intal_a[i] > intal_b[i])
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

char *intal_add(char *intal_a, char *intal_b)
{
    //Finding which one is bigger
    int bigger = intal_compare(intal_a, intal_b);
    if (bigger == -1)
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

//This has all functions for implimentation 
