/* Assignment: 1
Author1: Shahaf Zohar, ID: 205978000
Author2: Shaked Basa, ID: 206310781
*/

#include <stdio.h>
#define  SizeMatrix3 10
#define SizeMatrix6 8

void  histogramArray(int arr1[] , int size1);
void printMaxPartAscending(int arr2[], int size2);
int countWords(char matrix[][8],int Rows,int coluns, char word[]);
void Goesup(int arr[], int size, int end, int start);
int checkSaddleElement(int Matrix[][SizeMatrix3], int row, int coluns);
void rotateMatrix90(int matrix[][3], int rows,int colns);
int checker(char matrix[][8], char *p, int incident, int indexrow,int indexcoluns, int numword);
int countWords(char matrix[][8],int Rows,int coluns, char word[]);
void decipher(char Sentence[]);
void findSimilarWords(char sentence[]);



void  histogramArray(int arr1[] , int size1)
{
            printf("question 1\n");
            int p[20]= {0};
            for(int i = 0 ; i < size1 ; i++ )
                        {
                        p[arr1[i]] = p[arr1[i]] + 1;
                        }
            printf("\nValue\t\thistogram\n");
            for(int k=0 ; k <20 ; k++)
                    {                      
                    if(p[k] != 0){
                                   printf("%d\t\t",  k );
                                   int w= 0;
                                   while(p[k] != w)
                                            {
                                                printf("*");
                                                w++;
                                             }
                                    printf("\n");
                                   }
                    }
}

void Goesup(int arr[], int size, int end, int start)
    {
            for(int i = start; i <= end; i ++)
                    printf("%d\t" , arr[i]);
            printf("\n");
    }

void printMaxPartAscending(int arr2[], int size2)
{   
                printf("\nquestion 2\n\n");
                int start1 = 0, start2 = 0 ;
                int count1 = 0, count2 = 0;
                for(int k = 0; k < size2; k++)
                        {          
                                    if(count1 <  count2 ||  count1 == 0){
                                                start1 = k;
                                                count1 = 0;
                                                while((arr2[k] < arr2[k+1]) && (k+1 < size2 )){
                                                        count1++;
                                                        k++;
                                                }
                                    }
                                    if(count2 < count1 ||  count2 == 0){
                                                start2 = k;
                                                count2 = 0;
                                                while((arr2[k]< arr2[k+1]) && (k+1 < size2 )){                
                                                        count2++;
                                                        k++;   
                                                }
                                    }
                        }
                        if (count1 > count2){
                                    Goesup(arr2, size2, count1+start1, start1);
                        }
                       else if (count1 < count2){
                                    Goesup(arr2, size2, count2+start2, start2);
                        }
                        else{
                        printf("No such segment!\n");
                        }
}
    

int checkSaddleElement(int Matrix[][SizeMatrix3], int row, int coluns)
{   
        printf("question 3\n");
        int  flag = 0,mark= 0,q=0;
        int *ptr =&Matrix[0][0];
        for(int i=0; i < coluns; i++){
                for(int k =0 ; k < row ; k++)  {
                        if((*ptr < Matrix[k][i])&&(q < Matrix[k][i])){
                                q = Matrix[k][i];
                                mark = k;
                        }
                }
                for(int j = 0; j < coluns; j++){
                                    if((q <= Matrix[mark][j])) {
                                            flag++;
                                    } 
                                    else{
                                            flag =0; 
                                        break; 
                                        }
                }
                if(flag)
                    {
                        return 1;
                    }
            flag=0;
            ptr++;
            q=0;
                }
        return 0 ;}
        
        
void rotateMatrix90(int matrix[][3], int rows,int colns)
{   
    printf("question 4\n");
    int newmatrix[rows][colns];
    int x = 0;
    for(int i=0; i<rows;i++)
    {
            for(int j=colns-1; j>=0;j--)
                {
                        newmatrix[i][x++] = matrix[j][i]; 
                }
                x = 0;
                printf("\n");
                }
for(int i=0; i<3;i++)
{
    for(int j=0; j<3;j++)
    {
        matrix[i][j] = newmatrix[i][j]; 
    }
}
}

void rotateString(char str[], int moves, int direction) {
    
    printf("question 5\n");
    int i=0;
    int j=0;
    int x=0;
    int y=0;
    char sub1[20] = "\0";
    char sub2[20] = "\0";
    int emoves ;
    int c=0;
    while (str[c] != '\0'){
        c++;
    }
    int len = c-1;
    emoves = moves%len;
    if(direction == 2) {
        while(j < emoves) {
            sub1[j] = str[len-emoves +j];
            j++;
        }
        while(i < len - emoves) {
            sub2[i] = str[i];
            i++;
        }
        while(sub1[x] !='\0'){
            str[x]=sub1[x];
            x++;
        }
        while(sub2[y] != '\0'){
            str[x]=sub2[y];
            x++;
            y++;    
        } 
    }

    else if (direction == 1) {
        while(j < len - emoves) {
            sub1[j] = str[emoves + j];
            j++;
        }
        while(i < emoves) {
            sub2[i] = str[i];
            i++;
        }
        while(sub1[x] !='\0'){
            str[x]=sub1[x];
            x++;
        }
        while(sub2[y] != '\0'){
            str[x]=sub2[y];
            x++;
            y++;    
        }       
    }

}

