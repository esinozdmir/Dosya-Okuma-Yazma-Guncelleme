
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#define SIZE 10000
#define BUFFER_SIZE 10000
#define MAX_LINE_LENGTH 1000
#define MAX_WORDS   1000

struct {
    char *adres[SIZE];
}employee;

void indexOf(FILE *fptr, const char *word,struct dirent *dosya_entry2,struct dirent *dosya_entry);

void etiket_bul(const char *word,char d[BUFFER_SIZE]);

void indexOf_etiket(FILE *fptr, const char *etiketli_hal,struct dirent *dosya_entry2,struct dirent *dosya_entry,const char *word,int *control);

void normal_etiketmi(const char *word_txt,struct dirent *dosya_entry2,int *control);

void replaceWordInText(FILE *fptr,char word[100],char new_word[100],struct dirent *dosya_entry2,struct dirent *dosya_entry);

void replaceAll(char *str, const char *oldWord, const char *newWord);

void etiket_saydirma(FILE *fptr);

void all_file_content(FILE *fptr,FILE *dosya);

void count_all_files(FILE *dosya,FILE *output,struct dirent *dosya_entry2);

void create_output(FILE *fptr,FILE *dosya);

void istenen_etiketmi(const char *delp,FILE *butun);

int main() {

    char *directory_path="/Users/esinozdemir/Desktop/Üniversite";
    int dosyaindex=0;
    int txtindex=0;
    int control1=0;

    DIR *dir;
    struct dirent *dosya_entry;
    struct dirent *dosya_entry2;
    char word[500];
    char new_word[500];
    char gec[500];//geçiçi değişken arananı txt ile karşılaştırıp normal etiket olma durumunu öğrenmek için
    char gecYeni[500];
    int choice=0;
    char etiketli_hal[BUFFER_SIZE];
    int control=0;
    int sec=0;
    int  etiket_sayisi;
    const char *delp;
    FILE *butun;
    butun=fopen("/Users/esinozdemir/Desktop/butun.txt", "w");

    while(1){
    printf("aşağıdaki seçeneklerden birini seçiniz.\n");
        printf("1)Arama\n");
        printf("2)Güncelleme\n");
        printf("3)Dosyaya yazdırma\n");
        printf("4)çıkış\n");
        printf("seçiminizi giriniz:");
        scanf("%d", &choice);

    switch(choice){

        case 1:


    printf("Enter word to search in file: ");
            scanf("%s",word);
    strcpy(gec, word);
    strcat(gec,".txt");



    dir = opendir("/Users/esinozdemir/Desktop/Üniversite");
    if (dir)
    {
        while ((dosya_entry = readdir(dir)) != NULL)
        {
            char *file_extension =(strrchr(dosya_entry->d_name,'.'));
            if(file_extension==NULL)
            {
                char *file_name = (char *)malloc(strlen(dosya_entry->d_name)+1);
                strcpy(file_name,dosya_entry->d_name);
                if(file_name && strlen(file_name)>1){

                    char *fullPath = (char *) malloc(1 + strlen(directory_path)+ strlen(file_name) );
                    strcpy(fullPath, directory_path);
                    strcat(fullPath, "/");
                    strcat(fullPath, file_name);
                    dosyaindex++;

                    DIR *d;
                    d = opendir(fullPath);

                    while ((dosya_entry2 = readdir(d)) != NULL){
                        char *file_name2 = (char *)malloc(strlen(dosya_entry2->d_name)+1);
                        strcpy(file_name2,dosya_entry2->d_name);

                    if (d){
                        char aranan='.';
                        char *txt_tut;
                        txt_tut=strrchr(dosya_entry2->d_name, aranan);
                        if(strcmp(txt_tut, ".txt")==0){
                            char *fullPath2 = (char *) malloc(1 + strlen(fullPath)+ strlen(file_name2) );
                            strcpy(fullPath2, fullPath);
                            strcat(fullPath2, "/");
                            strcat(fullPath2, file_name2);
                            employee.adres[txtindex]=fullPath2;

                            FILE *fptr;
                            fptr=fopen(employee.adres[txtindex], "r");
                            if (fptr == NULL)
                                {
                                    printf("Unable to open file.\n");
                                    printf("Please check you have read/write previleges.\n");

                                    exit(EXIT_FAILURE);
                                }
                            else indexOf(fptr,word,dosya_entry2,dosya_entry);
                            fclose(fptr);

                            fptr=fopen(employee.adres[txtindex], "r");
                            if (fptr == NULL)
                                {
                                    printf("Unable to open file.\n");
                                    printf("Please check you have read/write previleges.\n");

                                    exit(EXIT_FAILURE);
                                }
                            else all_file_content(fptr,butun);
                            fclose(fptr);

                            fptr=fopen(employee.adres[txtindex], "r");
                            if (fptr == NULL)
                                {
                                    printf("Unable to open file.\n");
                                    printf("Please check you have read/write previleges.\n");

                                    exit(EXIT_FAILURE);
                                }
                            else etiket_bul(word,etiketli_hal);
                            etiket_sayisi++;
                                indexOf_etiket(fptr, etiketli_hal, dosya_entry2, dosya_entry,gec,control);
                            fclose(fptr);
                            txtindex++;
                            }
                        }
                    }
                closedir(d);
                }
            }
        }
        fclose(butun);
        closedir(dir);
        if(control1==1) printf("normal etiket");
    }
            break;
        case 2:
            printf("*********GÜNCELLEME**********\n");
            printf("\ndeğiştirmek istediğiniz kelimeyi giriniz: ");
                    scanf("%s",word);

            printf("\nolmasını istediğiniz yeni kelimeyi giriniz: ");
                    scanf("%s",new_word);

                printf("sadece kelime güncellemek için 1\n");
            printf("txt adı ile keime güncellemek için 2\n");
            scanf("%d",&sec);
                      strcpy(gec, "/Users/esinozdemir/Desktop/Üniversite/Dersler");
                      strcat(gec,"/");
                      strcat(gec,word);
                      strcat(gec,".txt");

                      printf("%s",gec);

               strcpy(gecYeni, "/Users/esinozdemir/Desktop/Üniversite/Dersler");
               strcat(gecYeni,"/");
               strcat(gecYeni,new_word);
               strcat(gecYeni,".txt");

               printf("%s\n",gecYeni);

            int result=rename(gec, gecYeni);

               if(result==NULL){
                   printf("değiştirildi :%s\n",gec);
               }
               else printf("güncelleme başarısız.");
            dir = opendir("/Users/esinozdemir/Desktop/Üniversite");
            if (dir)
            {
                while ((dosya_entry = readdir(dir)) != NULL)
                {
                    char *file_extension =(strrchr(dosya_entry->d_name,'.'));
                    if(file_extension==NULL)
                    {                        char *file_name = (char *)malloc(strlen(dosya_entry->d_name)+1);
                        strcpy(file_name,dosya_entry->d_name);
                        if(file_name && strlen(file_name)>1){

                            char *fullPath = (char *) malloc(1 + strlen(directory_path)+ strlen(file_name) );
                            strcpy(fullPath, directory_path);
                            strcat(fullPath, "/");
                            strcat(fullPath, file_name);

                            dosyaindex++;

                            DIR *d;
                            d = opendir(fullPath);

                            while ((dosya_entry2 = readdir(d)) != NULL){
                                char *file_name2 = (char *)malloc(strlen(dosya_entry2->d_name)+1);
                                strcpy(file_name2,dosya_entry2->d_name);
                            if (d){
                                char aranan='.';
                                char *txt_tut;
                                txt_tut=strrchr(dosya_entry2->d_name, aranan);
                                if(strcmp(txt_tut, ".txt")==0){
                                    char *fullPath2 = (char *) malloc(1 + strlen(fullPath)+ strlen(file_name2) );
                                    strcpy(fullPath2, fullPath);
                                    strcat(fullPath2, "/");
                                    strcat(fullPath2, file_name2);

                                    employee.adres[txtindex]=fullPath2;//bütün adresler
                                    FILE *fptr;
                                    fptr=fopen(employee.adres[txtindex], "r");
                                    if (fptr == NULL)
                                        {
                                            printf("Unable to open file.\n");
                                            printf("Please check you have read/write previleges.\n");

                                            exit(EXIT_FAILURE);
                                        }
                                    else    replaceWordInText(fptr,word,new_word,dosya_entry2,dosya_entry);
                                    remove(employee.adres[txtindex]);
                                    rename("replace.tmp", employee.adres[txtindex]);
                                    fclose(fptr);
                                    txtindex++;
                                    }
                                }
                            }
                            closedir(d);
                        }
                    }
                }
                closedir(dir);
                if(control1==1) printf("normal etiket");
                break;
          }
        case 3:
            printf("*************DOSYA YAZDIRMA************\n");

            FILE *dosya;

               dosya=fopen("/Users/esinozdemir/Desktop/Üniversite/toplam.txt","w");

            FILE *output;

               output=fopen("/Users/esinozdemir/Desktop/Üniversite/output.txt","w");

            fprintf(output,"istenen etiketler\n");
            dir = opendir("/Users/esinozdemir/Desktop/Üniversite");
            if (dir)
            {
                while ((dosya_entry = readdir(dir)) != NULL)
                {
                    char *file_extension =(strrchr(dosya_entry->d_name,'.'));
                    if(file_extension==NULL)
                    {

                        char *file_name = (char *)malloc(strlen(dosya_entry->d_name)+1);
                        strcpy(file_name,dosya_entry->d_name);
                        if(file_name && strlen(file_name)>1){

                            char *fullPath = (char *) malloc(1 + strlen(directory_path)+ strlen(file_name) );
                            strcpy(fullPath, directory_path);
                            strcat(fullPath, "/");
                            strcat(fullPath, file_name);
                            dosyaindex++;

                            DIR *d;
                            d = opendir(fullPath);

                            while ((dosya_entry2 = readdir(d)) != NULL){
                              char *file_name2 = (char *)malloc(strlen(dosya_entry2->d_name)+1);
                                strcpy(file_name2,dosya_entry2->d_name);
                                 if (d){
                                char aranan='.';
                                char *txt_tut;
                                txt_tut=strrchr(dosya_entry2->d_name, aranan);
                                if(strcmp(txt_tut, ".txt")==0){
                                    char *fullPath2 = (char *) malloc(1 + strlen(fullPath)+ strlen(file_name2) );

                                    printf("%s\n",dosya_entry2->d_name);

                                    strcpy(fullPath2, fullPath);
                                    strcat(fullPath2, "/");
                                    strcat(fullPath2, file_name2);//printf("%s\n",fullPath2);//txt adreslerine ulaştık

                                    employee.adres[txtindex]=fullPath2;
                                    FILE *fptr;
                                    fptr=fopen(employee.adres[txtindex], "r");



                                    if (fptr == NULL)
                                        {
                                            printf("Unable to open file.\n");
                                            printf("Please check you have read/write previleges.\n");
                                            exit(EXIT_FAILURE);
                                        }
                                    else
                                        etiket_saydirma(fptr);
                                    fclose(fptr);

                                    fptr=fopen(employee.adres[txtindex], "r");

                                    if (fptr == NULL)
                                        {
                                            printf("Unable to open file.\n");
                                            printf("Please check you have read/write previleges.\n");

                                            exit(EXIT_FAILURE);
                                        }
                                    else
                                       all_file_content(fptr,dosya);
                                    fclose(fptr);
                                    output=fopen("/Users/mumintopcu/Desktop/Üniversite/output.txt","r");
                                    fptr=fopen(employee.adres[txtindex], "r");
                                    delp=strtok(dosya_entry2->d_name,".");
                                    fprintf(output,"%s\n",delp);
                                    //istenen_etiketmi(delp,output);
                                    fclose(fptr);
                                    fclose(output);
                                    txtindex++;
                                     }}}
                            closedir(d);
                        }
                    }
                }
                closedir(dir);
            }
            fclose(dosya);

            dosya=fopen("/Users/esinozdemir/Desktop/Üniversite/toplam.txt","r");
            count_all_files(dosya,output,dosya_entry2);
            fclose(dosya);
            fclose(output);
            break;
        case 4:
            printf("dosyadan çıkış");
            exit(EXIT_SUCCESS);
            break;
    }}
    fclose(butun);
    return(0);
}

