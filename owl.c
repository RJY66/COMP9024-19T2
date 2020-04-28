// COMP9024 Assignment2:Ordered Word Ladder
// Created by Junyu Ren
// Date 01/08/2019

#include "Graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define MAXWORDNUM 1000
#define MAXWORDLEN 20
#define MAXPATHCOUNT 99

/**
 * define struct of a node
 */
typedef struct node{
    int longest;             //length of longest path
    int path[MAXWORDNUM][MAXWORDNUM];    //array to store each path
    int nb_path;             //number of path of a node
}node;

/**
 * judge whether 2 words have 1 letter different
 * @param pointers of 2 words
 * @return true or false
 */
bool differByOne(char *first, char *second) {
    //difference of length between 2 words
    int differ = strlen(second) - strlen(first);
    char shorter[MAXWORDLEN], longer[MAXWORDLEN];
    if(differ>0){
        strcpy(longer, second);
        strcpy(shorter, first);
    } else {
        strcpy(longer, first);
        strcpy(shorter, second);
    }
    int count = 0;
    //if have same length
    if (differ == 0) {
        for (int i = 0; i < strlen(first); i++) {
            if (*(second + i) != *(first + i)) {
                count++;
            }
        }
        //only one letter different,true
        if(count==1){
            return true;
        }
        //otherwise false
        return false;
    }
    //if length difference is 1
    else if (differ * differ == 1) {
        for(int i=0;i<strlen(shorter);i++){
            if (shorter[i] != longer[i+count]) {
                count++;
                i--;
            }
            if (count > 1) {
                return false;
            }
        }
        return true;
    }
    return false;
}

/**
 * append node to a path
 * @param nodes a and b and a number need appending
 * @return no return
 */
void append(node *a, node *b, int ele){
    for (int i = 0; i < a->nb_path; i++) {
        for (int j = 0; j < a->longest; ++j) {
            b->path[b->nb_path+i][j] = a->path[i][j];
        }
        b->path[b->nb_path+i][a->longest] = ele;     //append ele from node a to b
    }
    b->nb_path += a->nb_path;   //increment nb_path from node a to b
}

/**
 * find longest path of a graph
 * @param graph,num of vertexes,all path of one node
 * @return two-dimensional array of all longest path
 */
int** find_path(Graph g ,int num_v,node **arr){
    int all_max=0;       //maxlength of all path
    for(int i=0;i<num_v;i++){
        arr[i]=malloc(sizeof(node));   //initialization for the node
        arr[i]->longest=0;
        arr[i]->nb_path=0;
    }
    arr[0]->nb_path=1;      //nb_path starts from 1
    int newlen;
    for (int i=0;i<num_v;i++){
        for(int j=i+1;j<num_v;j++){
            if(isEdge(newEdge(i,j),g)){       //if there is an edge between a node and any nodes behind it
                newlen=arr[i]->longest+1;
                if(newlen>arr[j]->longest){   //if newlen > longest path
                    arr[j]->longest=newlen;
                    arr[j]->nb_path=0;
                    append(arr[i], arr[j], i);
                }
                else if(newlen==arr[j]->longest){      //if newlen is the longest path
                    append(arr[i], arr[j], i);
                }
            }
            if(newlen>all_max){     //update length value of longest path
                all_max=newlen;
            }
        }
    }
    //count of max path
    int max_path_count=0;
    //store first 99 max path
    int **max_path = malloc(sizeof(int *) * MAXPATHCOUNT);
    for(int i=0;i<MAXPATHCOUNT;i++){
        max_path[i] = malloc(sizeof(int) * MAXWORDNUM);
    }
    for(int i=0;i<num_v;i++){
       if(arr[i]->longest<all_max){    //current node longest smaller than global longest
           continue;
       }
       for(int j=0;j<arr[i]->nb_path;j++){
           for(int k=0;k<arr[i]->longest;k++){
               max_path[max_path_count][k]=arr[i]->path[j][k];
           }
           max_path[max_path_count][all_max]=i;    //put node i to correct place
           max_path_count++;           //count increment of longest ladder
       }
    }

    for(int i=0;i<max_path_count;i++){
        max_path[i][all_max+1]=-1;    //signal for the end horizontally
    }
    max_path[max_path_count][0]=-1;   //signal for the end vertically
    return max_path;
}

/**
 * compare sequence of 2 paths, for qsort() function
 * @param 2 arrays
 * @return 0 if a==b,<0 if a<b,>0 if a>b
 */
int path_cmp(const void *a,const void *b){
    int * p1=*(int **)a;
    int * p2=*(int **)b;
    int path_length=0;
    for(int i=0;p1[i]!=-1;i++){     //get length of longest path
        path_length++;
    }
    for(int i=0;i<path_length;i++){
        if(p1[i]!=p2[i]){
            return p1[i]-p2[i];
        }
    }
    return p1[path_length-1]-p2[path_length-1];
}

/**
 * main method
 * @param no parameter here is ok
 * @return print dictionary,the edges of a graph and longest ladders
 */
int main(void){
    char input[MAXWORDLEN];
    char word[MAXWORDNUM][MAXWORDLEN];
    int index=0;
    printf("Dictionary");
    if(scanf("%s",input)==EOF){    //deal with empty input
        printf("\nOrdered Word Ladder Graph");
        printf("\nV=0, E=0");
        printf("\nLongest ladder length: 0");
        printf("\nLongest ladders:");
        return EXIT_SUCCESS;
    }
    else{
        //deal with word[0]
        strcpy(word[index],input);
        index++;
        while(scanf("%s",input)!=EOF){
            if(strcmp(word[index-1],input)==0){     //remove duplicate words
                continue;
            }
            strcpy(word[index],input);              //deal with from word[1] till the EOF
            index++;
        }
        strcpy(word[index+1],"");
        for(int i=0;i<index;i++){           //print the dictionary
            printf("\n%d: %s",i,word[i]);
        }

        printf("\nOrdered Word Ladder Graph\n");
        Graph g=newGraph(index);   //create a new graph
        for(int j=0;j<index;j++){
            for(int k=j+1;k<index;k++){
                if(differByOne(word[j],word[k])){    //judge whether there's an edge between 2 nodes
                    insertEdge(newEdge(j,k),g);
                }
            }
        }
        showGraph(g);            //print all edges
        node *arr[index];
        int **max_path=find_path(g,index,arr);   //get return value for find_path function
        int path_length=0;      //length of longest ladder
        int max_path_count=0;   //count of longest ladder
        for(int i=0;max_path[0][i]!=-1;i++){    //get value of length of longest ladder
            path_length++;
        }
        for(int i=0;max_path[i][0]!=-1;i++){    //get value of count of longest ladder
            max_path_count++;
        }
        printf("Longest ladder length: %d\n", path_length);
        //deal with longest ladder>1
        if(path_length>1) {
            printf("Longest ladders:\n");
            //quick sort path to follow alphabetic order
            qsort(max_path, max_path_count, sizeof(int *), path_cmp);
            for (int i = 0; i < max_path_count; i++) {                //print them as required
                printf("%2d: ", i + 1);
                for (int j = 0; j < path_length - 1; j++) {
                    int tmp = max_path[i][j];
                    printf("%s -> ", word[tmp]);
                }
                printf("%s\n", word[max_path[i][path_length - 1]]);   //print last element for every longest path differently
            }
        }
        else{                                   //if longest length=1
           printf("Longest ladders:\n");
           for(int i=0;i<index;i++){            //print all nodes
               printf("%2d: %s\n",i+1,word[i]);
            }
        }
    }
    return EXIT_SUCCESS;
}
