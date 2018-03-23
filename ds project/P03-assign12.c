//LAST UPDATED: 1:31am 18 04 2017

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

typedef struct fr {
	int proId,year,month,date;
	char name[50];
	struct fr* next;
} FR;

// A structure to represent an adjacency liat
typedef struct list {
	int proId,year,month,date;
	char name[50];
	char place[100];
	char homeTown[100];
	FR *head; // pointer to head node of Linked List
} LIST;

typedef struct node{

	LIST* array;
}ITEM;

int n=50;
int hook=0;
FR *newnode(int dest,int a,char *str,int date,int month,int year) {
	FR *new = (FR *) malloc(sizeof(FR));
	if (new == NULL) exit(-1);
	//new->dest = dest;
	new->proId= a;
	strcpy(new->name,str);
	new->date=date;
	new->month=month;
	new->year=year;
	new->next = NULL;
	return new;
}

void addfriend(ITEM* graph, int src, int dest) {
	// Add an edge from src to dest.  A new node is added at FRONT
	if(graph->array[dest].proId!=0 && graph->array[src].proId!=0){
		FR* newNode = newnode(dest,graph->array[dest].proId,graph->array[dest].name,graph->array[dest].date,graph->array[dest].month,graph->array[dest].year);
		newNode->next = graph->array[src].head;
		graph->array[src].head = newNode;

		// Since GRAPH is undirected, add an edge from dest to src as well
		newNode = newnode(src,graph->array[src].proId,graph->array[src].name,graph->array[src].date,graph->array[src].month,graph->array[src].year);
		newNode->next = graph->array[dest].head;
		graph->array[dest].head = newNode;
	}
}
int p=10,q=20;
/*HOME TOWNS*/

char B[20][16]={"DELHI","PUNJAB","HYDERABAD","CHENNAI","BANGALORE","BHOPAL",
	"NAGPUR","MUMBAI","KOLKATA","VARANASI"};

/*FAVOURITE PLACES*/

char A[25][16]={"NEW YORK","SYDNEY","NETHERLANDS","SWITZERLAND","VATICAN CITY","URUGUAY",
	"ROME","PARIS","BRAZIL","DUBAI","ITALY","SINGAPORE","SPAIN","CHINA","RUSSIA","INDIA","LONDON","SPAIN","GERMANY","ABU DABI"};

/*GENERATING RANDOM INTEGERS*/

int random_int(int min, int max){
	return min + rand() % (max+1 - min);
}
ITEM *flag = NULL;

char c[50][100];

void read(FILE *fp){
	char word[1000];
	int z=0,i=0;
	while(fgets(word,sizeof(word),fp) != NULL){
		for(i=0;i<strlen(word)-2;)
		{
			c[z][i]=word[i];
			i++;

		}
		c[z][i]='\0';
		z++;
	}
}
int ID=20170350;
//Read each line from the file and linking it to linked list.
ITEM *genDataset(int n){
	char b[50][100];
	int x,h,z,yr,mnth,dt;	
	int ID=20170300;
	ITEM *p;
	p = (ITEM *)malloc(sizeof(ITEM));  //typecasting procedure
	//to integer
	p->array = (LIST *) malloc (n * sizeof(LIST));
	int i;
	for (i = 0; i < n; i++)
		p->array[i].head = NULL;
	//int count=0;
	h=0;
	while(h<n){
		z=rand()%50;
		strcpy(p->array[h].name,c[z]);
		p->array[h].proId =ID;
		ID++;
		z=random_int(1,19);
		x=random_int(1,9);
		strcpy(p->array[h].place,A[z]);
		strcpy(p->array[h].homeTown,B[x]);
		printf("%d %s\n",p->array[h].proId,p->array[h].homeTown);
		p->array[h].year=random_int(1992,2002);
		p->array[h].month=random_int(1,12);
		if(p->array[h].month==2){
			p->array[h].date=random_int(1,28);
		}
		else{
			p->array[h].date=random_int(1,30);
		}
		h++;
	}


	return p;
}

/* *********************************************************SORTING BASED ON PLACE****************************************************** */


int vec[15];int inArray(int, int, int*);
void hello(int y){
	int i,j;
	int temp,count=0,flag=0;
	for (i=0;i<15;i++){
		temp =rand()%50+1;     
		int k=0;
		while(temp==y)
		{
			temp =rand()%50+1;     
		}
		while(k<i)
		{
			if(temp==vec[k])
			{
				flag=1;
				break;
			}
			k++;
		}
		if(flag==0)
			vec[i] = temp;//count++;
		else{
			i--;
		}
		flag=0;
	}

}

