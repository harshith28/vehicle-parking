/* Vehicle parking program */

#include <stdio.h>
#include <string.h>
#include<stdlib.h>
#define CAR 1
#define BIKE 2
#define BUS 3
int h1,m1,t,f,i,number;
int ar[10000];
    
	
/* to store vehicle number, and its
   row-col position in an array */
   
struct vehicle /*vehicle contains slot , its number , type, hours, minutes and the parking cash for regular user*/
{
  int num ;
  int row ;
  int col ;
  int type ;
  int hours;
  int minutes;
  int pc;
} ;

void generatingticket();

int parkarray[9][10] ;  /* a 2-D array to store number of vehicle parked */
int vcount ;  /* to store total count of vehicles */
void displayslots( ) ;
struct vehicle * add ( int, int, int, int ) ;
void rowcolpark ( int, int * ) ;
void rowcolnum ( int, int, int * ) ;
void delete();
int generatingprice(struct vehicle*v,int,int,int,int);
int login();
	
/* adds a data of vehicle */
struct vehicle * add ( int t, int num, int row, int col )
{
    struct vehicle *v ;

    v = ( struct vehicle * ) malloc ( sizeof ( struct vehicle ) ) ;

    v -> type = t ;
    v -> row = row ;
    v -> col = col ;
    //v->hours=hours;
    //v->minutes=minutes;
    vcount++ ;
	  parkarray[row][col] = num ;

    return v ;
}

    
void delete( struct vehicle *v )
{
 

	parkarray[v -> row][v -> col] = 0 ;


	vcount-- ;
}
/* get the row-col position for the vehicle to be parked */
void rowcolpark ( int type, int *arrstore )
{
  int r, c, startrow = 0, endrow = 3 ;

  if ( type == BIKE )
  {
    startrow += 3 ;
    endrow += 3 ;
  }
  if ( type == BUS )
  {
    startrow += 6 ;
    endrow += 6 ;
  }
  

	for ( r = startrow ; r < endrow ; r++ )
	{
		for ( c = 0 ; c < 10 ; c++ )
		{
			if ( parkarray[r][c] == 0 )
			{
				arrstore[0] = r ;
				arrstore[1] = c ;
        return ;
			}
		}
	}

	if ( r == 3 || r == 6 || r==9 )
	{
   	arrstore[0] = -1 ;
    arrstore[1] = -1 ;
  }
}

/* get the row-col position for the vehicle with specified number */
void rowcolnum ( int type, int num, int *arrstore )
{
  int r, c, startrow = 0, endrow = 3 ;

  if ( type == BIKE )
  {
    startrow += 3 ;
    endrow += 3 ;
  }
  if ( type == BUS )
  {
    startrow += 6 ;
    endrow += 6 ;
  }
  

	for ( r = startrow ; r < endrow ; r++ )
	{
		for ( c = 0 ; c < 10 ; c++ )
		{
			if ( parkarray[r][c] == num )
			{
				arrstore[0] = r ;
				arrstore[1] = c ;
        return ;
			}
		}
	}

	if ( r == 3 || r == 6 || r==9 )
	{
		arrstore[0] = -1 ;
		arrstore[1] = -1 ;
	}

}