void indexOf(FILE *fptr, const char *word,struct dirent *dosya_entry2,struct dirent *dosya_entry)
{
    char str[BUFFER_SIZE];
    char *pos;
    int count_lines = 0;
    while (fgets(str, BUFFER_SIZE, fptr)!= NULL){
        pos = strstr(str, word);
        if(pos!=NULL){
            printf(" satir:%d\n ", count_lines+1);
            printf("TXT ismi:%s\n", dosya_entry2->d_name);
            printf("Dosya ismi:%s\n", dosya_entry->d_name);
            printf("\n\n\n");
            }
        else {
            count_lines = count_lines + 1;
            }
        }
    }

void etiket_bul(const char *word,char d[BUFFER_SIZE]){
    char *BASET="[[";
    strcpy(d,BASET);
    strcat(d,word);
    strcat(d, "]]");

}

void indexOf_etiket(FILE *fptr, const char *etiketli_hal,struct dirent *dosya_entry2,struct dirent *dosya_entry,const char *gec,int *control)
{
    char str[BUFFER_SIZE];
    char *pos;
    int count_lines = 0;
    int control1=0;
    printf("\n\n\n");
    while (fgets(str, BUFFER_SIZE, fptr)!= NULL){
        pos = strstr(str, etiketli_hal);

        if(pos!=NULL){
            printf("\n*****etiket araması******\n");
            printf(" etiket satiri:%d\n ", count_lines+1);
            printf("Etiketin bul. yer TXT ismi:%s\n", dosya_entry2->d_name);
            printf("etiket Dosya ismi:%s\n", dosya_entry->d_name);
            printf("etikettir.");
            control++;
                    }
        if(pos==NULL){
            count_lines = count_lines + 1;
                }
            }
    normal_etiketmi(gec,dosya_entry2,&control1);
        }