int abc=1;

int BIN[100];

ITEM *assignfr(ITEM *F,int n){
	int i,r,f,j;
	int z=0,cnt=0;
	for(i=0;i<n;i++){	
		cnt=0;	
		r=random_int(10,15);
		FR *cnode = F->array[i].head;
		while (cnode!=NULL){
			cnode = cnode->next;
			cnt++;
		}
		r=r-cnt;
		hello(i);
		for(int k=0;k<r;k++){
			int flag=0; 
			cnode = F->array[i].head;		
			while (cnode!=NULL) {
				if(cnode->proId==F->array[vec[k]].proId){
					flag=1;
				}
				cnode = cnode->next;
			}
			if(flag==0)
				addfriend(F,i,vec[k]);
			flag=0;
		}
	}
}


void printfrends(ITEM* graph,int n) {
	int v;
	for (v = 0; v < n; ++v) {
		FR* cnode = graph->array[v].head;
		printf("\nFRIENDS OF %d---%s(%d/%d/%d)---%s---%s: \n\n", graph->array[v].proId,graph->array[v].name,graph->array[v].date,graph->array[v].month,graph->array[v].year,graph->array[v].homeTown,graph->array[v].place);
		while (cnode!=NULL) {
			printf(" %d----%s \n", cnode->proId, cnode->name);
			cnode = cnode->next;
		}
		printf("\n");
	}
}
void searchbyname(ITEM *graph,char person[15],int n){
	char tempplace[100],tempname[100];
	strcpy(tempname,person);
	int i,cnt=0,r=0;
	for(i=0;i<n;i++){
		if(strcmp(graph->array[i].name,person)==0){
		cnt=0;
			printf("%s\n",person);
			printf("%s\n",graph->array[i].homeTown);
			FR* cnode = graph->array[i].head;
			while (cnode!=NULL){
				cnt++;
				cnode = cnode->next;
			}
			r++;
			printf("NO.OF FRIENDS: %d\n",cnt);
		}	
	}

	if(r>1){
		printf("\n\nENTER %s's HOMETOWN\n",tempname);
		scanf("%s",tempplace);
		for(i=0;i<n;i++){
			if(strcmp(graph->array[i].name,tempname)==0&&strcmp(graph->array[i].homeTown,tempplace)==0){
			cnt=0;
				printf("%s\n",person);
				FR* cnode = graph->array[i].head;
				while (cnode!=NULL){
					cnt++;
					cnode = cnode->next;
				}
				printf("NO.OF FRIENDS: %d\n",cnt);
				break;
			}	
		}

	}


}

void searchbyplace(ITEM *graph,char place1[15],int n){
	int i,count=0;
	printf("NO.OF PERSONS: ");
	for(i=0;i<n;i++){
	
		if(strcmp(graph->array[i].place,place1)==0){
			count++;
		}
	}
	printf("%d\n",count);
	for(i=0;i<n;i++){
		if(strcmp(graph->array[i].place,place1)==0){
			printf("%s\n",graph->array[i].name);
		}
	}
}

void peopleFromSamePlace(ITEM *graph,char place1[15],int n){
	int i,k=0;
	printf("PEOPLE FROM %s: \n",place1);
	for(i=0;i<n;i++){
		if(strcmp(graph->array[i].homeTown,place1)==0){
			k++;
			printf("%s\n",graph->array[i].name);
		}
	}
	if(k==0){
		printf("NONE....");	
	}
}

void print(FR *cnode){
	while (cnode!=NULL) {
		printf("->  %d %s(%d/%d/%d)\n", cnode->proId, cnode->name,cnode->date,cnode->month,cnode->year);
		cnode = cnode->next;
	}
	printf("\n");
}

void findmutual(FR *cnode,FR *cnode1,char person[15]){
	int cnt=0;
	while(cnode!=NULL)
	{
		FR *k=cnode1;
		while(k!=NULL)
		{
			if(cnode->proId==k->proId)
			{
				cnt++;
				printf("%s\n",k->name);		
			}
			k=k->next;
		}
		cnode=cnode->next;	
	}
	printf("NO.OF MUTUAL FRIENDS OF %s FRIEND %d ARE %d \n\n",person,abc,cnt);
	abc++;	
}