/* displays list of vehicles parked */
void displayslots( )
{
  int r, c ;

  printf ( "Cars ->\n" ) ;

  for ( r = 0 ; r < 9 ; r++ )
  {
    if ( r == 3 )
		  printf ( "bikes ->\n" ) ;
    if ( r == 6 )
		  printf ( "buses ->\n" ) ;
		  

    for ( c = 0 ; c < 10 ; c++ )
      printf ( "%d\t", parkarray[r][c] ) ;
       
   
    printf ( "\n" ) ;
    
	}
	
}
/* To generate ticket*/
void generatingticket(struct vehicle *v){
    char a[100];
    printf("\nEnter driver's name\n");
    scanf("%s",a);
    while(1)
    {
    printf("\nEnter time of arrival hh and mm\n");
    scanf("%d%d",&(v->hours),&(v->minutes));
    if((v->hours<=23&&v->hours>=0)&&(v->minutes<=59&&v->minutes>=0))
    {
    printf("\t*****TICKET GENERATION*******\n");
    printf("Driver name : "); 
    for(int i=0;i<strlen(a);i++)
    printf("%c",a[i]);
    printf("\n");
    printf("Entry time = %d:%d\n",v->hours,v->minutes);
    break;
    }
    else{
        printf("\nInvalid Entry time");
    }
  }
}
/*Generating price*/
int generatingprice(struct vehicle*v,int h1,int m1,int t,int type)
{
    int nh,nm;
  
    //printf("*****%d*****",v->hours);
  if(v->hours>h1)
  {
      h1=h1+24;
      }
  if(v->minutes>m1)
  {
      m1=m1+60;
      v->hours++;
  }
   nh=h1-v->hours;
   nm=m1-v->minutes;
   printf("Enter the type of user that is departured 1 for new user , 2 for regular\n");
   scanf("%d",&t);
   printf("\t*******Generating Price*******\n");
   printf("Number of hours parked = %d : %d\n",nh,nm);
   if(t==1)
   {
       printf("New user\n");
       if(type==CAR){
           printf("Amount to be paid = %d",(nh*30)+(nm*30/60));
          
       }
       else if(type==BIKE){
           printf("Amount to be paid = %d",(nh*20)+(nm*20/60));
       }
       else{
           printf("Amount to be paid = %d",(nh*40)+(nm*40/60));
       }
   }
   if(t==2)
   {
       printf("Regular user \n");
       //int nc,nbi,nbu;
       if(type==CAR){
       
           printf("Amount to be paid = %d",(nh*20)+(nm*20/60));
           //printf("%d",v->pc);
           printf("\n Your current parking cash after Departure is %d \n",v->pc-(nh*20)+(nm*20/60));
           v->pc=v->pc-(nh*20)+(nm*20/60);
           if(v->pc<=0)
           {
               printf("\nplease pay the remaning amount of %d\n",-(v->pc));
               v->pc=0;
           }
           
       }
       else if(type==BIKE)
       {
           printf("Amount to be paid = %d",(nh*10)+(nm*10/60));
           printf("\n Your current parking cash after Departure is %d \n",v->pc-(nh*10)+(nm*10/60));
           v->pc=v->pc-(nh*10)+(nm*10/60);
           if(v->pc<=0)
           {
               printf("\nplease pay the remaning amount of %d\n",-(v->pc));
               v->pc=0;
           }
       }
       else{
           printf("Amount to be paid = %d",(nh*30)+(nm*30/60));
           printf("\n Your current parking cash after Departure is %d \n",v->pc-(nh*30)+(nm*30/60));
           v->pc=v->pc-(nh*30)+(nm*30/60);
           if(v->pc<=0)
           {
               printf("\nplease pay the remaning amount of %d\n",-(v->pc));
               v->pc=0;
           }
       }
   }
 return v->pc;     
}
int login()
{
    int i, found = 0;
    int a=2,b=3;

    char check_names[5][20] = {
                                  "vivek",
                                  "harshith",
                                  "pspk",
                                  "admin",
                                  "user"
                              }, name[10];
    int pin[5]={1234,5656,2345,3456,4567};
    int pass;
    printf("Enter username: ");
    scanf("%s",name);
    printf("Enter password: ");
    scanf("%d",&pass);
    for(i = 0; i < 5; i++)
    {
        if(strcmp(name, check_names[i]) == 0 && pin[i]==pass )
        {
            found = 1;
            break;
        }
    }
   f=found;
}