void normal_etiketmi(const char *word_txt,struct dirent *dosya_entry2,int *control){
    char *txt_adi;

    txt_adi=dosya_entry2->d_name;
    if(strcmp(word_txt,txt_adi)==0){
        printf("\n-------normal etiket------\n");
    }
}

void etiket_Guncelleme(FILE *fptr, const char *etiketli_hal,const char *file_name2,const char *word){

    int choice;
    char *new_txt_name = NULL;
    printf("txt adı ve etiket güncelleme için 1 \n");
    printf("sadece etiket güncelleme için 2 \n");
    scanf("%d",&choice);
    switch(choice){

        case 1:
            printf("güncellemek istediğiniz kelimeyi giriniz:");
            fgets(new_txt_name,BUFFER_SIZE,stdin);
            strcat(new_txt_name, ".txt");
            rename(file_name2,new_txt_name);
            printf("newname:%s\n",new_txt_name);
    }}

void replaceWordInText(FILE *fptr,char old_word[100],char new_word[100],struct dirent *dosya_entry2,struct dirent *dosya_entry){

    FILE * fTemp;

    char buffer[BUFFER_SIZE];
    fTemp = fopen("replace.tmp", "w");

    if (fptr == NULL || fTemp == NULL)
    {   printf("\nUnable to open file.\n");
        printf("Please check whether file exists and you have read/write privilege.\n");
        exit(EXIT_SUCCESS);
    }
    while ((fgets(buffer, BUFFER_SIZE, fptr)) != NULL)
    {
        replaceAll(buffer, old_word, new_word);
        fputs(buffer, fTemp);
    }

    fclose(fptr);
    fclose(fTemp);
    printf("\nSuccessfully replaced all occurrences of '%s' with '%s'.", old_word,new_word);
}
void replaceAll(char *str, const char *oldWord, const char *newWord)
{
    char *pos, temp[BUFFER_SIZE];
    int index = 0;
    int owlen;
    owlen = strlen(oldWord);
    if (!strcmp(oldWord, newWord)) {
        printf("Değiştirmek istediğiniz kelimeyle yeni kelime farklı olmalıdır!");
        return;
    }
    while ((pos = strstr(str, oldWord)) != NULL)
    {
        strcpy(temp, str);
        index = pos - str;
        str[index] = '\0';
        strcat(str, newWord);
        strcat(str, temp + index + owlen);
    }
}