void mutualfriends(ITEM *graph,int n,char person[15]){
	int i,j;
	for(i=0;i<n;i++)
	{

		if(strcmp(graph->array[i].name,person)==0)
		{
			FR* cnode = graph->array[i].head;
			printf("FRIENDS OF %s ARE: \n",person);
			print(graph->array[i].head);	
			FR *star=cnode;
			while(cnode!=NULL)
			{
				for(j=0;j<n;j++)
				{
					if(cnode->proId==graph->array[j].proId)
					{
						FR* cnode1 = graph->array[j].head;
						findmutual(star,cnode1,person);
						printf("-----------------------------------------------\n");
					}
				}
				cnode=cnode->next;
			}
			break;
		}
	}
}	

void list(ITEM *p,int n){
	int i;
	for(i=0;i<n;i++)
	{
		printf("%d - %s\n",i,p->array[i].name);
	}
}

void deletefriend(ITEM* graph, int src, int dest) {
	FR *temp = NULL;int cnt=0,flag=0;
	FR *p = graph->array[src].head;
	while(p !=NULL){
		if(p->proId==graph->array[dest].proId){
			flag=1;
			break;
		}			
		p=p->next;	
	}
	printf("%d  ------\n",flag);
	if(flag==1){
		FR *dummy=NULL;FR *dummy1=NULL;
		FR *k = graph->array[src].head;
		while(k->proId != graph->array[dest].proId){	
			dummy=k;		
			k=k->next;
		}

		temp =k;
		dummy->next = k->next;
		free(temp);

		FR *k1 = graph->array[dest].head;
		while(k1->proId != graph->array[src].proId){		
			dummy1=k1;	
			k1=k1->next;
		}

		temp =k1;
		dummy1->next = k1->next;
		free(temp);

		FR* cnode = graph->array[src].head;
		while (cnode!=NULL)
		{
			cnt++;
			cnode = cnode->next;
		}
		printf("\nNO.OF FRIENDS OF THE PERSON CURRENTLY : %d\n",cnt);
	}
	else
	{
		printf("\nGIVEN TWO PERSONS ARE NOT FRIENDS\n");	
	}

}

void searchbyid(ITEM *graph,int id,int n){
	int i,cnt=0;
	for(i=0;i<n;i++){
		if(graph->array[i].proId==id){
			printf("ID:%d\nNAME:%s\nHOME TOWN:%s\nDATE OF BIRTH:%d %d %d\n",id,graph->array[i].name,graph->array[i].homeTown,graph->array[i].date,graph->array[i].month,graph->array[i].year);
			break;
		}	
	}
}

void request(int a1,int a2,ITEM *graph,int n){
	ITEM *g=graph;
	int i,j;
	for(i=0;i<n;i++){
		if(graph->array[i].proId==a1){
			FR *cnode=graph->array[i].head;
			FR *new = (FR *) malloc(sizeof(FR));
			for(j=0;j<n;j++){
				if(graph->array[j].proId==a2){
					FR *cnode1=graph->array[j].head;
					FR *new1 = (FR *) malloc(sizeof(FR));
					printf("\n%d---\n",a1);
					new1->proId=a1;
					new1->next=NULL;
					strcpy(new1->name,graph->array[i].name);
					printf("\n%d---\n",a2);
					new->proId=a2;
					new->next=NULL;
					strcpy(new->name,graph->array[j].name);
					while(cnode1->next!=NULL)
					{
						cnode1=cnode1->next;
					}
					cnode1->next=new1;

					break;
				}
			}

			while(cnode->next!=NULL){
				cnode=cnode->next;
			}
			cnode->next=new;
			printf("\nBECAME FRIENDS\n\n");
			printfrends(g,n);
			break;
		}

	}

}
void addfriend123(ITEM *graph,int a1,int a2,int n){
	int i,flag=0;
	for(i=0;i<n;i++){		
		if(graph->array[i].proId==a1){
			FR* cnode = graph->array[i].head;
			while(cnode!=NULL){
				if(cnode->proId==a2){
					printf("\nTHEY ARE ALREADY FRIENDS\n");
					flag=1;
					break;
				}
				cnode=cnode->next;
			}
			if(flag==0){
				request(a1,a2,graph,n);
			}
		}
	}	

}


