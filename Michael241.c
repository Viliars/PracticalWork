/* created by
Michael Pritugin
in 25.09.2017 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 3
typedef struct list {
	char s[N+1];
        struct list* link;
        struct list* last;
} list;

list* associationList(list*,list*);

int inList(list*,char*);

void createList(list**, char*);

void deleteList(list **);

void printList(const list *);

void pushBack(list*, char*);

list* CinList(void);

list* getLast(list*);
/*main*/
int main()
{
list* text1=NULL;
list* text2=NULL;
list* rez=NULL;
text1=CinList();
text2=CinList();
rez=associationList(text1,text2);
if(rez==NULL) printf("ERROR");
else { printList(rez);
deleteList(&rez); }
return 0;
}

/* functions */

list* CinList(void)
{
    char str[N];
    list* first=NULL;
    list* last;
    int i,k=0;
    char c;
        for(i=0;i<N;i++) {
            if((c=getchar())=='\n')
            if(i>0) { str[i]='\0'; createList(&first,str);last=first;
                 return first; }
              else return NULL;

         str[i]=c;
        }
        str[N]='\0';
        createList(&first,str);
           do{
            for(i=0;i<N;i++){
            if((c=getchar())=='\n'){
            if(i>0) { str[i]='\0'; pushBack(first,str);  last=first;  }

              return first;
           }
         str[i]=c;
        }
        str[N]='\0';
        pushBack(first,str);
           } while(1);
}

list* associationList(list* L1,list* L2){
list* l=NULL;
list* del=NULL;
list* rezult=NULL;
int K1=1,K2=1;
    if(L1==NULL) return L2;
    if(L2==NULL) return L1;
    l=L1;
    rezult=l;
    L1=L1->link;
    l->link=NULL;
    if(L1!=NULL) {
            while(L1->link!=NULL)
            {
                if(inList(rezult,L1->s)) { l->link=L1; L1->last=l; l=l->link; L1=L1->link; l->link=NULL;}
                    else { del=L1; L1=L1->link; free(del); }
            }
        if(inList(rezult,L1->s)) { l->link=L1; L1->last=l; l=l->link; l->link=NULL;}
            else free(L1);
            }
            while(L2->link!=NULL)
            {
                if(inList(rezult,L2->s)) { l->link=L2; L2->last=l; l=l->link; L2=L2->link; l->link=NULL;}
                    else { del=L2; L2=L2->link; free(del); }
            }
        if(inList(rezult,L2->s)) { l->link=L2; L2->last=l; l=l->link; l->link=NULL;}
            else free(L2);

   return rezult;
}

int inList(list* head,char* data)
{
    int i;;
    while (head) {
        if(!strcmp(head->s,data)) return 0;
        head = head->link;
    }
    return 1;
}

void deleteList(list **elem) {
	 list* prev=NULL;
	 while ((*elem)->link) {
		prev=(*elem);
          	(*elem)=(*elem)->link;
		free(prev);
		};
	 free(*elem);
}

void printList(const list *head) {
    while (head) {
        printf("%s|", head->s);
        head = head->link;
    }
    printf("\n");
}

void pushBack(list *head, char* data) {
    list  *buf = getLast(head);
    list  *tmp = malloc(sizeof(list));
    strcpy(tmp->s,data);
    tmp->link = NULL;
    tmp->last=buf;
    buf->link = tmp;
}


void createList(list **elem, char* data) {
    list *tmp =malloc(sizeof(list));
    strcpy(tmp->s,data);
    tmp->link = (*elem);
    tmp->last=NULL;
    (*elem) = tmp;
}

list* getLast(list *head) {
    if (head == NULL) {
        return NULL;
    }
    while (head->link) {
        head = head->link;
    }
    return head;
}