void etiket_saydirma(FILE *fptr){
    char *pos;
    char str[BUFFER_SIZE];
    int sayim=0;
    while (fgets(str, BUFFER_SIZE, fptr)!= NULL){
    pos=strstr(str, "[[");
    while(pos!=NULL){
        pos=strstr(pos,"]]");
        if(pos!=NULL){
            pos=strstr(pos,"[[");
            sayim++;
            }
        }
    }
    printf("etiket sayisi:%d\n",sayim);
}

void all_file_content(FILE *fptr,FILE *dosya){
    char str[BUFFER_SIZE];
    while (fgets(str, BUFFER_SIZE, fptr)!= NULL){
        fprintf(dosya,"%s\n",str);
    }
}

void count_all_files(FILE *dosya,FILE *output,struct dirent *dosya_entry2 ){
    char b=0;
   char a=0;
    int i, len, index, isUnique;
    char words[MAX_WORDS][100];
        char word[100];
    int  count[MAX_WORDS];
    FILE *fPtr;

    fPtr = fopen("/Users/esinozdemir/Desktop/Üniversite/toplam.txt", "r");

    for (i=0; i<MAX_WORDS; i++)
            count[i] = 0;

        index = 0;
    while (fscanf(fPtr, "%s", word) != EOF)
       {
           len = strlen(word);
           if (ispunct(word[len -1]))
               word[len ] = '\0';

           isUnique = 1;
           for (i=0; i<index && isUnique; i++)
           {
               if (strcmp(words[i], word) == 0)
                   isUnique = 0;
           }
           if (isUnique)
           {
               strcpy(words[index], word);
               count[index]++;
               index++;
           }
           else
           {
               count[i - 1]++;
           }
       }
       fclose(fPtr);
       printf("\nOccurrences of all distinct words in file: \n");
       for (i=0; i<index; i++)
       {
           a=strstr(words[i],"[[");
           b=strstr(words[i],"]]");
           if(a!=NULL){
               if(b!=NULL){
                   fprintf(output,"%-15s => %d\n\n",words[i], count[i]);
               }}}
}