int checker(char matrix[][8], char *p, int incident, int indexrow,int indexcoluns, int numword)
{
    int count = 1;
    switch(incident){
                case 1 :
                {
                    for(int i = 1; i < numword ; i++){
                                if(matrix[indexrow][indexcoluns+i] == *(p+i)){
                                            count+=1;}}
                    if(count == numword){
                            return 1;}
                    else{
                            return 0; }}
                case 2 :
                {
                    for(int j = 1;j < numword; j++){
                                if((matrix[indexrow+j][indexcoluns+j] == *(p+j))&&(matrix[indexrow+j][indexcoluns+j] != '\0')){
                                            count+=1;}}
                    if(count == numword){
                            return 1;}
                    else{
                            return 0; }}              
                case 3 :
                {
                    for(int k = 1;k < numword; k++){
                                if(matrix[indexrow+k][indexcoluns] == *(p+k)){
                                            count+=1;}}
                    if(count == numword){
                            return 1;}
                    else{
                            return 0; }}
                default:{
                        printf("None");
                        return 0 ;}
            }
}


int countWords(char matrix[][8],int Rows,int coluns, char word[])
{   
            printf("question 6\n");
            char *ptr = word;
            int  count = 0, incident= 0;
            int numword = 0,k = 0;
            while(*(ptr+k) !='\0'){
                    numword++;
                    k++;}
            for(int i = 0; i < Rows; i++){
                                for(int k = 0; k < coluns; k++){
                                    if(matrix[i][k] == *ptr){   
                                                if((matrix[i][k+1] == *(ptr+1)) &&(matrix[i][k+1] != '\0')){
                                                        incident =1;
                                                         count += checker(matrix, ptr, incident, i, k,numword);} 
                                                 if((matrix[i+1][k+1] == *(ptr+1)) && (matrix[i+1][k+1] !='\0')){
                                                        incident = 2;
                                                         count = count + checker(matrix, ptr, incident, i,k,numword);}
                                                 if((matrix[i+1][k] == *(ptr+1)) && (matrix[i+1][k] !='\0')){
                                                        incident = 3;
                                                         count += checker(matrix, ptr, incident, i,k,numword);}
                                        }
                                }
                            }
            return count;
}
void decipher(char Sentence[]){
    
        printf("question 7\n");
        int k = 0;
        int indexascii =1;
        while(Sentence[k+1] != '\0' ){
            if(Sentence[k] == 32){
                printf(" ");
                indexascii = 1;}
            else{
                printf("%c", Sentence[k] - indexascii );
                indexascii++;}
            k++;
            }
        printf("\n\n");
    }
    

void findSimilarWords(const char word[]){
    char newString[1000][1000]; 
    int c = 0;
    int i = 0;
    int x = 0;
    int y = 0;
    int z = 0;
    int i1 = 0;
    int j1 = 0;
    int ctr = 0;
    char space=' ';
    int j = 0;
    int rows = 0;
    int columns = 0;
    char lcword[1000] = "\0";
    int words[][26] = {0};
    
    while(word[j] != '\0'){
        lcword[j]=word[j];
        j++;
    }
    while (word[c] != '\0'){
        c++;
    }
    int len = c;
    for(i1=0;i1<=len;i1++){
        if((word[i1]==space||word[i1]=='\0')&& word[i1+1]!=space)
        {
            newString[ctr][j1]='\0';
            ctr++;  
            j1=0;    
        }
        else if(word[i1+1]!=space || word[i1]!=space)
        {
            newString[ctr][j1]=word[i1];
            j1++;
        }
    }
    while (lcword[c] != '\0') {
       if (lcword[c] >= 'A' && lcword[c] <= 'Z') {
           lcword[c] = lcword[c] + 32;
       }
       c++;
    }
    while(lcword[i] != '\0'){
        columns = 0;
        if(lcword[i] == space && lcword[i+1] != space){
            rows++;
        }
        else{
            while(columns<26){
                if(lcword[i] == 97+columns){
                    words[rows][columns] = 1;
                    break;
                }
                else{                    
                    columns++;
                }
            }
        } 
        i++;
    }
    for(x=0;x<=ctr-2;x++){
        z=0;
        for(z=0;z<=ctr-3;z++){
            y=0;
            while(y<=26 && x+z!=x){
                if(words[x][y] == words[x+z][y]){
                    y++;
                    if(y==26){
                        printf("%s",newString[x]);
                        printf(" %s\n",newString[x+z]);
                    }
                }
                else{
                    break;
                }
                
            }
        }
    }
    printf("\n");
}           