int main( )
{
	int choice, type, row = 0, col = 0,hours,minutes,j ;
    int toarr[2] ;
	//int finish = 1 ;
	for (i=0;i<100;i++)
	ar[i]=0;
	struct vehicle *s;

	/* creates a 2-D array of car, bike and bus class */
	struct vehicle *car[3][10] ;
	struct vehicle *bike[3][10] ;
	struct vehicle *bus[3][10] ;
	printf("\t\t********************************************************\n");
	printf("\t\t* **************************************************** *\n");
	printf("\t\t* *                                                  * *\n");
	printf("\t\t* *     =====================================        * *\n");
	printf("\t\t* *     WELCOME TO VEHICLE PARKING MANAGEMENT        * *\n");
	printf("\t\t* *     =====================================        * *\n");
	printf("\t\t* *                                                  * *\n");
	printf("\t\t* *     BROUGHT TO YOU BY HARSHITH AND VIVEK         * *\n");
	printf("\t\t* *                                                  * *\n");
	printf("\t\t* *                                                  * *\n");
	printf("\t\t* *       VASAVI COLLEGE OF ENGINEERING              * *\n");
	printf("\t\t* *                                                  * *\n");
	printf("\t\t* **************************************************** *\n");
	printf("\t\t********************************************************\n");
	printf("\t\t                  \n");
	/* displays menu and calls corresponding functions */
	while ( 1 )
	{
		printf ( "\t\t\t\tVehicle Parking\n" ) ;
		printf("\t\t                  \n");
		printf ( "\t\t1. Arrival of a vehicle and generating its ticket\n" ) ;
		printf ( "\t\t2. Total no. of vehicles parked\n" ) ;
		printf ( "\t\t3. Display slot availability of each type of vehicle\n" ) ;
		printf ( "\t\t4. Departure of the vehicle and generating price \n" ) ;
		printf ( "\t\t5. Exit\n" ) ;
		scanf ( "%d", &choice ) ;

		switch ( choice )
		{
			case 1 :
				  printf ( "\nAdd: \n" ) ;
				  printf("enter 1 for new user and 2 for regular user\n");
                  scanf("%d",&t);
				  if(t==1){
				  
          type = 0 ;

          /* check for vehicle type */
          while ( type != CAR && type != BIKE && type != BUS )
          {
					  printf ( "Enter vehicle type (1 for Car , 2 for Bike , 3 for Bus ): \n" ) ;
            scanf ( "%d", &type ) ;
	          if ( type != CAR && type != BIKE && type != BUS )
						  printf ( "\nInvalid vehicle type.\n" ) ;
          }
                printf ( "Enter vehicle number: " ) ;
				  scanf ( "%d", &number ) ;
                  while(number>=10000){
                      printf("invalid number enter a number which is less than 5 digits\n");
                       printf ( "Enter vehicle number: " ) ;
				  scanf ( "%d", &number ) ;
                  }
				  if ( type == CAR || type == BIKE || type == BUS )
				  {
					  rowcolpark ( type, toarr ) ;

					  if ( toarr[0] != -1 && toarr[1] != -1 )
					  {
						  row = toarr[0] ;
						  col = toarr[1] ;
             
              if ( type == CAR )
              {
                car[row][col] =  add ( type, number, row, col) ;
            
                s= &car[row][col];
                printf("car parked successfully");
                  
              }                 
              else if( type == BIKE)
              {
				bike[row - 3][col] = add ( type, number, row, col ) ;
				 s= &bike[row-3][col];
				 printf("bike parked successfully");
                  
              }  
			  else{
			    bus[row - 6][col] = add( type, number, row, col  );
			    s= &bus[row - 6][col];
				 printf("bus parked successfully");
			  }  
            }
					  else
            {
              if ( type == CAR )
              {
               for(i=0;i<3;i++)
               {
                   for(j=0;j<10;j++)
                   {
                       if(car[i][j]->num==0)
                       {
                           car[i][j] =  add ( type, number, row, col) ;
                            s= &car[i][j];
                       }
                   }
               }
               if(i==2&&j==9)
                printf ( "\nNo parking slot free to park a car\n" ) ;
              }
              else if( type == BIKE)
              {
               for(i=0;i<3;i++)
               {
                   for(j=0;j<10;j++)
                   {
                       if(bike[i][j]->num==0)
                       {
                           bike[i][j] =  add ( type, number, row, col) ;
                            s= &bike[i][j];
                       }
                   }
               }
               if(i==2&&j==9)
                printf ( "\nNo parking slot free to park a bike\n" ) ;
              }
              else
              {
               for(i=0;i<3;i++)
               {
                   for(j=0;j<10;j++)
                   {
                       if(bus[i][j]->num==0)
                       {
                           bus[i][j] =  add ( type, number, row, col) ;
                            s= &bus[i][j];
                       }
                   }
               }
               if(i==2&&j==9)
                printf ( "\nNo parking slot free to park a bus\n" ) ;
              }
            }
          }
				  else
				  {
            printf ( "Invalid type\n" ) ;
				      }
				  generatingticket(s);
			 printf("Vehicle type(1 is car, 2 is bike, 3 is bus) is %d\n",type);
            printf("Vehicle number : %d\n",number);
				      printf("\n\n");
				  }
          
          
          if(t==2){
              login();
             //printf("Your current parking cash amount  : %d\n",pc);
          
              if(f==1)
              {
           type = 0 ;
           
          /* check for vehicle type */
          
          while ( type != CAR && type != BIKE && type != BUS )
          {
			printf ( "Enter vehicle type (1 for Car , 2 for Bike , 3 for Bus ): \n" ) ;
            scanf ( "%d", &type ) ;
	          if ( type != CAR && type != BIKE && type != BUS )
			  printf ( "\nInvalid vehicle type.\n" ) ;
          }
                  
				  printf ( "Enter vehicle number: " ) ;
				  scanf ( "%d", &number ) ;
                  while(number>=10000)
                  {
                      printf("invalid number enter a number which is less than 5 digits\n");
                       printf ( "Enter vehicle number: " ) ;
				  scanf ( "%d", &number ) ;
                  }
				  if ( type == CAR || type == BIKE || type == BUS )
				  {
					  rowcolpark ( type, toarr ) ;

					  if ( toarr[0] != -1 && toarr[1] != -1 )
					  {
						  row = toarr[0] ;
						  col = toarr[1] ;

              if ( type == CAR )
              {
                car[row][col] =  add ( type, number, row, col) ;
                s= &car[row][col];
                printf("car parked successfully");
                  
              }                 
              else if( type == BIKE)
              {
				bike[row - 3][col] = add ( type, number, row, col ) ;
				s= &bike[row-3][col];
				 printf("bike parked successfully");
              }  
			  else
			  {
			    bus[row - 6][col] = add( type, number, row, col );
			    s= &bus[row-6][col];
				 printf("bus parked successfully");}  
            }
			 else
            {
              if ( type == CAR )
              {
               for(i=0;i<3;i++)
               {
                   for(j=0;j<10;j++)
                   {
                       if(car[i][j]->num==0)
                       {
                           car[i][j] =  add ( type, number, row, col) ;
                            s= &car[i][j];
                       }
                   }
               }
               if(i==2&&j==9)
                printf ( "\nNo parking slot free to park a car\n" ) ;
              }
              else if( type == BIKE)
              {
               for(i=0;i<3;i++)
               {
                   for(j=0;j<10;j++)
                   {
                       if(bike[i][j]->num==0)
                       {
                           bike[i][j] =  add ( type, number, row, col) ;
                            s= &bike[i][j];
                       }
                   }
               }
               if(i==2&&j==9)
                printf ( "\nNo parking slot free to park a bike\n" ) ;
              }
              else
              {
               for(i=0;i<3;i++)
               {
                   for(j=0;j<10;j++)
                   {
                       if(bus[i][j]->num==0)
                       {
                           bus[i][j] =  add ( type, number, row, col) ;
                            s= &bus[i][j];
                       }
                   }
               }
               if(i==2&&j==9)
                printf ( "\nNo parking slot free to park a bus\n" ) ;
              }
            }
          }
				  else
				  {
            printf ( "Invalid type\n" ) ;
					  
          }
          
          if(ar[number]==0)
          {
              printf("\nenter the amount to be deposited\n");
          scanf("%d",&s->pc);
            ar[number]=s->pc;
              
          }
            else
            {
           s->pc=ar[number];
           printf("\nYou are a regular user and your parking cash after the past transaction is %d\n",ar[number]);
            }
            
        //printf("%d",ar[number]);
          
        
                generatingticket(s);
             printf("Vehicle type(1 is car, 2 is bike, 3 is bus) is %d\n",type);
            printf("Vehicle number : %d\n",number);
            printf("Your current parking cash amount is %d\n",ar[number]);
            printf("\n\n");
		}
		else{
		    printf("Invalid user name or password\n");
		}
          }
          

				  break ;

      case 2 :
				  printf ( "Total vehicles parked: %d\n", vcount ) ;
				  printf("\n\n");
         
				  break ;

			case 3 :
				  printf ( "Display\n" ) ;
				  displayslots( ) ;
				   printf("\n\n");
         
				  break ;
			case 4 :
				  printf ( "Departure\n" ) ;
          type = 0 ;
          /* check for vehicle type */
          while ( type != CAR && type != BIKE && type!= BUS )
          {
					  printf ( "Enter vehicle type (1 for Car ,2 for bike , 3 for bus ): \n" ) ;
            scanf ( "%d", &type ) ;
	          if ( type != CAR && type != BIKE && type!= BUS )
						  printf ( "\nInvalid vehicle type.\n" ) ;
          }
				  printf ( "Enter number: "  ) ;
				  scanf ( "%d", &number ) ;
                 printf("Enter exit time\n");
                 scanf("%d%d",&h1,&m1);
                 
                 
  				if ( type == CAR || type == BIKE || type== BUS )
	  			{
		  			rowcolnum ( type, number, toarr ) ;
		  			//printf("%d %d",toarr[0],toarr[1]);
			  		if ( toarr[0] != -1 && toarr[1] != -1 )
				  	{
              col = toarr [1] ;
              /* if the vehicle is car */
              if ( type == CAR )
              {
                row = toarr [0] ;
                
                ar[number]=	generatingprice(&car[row][col], h1, m1, t, type); 
                
                //	printf("departure ar value %d",ar[number]);
	              delete ( car [row][col] ) ;
	              printf("\ncar with number %d has just departured\n",number);
	               printf("\n\n");
				    		  
              }
						  /* if a vehicle is scooter */
						  else if( type == BIKE)
              {
                row = toarr[0] - 3 ;
							  if ( ! ( row < 0 ) )
							  {
							    ar[number]=  generatingprice(&bike[row][col], h1, m1, t, type);
								  delete ( bike [row][col] ) ;
							  printf("\nbike with number %d has just departured\n",number);
							   printf("\n\n");
							    
                }
              }
              else{
                   row = toarr[0] - 6 ;
							  if ( ! ( row < 0 ) )
							  {
							      ar[number]=generatingprice(&bus[row][col], h1, m1, t, type);
							      
								  delete ( bus [row][col] ) ;
								 printf("\nbus with number %d has just departured\n",number); 
								  printf("\n\n");
								    
                }
              }
            }
					  else
            {
              if ( type == CAR )
				  printf ( "The car number which you have enterd is not there in the parking lot.\n" ) ;
              else if( type == BIKE)
                printf ( "The bike number which you have enterd is not there in the parking lot.\n" ) ;
                else
                printf ( "The bus number which you have enterd is not there in the parking lot.\n" ) ;
                 
            }
          }
             //generatingprice(h, m, h1, m1, t, type);       
                  
         
				  break ;	  

			case 5 :
              return 0;
		 	  break ;
		 	  
		 	 default : printf("You have entered a wrong choice!!\n");
    }
}
  return 0 ;
}