void signup(ITEM * graph,char pro[],int n,int ID){
	int i,z;
	char j[15];
	
	printf("ENTER YOUR NAME:\n");
	scanf("%s", graph->array[n-1].name);
	
	printf("ENTER YOUR HOMETOWN:\n");
	scanf("%s", graph->array[n-1].homeTown);
	p++;
	strcpy(B[p],graph->array[n-1].homeTown);

	printf("ENTER YOUR FAVOURITE PLACE:\n");
	scanf("%s", graph->array[n-1].place);
	q++;
	strcpy(A[q],graph->array[n-1].place);
	printf("ENTER YOUR DATE OF BIRTH\n");
	scanf("%d %d %d",&graph->array[n-1].date,&graph->array[n-1].month,&graph->array[n-1].year);

	graph->array[n-1].proId=ID;
	printf("YOUR ID IS %d\n",ID);
	
	graph->array[n-1].head=NULL;
	
	FR *cnode=graph->array[n-1].head;
	
	for(z=0;z<2;z++){

	FR *new = (FR *) malloc(sizeof(FR));

	FR *new1 = (FR *) malloc(sizeof(FR));
					//printf("\n%d---\n",a1);
					new1->proId=ID;
					new1->next=NULL;
					strcpy(new1->name,graph->array[n-1].name);
					new1->date=graph->array[n-1].date;
					new1->month=graph->array[n-1].month;
					new1->year=graph->array[n-1].year;


	printf("PEOPLE YOU MAY KNOW:\n\n");
		list(graph,n);
	
	printf("enter name of person\n");
	scanf("%s",j);
		for(i=0;i<n;i++){
			if(strcmp(graph->array[i].name,j)==0){
					FR *cnode1=graph->array[i].head;
					new->proId=graph->array[i].proId;
					new->next=NULL;
					strcpy(new->name,graph->array[i].name);
					new->date=graph->array[i].date;
					new->month=graph->array[i].month;
					new->year=graph->array[i].year;
	  				while(graph->array[i].head->next!=NULL)
					{
						
						graph->array[i].head = graph->array[i].head->next;
					}				
					graph->array[i].head->next=new1;
					printf("%d %s\n",graph->array[i].head->proId,graph->array[i].head->name);					
					graph->array[i].head=cnode1;
					
					break;
			}
		}
		
		if(graph->array[n-1].head==NULL){
			graph->array[n-1].head=new;
		}
		else{
			while(graph->array[n-1].head->next!=NULL)
			{
				graph->array[n-1].head=graph->array[n-1].head->next;
			}
			graph->array[n-1].head->next=new;
		}
printfrends(graph,n);
printf("YOU ARE FRIENDS NOW.....!!!!!!!!!!!!\n\n");
printf("------------------------------------------------------------------------------\n\n");
}	
}
int countfrends(FR *CNODE){
	int count=0;
	while(CNODE!=NULL){
		count++;
		CNODE=CNODE->next;
	}
	return count;
}

