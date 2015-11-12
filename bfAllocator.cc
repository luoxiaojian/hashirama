
#include "bfAllocator.h"
#include <iostream>
#define MAX(a,b) ((a>b)?a:b)

static int tnum, pnum, rnum, lcm_period;
static int *period, *execute, *rwidth, *b, *RWmP;
static int **alloc;

static int **alpha, **UF;

static int getSign(int x)
{
	if(x>0)
		return 1;
	else if(x<0)
		return -1;
	return 0;
}


static void init() {
	alpha=(int **)malloc(sizeof(int *)*tnum);
	for(int i=0; i<tnum; i++)
		alpha[i]=(int *)malloc(sizeof(int)*rnum);

	UF=(int **)malloc(sizeof(int *)*tnum);
	for(int i=0; i<tnum; i++)
		UF[i]=(int *)malloc(sizeof(int)*(rnum+1));

	RWmP=(int *)malloc(sizeof(int)*tnum);


	for(int i=0; i<rnum; i++)
		for(int j=0; j<tnum; j++)
		{
			int tmp=b[i]*execute[j]/period[j]+(b[i+1]-b[i]);
			alpha[j][i]=getSign(b[i+1]*execute[j]-tmp*period[j]);
		}

	for(int i=0; i<tnum; i++)
		for(int j=0; j<rnum+1; j++)
		{
			UF[i][j]=0;
			for(int k=1; k<rnum-j; k++)
			{
				if(alpha[i][j+k]==-1)
				{
					int tmp=(b[j+k]*execute[i])/period[i];
					UF[i][j]=(1+tmp)*period[i]-b[j+k]*execute[i];
					break;
				}
			}
		}

	for(int i=0; i<tnum; i++)
		RWmP[i]=0;
}

static void uninit() {
	for(int i=0; i<tnum; i++)
		free(alpha[i]);
	free(alpha);

	for(int i=0; i<tnum; i++)
		free(UF[i]);
	free(UF);

	free(RWmP);
}

static int compare(int i, int j, int k)
{
	int s=1;
	while((alpha[i][k+s]==1) && (alpha[j][k+s]==1))
		s++;

	if(alpha[i][k+s]>alpha[j][k+s])
		return 1;
	else if(alpha[i][k+s]<alpha[j][k+s])
		return 0;
	else if((alpha[i][k+s]==0) && (alpha[j][k+s]==0))
		return 1;
	else {
		int xi=UF[i][k]*execute[j];
		int xj=UF[j][k]*execute[i];
		if(xi>xj)
			return 0;
		else
			return 1;
	}
}

static void taskSelect(int *selected, int ru, int k, int el)
{
	for(int i=0; i<ru; i++)
		for(int j=i+1; j<el; j++)
		{
			if(compare(selected[i], selected[j], k)==0)
			{
				int tmp=selected[i];
				selected[i]=selected[j];
				selected[j]=tmp;
			}
		}
}

static void bfair(int k)
{
	int *m, *PWmP, *o, *selected;

	m=(int *)malloc(sizeof(int)*tnum);
	PWmP=(int *)malloc(sizeof(int)*tnum);
	o=(int *)malloc(sizeof(int)*tnum);
	selected=(int *)malloc(sizeof(int)*tnum);

	int summ=0;

	for(int i=0; i<tnum; i++)
	{
		int tmp=RWmP[i]+(rwidth[k]*execute[i]);
		tmp=tmp/period[i];
		m[i]=0;
		if(tmp>0)
			m[i]=tmp;
		PWmP[i]=RWmP[i]+rwidth[k]*execute[i]-m[i]*period[i];
		o[i]=0;
		summ+=m[i];
	}

	int RU=pnum*rwidth[k]-summ;
	int el=0;

	if(RU>0) {
		for(int i=0; i<tnum; i++) {
			if((PWmP[i]>0) && (m[i]<rwidth[k]))
			{
				selected[el]=i;
				el++;
			}
		}

		taskSelect(selected, RU, k, el);
		for(int i=0; i<RU; i++)
			o[selected[i]]=1;
	}

	for(int i=0; i<tnum; i++)
		m[i]=m[i]+o[i];

	for(int i=0; i<tnum; i++)
		alloc[i][k]=m[i];

	for(int i=0; i<tnum; i++)
		RWmP[i]=PWmP[i]-o[i]*period[i];

	free(m);
	free(PWmP);
	free(o);
	free(selected);
}

static bool checkAlloc() {
	for(int i=0; i<tnum; i++)
	{
		for(int j=0; j<lcm_period/period[i]; j++)
		{
			int start=j*period[i];
			int end=(j+1)*period[i];
			int count=0;
			for(int k=0; k<rnum; k++)
			{
				if((b[k]>=start) && (b[k]<end))
					count+=alloc[i][k];
			}
			if(count!=execute[i])
				return false;
		}
	}

	for(int i=0; i<rnum; i++)
	{
		int sum=0;
		for(int j=0; j<tnum; j++)
			sum+=alloc[j][i];
		if(sum!=(rwidth[i]*pnum))
			return false;
	}
	return true;
}

bool bfAllocator::allocate(const taskset& ts, allocation& al) {
	tnum=ts.tnum;
	pnum=ts.pnum;
	lcm_period=ts.lcm_period;
	period=ts.period;
	execute=ts.execute;
	rnum=ts.rnum;
	rwidth=ts.rwidth;
	b=ts.b;
	alloc=al.alloc;

	init();

	for(int i=0; i<rnum; i++)
		bfair(i);

	uninit();

	return checkAlloc();
}
