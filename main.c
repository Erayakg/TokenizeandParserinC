#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
int converterInt(char value[]){
    int i=0;
    int j=1;
    int newValue=0;
    while (value[i]!='\0'){
        i++;
        j=j*10;
    }
    j=j/10;
    int s;
    for (int k = 0; k <i ; k++) {
        s=(int)value[k];
        newValue+=(s-48)*j;
        j=j/10;
    }
    return  newValue;
}
void constController(char token[]){
/*  Fonksiyon girilen char değerini alır ve tipini integer olarak değiştirir.
 *  girilen sayının 0 ile 255  arasında bir sayı olduğu kontrol edilir */
    int newToken;
    newToken=converterInt(token);

    if(newToken<255 && newToken>0){
        printf("\nhatasiz sabit: %d",newToken);
    } else{
        printf("\nhatali sabit: %d",newToken);
    }
}

void ramController(char token[]){
    /* Grammerdeki [int] değerini kontrol eden fonksiyondur.*/
    int i=0;
    char newtokens[5];
    int j=i+1;
    if(token[i]=='['){//ilk eleman [ ise başlar ve ] değeri gelene kadar bir başka diziye atar.Böylece sadece köşeli parantez içindeki değer okunur
        while (token[i]!=']'){
        newtokens[i]=token[j];
        i++;
        j++;
        }
        newtokens[j-2]='\0';
    }
    printf("\nram:");
    constController(newtokens);
}
int opController(char token[]){
    /*gramerdeki <op> AX | BX | CX | DX | [<sabit>] | <sabit> kontrol edildiği fonksiyondur
     * */
    int i=0;
    if(token[i]=='A'||token[i]=='B'||token[i]=='C'||token[i]=='D'){//ilk karakter yandakilerden biriyse diğeri x olmak zorundadır
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
        // ilk karakter sayıysa sabit kontrolü yapılır.(0-255 arası)
        constController(token);
    }
    else if(token[i]=='['){
        // ilk karakter köşeli parantez ise ram kontrolü yapılır
        ramController(token);
    }
    else
    {
        printf("\nhatali %s",token);
        return 0;
    }
}
void EtiketController(char token[]){
    /*gramerdeki <etiket>  ETIKET1 | ETIKET2 | … | ETIKET9 kontrolünün yapıldığı fonksiyondur.*/
    int i=0;
    char etiket[] = "ETIKET";//gelen token bu string ifadeyle karşılaştrılır,
    while (token[i] != '\0'){
        if(etiket[i] == token[i]){
            i++;
            if(token[i+1]=='\0'){//karşılaştırma hatasız ise son karakter kontrolü yapılır
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
    /*input olarak gelen 2 karakter dizisini karşılaştırır*/
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
    } Token[100];//dosyadaki kelimelerin struct yapısı oluşturulur
    char fileName[]="";
    printf("dosya adini giriniz:");
    gets(fileName);
    if ((fp = fopen(fileName, "r"))) {
        int j = 0;

        while (!feof(fp)) {
            fgetc(fp);
            j++;
        }
        fclose(fp);

        char array[j];

        fp2 = fopen(fileName, "r");

        for (int i = 0; i < j; ++i) {
            array[i] = getc(fp2);
        }
        //yukarıdaki işlemlerde dosya açılır okunur ve bütün elemanlar bir diziye aktarılır.
        fclose(fp2);

        int r = 0;
        int l = 0;
        for (int s = 0; s < j; s++) {
            //ayraçlara göre tokenlaştırma işlemi yapılır
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
        printf("\n <<  Tokens  >> \n");
        for (int b = 0; b <l+1; b++) {
            printf("<<Token>>");
            printf("%s", Token[b].token);
            printf("<<Token>>");
            printf("\n\n");
        }
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
                        CharCompare(vey,Token[d].token);//VEY kelimesi kontrol edilir
                        d++;
                        opController(Token[d].token);
                        d++;
                        opController(Token[d].token);
                    } else{
                        CharCompare(ve,Token[d].token);//VE kelimesi kontrol edilir
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
                                CharCompare(dsd,Token[d].token);//DSD kelimesi kontrol edilir
                                d++;
                                EtiketController(Token[d].token);
                            } else{
                                CharCompare(ds,Token[d].token);//DS kelimesi kontrol edilir
                                d++;
                                EtiketController(Token[d].token);
                            }
                    }
                    else if(Token[d].token[g+1]=='A')
                    {
                        CharCompare(dal,Token[d].token);//DAL kelimesi kontrol edilir
                        d++;
                        EtiketController(Token[d].token);
                    }
                    else if(Token[d].token[g+1]=='K')
                    {
                        CharCompare(dk,Token[d].token);//DK kelimesi kontrol edilir
                        d++;
                        EtiketController(Token[d].token);
                    }
                    else if(Token[d].token[g+1]=='B')
                    {
                        CharCompare(db,Token[d].token);//DB kelimesi kontrol edilir
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

}
    else {
        printf("dosya bulunamadi");
    }

}