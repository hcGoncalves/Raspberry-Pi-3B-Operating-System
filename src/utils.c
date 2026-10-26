void intToString(char *str, int str_size, int N) {
    int i = 0;

    int negative = (N < 0);
    unsigned int un = negative ? -(unsigned int)N : (unsigned int)N;

    if (un == 0) {
        str[i++] = '0'; str[i++] = '\0';
        return;
    }

    while (un > 0 && i < str_size-1) {
        unsigned int q = un / 10;
        str[i++] = (char)(un - q * 10) + '0';
      	un = q;
    }

    if (negative) str[i++] = '-';

    str[i] = '\0';

    for (int j = 0, k = i - 1; j < k; j++, k--) {
        char temp = str[j];
        str[j] = str[k];
        str[k] = temp;
    }
}

int stringLength(char str[]) {
    int length = 0;

    while (str[length] != '\0') {
        length++;
    }

    return length;
}

int equalStrings(char str1[], char str2[]) {
    int i = 0;
    while (str1[i] == str2[i]) {
        if (str1[i] == '\0' || str2[i] == '\0') return 1;
        i++;
    }

    return 0;
}

//Hello == Hel
int equalTruncatedStrings(char str1[], char str2[]) {
    int i = 0;
    while (str1[i] == str2[i] || (str1[i] == '\0' || str2[i] == '\0')) {
        if (str1[i] == '\0' || str2[i] == '\0') return 1;
        i++;
    }

    return 0;
}