//function to swap data of two nodes a and b
void swap(FR *a, FR *b){
	FR *temp = a;
	a = b;
	b = temp;
}
void findupcomingbdays(ITEM *GRAPH,int num){
	int i,swapped,count=0,temp1,temp2,temp3,temp4;
	char temp5[50];
	FR *hie=NULL,*cnode;
	for(i=0;i<hook;i++){		
		if(GRAPH->array[i].proId==num){ 
			//if (cnode == NULL)
				//return;

			do
			{
				swapped = 0;
				cnode = GRAPH->array[i].head;
				while (cnode->next != hie)
				{
					if (cnode->month >= cnode->next->month)
					{
						if(cnode->month==cnode->next->month){
							if(cnode->date >= cnode->next->date)
							{
								//swap(cnode, cnode->next);
								temp1=cnode->date;cnode->date=cnode->next->date;cnode->next->date=temp1;
								temp2=cnode->month;cnode->month=cnode->next->month;cnode->next->month=temp2;
								temp3=cnode->year;cnode->year=cnode->next->year;cnode->next->year=temp3;
								temp4=cnode->proId;cnode->proId=cnode->next->proId;cnode->next->proId=temp4;
								strcpy(temp5,cnode->name);strcpy(cnode->name,cnode->next->name);strcpy(cnode->next->name,temp5);
								swapped = 1;
							}
						}
						else{
							//swap(cnode, cnode->next);
							temp1=cnode->date;cnode->date=cnode->next->date;cnode->next->date=temp1;
							temp2=cnode->month;cnode->month=cnode->next->month;cnode->next->month=temp2;
							temp3=cnode->year;cnode->year=cnode->next->year;cnode->next->year=temp3;
							temp4=cnode->proId;cnode->proId=cnode->next->proId;cnode->next->proId=temp4;
							strcpy(temp5,cnode->name);strcpy(cnode->name,cnode->next->name);strcpy(cnode->next->name,temp5);
							swapped = 1;
						}
					}
					cnode = cnode->next;
				}
				hie = cnode;
			}
			while (swapped);
			
		}
	}	

}
void printwidbday(FR *cnode,int date,int month,int year)
{
	while (cnode!=NULL) {
		if(cnode->month>=month){
			if(cnode->month==month){
				if(cnode->date>=date){
					printf("->  %s (%d/%d/%d) \n", cnode->name, cnode->date,cnode->month,cnode->year);
				}
			}
			else{
				printf("->  %s (%d/%d/%d) \n", cnode->name, cnode->date,cnode->month,cnode->year);
			}
		}
		cnode = cnode->next;
	}
	printf("\n");
}
void printupcomingbdays(ITEM *graph,int num){
int date,month,year;
	for(int i=0;i<hook;i++)
	{		
		if(graph->array[i].proId==num)
		{
			FR* cnode=graph->array[i].head;
			printf("ENTER TODAYS DATE TO KNOW UPCOMING BDAYS OF FRIENDS OF %s\n",graph->array[i].name);
			scanf("%d ",&date);scanf("%d ",&month);scanf("%d",&year);
			//printf("%d/%d/%d\n",date,month,year);
			printwidbday(cnode,date,month,year);
		}
	}
}
//(OP-1)TO SEARCH BY PERSON NAME
void op1(ITEM *item,int n)
{
	char person[20];
	list(item,n);
	printf("\nENTER PERSON NAME FROM ABOVE LIST:\n\n");
	scanf("%s",person);
	//strcpy(person,"Bhavin");
	searchbyname(item,person,n);
	printf("\n****************************************************************\n\n");  

}

//(OP-2)TO SEARCH BY FAVOURITE PLACE
void op2(ITEM *item,int n)
{
	char place[20];
	int i;
	for(i=0;i<20;i++)
	{
		printf("%s\n",A[i]);
	}
	printf("\nENTER PLACE NAME FROM ABOVE LIST:\n\n");
	scanf("%s",place);
	//strcpy(place,"PARIS");
	searchbyplace(item,place,n);
	printf("\n****************************************************************\n\n");
}
//(OP-3)TO FIND FRIENDS AND MUTUAL FRIENDS OF A PERSON
void op3(ITEM *item,int n)
{
	char person1[20];
	list(item,n);
	printf("\nENTER PERSON NAME FROM ABOVE LIST:\n\n");
	scanf("%s",person1);
	//strcpy(person1,"Arnav");
	mutualfriends(item,n,person1);
	printf("\n****************************************************************\n\n");
}
//(OP-4)TO DELETE A FRIEND FROM FRIENDS LIST
void op4(ITEM *item,int n)
{
	int p1,p2;
	list(item,n);
	printf("\nENTER SERIAL NO. OF PERSON'S NAME FROM ABOVE LIST:\n");
	scanf("%d",&p1);
	int v;
	v=p1;
	if(p1<1 || p1>50){
		printf("INVALID NO. .PLEASE CHOOSE A VALID NO. AGAIN\n");		
		scanf("%d",&p1);
		v=p1;
		printf("----------------------------");
	}
	FR* cnode = item->array[v].head;
	printf("\nFRIENDS OF %d---%s---%s---%s: \n\n", item->array[v].proId,item->array[v].name,item->array[v].homeTown,item->array[v].place);//PRINTING THE HOMETOWN,NAME,PLACE OF THE USER
	while (cnode!=NULL) {
		printf(" %d----%s \n", cnode->proId, cnode->name);//PRINTING THE NAMES AND ID'S OF FRIENDS OF USER
		cnode = cnode->next;
	}
	printf("\n");
	printf("\nENTER SERIAL NO. OF PERSON'S FRIEND NAME FROM ABOVE LIST:\n");
	scanf("%d",&p2);
	if(p2<0 || p2>49){
		printf("INVALID NO. .PLEASE CHOOSE A VALID NO. AGAIN\n");		
		scanf("%d",&p2);
		printf("----------------------------");
	}
	deletefriend(item,p1,p2);
}
//(OP-5)SAME HOME TOWN
void op5(ITEM *item,int n)
{
	int i;
	char place[20];
	for(i=0;i<10;i++)
	{
		printf("%s\n",B[i]);
	}
	printf("\nENTER PLACE NAME FROM ABOVE LIST:\n\n");
	scanf("%s",place);
	peopleFromSamePlace(item,place,n);
	printf("\n****************************************************************\n\n");		
}
//(OP-6)ADD A FRIEND
void op6(ITEM *item,int n)
{
	int a1,a2;
	printfrends(item,n);
	printf("\nENTER IDS OF TWO PERSONS:\n");
	printf("ENTER THE ID OF THE PERSON TO WHOM YOU WANT TO ADD\n");
	scanf("%d",&a1);
	printf("ENTER THE ID OF THE PERSON WHOM YOU WANT TO ADD\n");
	scanf("%d",&a2);
	addfriend123(item,a1,a2,n);
	printf("\n****************************************************************\n\n");	

}
//(OP-7)TO SEARCH A PERSON BY AN ID
void op7(ITEM *item,int n)
{
	int q;
	printf("\nENTER ID OF THE PERSON IN RANGE 20170300-20170350:\n");
	scanf("%d",&q);
	searchbyid(item,q,n);
	printf("\n****************************************************************\n\n");
}
void op8(ITEM *item,int n)
{
char pro[100];
 FILE *out = fopen("name.txt", "a");  
printf("WELCOME TO FB\n");
	printf("YOU CAN SIGNUP HERE FOR FREE\n\n\n");
		 printf("ENTER YOUR NAME:\n");
			scanf("%s",pro);
		  fprintf(out, "%s\n", pro);  
		 
			n++;
			ID;
		//printf("%s***",pro);

		signup(item,pro,n,ID); 
			ID++;

 fclose(out); 
}
//(OP-9)TO FIND THE UPCOMING BIRTHDAY
void op9(ITEM *GRAPH){
	int num;
	printf("ENTER THE SERIAL NUMBER OF THE PERSON FROM THE LIST\n");
	scanf("%d",&num);
	num=20170300+num;
	//printf("%d\n",num);
	findupcomingbdays(GRAPH,num);
	printupcomingbdays(GRAPH,num);
}
//



