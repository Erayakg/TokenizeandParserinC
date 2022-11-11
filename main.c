#include <stdio.h>
#include <ctype.h>


void opController(char token[]){
    int i=0;
        if(token[i]=='A'||token[i]=='B'||token[i]=='C'||token[i]=='D'||(int)token[i]<=255||(int)token[i]>=0){
            i++;
            if(token[i]=='X'){
                printf("Hatasiz");
            } else{
                printf("hatali");

            }
        }else
        {
            printf("hatali");
        }
}
void EtiketController(char token[]){

    int i=0;

    char etiket[] = "ETIKET";
    while (token[i] != '\0'){
        if(etiket[i] == token[i]){
            i++;
            if(token[i+1]=='\0'){
                if(token[i]=='1'||token[i]=='2'||token[i]=='3'||token[i]=='4'||
                token[i]=='5'||token[i]=='6'||token[i]=='7'||token[i]=='8'||token[i]=='9'){
                    printf("hatasiz\n");
                    break;
                }else
                {
                    printf("hatali\n");
                    break;
                }
            }
        } else{
            printf("hatali\n");
            break;
        }
    }
}
int CharCompare(char grammarToken[],char input[]){
    int i=0;
    while (input[i] != '\0'){
        if(grammarToken[i]==input[i]){
            printf("hatasiz");
            break;
        } else
        {
            printf("hatali");
            break;
        }

    }
}

int main() {

    FILE *fp;
    FILE *fp2;
    struct {
        char token[10];
    } Token[100];

    if ((fp = fopen("ornek.txt", "r"))) {
        int j = 0;

        while (!feof(fp)) {
            fgetc(fp);
            j++;
        }
        fclose(fp);

        char array[j];

        fp2 = fopen("ornek.txt", "r");

        for (int i = 0; i < j; ++i) {
            array[i] = getc(fp2);
        }

        fclose(fp2);

        int r = 0;
        int l = 0;
        for (int s = 0; s < j; s++) {
            if (array[s] ==toascii(0x0A) || array[s] == toascii(0x2C) || array[s] == toascii(91) ||
                array[s] == toascii(93) || array[s] == toascii(32) || array[s] == toascii(0x3A)) {
                Token[l].token[r] = '\0';
                s++;
                r = 0;
                l++;
            }
            Token[l].token[r++] = array[s];
        }

        char top[]="TOP";
        char crp[]="CRP";
        char atm[]="ATM";
        char bol[]="BOL";
        char cik[]="CIK";
        char ve[]="VE";
        char vey[]="VEY";
        char ds[]="DS";
        char dsd[]="DSD";
        char dal[]="DAL";
        char dk[]="DK";
        char db[]="DB";
        int g=0;
        for (int d = 0; d <  l; d++) {
            switch (Token[d].token[g]) {
                case  'T':
                    CharCompare(top,Token[d].token);//TOP kelimesi kontrol edilir
                    d++;
                    opController(Token[d].token);
                    d++;
                    opController(Token[d].token);
                    break;
                case 'C':
                    if(Token[d].token[g+1]=='R'){//CRP ve CIK hangi kelime  olduğu kontrol edilir
                        CharCompare(crp,Token[d].token);//CRP kelimesi kontrol edilir
                        d++;
                        opController(Token[d].token);
                        d++;
                        opController(Token[d].token);
                    } else{
                        CharCompare(cik,Token[d].token);//CIK kelimesi kontrol edilir
                        d++;
                        opController(Token[d].token);
                        d++;
                        opController(Token[d].token);
                    }
                    break;
                case 'A':
                    CharCompare(atm,Token[d].token);//ATM kelimesi kontrol edilir
                    d++;
                    opController(Token[d].token);
                    d++;
                    opController(Token[d].token);
                    break;
                case 'B':
                    CharCompare(bol,Token[d].token);//BOL kelimesi kontrol edilir
                    d++;
                    opController(Token[d].token);
                    d++;
                    opController(Token[d].token);
                    break;
                case 'V':
                    if(Token[d].token[g+2]=='Y'){
                        CharCompare(vey,Token[d].token);
                        d++;
                        opController(Token[d].token);
                        d++;
                        opController(Token[d].token);
                    } else{
                        CharCompare(ve,Token[d].token);
                        d++;
                        opController(Token[d].token);
                        d++;
                        opController(Token[d].token);
                    }
                    break;
                case 'D':
                    if(Token[d].token[g+1]=='S')
                    {
                            if(Token[d].token[g+2]=='D'){
                                CharCompare(dsd,Token[d].token);
                                d++;
                                EtiketController(Token[d].token);
                            } else{
                                CharCompare(ds,Token[d].token);
                                d++;
                                EtiketController(Token[d].token);
                            }
                    }
                    else if(Token[d].token[g+1]=='A')
                    {
                        CharCompare(dal,Token[d].token);
                        d++;
                        EtiketController(Token[d].token);
                    }
                    else if(Token[d].token[g+1]=='K')
                    {
                        CharCompare(dk,Token[d].token);
                        d++;
                        EtiketController(Token[d].token);
                    }
                    else if(Token[d].token[g+1]=='B')
                    {
                        CharCompare(db,Token[d].token);
                        d++;
                        EtiketController(Token[d].token);
                    }
                    break;
                    default:
                    printf("hatali");
                    break;


            }
        }
        printf("\n\n\n");
    for (int b = 0; b <l; b++) {
        printf("<<Token>>");
        printf("%s", Token[b].token);
        printf("<<Token>>");
        printf("\n\n");
    }
}
    else {
        printf("dosya bulunamadi");
    }

}


