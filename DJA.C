#include <stdio.h>
#include <stdlib.h>
#define MAX 20

int adj[MAX][MAX];
int W[MAX];
double Rij[MAX][MAX];
double Tij[50][50];
double Nij[MAX][MAX];
double Pij[MAX][MAX];

int n,s;
double alpha,beta,rho;

struct scenario
{
	int data;
	struct scenario *next;
};
struct scenario *sce[MAX];


float random_val(int i,int j)
{
    float f;//=(float)(rand()%100) * .01;
			 printf("Enter value of %d,%d for reliability: ",i,j);
			 scanf("%f",&f);

    return f;
}

void create_graph()
{
    int i,max_edges,origin,destin,fer;

    printf("Enter initial amount of pheromone: ");
    scanf("%f",fer);
    printf("Enter number of nodes : ");
    scanf("%d",&n);

    max_edges=n*(n-1);

    for(i=1;i<=max_edges;i++)
    {
	printf("Enter edge %d( 0 0 to quit ) : ",i);
	scanf("%d %d",&origin,&destin);

	if((origin==0) && (destin==0))
	    break;

	if( origin > n || destin > n || origin<=0 || destin<=0)
	{
	    printf("Invalid edge!\n");
	    i--;
	}
	else
	{
	    adj[origin][destin]=1;
	    Rij[origin][destin]=random_val(origin,destin);
	    Tij[origin][destin]=fer;
	    Nij[origin][destin]=1-(Rij[origin][destin]);

	}
    }

}

void input_scenarios()
{
      //	int src,dest,flag=0;
	int d;
	struct scenario *p,*q;
	int src,dest,nn,i,x;
	int temp_dest=0,flag;

	s=0;
	while(1)
	{       temp_dest=0;
		printf("\n\nEnter new scenario? \n1-Yes 2-No:  ");
		scanf("%d",&d);
		if(d==2)
			break;

		printf("Enter a source node from 1 to %d: ",n);
		scanf("%d",&src);

		printf("Enter a destination node from 1 to %d: ",n);
		scanf("%d",&dest);

		if(src>n && dest>n && src<1 && dest<1)
		{    	printf("Invalid node!\n");

		}
		else
		{
			p=malloc(sizeof(struct scenario));
			p->data=src;
			p->next=NULL;
			sce[s]=p;
		}


		while(dest!=temp_dest)
		{       flag=0;
			for(i=1;i<=n;i++)
			{
				x=p->data;
				if (adj[x][i]==1)
				{
					printf("%d,",i);
					flag=1;
				}

			}
			if (flag==0)
			{
				printf("\nNo next node available. ");
				if(temp_dest!=dest)
					break;
			}
			else
			{
				printf("0\nSelect next node from above: ");
				scanf("%d",&nn);
				temp_dest=nn;

				p=malloc(sizeof(struct scenario));
				p->data=temp_dest;
				p->next=NULL;

				//traverse until reached to end
				q=sce[s];
				while(q->next!=NULL)
				{
					q=q->next;
				}
				printf("%d",q->next);
				q->next=p;

			}
		}

		if (temp_dest==dest)
		{	printf("Scenario Complete!\n");

			//display scenario
			q=sce[s];

			while(q->next!=NULL)
			{
				printf("%d -> ",q->data);
				q=q->next;
			}
			printf("%d",q->data);

			s++; //scenario only increments if done.

		}
		else
		{
			printf("Scenario failed! Try again.");
		}
	}
}


void update_TP()
{
	int i,j,l;
	double temp1,temp2,temp3,tij,nij;
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
		{
			if (adj[i][j]==1)
			{
				tij=Tij[i][j];
				nij=Nij[i][j];
				temp1= (tij)*(nij);//*(pow(nij,beta));

				temp2=0;
				for(l=1;l<=n;l++)
				{
					if (adj[i][l]==1)
					{
						temp2 += (Tij[i][l])*(Nij[i][l]);
					}
				}

				temp3=temp1/temp2;

				Pij[i][j]=(float) temp3;
			}
		}
	}
}

void display_adj()
{
    int i,j;
    for(i=1;i<=n;i++)
    {
	for(j=1;j<=n;j++)
	    printf("%4d",adj[i][j]);
	printf("\n");
    }
}

void display_Rij()
{       int i,j;
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
		{
			printf("%.2f ",Rij[i][j] );
		}
		printf("\n");
	}
}

void display_Tij()
{       int i,j;
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
		{
			printf("%.2f ",Tij[i][j] );
		}
		printf("\n");
	}
}

void display_Nij()
{       int i,j;
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
		{
			printf("%.2f ",Nij[i][j] );
		}
		printf("\n");
	}
}

void display_Pij()
{       int i,j;
	for(i=1;i<=n;i++)
	{
		for(j=1;j<=n;j++)
		{
			printf("%.4f ",Pij[i][j] );
		}
		printf("\n");
	}
}

void assign_weight()
{
	int i;
    for(i=1;i<=n;i++)
    {
	W[i]=rand()%10;
    }

}

int main()
{
    int i,v,choice;
    float data[MAX];
    struct scenario *p,*q;
    int final_data;
    int final_path;
    int former,latter;
    clrscr();
  //  alpha=beta=rho=0.5;

    create_graph();
    input_scenarios();
    assign_weight(); //to each node

    printf("\nAdjacency matrix:\n------------------\n");
    display_adj();

    printf("\n\nReliability of Path:\n------------------\n");
    display_Rij();

    printf("\n\nPheromone Amount:\n------------------\n");
    display_Tij();

    printf("\n\nHeuristic Information:\n------------------\n");
    display_Nij();

    update_TP();
    printf("\nUpdating Transition Probability with alpha=beta=0.5 ...\nTransition Probability:\n-------------\n");
    display_Pij();


    for(i=0;i<s;i++)
    {
	printf("\nCalculating probability of scenario %d...",i+1);//for each scenario
	q=p=sce[i];

	while(p->next!=NULL)
	{
	       //	former=p->data;
	    //	printf("%d->",p->data,);
		former=p->data;
		p=p->next;
		latter=p->data;
		data[i] +=Pij[former][latter]+Rij[former][latter];
		printf("\n\n Adding for nodes: %d->%d,\n%f+%f",former,latter,Pij[former][latter],Rij[former][latter]);

	       //	latter=p->data;
	     //	printf("\n%f-latter",p->data);

	}
	printf("Sum of probability=%f",data[i]);

      //	printf("%d",p->data);

     //		if(W[former]<W[latter])
       //		{
		//	data[i]= data[i] + ((Tij[former][latter])+Rij[former][latter]);

	 //	}
	   //	else
	    //	{
	       //		data[i]+=(0.5*Tij[former][latter]);
	     //	}

    }



 /*   final_data=data[0];
    for(i=0;i<s;i++)
    {
	printf("probability of scenario %d: %f ",i, data[i]);
	  if(data[i]>final_data)
	  {
		 final_data=data[i];
		 final_path=i;
	  }
    }
    printf("\n\nFinal path is scenario %d with transition probability %f",final_path,final_data);
    //display final scenario
  /*  q=sce[final_path];
    while(q->next!=NULL)
    {
	printf("%d -> ",q->data);
	q=q->next;
    }
    printf("%d",q->data); */


    getch();
    return 0;
}