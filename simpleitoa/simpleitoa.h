#ifndef simpleitoa_h
#define simpleitoa_h

template <class T> void swap ( T& a, T& b )
{
  T c(a); a=b; b=c;
}

void simplereverse(char str[], int length)
{
    int start = 0;
    int end = length;
    while (start < end)
    {
        swap(*(str+start), *(str+end));
        start++;
        end--;
    }
}
 
// Implementation of itoa()// source: http://www.geeksforgeeks.org/implement-itoa/
void simpleitoa(uint32_t num, int base, char* dest)
{
    int i = 0;
    //bool isNegative = false;
 
    /* Handle 0 explicitely, otherwise empty string is printed for 0 */
    if (num == 0)
    {
        dest[i++] = '0';
        dest[i] = '\0';
        return;
    }
 
    // In standard itoa(), negative numbers are handled only with 
    // base 10. Otherwise numbers are considered unsigned.
    /*if (num < 0 && base == 10)
    {
        isNegative = true;
        num = -num;
    }*/
 
    // Process individual digits
    while (num != 0)
    {
        int rem = num % base;
        dest[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        num = num/base;
    }
 
    // If number is negative, append '-'
    /*if (isNegative){
        dest[i++] = '-';
    }*/
 
    dest[i] = '\0'; // Append string terminator
 
    // Reverse the string
    simplereverse(dest, i-1);
}
#endif