void istenen_etiketmi(const char *delp,FILE *output){
    char b=0;
   char a=0;
    char isaret[10];
    int i, len, index, isUnique;
    char words[MAX_WORDS][100];
        char word[100];
    int  count[MAX_WORDS];
    char bazen[MAX_WORDS];
    printf("istenen etiketi çağırdı.");
    FILE *fPtr;

    fPtr = fopen("/Users/esinozdemir/Desktop/Üniversite/toplam.txt", "r");

    for (i=0; i<MAX_WORDS; i++)
            count[i] = 0;

        index = 0;
    while (fscanf(fPtr, "%s", word) != EOF)
       {
           len = strlen(word);
           if (ispunct(word[len -1]))
               word[len ] = '\0';

           isUnique = 1;
           for (i=0; i<index && isUnique; i++)
           {
               if (strcmp(words[i], word) == 0)
                   isUnique = 0;
           }
           if (isUnique)
           {
               strcpy(words[index], word);
               count[index]++;
               index++;
           }
           else
           {
               count[i - 1]++;
           }
       }
    strcmp(isaret,"[[");
    strcmp(bazen, delp);
    strcat(isaret,bazen);
    strcat(isaret,"]]");
       fclose(fPtr);
       printf("\nOccurrences of all distinct words in file: \n");
       for (i=0; i<index; i++)
       {
           a=strstr(words[i],"[[");
           b=strstr(words[i],"]]");
           if(a!=NULL){
               if(b!=NULL){
                   if(strcmp(words[i],delp)==NULL){
                   fprintf(output,"istenenleer ::%-15s => %d\n\n",words[i], count[i]);
                       printf("istenenleeer:::");
                   }
               }}}


}