int main(int argc,char *argv[]) {
	ITEM *item;
	FILE *fp;
	int i,p1,p2,d=10;
	char person[20],place[20],person1[15];
	char pro[100];
	 FILE *out = fopen("name.txt", "a");  
	int opcode;
	hook=n;
	int a1,a2,q;
	srand((unsigned)time(NULL));
	fp = (argc > 1) ? fopen(argv[1], "r+") : fopen("name.txt", "r+");
	read(fp);	
	item = genDataset(n);
	fclose(fp);
	printf("\nTO PRINT THE ITEMS IN A LIST IS:\n\n");
	assignfr(item,n);
	printfrends(item,n);
	printf("\n****************************************************************\n\n");
	while(d>0)
	{
		printf("ENTER OPERATION CODE : \n\n");
		printf("1 - TO SEARCH BY PERSON NAME \n");
		printf("2 - TO SEARCH BY FAVOURITE PLACE\n");
		printf("3 - TO FIND FRIENDS AND MUTUAL FRIENDS OF A PERSON\n");
		printf("4 - TO DELETE A FRIEND FROM FRIENDS LIST\n");
		printf("5 - SAME HOME TOWN\n");
		printf("6 - ADD A FRIEND\n");
		printf("7 - TO SEARCH A PERSON BY AN ID\n");
		printf("8 - TO SIGNIN\n");
		printf("9 - TO KNOW THE UPCOMING BIRTHDAY\n");	
		printf("10 - TO EXIT\n");
		scanf("%d",&opcode);
		switch(opcode)
		{
			case 1:
				op1(item,n);    
				break;
			case 2:
				op2(item,n);
				break;
			case 3:
				op3(item,n);
				break;
			case 4:
				op4(item,n);
				break;
			case 5:
				op5(item,n);
				break;
			case 6:
				op6(item,n);
				break;
			case 7:
				op7(item,n);
				break;
			case 8:
				list(item,n);
				op8(item,n);
				break;	
				
			case 9:
				list(item,n);
		           op9(item);
				break;	
										
			case 10:
				printf("THANKS FOR USING OUR FB\n");
				exit(0);		   
		}
	}   
	return 0;

}
