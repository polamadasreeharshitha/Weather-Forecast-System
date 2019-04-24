/*Include Standard Libraries*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
/*Defining structure Date*/
typedef struct Date{
	int date;         /*date*/
	char month[100];  /*month*/
	int year;         /*year*/
}DATE;
/*Defining structure weather*/
typedef struct weather{
	char place[20];
	char lat[10];
	char lon[10];
	float tempin_cel;  /*temperature in celsius*/
	int humidity;     /*percentage*/
	int CO2_level;    /* in ppm*/
	int sm_density;   /* in nm*/
	DATE D;           /*defining structure date in a structure weather*/
	struct weather *next ;
}WEATHER;
/*Defining the structure User*/
struct user{
	char username[10];    /*username*/
	char password[10];    /*password*/
}*pUser;
/*Defining the structure Admin*/
struct admin{
	char ausername[10];
	char apassword[10];
}*pAdmin;
WEATHER *head=NULL;
/*Insert the weather details*/
WEATHER *insert(WEATHER *w){
	WEATHER *we;            /*declaring we in structure weather*/
	we=head;
	if(head==NULL){         /*if head is NULL it is initiated to w*/
		head=w;
	}
	else{                           /*else it is inserted in next of last node in a list*/
		while(we->next!=NULL){ 
			we=we->next;	
		}
		we->next=w;
	}
	return head;          /*returning head*/
}  
/*Generate the weather details*/
WEATHER *genWeather(FILE *fp){
	WEATHER *w=(WEATHER*)malloc(sizeof(WEATHER));                        /*Allocating space to weather w*/
	float t;                                        /*Declaring required variables*/
	char u[20],A[2000][2000],ch;
	int o=0,j=0,k=0,z,count=0;
	if(fp!=NULL){                                   /*Weather details are taken from file*/
		while(fscanf(fp,"%c",&ch)!=EOF){  
			if(ch=='\n'){
				count++;
			}
			if(ch!=',' && ch!='\n'){
				u[o]=ch;
				o++;
			}
			u[o]='\0';
			strcpy(A[j],u);
			if(ch==','){
				o=0;
				j++;
			}
		}
	}
	z=0;
	for(k=0;k<count;k++){                           /*Inserting the details in the linked list*/
		strcpy(w->place,A[z++]);
		strcpy(w->lat,A[z++]);
		strcpy(w->lon,A[z++]);
		w->tempin_cel=atof(A[z++]);
		w->humidity=atoi(A[z++]);
		w->CO2_level=atoi(A[z++]);
		w->sm_density=atoi(A[z++]);
		w->D.date=atoi(A[z++]);
		strcpy(w->D.month,A[z++]);
		w->D.year=atoi(A[z++]);
		w->next=NULL;                           /*Initiating next pointer to NULL*/
		head=insert(w);                         /*Inserting head node in a linked list*/
		w=(WEATHER*)malloc(sizeof(WEATHER));
	}
	return head;                                    /*Returning head*/
}
/*Function to generate Weather details*/
WEATHER *genweatherDetails(FILE *fp){
	WEATHER *w=(WEATHER*)malloc(sizeof(WEATHER));   /*Allocating space for weather structure w*/
	float t;
	char u[20],A[2000][2000],ch;
	int o=0,j=0,k=0,z,n,i,l1,l2,x,rp,count1=0,count2=0,h,c,s,d,y,count=0;/*Declaring required variables*/
	if(fp!=NULL){
		while(fscanf(fp,"%c",&ch)!=EOF){  
			if(ch=='\n'){
				count++;
			}
			if(ch!=',' && ch!='\n'){
				u[o]=ch;
				o++;
			}
			u[o]='\0';
			strcpy(A[j],u);
			if(ch==','){
				o=0;
				j++;
			}
		}
	}      
	z=0;
	for(k=0;k<count;k++){                           /*Inserting the details in the linked list*/
		strcpy(w->place,A[z++]);
		strcpy(w->lat,A[z++]);
		strcpy(w->lon,A[z++]);
		w->tempin_cel=atof(A[z++]);
		w->humidity=atoi(A[z++]);
		w->CO2_level=atoi(A[z++]);
		w->sm_density=atoi(A[z++]);
		w->D.date=atoi(A[z++]);
		strcpy(w->D.month,A[z++]);
		w->D.year=atoi(A[z++]);
		w->next=NULL;                           /*Initialising next pointer to NULL*/
		head=insert(w);                         /*Inserting head node in linked list*/
		w=(WEATHER*)malloc(sizeof(WEATHER));    /*Allocating space for weather structure w*/
	}
	WEATHER *wt=(WEATHER*)malloc(sizeof(WEATHER));  /*Allocating space for weather structure wt*/
	WEATHER *b1,*b2;                                /*Declaring b1 & b2 in structure weather*/
	printf("How many entries do you want to enter?\n");/*Give the number of new entries you want to enter in a file*/
	scanf("%d",&n);                                 /*Scanning the number*/
	if(n==0){                                       /*If 0 entry then add data exits*/
		printf("Thank you");
		exit(1); 
	}
	for(i=1;i<=n;i++){                              /*Else entered details are stored in file and linked list*/
		char p[20]={ },l[10]={ },lo[10]={ },m[10]={ };
		printf("Enter the place, Latitude,Longitude:\n");
		scanf("%s %s %s",p,l,lo);               /*Scanning Place,latitude & longitude*/
		l1=strlen(l);
		l2=strlen(lo);
		for(rp=0;rp<l1;rp++){                   /*Conditions to check Admin entered valid latitude and longitude*/
			if(l[rp]=='.'){                 /*condition that only one '.' should be present in lat & lon string*/
				count1++; 
			}
		} 
		for(x=0;x<l2;x++){
			if(lo[x]=='.'){
				count2++; 
			}
		}
		while(count1>=2){                       /*If the admin entered wrong lat or lon asking for correct lat & lon*/
			count1=0;
			printf("Enter the Latitude:\n");
			scanf("%s",l);
			l1=strlen(l);
			for(rp=0;rp<l1;rp++){
				if(l[rp]=='.'){
					count1++; 
				}
			}
		}
		while(count2>=2){
			count2=0;
			printf("Enter the Longitude:\n");
			scanf("%s",lo);
			l2=strlen(lo);
			for(x=0;x<l2;x++){
				if(lo[x]=='.'){
					count2++;
				}
			}
		}    
		l1=strlen(l);
		l2=strlen(lo);      /*condition to check in lat & lon only 'N' 'E' 'W' 'S' directions present */
		while(l[l1-1]!='N' && l[l1-1]!='S' && l[l1-1]!='E' && l[l1-1]!='W'){ 
			printf("Please enter a valid latitude:\n");
			scanf("%s",l);
		}
		while(lo[l2-1]!='N' && lo[l2-1]!='S' && lo[l2-1]!='E' && lo[l2-1]!='W'){
			printf("Please enter a valid longitude:\n");
			scanf("%s",lo);
		}
		while(l[l1-1]==lo[l2-1]){
			printf("Please enter valid latitude and longitude:\n");
			scanf("%s",l);
			scanf("%s",lo);
		}
		FILE *fp3=fopen("ram1.txt","r+"); /*Inserting ddetails in a file*/
		b1=genWeather(fp3);               /*Inserting in linked list*/
		fclose(fp3);                      /*closing file*/
		while(b1!=NULL){
			if(strcmp(p,b1->place)==0){     /*If place exist latitude and longitude are checked with previous one*/
				while(strcmp(l,b1->lat)!=0){
					printf("Enter correct latitude for that place:  ");
					scanf("%s",l);
				}
			}
			b1=b1->next;
		}
		FILE *fp4=fopen("ram1.txt","r+");       /*Opening the file in read+ mode*/
		b2=genWeather(fp4);                     /*Inserting weather details in linked list*/
		fclose(fp4);                            /*closing the file*/
		while(b2!=NULL){
			if(strcmp(p,b2->place)==0){
				while(strcmp(lo,b2->lon)!=0){
					printf("Enter correct longitude for that place:  ");
					scanf("%s",lo);
				}
			}
			b2=b2->next;
		}
		printf("Enter data-");
		printf("Enter Temperature(in celsius): ");  /*Entering temperature in celsius*/
		scanf("%f",&t);
		while(t<=-20 || t>=60){
		  printf("Temperature is beyond the expected range,so try again");
		  scanf("%f",&t);}
		printf("Enter  humidity level(percentage): ");  /*Entering humidity in gram per cubic meter*/
		scanf("%d",&h);
		while(h<8 || h>99){
		  printf("Humidity is beyond expected range,so try again");
		  scanf("%d",h);}
		printf("Enter CO2 level(in ppm): ");    /*Entering CO2_level in ppm*/
		scanf("%d",&c);
		while(c<100 || c>450){
		  printf("CO2 level is beyond expected range, so try again");
		  scanf("%d",c);}
		printf("smoke_density(in nm): ");     /*Entering Smoke_density in nanometers*/
		scanf("%d",&s);
		while(s<1 && s>300){
		printf("smoke_density(in nm): ");     /*Entering Smoke_density in nanometers*/
		scanf("%d",&s);}
		printf("Enter today's date in date month year format:\n");  /*Entering date*/
		scanf("%d %s %d",&d,m,&y);
		/*Conditions to check admin entered date in correct form or not*/
		while(strcmp(m,"Jan")!=0 && strcmp(m,"Feb")!=0 && strcmp(m,"Mar")!=0 && strcmp(m,"Apr")!=0 && strcmp(m,"may")!=0  && strcmp(m,"Jun")!=0  && strcmp(m,"Jul")!=0 && strcmp(m,"august")!=0 && strcmp(m,"Sep")!=0 && strcmp(m,"Oct")!=0 && strcmp(m,"Nov")!=0 && strcmp(m,"Dec")!=0){
			printf("Enter valid date in date month year format:\n"); /*condition for correct month*/
			scanf("%d %s %d",&d,m,&y);
		}
		while(y<=1520 || y>=2050){              /*Range of year should be between 1520 and 2050*/
			printf("Enter valid date in date month year format:\n");
			scanf("%d %s %d",&d,m,&y);
		}
		if(strcmp(m,"Feb")==0){
			if(y%4==0){                     /*condition for leap year*/
				while(d>29){
					printf("Enter valid date in date month year format:\n");
					scanf("%d %s %d",&d,m,&y);
				}
			}
			else{                           /*condition for 28 days in feb*/
				while(d>28){
					printf("Enter valid date in date month year format:\n");
					scanf("%d %s %d",&d,m,&y);
				}
			}
		}/*Condition for 31 days months*/
		else if(strcmp(m,"Jan")==0 || strcmp(m,"Mar")==0 || strcmp(m,"may")==0 || strcmp(m,"Jul")==0 || strcmp(m,"august")==0 || strcmp(m,"Oct")==0 || strcmp(m,"Dec")==0){
			while(d>31){
				printf("Enter valid date in date month year format:\n");
				scanf("%d %s %d",&d,m,&y);
			}
		}/*Condition for 30 days months*/
		else if(strcmp(m,"Apr")==0 || strcmp(m,"Jun")==0 || strcmp(m,"Sep")==0 || strcmp(m,"Nov")==0 ){
			while(d>30){
				printf("Enter valid date in date month year format:\n");
				scanf("%d %s %d",&d,m,&y);
			}
		}		
		fprintf(fp,"%s,%s,%s,%.2f,%d,%d,%d,%d,%s,%d,",p,l,lo,t,h,c,s,d,m,y); /*Inserting weather details in file*/
		fprintf(fp,"\n");
		strcpy(wt->place,p);
		strcpy(wt->lat,l);
		strcpy(wt->lon,lo);
		wt->tempin_cel=t;
		wt->humidity=h;
		wt->CO2_level=c;
		wt->sm_density=s;
		wt->D.date=d;
		strcpy(wt->D.month,m);
		wt->D.year=y;
		wt->next=NULL;                  /*Initialising next pointer to NULL*/
		head=insert(wt);                /*Inserting head node in linked list*/
		wt=(WEATHER*)malloc(sizeof(WEATHER));/*Allocating space for weather stucture wt*/
	}
	return head;                          /*returning head*/
}
/*Function to print the details of weather*/
void print(WEATHER *w){
	while(w!=NULL){
		printf("location:%s  lat:%s  lon:%s  temp:%.2f  humidity:%d  CO2level:%d  sm-density:%d  Date:%d %s %d \n",w->place,w->lat ,w->lon,w->tempin_cel,w->humidity,w->CO2_level,w->sm_density,w->D.date,w->D.month,w->D.year);
		w=w->next;
	}
}
/*Function to convert month to number format*/
int strToNum(char month[]){
	int k;                          /*Declaring required variable*/
	if(strcmp("Jan",month)==0)
		k=1;
	else if(strcmp("Feb",month)==0)
		k=2;
	else if(strcmp("Mar",month)==0)
		k=3;
	else if(strcmp("Apr",month)==0)
		k=4;
	else if(strcmp("may",month)==0)
		k=5;
	else if(strcmp("Jun",month)==0)
		k=6;
	else if(strcmp("Jul",month)==0)
		k=7;
	else if(strcmp("august",month)==0)
		k=8;
	else if(strcmp("Sep",month)==0)
		k=9;
	else if(strcmp("Oct",month)==0)
		k=10;
	else if(strcmp("Nov",month)==0)
		k=11;
	else if(strcmp("Dec",month)==0)
		k=12;
	return k;                       /*returning k*/
}
/*Function to swap integers*/
void IntSwap(int a[],int b[]){
	*a = *a + *b;                   /*swapping the arrays without using temperary array*/
	*b = *a - *b;
	*a = *a - *b;
}
/*Function to swap strings*/
void StringSwap(char a[],char b[]){
	char temp[100];                 /*swapping the strings using temperary string*/
	strcpy(temp,a);
	strcpy(a,b);
	strcpy(b,temp);
}
/*Function to swap floats*/
void FloatSwap(float a[],float b[]){
	*a = *a + *b;                   /*swapping the arrays without using temperary array*/
	*b = *a - *b;
	*a = *a - *b;
}
/*Function to SortDates*/
void sortdates(WEATHER *w){
	WEATHER *q,*q1;
	q=(WEATHER *)malloc(sizeof(WEATHER));  /*Allocating space for weather structure w*/
	q1=(WEATHER *)malloc(sizeof(WEATHER));	/*Allocating space for weather structure w*/
	q=w;
	while(q!=NULL){                         /*Checking date1 with rest of the dates and date2 with rest and so on..*/
		q1=w;
		while(q1!=NULL){
			if(q->D.year<q1->D.year){      /*If q->D.year is greater than q1->D.year then swapping occurs*/
				IntSwap(&q->D.year,&q1->D.year);
				StringSwap(q->D.month,q1->D.month);
				IntSwap(&q->D.date,&q1->D.date);
				IntSwap(&q->sm_density,&q1->sm_density);           
				StringSwap(q->place,q1->place);   
				FloatSwap(&q->tempin_cel,&q1->tempin_cel);
				IntSwap(&q->humidity,&q1->humidity);
				IntSwap(&q->CO2_level,&q1->CO2_level);
				StringSwap(q->lat,q1->lat);
				StringSwap(q->lon,q1->lon);

			}
			else if(q->D.year==q1->D.year){         /*If q->D.year is equal to q1->D.year*/
				if(strToNum(q->D.month)<strToNum(q1->D.month)){ /*If q->D.month is greater q1->D.month then swapping occurs*/
					IntSwap(&q->D.year,&q1->D.year);
					StringSwap(q->D.month,q1->D.month);
					IntSwap(&q->D.date,&q1->D.date);
					IntSwap(&q->sm_density,&q1->sm_density);          
					StringSwap(q->place,q1->place);   
					FloatSwap(&q->tempin_cel,&q1->tempin_cel);
					IntSwap(&q->humidity,&q1->humidity);
					IntSwap(&q->CO2_level,&q1->CO2_level);
					StringSwap(q->lat,q1->lat);
					StringSwap(q->lon,q1->lon);
				}
				else if(strToNum(q->D.month)==strToNum(q1->D.month)){/*If q->D.month is equal to q1->D.month*/
					if(q->D.date<q1->D.date){               /*If q->D.date is greater q1->D.date then swapping occurs*/
						IntSwap(&q->D.year,&q1->D.year);
						StringSwap(q->D.month,q1->D.month);
						IntSwap(&q->D.date,&q1->D.date);
						IntSwap(&q->sm_density,&q1->sm_density);            
						StringSwap(q->place,q1->place);   
						FloatSwap(&q->tempin_cel,&q1->tempin_cel);
						IntSwap(&q->humidity,&q1->humidity);
						IntSwap(&q->CO2_level,&q1->CO2_level);
						StringSwap(q->lat,q1->lat);
						StringSwap(q->lon,q1->lon);
					}
					else if(q->D.date==q1->D.date){     /*If q->D.date is equal to q1->D.date*/
						q1=q1->next;
						continue;
					}
				}
			}
			q1=q1->next;            /*Pointer is moved to next till next pointer is pointed to NULL*/
		}
		q=q->next;                      /*Pointer is moved to next till next pointer is pointed to NULL*/
	}
	print(w);                               /*Print the weather details after date sort*/
}
/*Function for Temperature sort*/
void TemperatureSort(WEATHER *q){
	WEATHER *q1,*q2;                          /*Declaring q1 & q2 in structure weather*/
	q1=(WEATHER *)malloc(sizeof(WEATHER));    /*Allocating space nodes q1 & q2*/
	q2=(WEATHER *)malloc(sizeof(WEATHER));
	q1=q;                                        /*Equating q1 with head*/
	while(q1!=NULL){                                /*loop runs till q1==NULL*/
		q2=q;                                /*Equating q1 with head*/
		while(q2!=NULL){                        /*loop runs till q2==NULL*/
			if(q1->tempin_cel<q2->tempin_cel){
				IntSwap(&q1->sm_density,&q2->sm_density);           
				StringSwap(q1->place,q2->place);   
				FloatSwap(&q1->tempin_cel,&q2->tempin_cel);
				IntSwap(&q1->humidity,&q2->humidity);
				IntSwap(&q1->CO2_level,&q2->CO2_level);
				StringSwap(q1->lat,q2->lat);
				StringSwap(q1->lon,q2->lon);
				IntSwap(&q1->D.date,&q2->D.date);
				StringSwap(q1->D.month,q2->D.month);
				IntSwap(&q1->D.year,&q2->D.year);
			}
			else{
				q2=q2->next;            /*q2 pointer moves to next*/
				continue;
			}
			q2=q2->next;
		}
		q1=q1->next;                            /*q1 pointer moves to next*/
	}
	print(q);                               /*Print the weather details after temperature sort*/
}
/*Function for Humidity sort*/
void HumiditySort(WEATHER *q){
	WEATHER *q1,*q2;                        /*Declaring q1 & q2 in structure weather*/
	q1=(WEATHER *)malloc(sizeof(WEATHER));    /*allocating space nodes q1 & q2*/
	q2=(WEATHER *)malloc(sizeof(WEATHER));
	q1=q;                                        /*Equating q1 with head*/
	while(q1!=NULL){                                /*loop runs till q1==NULL*/
		q2=q;                                /*Equating q1 with head*/
		while(q2!=NULL){                        /*loop runs till q2==NULL*/
			if(q1->humidity<q2->humidity){
				IntSwap(&q1->sm_density,&q2->sm_density);          
				StringSwap(q1->place,q2->place);   
				FloatSwap(&q1->tempin_cel,&q2->tempin_cel);
				IntSwap(&q1->humidity,&q2->humidity);
				IntSwap(&q1->CO2_level,&q2->CO2_level);
				StringSwap(q1->lat,q2->lat);
				StringSwap(q1->lon,q2->lon);
				IntSwap(&q1->D.date,&q2->D.date);
				StringSwap(q1->D.month,q2->D.month);
				IntSwap(&q1->D.year,&q2->D.year);
			}
			else{
				q2=q2->next;            /*q2 pointer moves to next*/
				continue;
			}
			q2=q2->next;
		}
		q1=q1->next;                            /*q1 pointer moves to next*/
	}
	print(q);                               /*Print the weather details after humidity sort*/
}
/*Function for CO2 sorting*/
void CO2Sort(WEATHER *q){
	WEATHER *q1,*q2;                          /*Declaring q1 & q2 in structure weather*/
	q1=(WEATHER *)malloc(sizeof(WEATHER));    /*allocating space nodes q1 & q2*/
	q2=(WEATHER *)malloc(sizeof(WEATHER));
	q1=q;                                        /*Equating q1 with head*/
	while(q1!=NULL){                                /*loop runs till q1==NULL*/
		q2=q;                                /*Equating q1 with head*/
		while(q2!=NULL){                        /*loop runs till q2==NULL*/
			if(q1->CO2_level<q2->CO2_level){
				IntSwap(&q1->sm_density,&q2->sm_density);           
				StringSwap(q1->place,q2->place);   
				FloatSwap(&q1->tempin_cel,&q2->tempin_cel);
				IntSwap(&q1->humidity,&q2->humidity);
				IntSwap(&q1->CO2_level,&q2->CO2_level);
				StringSwap(q1->lat,q2->lat);
				StringSwap(q1->lon,q2->lon);
				IntSwap(&q1->D.date,&q2->D.date);
				StringSwap(q1->D.month,q2->D.month);
				IntSwap(&q1->D.year,&q2->D.year);
			}
			else{
				q2=q2->next;            /*q2 pointer moves to next*/
				continue;
			}
			q2=q2->next;
		}
		q1=q1->next;                            /*q1 pointer moves to next*/
	}
	print(q);                               /*Printing the weather details after co2 sort*/
}
/*Function for DensitySort*/
void DensitySort(WEATHER *q){
	WEATHER *q1,*q2;
	q1=(WEATHER *)malloc(sizeof(WEATHER));    /*allocating space nodes q1 & q2*/
	q2=(WEATHER *)malloc(sizeof(WEATHER));
	q1=q;                                        /*Equating q1 with head*/
	while(q1!=NULL){                                /*loop runs till q1==NULL*/
		q2=q;                                /*Equating q1 with head*/
		while(q2!=NULL){                        /*loop runs till q2==NULL*/
			if(q1->sm_density<q2->sm_density){
				IntSwap(&q1->sm_density,&q2->sm_density);           
				StringSwap(q1->place,q2->place);   
				FloatSwap(&q1->tempin_cel,&q2->tempin_cel);
				IntSwap(&q1->humidity,&q2->humidity);
				IntSwap(&q1->CO2_level,&q2->CO2_level);
				StringSwap(q1->lat,q2->lat);
				StringSwap(q1->lon,q2->lon);
				IntSwap(&q1->D.date,&q2->D.date);
				StringSwap(q1->D.month,q2->D.month);
				IntSwap(&q1->D.year,&q2->D.year);
			}
			else{
				q2=q2->next;            /*q2 pointer moves to next*/
				continue;
			}
			q2=q2->next;
		}
		q1=q1->next;                            /*q1 pointer moves to next*/
	}
	print(q);               /*Print the weather details after Density sort*/
}
/*Function for Temperature Modify*/
void Temperaturemodify(WEATHER *w){
	char P[100],m[100];             /*Declaring required variables*/
	int d,y,flag=0;
	float temp;
	printf("Enter the Place\n");  /*Modifying temperature based on place and date*/
	scanf("%s",P);
	printf("Enter the date\n");
	scanf("%d %s %d",&d,m,&y);
	if(strcmp(m,"Feb")==0){       /*Condition to check valid date*/
		while(d>28){
			printf("Enter valid date in date month year format:\n");
			scanf("%d %s %d",&d,m,&y);
		}
	}/*condition for 31 days month*/
	else if(strcmp(m,"Jan")==0 || strcmp(m,"Mar")==0 || strcmp(m,"may")==0 || strcmp(m,"Jul")==0 || strcmp(m,"august")==0 || strcmp(m,"Oct")==0 || strcmp(m,"Dec")==0){
		while(d>31){
			printf("Enter valid date in date month year format:\n");
			scanf("%d %s %d",&d,m,&y);
		}
	}/*condition for 30 days month*/
	else{
		while(d>30){
			printf("Enter valid date in date month year format:\n");
			scanf("%d %s %d",&d,m,&y);
		}
	}		
	while(w!=NULL){                /*Modifying Temperature based on given value to the place*/
		if(strcmp(w->place,P)==0){
			if(w->D.date==d && strcmp(w->D.month,m)==0 && w->D.year==y){
				printf("Enter the required temperature:\n");
				scanf("%f",&temp);
				w->tempin_cel=temp;
				flag=1;
				break;
			}
		}
		w=w->next;
	}
	if(flag==0){                   /*If the file is empty*/
		printf("There is no such entry to modify temperature\n");
	}

}
/*Function for Humidity Modify*/
void Humiditymodify(WEATHER *w){
	char P[100],m[100];             /*Declaring required variables*/
	int d,y,flag=0;
	float temp;
	printf("Enter the Place\n");    /*Modifying humidity based on place and date*/
	scanf("%s",P);
	printf("Enter the date\n");
	scanf("%d %s %d",&d,m,&y);
	if(strcmp(m,"Feb")==0){       /*Condition to check valid date*/
		while(d>28){
			printf("Enter valid date in date month year format:\n");
			scanf("%d %s %d",&d,m,&y);
		}
	}/*condition for 31 days month*/
	else if(strcmp(m,"Jan")==0 || strcmp(m,"Mar")==0 || strcmp(m,"may")==0 || strcmp(m,"Jul")==0 || strcmp(m,"august")==0 || strcmp(m,"Oct")==0 || strcmp(m,"Dec")==0){
		while(d>31){
			printf("Enter valid date in date month year format:\n");
			scanf("%d %s %d",&d,m,&y);
		}
	}/*condition for 30 days month*/
	else{
		while(d>30){
			printf("Enter valid date in date month year format:\n");
			scanf("%d %s %d",&d,m,&y);
		}
	}
	while(w!=NULL){                 /*Modifying humidity based on given value to the place*/
		if(strcmp(w->place,P)==0){
			if(w->D.date==d && strcmp(w->D.month,m)==0 && w->D.year==y){
				printf("Enter the required humidity:\n");
				scanf("%f",&temp);
				w->humidity=temp;
				flag=1;
				break;
			}
		}
		w=w->next;
	}
	if(flag==0){                    /*If the file is empty*/
		printf("There is no such entry to modify humidity\n");
	}
}
/*Function for Smoke_density Modify*/
void SmokeDensitymodify(WEATHER *w){
	char P[100],m[100];                     /*Declaring required variables*/
	int d,y,flag=0;
	float temp;
	printf("Enter the Place\n");            /*Modifying Smoke_density based on place and date*/
	scanf("%s",P);
	printf("Enter the date\n");
	scanf("%d %s %d",&d,m,&y);
	if(strcmp(m,"Feb")==0){       /*Condition to check valid date*/
		while(d>28){
			printf("Enter valid date in date month year format:\n");
			scanf("%d %s %d",&d,m,&y);
		}
	}/*condition for 31 days month*/
	else if(strcmp(m,"Jan")==0 || strcmp(m,"Mar")==0 || strcmp(m,"may")==0 || strcmp(m,"Jul")==0 || strcmp(m,"august")==0 || strcmp(m,"Oct")==0 || strcmp(m,"Dec")==0){
		while(d>31){
			printf("Enter valid date in date month year format:\n");
			scanf("%d %s %d",&d,m,&y);
		}
	}/*condition for 30 days month*/
	else{
		while(d>30){
			printf("Enter valid date in date month year format:\n");
			scanf("%d %s %d",&d,m,&y);
		}
	}
	while(w!=NULL){
		if(strcmp(w->place,P)==0){      /*Modifying Smoke_density based on given value to the place*/
			if(w->D.date==d && strcmp(w->D.month,m)==0 && w->D.year==y){
				printf("Enter the required smokeDensity:\n");
				scanf("%f",&temp);
				w->sm_density=temp;
				flag=1;
				break;
			}
		}
		w=w->next;
	}
	if(flag==0){                    /*If the file is empty*/
		printf("There is no such entry to modify smokeDensity\n");
	}      
}
/*Function to print weather details*/
void Print_D(WEATHER *w){
	printf("location:%s  lat:%s  lon:%s  temp:%.2f  humidity:%d  CO2level:%d  sm-density:%d  Date:%d %s %d \n",w->place,w->lat ,w->lon,w->tempin_cel,w->humidity,w->CO2_level,w->sm_density,w->D.date,w->D.month,w->D.year);
}
/*Function to CO2_level Modify*/
void CO2levelmodify(WEATHER *w){
	char P[100],m[100];             /*Declaring required variables*/
	int d,y,flag=0;
	float temp;
	printf("Enter the Place\n");   /*Modifying CO2_level based on place and date*/
	scanf("%s",P);
	printf("Enter the date\n");
	scanf("%d %s %d",&d,m,&y);
	if(strcmp(m,"Feb")==0){       /*Condition to check valid date*/
		while(d>28){
			printf("Enter valid date in date month year format:\n");
			scanf("%d %s %d",&d,m,&y);
		}
	}/*condition for 31 days month*/
	else if(strcmp(m,"Jan")==0 || strcmp(m,"Mar")==0 || strcmp(m,"may")==0 || strcmp(m,"Jul")==0 || strcmp(m,"august")==0 || strcmp(m,"Oct")==0 || strcmp(m,"Dec")==0){
		while(d>31){
			printf("Enter valid date in date month year format:\n");
			scanf("%d %s %d",&d,m,&y);
		}
	}/*condition for 30 days month*/
	else{
		while(d>30){
			printf("Enter valid date in date month year format:\n");
			scanf("%d %s %d",&d,m,&y);
		}
	}
	while(w!=NULL){
		if(strcmp(w->place,P)==0){      /*Modifying CO2_level based on given value to the place*/
			if(w->D.date==d && strcmp(w->D.month,m)==0 && w->D.year==y){
				printf("Enter the required CO2level:\n");
				scanf("%f",&temp);
				w->CO2_level=temp;
				flag=1;
				break;
			}
		}
		w=w->next;
	}
	if(flag==0){                    /*If the file is empty*/
		printf("There is no such entry to modify CO2level\n");
	}       
}
char str[10],k[10],month[10];
int y,d;                        /*Declaring required variables globally*/
char m[100];
/*Function to know automatic date*/
void Aut(){
	char D[100];            /*Declaring required variables*/
	time_t t;
	time(&t);
	strcpy(D,ctime(&t));    
	int count3=0;
	for(int i=0;i<strlen(D)-1;i++){
		if(D[i]==' ' || D[i]=='\n'){
			count3++;
			continue;
		}
		if(i==8){
			int d=0;
			for(int h=i;h<i+2;h++){
				k[d++]=D[h];            /*date is stored in k*/
			}
			k[d++]='\0';
		}
		if(i==4){
			int r=0;
			for(int y=i;y<i+3;y++){
				month[r++]=D[y];        /*month is stored in month array*/
			}
			month[r++]='\0';
		}
		if(i==strlen(D)-2){
			int l=0;
			for(int j=i-3;j<=i;j++){
				str[l++]=D[j];          /*Year is stored in D*/
			}
			str[l++]='\0';
		}
	}
	d=atoi(k);
	strcpy(m,month);
	y=atoi(str);
	printf("Today's date is:");
	printf("%d %s %d\n",d,m,y);
}
/*Function to show today's details*/
void TodayDetails(WEATHER *w){
	int flag=0;             /*Declaring required variables*/
	Aut();  
	while(w!=NULL){
		if(w->D.date==d && strcmp(w->D.month,m)==0 && w->D.year==y){
			flag=1;
			printf("location:%s  lat:%s  lon:%s  temp:%.2f  humidity:%d  CO2level:%d  sm-density:%d\n",w->place,w->lat ,w->lon,w->tempin_cel,w->humidity,w->CO2_level,w->sm_density);
		}
		w=w->next;
	}
	if(flag==0)            /*If file is empty*/
		printf("SORRY!There are no details with this date.Make sure you have details with this date");
}
/*Function to show yesterday's details*/
void YesterdayDetails(WEATHER *w){
	int flag=0;             /*Declaring required variables*/
	Aut();
	int newd=d-1;
	while(w!=NULL){
		if(w->D.date==newd && strcmp(w->D.month,m)==0 && w->D.year==y){
			flag=1;   
			Print_D(w);
		}
		w=w->next;
	}
	if(flag==0)            /*If file is empty*/
		printf("SORRY!There are no details with this date.Make sure you have details with this date");
}
/*Function to show last week details*/
void LastWeekDetails(WEATHER *w){
	int count,count1, mo,flag=0;            /*Declaring required variables*/
	Aut();
	int newdate=d-7;
	char month[100];
	count=d-1;
	count1=7-count;
	mo=strToNum(m);                 /*Converting month to number*/
	if(mo==1)
		mo=12;
	else
		mo=mo-1;	
	if(mo==1)
		strcpy(month,"Jan");
	if(mo==2)	
		strcpy(month,"Feb");
	if(mo==3)
		strcpy(month,"Mar");
	if(mo==4)
		strcpy(month,"Apr");
	if(mo==5)
		strcpy(month,"may");
	if(mo==6)
		strcpy(month,"Jun");
	if(mo==7)
		strcpy(month,"Jul");
	if(mo==8)
		strcpy(month,"Aug");
	if(mo==9)
		strcpy(month,"Sep");
	if(mo==10)
		strcpy(month,"Oct");
	if(mo==11)
		strcpy(month,"Nov");
	if(mo==12)
		strcpy(month,"Dec");
	while(w!=NULL){
		if(d>7){                /*If date is greater than 7 we are printing date with date-7*/
			if(w->D.date>=newdate && w->D.date<d && strcmp(w->D.month,m)==0 && w->D.year==y){ 
				flag=1;   
				Print_D(w);
			}
		}
		else{                /*If date is less than 7 print the dates with dates 1 to date in that month*/
			if(w->D.date>=1 && w->D.date<d && strcmp(w->D.month,m)==0 && w->D.year==y){
				flag=1;
				Print_D(w);                  /*print weather details*/
			}           /*If month is december then month is decremented to january and year is decremented by 1*/
			if(strcmp(month,"Dec")==0){ 
				if(w->D.date<=31 && w->D.date>31-count1 && strcmp(w->D.month,month)==0 && w->D.year==y-1){
					flag=1;
					Print_D(w);         /*print weather details*/
				}
			}
			else{   /*If date is less than 7 , prints the remaining dates in last month*/
				if(w->D.date<=31 && w->D.date>31-count1 && strcmp(w->D.month,month)==0 && w->D.year==y){
					flag=1;
					Print_D(w);        /*print weather details*/
				}
			}
		}
		w=w->next;
	}
	if(flag==0){            /*If file is empty*/
		printf("SORRY!There are no details in last week with this date.Make sure you have details with this date");
	}
}
/*Function to show place details*/
void PlaceDetails(WEATHER *w){
	char pl[20];            /*Declaring required variables*/
	int flag=0;
	printf("Enter place: ");
	scanf("%s",pl);
	Aut();
	while(w!=NULL){         /*It checks whether the place details are there with today's date*/
		if(strcmp(w->place,pl)==0 && d==w->D.date && y==w->D.year && strcmp(w->D.month,m)==0){ 
		        flag=1;   
			printf("location: %s\n  lat: %s  lon: %s\n  temp: %.2f\n  humidity: %d\n  CO2level: %d\n  sm-density: %d\n",w->place,w->lat ,w->lon,w->tempin_cel,w->humidity,w->CO2_level,w->sm_density);
		} 
		w=w->next;
	}
	if(flag==0){    /*If file is empty*/
	        printf("SORRY!There are no details regarding this place\n.");
	}
}
/*Function to show last month details*/
void LastMonthDetails(WEATHER *w){
	int count,count1,mo,flag=0;             /*Declaring required variables*/
	char newm[100];
	Aut();
	int newdate=d-30;
	char month[100];
	count=d-1;
	count1=31-count;
	mo=strToNum(m);                         /*Converting month to number*/
	if(mo==1)
		mo=12;
	else
		mo=mo-1;	
	if(mo==1)
		strcpy(month,"Jan");
	if(mo==2)	
		strcpy(month,"Feb");
	if(mo==3)
		strcpy(month,"Mar");
	if(mo==4)
		strcpy(month,"Apr");
	if(mo==5)
		strcpy(month,"may");
	if(mo==6)
		strcpy(month,"Jun");
	if(mo==7)
		strcpy(month,"Jul");
	if(mo==8)
		strcpy(month,"august");
	if(mo==9)
		strcpy(month,"Sep");
	if(mo==10)
		strcpy(month,"Oct");
	if(mo==11)
		strcpy(month,"Nov");
	if(mo==12)
		strcpy(month,"Dec");	
	while(w!=NULL){
		if(d>=30){              /*If date is greater than 29 then we are printing date-30*/
			if(w->D.date>=newdate && w->D.date<d && strcmp(w->D.month,m)==0 && w->D.year==y){
				flag=1;
				Print_D(w);      /*print weather details*/
			}
		}
		else{   /*If month is december both month and year is decremented by 1*/
			if(strcmp(month,"Dec")==0){
				if(w->D.date>=1 && w->D.date<d && strcmp(w->D.month,m)==0 && w->D.year==y-1){
					flag=1;
					Print_D(w);      /*print weather details*/
				} 
			}
			else{ /*If date is less than 31 then we print 31-count1*/
				if(w->D.date<=31 && w->D.date>31-count1 && strcmp(w->D.month,month)==0 && w->D.year==y){
					flag=1;
					Print_D(w);      /*print weather details*/
				}
			}	 
		}
		w=w->next;
	}
	if(flag==0){    /*If file is empty*/
		printf("SORRY!There are no details in last month with this date.Make sure you have details with this date");
	}
}
/*Function to user login*/
void userlogin(){
	FILE *fp;
	int count=0,input,i,n,flag;             /*Declaring required variables*/
	char sort,cap;
	char uName[10], pwd[10];char c,v;
	WEATHER *w;                             /*Declaring w in structure weather*/
	pUser=(struct user *)malloc(sizeof(struct user));       /*Allocating memory*/
	FILE *fp1=fopen("ram1.txt","a+");               /*Opening file in append+ mode*/
	printf("1. Login Through An Existing Account\n2. Create New account\n");
	scanf("%d",& i);                        /*input for switch case*/
	switch(i){
		case 1:                         /*case 1 for user accout already exist*/
			if ( ( fp=fopen("user.txt", "r+")) == NULL) {   /*condition to check if file doesnot exist*/
				if ( ( fp=fopen("user.txt", "w+")) == NULL) {
					printf ("Could not open file\n");
					exit (1);
				}
			}
			flag=0;
			printf("Username: ");           /*Enter username*/
			scanf("%9s",uName);
			printf("Password: ");           /*Enter password*/
			scanf("%9s",pwd);
			while ( fread (pUser, sizeof(struct user), 1, fp) >= 1) { /*condition to check useraccount exists or not*/
				if( strcmp ( pUser->username, uName) == 0) {
					flag=1;                         /*flag is 1 if useraccount exists*/
					if( strcmp ( pUser->password, pwd) == 0) { /*if password is correct or not*/
						do{
							flag=1;
							printf("Logged in Successfully\n");
							printf("Show data\n");
							int var;
							int j=0;
							w=genWeather(fp1);          /*weather details are generated*/
							printf("1.Show today's details:\n");
							printf("2.Show yesterdays's details:\n");
							printf("3.Show details of last week:\n");
							printf("4.Show details of last month:\n");
							printf("5.Place details:\n");
							scanf("%d",&var);   /*input to show data*/
							switch(var){        /*switch case*/
								case 1:{    /*In case 1 it show's today's details*/
									       TodayDetails(w);
									       break;
								}
								case 2:{   /*In case 2 it show's yesterday's details*/
									       YesterdayDetails(w);
									       break;
								}
								case 3:{   /*In case 3 it show's lastweek details*/
									       LastWeekDetails(w);
									       break;
								}
								case 4:{   /*In case 4 it show's last month details*/
									       LastMonthDetails(w);
									       break;
								}
								case 5:{   /*In case 5 it show's place details*/
									       PlaceDetails(w);
									       break;
							        }
							}	
							printf("Do you want to go with other options (Y/N): ");
							scanf(" %c",&v); /*If user wants to know more than 1 cases he types y*/
						}while(v=='Y' || v=='y');			          	 
					}			     
					else{/*If password is wrong user gets 3 chances to type correct password*/
						do{
							while(count<3){ 
								printf("Try again\n");
								printf("Password: ");  /*User reenters the password*/
								scanf("%9s",pwd);
								if(strcmp ( pUser->password, pwd) == 0){       
									count=4;
									flag=1;
									printf("Logged in Successfully\n");
									printf("Show data\n");
									int var;        /*Declaring required variables*/
									int j=0;
									w=genWeather(fp1);  /*weather details are generated*/
									printf("1.Show today's details:\n");
									printf("2.Show yesterdays's details:\n");
									printf("3.Show details of last week:\n");
									printf("4.Show details of last month:\n");
									printf("5.Place details:\n");
									scanf("%d",&var); /*input to show data*/
									switch(var){      /*switch case*/
										case 1:{  /*In case 1 it show's today's details*/
											       TodayDetails(w);
											       break;
										       }
										case 2:{   /*In case 2 it show's yesterday's details*/
											       YesterdayDetails(w);
											       break;
										       }
										case 3:{   /*In case 3 it show's lastweek details*/
											       LastWeekDetails(w);
											       break;
										       }
										case 4:{   /*In case 4 it show's last month details*/
											       LastMonthDetails(w);
											       break;
										       }
										case 5:{  /*In case 5 it show's place details*/
											       PlaceDetails(w);
											       break;
										       }
									}
									break;	     /*breaks the loop if password entered is correct*/     
								}
								count++;	 /*count is incremented*/
							}
							printf("Do you want to go with other options (Y/N): ");
							scanf(" %c",&v);        /*If user wants to know more than 1 cases he types y*/
						}while(v=='Y' || v=='y');
					} 

				}  
			}
			if(flag==0){    /*If flag is 0 user entered invalid username*/
				printf("Please enter the valid user name\n");
			}
			break;
		case 2:              /*Case 2 is to register new account if doesnot exists*/
			do{
				if ( ( fp=fopen("user.txt", "a+")) == NULL) { /*Checks whether file is empty or not*/
					if ( ( fp=fopen("user.txt", "w+")) == NULL) {
						printf ("Could not open file\n");
						exit ( 1);
					}
				}
				printf("Enter Username: ");     /*Username is entered*/
				scanf("%9s",pUser->username);
				printf("Choose A Password: ");  /*Password is entered*/
				scanf("%9s",pUser->password);
				fwrite (pUser, sizeof(struct user), 1, fp);
				printf("Add another account? (Y/N): ");
				scanf(" %c",&c);     /*skip leading whitespace*/
			}while(c=='Y'||c=='y');
			break;
	}
	free (pUser);/*free allocated memory*/
	fclose(fp);   /*closing file*/
}
/*Function to admin login*/
void adminlogin(){
	FILE *fp;
	int count=0,input,i,n,flag;             /*Declaring required variables*/
	char sort,cap;
	char uName[10], pwd[10];char c,v;
	WEATHER *w;                             /*Declaring w in weather structure*/
	pAdmin=(struct admin *)malloc(sizeof(struct admin));/*Allocating memory for padmin*/
	FILE *fp1=fopen("ram1.txt","a+");       /*opening the file in append+ mode*/
	printf("Welcome back admin! Login Through Your Account\n");
	if ( ( fp=fopen("admin.txt", "r+")) == NULL) {  /*condition to check if file doesnot exist*/
		if ( ( fp=fopen("admin.txt", "w+")) == NULL) {
			printf ("Could not open file\n");
			exit (1);
		}
	}
	flag=0;
	printf("Username: ");   /*entering username*/
	scanf("%9s",uName); 
	printf("Password: ");   /*entering password*/
 	scanf("%9s",pwd);
	while ( fread (pAdmin, sizeof(struct admin), 1, fp) >= 1) {  /*condition to check adminaccount exists or not*/
		if( strcmp ( pAdmin->ausername, uName) == 0) {
			flag=1;                 /*flag is 1 if adminaccount exists*/
			if( strcmp ( pAdmin->apassword, pwd) == 0) { /*if password is correct or not*/
				flag=1;
				printf("Logged in Successfully\n");
				do{
					printf("1. Add Data\n");
					printf("2.Sorting\n");
					printf("3.Modify Data\n");
					printf("4.Show data\n");
					scanf("%d",&input);    /*input to select swith case*/
					switch(input){         /*switch case*/
						case 1:{ /*In case 1 it generates weather details*/
							       w=genweatherDetails(fp1); /*weather details are generated from file*/
							       print(w);        /*print weather details*/
							       break;
						       }
						case 2:{ /*In case 2 weather details are sorted*/
							       w=genWeather(fp1);    /*weather details are generated*/
							       print(w);             /*print weather details*/
							       if(w!=NULL){
								       scanf("%c",&sort);
								       printf("a.Sorting based on Temperature\n");
								       printf("b.Sorting based on Humidity\n");
								       printf("c.Sorting based on CO2 content\n");
								       printf("d.Sorting based on SmokeDensity\n");
								       printf("e.Sorting based on Dates\n");
								       scanf("%c",&sort);/*input to select swith case*/
								       switch(sort){
									       case 'a':{ /*In case a sorting is based on temperature*/
												printf("\nThe data after sorting based on Temperature:\n\n");
												TemperatureSort(w);
												break;
											}
									       case 'b':{ /*In case b sorting is based on humidity*/
												printf("\nThe data after sorting based on Humidity:\n\n");
												HumiditySort(w);
												break;
											}
									       case 'c':{ /*In case c sorting is based on CO2_level*/
												printf("\nThe data after sorting based on CO2 content in air:\n\n");
												CO2Sort(w);
												break;
											}
									       case 'd':{ /*In case d sorting is based on smoke_density*/
												printf("\nThe data after sorting based on Smoke Density:\n\n");
												DensitySort(w);
												break;
											}
									       case 'e':{ /*In case e sorting is based on dates*/
												printf("\nThe data after sorting based on Dates:\n\n");
												sortdates(w);
												break;
											}
								       }
							       }
							       else{   /*If file is empty*/
								       printf("Please Add the data\n");
							       }
							       break;
						       }
						case 3:{       /*In case 3 weather details are sorted*/
							       int j=0;            /*Declaring required variable*/
							       w=genWeather(fp1);  /*weather details are generated*/
							       FILE *fp2=fopen("ram1.txt","w");
							       printf("How many entries do you want to enter:\n");
							       scanf("%d",&n);/*input for number of entries to change*/
							       while(j<n){    /*while loop to run for n entries*/
								       scanf("%c",&cap);
								       printf("A.To modify Temperature\n");
								       printf("B.To modify Humidity\n");
								       printf("C.To modify SmokeDensity\n");
								       printf("D.To modify CO2 content\n");
								       scanf("%c",&cap);/*input to select swith case*/
								       switch(cap){     /*switch case*/
									       case 'A':{ /*In case A temperature is modified*/
												Temperaturemodify(w);
												print(w);/*print weather details*/
												break;
											}
									       case 'B':{ /*In case B humidity is modified*/
												Humiditymodify(w);
												print(w);/*print weather details*/
												break;
											}
									       case 'C':{ /*In case C smokedensity is modified*/
												SmokeDensitymodify(w);
												print(w);/*print weather details*/
												break;
											}
									       case 'D':{ /*In case D CO2_level is modified*/
												CO2levelmodify(w);
												print(w);/*print weather details*/
												break;
											}		          
								       }
								       j++;  /*j is incremented*/
							       }
							       while(w!=NULL){ /*printing the weather details in a file*/
								       fprintf(fp2,"%s,%s,%s,%.2f,%d,%d,%d,%d,%s,%d,", w->place,w->lat ,w->lon,w->tempin_cel,w->humidity,w->CO2_level,w->sm_density,w->D.date,w->D.month,w->D.year);
								       fprintf(fp2,"\n");
								       w=w->next;
							       }				break;
						       }
						case 4:{       /*In case 4 weather details are shown*/
							       int var;            /*declaring required variables*/
							       int j=0;
							       w=genWeather(fp1);  /*weather details are generated*/
							       printf("1.Show today's details:\n");
							       printf("2.Show yesterdays's details:\n");
							       printf("3.Show details of last week:\n");
							       printf("4.Show details of last month:\n");
							       printf("5.Place details:\n");
							       scanf("%d",&var);   /*input to select swith case*/
							       switch(var){        /*switch case*/
								       case 1:{  /*In case 1 today's details are shown*/
										      TodayDetails(w);
										      break;
									      }
								       case 2:{  /*In case 2 it show's yesterday's details*/
										      YesterdayDetails(w);
										      break;
									      }
								       case 3:{  /*In case 3 it show's lastweek details*/
										      LastWeekDetails(w);
										      break;
									      }
								       case 4:
									      {  /*In case 4 it show's last month details*/
										      LastMonthDetails(w);
										      break;
									      }
								       case 5:{   /*In case 5 it show's place details*/
										      PlaceDetails(w);
										      break;
									      }
							       }
							       break;	          
						       }
					}
					printf("Do you want to go with other options(Y/N): ");
					scanf(" %c",&v); /*If admin wants to know more than 1 cases he types y*/
				}while(v=='Y' || v=='y');
			}	     
			else{   /*If password is wrong user gets 3 chances to type correct password*/
				while(count<3){ 
					printf("Try again\n");
					printf("Password: ");           /*reentering password*/
					scanf("%9s",pwd);
					if(strcmp ( pAdmin->apassword, pwd) == 0){       
						count=4;
						flag=1;
						printf("Logged in Successfully\n");
						do{
							printf("1. Add Data\n");
							printf("2.Sorting\n");
							printf("3.Modify Data\n");
							printf("4.Show data\n");
							scanf("%d",&input);  /*input to select swith case*/
							switch(input){       /*switch case*/
								case 1: {      /*In case 1 it generates weather details*/
										w=genweatherDetails(fp1);/*weather details are generated*/
										print(w);               /*print weather details*/
										break;
									}
								case 2:{       /*In case 2 weather details are sorted*/
									       w=genWeather(fp1); /*weather details are generated*/
									       print(w);          /*print weather details*/
									       if(w!=NULL){
										       scanf("%c",&sort);
										       printf("a.Sorting based on Temperature\n");
										       printf("b.Sorting based on Humidity\n");
										       printf("c.Sorting based on CO2 content\n");
										       printf("d.Sorting based on SmokeDensity\n");
										       printf("e.Sorting based on Dates\n");
										       scanf("%c",&sort);/*input to select swith case*/
										       switch(sort){
											       case 'a':{/*In case a sorting is based on temperature*/
														printf("\nThe data after sorting based on Temperature:\n\n");
														TemperatureSort(w);
														break;
													}
											       case 'b':{/*In case b sorting is based on humidity*/
														printf("\nThe data after sorting based on Humidity:\n\n");
														HumiditySort(w);
														break;
													}
											       case 'c':{/*In case c sorting is based on CO2_level*/
														printf("\nThe data after sorting based on CO2 content in air:\n\n");
														CO2Sort(w);
														break;
													}
											       case 'd':{/*In case d sorting is based on smoke_density*/
														printf("\nThe data after sorting based on Smoke Density:\n\n");
														DensitySort(w);
														break;
													}
											       case 'e':{/*In case e sorting is based on dates*/
														printf("\nThe data after sorting based on Dates:\n\n");
														sortdates(w);
														break;
													}
										       }
									       }
									       else{ /*If file is empty*/
										       printf("Please Add the data\n");
									       }
									       break;
								       }
								case 3:{       /*In case 3 weather details are sorted*/
									       int j=0;  /*declaring required variable*/
									       w=genWeather(fp1);/*weather details are generated*/
									       FILE *fp2=fopen("ram1.txt","w");
									       printf("How many entries do you want to enter:");
									       scanf("%d",&n); /*input for number of entries to change*/
									       while(j<n){   /*while loop to run for n entries*/
										       scanf("%c",&cap);
										       printf("A.To modify Temperature\n");
										       printf("B.To modify Humidity\n");
										       printf("C.To modify SmokeDensity\n");
										       printf("D.To modify CO2 content\n");
										       scanf("%c",&cap);/*input to select swith case*/
										       switch(cap){
											       case 'A':{ /*In case A temperature is modified*/
														Temperaturemodify(w);
														print(w);/*print weather details*/
														break;
													}
											       case 'B':{ /*In case B humidity is modified*/
														Humiditymodify(w);
														print(w);/*print weather details*/
														break;
													}
											       case 'C':{ /*In case C smokedensity is modified*/
														SmokeDensitymodify(w);
														print(w);/*print weather details*/
														break;
													}
											       case 'D':{ /*In case D CO2_level is modified*/
														CO2levelmodify(w);
														print(w);/*print weather details*/			                    
														break;
													}                    
										       }
										       j++; /*j is incremented*/
									       }
									       while(w!=NULL){ /*printing the weather details in a file*/
										       fprintf(fp2,"%s,%s,%s,%.2f,%d,%d,%d,%d,%s,%d", w->place,w->lat ,w->lon,w->tempin_cel,w->humidity,w->CO2_level,w->sm_density,w->D.date,w->D.month,w->D.year);
										       fprintf(fp2,"\n");
										       w=w->next;
									       }
									       fclose(fp2); /*closing the file*/    
									       break;
								       }
								case 4:{       /*In case 4 weather details are shown*/
									       int var;  /*Declaring required variables*/
									       int j=0;
									       w=genWeather(fp1);/*weather details are generated*/
									       printf("1.Show today's details:\n");
									       printf("2.Show yesterdays's details:\n");
									       printf("3.Show details of last week:\n");
									       printf("4.Show details of last month:\n");
									       printf("5.Place details:\n");
									       scanf("%d",&var);/*input to select swith case*/
									       switch(var){     /*switch case*/
										       case 1:{ /*In case 1 today's details are shown*/
												      TodayDetails(w);
												      break;
											      }
										       case 2:{ /*In case 2 it show's yesterday's details*/
												      YesterdayDetails(w);
												      break;
											      }
										       case 3:{  /*In case 3 it show's lastweek details*/
												      LastWeekDetails(w);
												      break;
											      }
										       case 4:{  /*In case 4 it show's last month details*/
												      LastMonthDetails(w);
												      break;
											      }
										       case 5:{  /*In case 5 it show's place details*/
												      PlaceDetails(w);
												      break;
											      }
									       }
									       break;	/*breaks the loop if password entered is correct*/          
								       }		
							}
							printf("Do you want to see more details(Y/N): ");
							scanf(" %c",&v); /*If admin wants to know more than 1 cases he types y*/
						}while(v=='Y' || v=='y');
					}
					count++;           /*count is incremented*/         
				}
			}
		}
	}
	if(flag==0){ /*If flag is 0 user entered invalid adminname*/
		printf("Please enter a valid Admin name\n");
	}	    
	free ( pAdmin);/*free allocated memory*/
	fclose(fp1);   /*Closing the file*/
}
/*Main Function*/
int main(int argc, char *argv[]){
	int i;                          /*Declaring required variable*/
	printf("1.Login through admin account\n");
	printf("2.Login through user account\n");
	scanf("%d",&i);                 /*input to select swith case*/
	switch(i){                      /*switch case*/
		case 1:
			adminlogin();     /*Calling the function admin login*/
			break;
		case 2:
			userlogin();     /*Calling the function user login*/
			break;
	}	
	return 0;
}  
