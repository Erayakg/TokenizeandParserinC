#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
int pow(int taban,int us){
    if(us==0){
        return 1;
    }
    return taban* pow(taban,us-1);
}

void constController(char token[]){

    int newToken;
    newToken=atoi(token);

    if(newToken<255 && newToken>0){
        printf("\nhatasiz sabit: %d",newToken);
    } else{
        printf("\nhatali sabit: %d",newToken);
    }
}
void ramController(char token[]){
    int i=0;
    char newtokens[4];
    int j=i+1;
    if(token[i]=='['){
        while (token[i]!=']'){
        newtokens[i]=token[j];
        i++;
        j++;
        }
        newtokens[j]='/0';
    }
    printf("\nram:");
    constController(newtokens);
}
int opController(char token[]){
    int i=0;
    if(token[i]=='A'||token[i]=='B'||token[i]=='C'||token[i]=='D'){
        i++;
        if(token[i]=='X'){
            printf("\nHatasiz %s",token);
            return 1;
        } else{
            printf("\nhatali %s",token);
            return 0;
        }
    }
    else if(token[i]=='1'||token[i]=='2'||token[i]=='3'||token[i]=='4'||token[i]=='5'||token[i]=='6'||token[i]=='7'||token[i]=='8'||token[i]=='9')
    {
        constController(token);
    }
    else if(token[i]=='['){
        ramController(token);
    }
    else
    {
        printf("\nhatali %s",token);
        return 0;
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
                    printf("\nhatasiz %s",token);
                    break;
                }else
                {
                    printf("\nhatali %s",token);
                    break;
                }
            }
        } else{
            printf("\nhatali %s",token);
            break;
        }
    }
}
int CharCompare(char grammarToken[],char input[]){
    int i=0;
    bool a=true;
    while (input[i] != '\0'){
        if(grammarToken[i]==input[i]){
            i++;
        } else
        {
            a=false;
            break;
        }
    }
    if(a){
        printf("\nhatasiz %s",input);
    } else{
        printf("\nhatali %s",input);
    }
}

int main() {

    FILE *fp;
    FILE *fp2;
    struct {
        char token[10];
    } Token[100];
    char fileName[]="";
    //printf("dosya adini giriniz:");
    char dosyadi[]="ornek.txt";
    //gets(fileName);
    if ((fp = fopen(dosyadi, "r"))) {
        int j = 0;

        while (!feof(fp)) {
            fgetc(fp);
            j++;
        }
        fclose(fp);

        char array[j];

        fp2 = fopen(dosyadi, "r");

        for (int i = 0; i < j; ++i) {
            array[i] = getc(fp2);
        }

        fclose(fp2);

        int r = 0;
        int l = 0;
        for (int s = 0; s < j; s++) {
            if (array[s] ==toascii(0x0A) || array[s] == toascii(0x2C) || array[s] == toascii(32) || array[s] == toascii(0x3A)) {
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
                    printf("\nhatali");
                    break;
            }
        }
        printf("\n\n\n");
    for (int b = 0; b <l+1; b++) {
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