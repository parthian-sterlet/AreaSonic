#define _CRT_SECURE_NO_WARNINGS
#include  <stdio.h>
#include  <stdlib.h>
#include  <string.h>
#include  <math.h>
#include  <time.h>
#include  <ctype.h>
#define Min(a,b) ((a)>(b))? (b):(a);
#define Max(a,b) ((a)>(b))? (a):(b);
#define BINS 5000
#define KBASE 1000
//shuffling for razmetka 
//input 1st
//chrX a	b
//input second chromosome length
struct areas {
	int lev;
	int pra;
	//void areas::get_copy(areas *a);
} ;
long double lnfact[171] =
{ 0.000000000000,  0.000000000000,  0.693147180560,  1.791759469228,  3.178053830348,  4.787491742782,  6.579251212010,  8.525161361065, 10.604602902745, 12.801827480082,
 15.104412573076, 17.502307845874, 19.987214495662, 22.552163853123, 25.191221182739, 27.899271383841, 30.671860106081, 33.505073450137, 36.395445208033, 39.339884187200,
 42.335616460754, 45.380138898477, 48.471181351835, 51.606675567764, 54.784729398112, 58.003605222981, 61.261701761002, 64.557538627006, 67.889743137182, 71.257038967168,
 74.658236348830, 78.092223553315, 81.557959456115, 85.054467017582, 88.580827542198, 92.136175603687, 95.719694542143, 99.330612454787,102.968198614514,106.631760260643,
 110.320639714757,114.034211781462,117.771881399745,121.533081515439,125.317271149357,129.123933639127,132.952575035616,136.802722637326,140.673923648234,144.565743946345,
 148.477766951773,152.409592584497,156.360836303079,160.331128216631,164.320112263195,168.327445448428,172.352797139163,176.395848406997,180.456291417544,184.533828861449,
 188.628173423672,192.739047287845,196.866181672890,201.009316399282,205.168199482641,209.342586752537,213.532241494563,217.736934113954,221.956441819130,226.190548323728,
 230.439043565777,234.701723442818,238.978389561834,243.268849002983,247.572914096187,251.890402209723,256.221135550010,260.564940971863,264.921649798553,269.291097651020,
 273.673124285694,278.067573440366,282.474292687630,286.893133295427,291.323950094270,295.766601350761,300.220948647014,304.686856765669,309.164193580147,313.652829949879,
 318.152639620209,322.663499126726,327.185287703775,331.717887196928,336.261181979198,340.815058870799,345.379407062267,349.954118040770,354.539085519441,359.134205369575,
 363.739375555563,368.354496072405,372.979468885689,377.614197873919,382.258588773060,386.912549123218,391.575988217330,396.248817051792,400.930948278916,405.622296161145,
 410.322776526937,415.032306728250,419.750805599545,424.478193418257,429.214391866652,433.959323995015,438.712914186121,443.475088120919,448.245772745385,453.024896238496,
 457.812387981278,462.608178526875,467.412199571608,472.224383926981,477.044665492586,481.872979229888,486.709261136839,491.553448223298,496.405478487218,501.265290891579,
 506.132825342035,511.008022665236,515.890824587822,520.781173716044,525.679013515995,530.584288294433,535.496943180170,540.416924105998,545.344177791155,550.278651724286,
 555.220294146895,560.169054037273,565.124881094874,570.087725725134,575.057539024710,580.034272767131,585.017879388839,590.008311975618,595.005524249382,600.009470555327,
 605.020105849424,610.037385686239,615.061266207085,620.091704128477,625.128656730891,630.172081847810,635.221937855060,640.278183660408,645.340778693435,650.409682895655,
 655.484856710889,660.566261075874,665.653857411106,670.747607611913,675.847474039737,680.953419513637,686.065407301994,691.183401114411,696.307365093814,701.437263808737,
 706.573062245787};

int StrNStr(char *str,char c, int n)
{
	int i, len=strlen(str);
	int k=1;
	for(i=0;i<len;i++)
	{
		if(str[i]==c)
		{
			if(k==n)return i;
			k++;
		}
	}
	return -1;
}
void DelChar(char *str,char c)
{
	int i, lens, size;

	size=0;
	lens=strlen(str);
	for(i=0;i<lens;i++)
	{
		if(str[i]!=c)str[size++]=str[i];
	}
	str[size]='\0';
}
void RazborArea(char *str, areas *a)
{
	int loc;
	DelChar(str,'\n');
	loc=StrNStr(str,'\t',1);
	a->lev=atoi(&str[loc]);	
	loc=StrNStr(str,'\t',2);
	a->pra=atoi(&str[loc]);
}
void Mix(int *a, int *b)
{
  int buf=*a;
  *a=*b;
  *b=buf;
}
void BigMix1(int *d, int len)
{
    int r;
	for(r=0;r<len-1;r++) Mix(&d[r], &d[1+r+(rand()%(len-1-r))]);
}
//formula stirlinga
long double ApproxLnFact(int n)
{
    double pi=3.14159265359;
	long double ret=0.5*log(2*pi*n)+n*(log((long double)n)-1);
	return ret;
}
long double LnFact(int n)
{
	int thr=150;
	if(n<thr)
	{
		return lnfact[n];
	}
	else 
	{
		return ApproxLnFact(n);
	}
}
double Erf_approx(double z)
{
	z /= sqrt((double)2);
	const double pi = 3.141592653589;
	double pi_sq = sqrt(pi);
	double prec = 1E-10;
	double ret = 1;
	int i;
	double mnoj = exp(-z * z) / (z * pi_sq);
	int sign = -1;
	for (i = 1;; i++)
	{
		double x2 = exp(LnFact(2 * i));
		double x1 = exp(LnFact(i));
		double x3 = pow((long double)(z), 2 * i);
		double dret = sign * x2 / x1 / x3;
		ret += dret;
		sign = -sign;
		double dif = fabs(dret);
		if (dif < prec)break;
	}
	ret *= mnoj;
	return ret;
}
double Log10Erf_approx(double z) //log10
{	
	//z = 50;
	z/=sqrt((double)2);	
	const double pi=3.141592653589;
	double pi_sq=sqrt(pi);
	double prec = 1E-10;
	double ret=1;
	int i;
	//double mnoj=exp(-z*z)/(z*pi_sq);
	double mnoj = (-z * z)/log(double(10)) - log10(z * pi_sq);
	int sign=-1;
	for(i=1;;i++)
	{				
		double x2=exp(LnFact(2*i));
		double x1=exp(LnFact(i));
		double x3=pow((long double)(z),2*i);
		double dret=sign*x2/x1/x3;
		ret+=dret;
		sign=-sign;		
		double dif=fabs(dret);
		if(dif<prec)break;
	}
	ret = -log10(ret);
	ret-=mnoj;
	return ret;
}
double Laplace(double z)
{
    const double pi=3.141592653589793; 
    const double step=0.0001;
	const double step2=step/2;
    double x, y=0, dy;    
    double prec = 1E-20;
	x=z;	    
	double mnoj=sqrt(2*pi);
	do
    {
		x+=step2;
		dy=step*exp(-x*x/2);
		dy/=mnoj;
		y+=dy;
		x+=step2;
    }	
	while(dy>prec);			
    return(y);
}

int main(int argc, char *argv[])
{	
	int i, j, k;
	int *chr_len;
	char str[200], filearea_var_base[500], filearea_const_base[500], fileo[500], fileod[500];
	char file_chr_len[500], file_chr_name[500], **filearea_var, **filechr, **filearea_const;
	if(argc!=8)
	{
		printf ("%s 1file_area_shuffled 2file chr_len_arrays 3file_area_constant_base 4int_no_of_generations 5file_out 6file_out_distribution 7 chr_name_array",argv[0]);
        exit (1);
	}	
	FILE **in_const, **in_var, *out, *outd, *in_len, *in_name;	
	strcpy(filearea_var_base,argv[1]);	
	strcpy(file_chr_len,argv[2]);
	strcpy(filearea_const_base,argv[3]);	
	int ngen=atoi(argv[4]);// 4islo iteraciy	
	strcpy(fileo,argv[5]);	
	strcpy(fileod,argv[6]);		
	strcpy(file_chr_name,argv[7]);
	
	if((in_name=fopen(file_chr_name,"rt"))==NULL)
	{
 		printf("Input file %s can't be opened!\n",file_chr_name);
		return -1;
	}
	if((in_len=fopen(file_chr_len,"rt"))==NULL)
	{
 		printf("Input file %s can't be opened!\n",file_chr_len);
		return -1;
	}
	int nchr=0;
	{
		int fl[2]={1,1};
		char sin[40];
		while(fl[0]==1 && fl[1]==1)	
		{
			if(fgets(sin,sizeof(sin),in_name)==NULL)fl[0]=0;
			if(strncmp(sin,"chr",3)!=0)fl[0]=0;
			if(fgets(sin,sizeof(sin),in_len)==NULL)fl[1]=0;
			if(isdigit(sin[0])==0)fl[1]=0;
			if(fl[0]==1 && fl[1]==1)nchr++;
		}
		rewind(in_name);
		rewind(in_len);
		if(nchr<1)
		{
			printf("Input files %s & %s are wrong!\n", file_chr_name,file_chr_len);
			return -1;
		}
		//printf("%d chromosomes are taken!\n",nchr);
		chr_len=new int[nchr];
		if(chr_len==NULL){printf("Not  enough memory!");return -1;}	
		filearea_var=new char*[nchr];
		if(filearea_var==NULL){printf("Not  enough memory!");return -1;}	
		for(i=0;i<nchr;i++)
		{
			filearea_var[i]=new char[500];
			if(filearea_var[i]==NULL){printf("Not  enough memory!");return -1;}	
		}		
		filechr=new char*[nchr];
		for(i=0;i<nchr;i++)
		{
			filechr[i]=new char[30];
			if(filechr[i]==NULL){printf("Not  enough memory!");return -1;}	
		}
		filearea_const=new char*[nchr];
		if(filearea_const==NULL){printf("Not  enough memory!");return -1;}	
		for(i=0;i<nchr;i++)
		{
			filearea_const[i]=new char[500];
			if(filearea_const[i]==NULL){printf("Not  enough memory!");return -1;}	
		}
		for(i=0;i<nchr;i++)
		{
			fgets(sin,sizeof(sin),in_name);
			DelChar(sin,'\n');	
			strcpy(filechr[i],sin);
			fgets(sin,sizeof(sin),in_len);
			chr_len[i]=atoi(sin);
			if(chr_len[i]<=0 || chr_len[i]>500000000)
			{
				printf("Length value %d out of range\n",chr_len[i]);
				return -1;
			}
		}
		fclose(in_name);
		fclose(in_len);
	}	
	in_var=new FILE*[nchr];
	if(in_var==NULL){printf("Not  enough memory!");return -1;}	
	char *data_present1;
	data_present1 = new char[nchr+1];
	for(i=0;i<nchr;i++)
	{
		memset(filearea_var[i],'\0',sizeof(filearea_var[i]));
		strcat(filearea_var[i],filearea_var_base);
		strcat(filearea_var[i],"_");
		strcat(filearea_var[i],filechr[i]);
		strcat(filearea_var[i],".bed");	
		if((in_var[i]=fopen(filearea_var[i],"rt"))==NULL)
		{
 			printf("Input file %s can't be opened!\n",filearea_var[i]);
			data_present1[i] = '-';
			continue;
		}	
		else
		{
			data_present1[i] = '+';
		}
	}
	data_present1[nchr] = '\0';
	if (strstr(data_present1,"+")==NULL)
	{
		printf("Input files %s can't be opened!\n", filearea_var_base);
		return -1;
	}
	in_const = new FILE*[nchr];
	if(in_const==NULL){printf("Not  enough memory!");return -1;}	
	char *data_present2;
	data_present2 = new char[nchr + 1];
	for (i = 0; i<nchr; i++)
	{
		memset(filearea_const[i],'\0',sizeof(filearea_const[i]));
		strcat(filearea_const[i],filearea_const_base);
		strcat(filearea_const[i],"_");
		strcat(filearea_const[i],filechr[i]);
		strcat(filearea_const[i],".bed");	
		if((in_const[i]=fopen(filearea_const[i],"rt"))==NULL)
		{
 			printf("Input file %s can't be opened!\n",filearea_const[i]);
			data_present2[i] = '-';
		}	
		else
		{
			data_present2[i] = '+';
		}
	}
	data_present2[nchr] = '\0';
	if (strstr(data_present2, "+") == NULL)
	{
		printf("Input const files can't be opened!\n");
		return -1;
	}
	int *string_area_var;
	string_area_var=new int[nchr];
	if(string_area_var==NULL){printf("Not  enough memory!");return -1;};	
	for(i=0;i<nchr;i++)
	{
		string_area_var[i] = 0;
		if (data_present1[i] == '+' && data_present2[i] == '+')
		{			
			while (fgets(str, sizeof(str), in_var[i]) != NULL)
			{
				if (*str != '\n')string_area_var[i]++;
			}
			rewind(in_var[i]);
		}
	}
	int *string_area_const;	
	string_area_const=new int[nchr];
	if(string_area_const==NULL){printf("Not  enough memory!");return -1;};	
	for(i=0;i<nchr;i++)
	{
		string_area_const[i] = 0;
		if (data_present1[i] == '+' && data_present2[i] == '+')
		{			
			while (fgets(str, sizeof(str), in_const[i]) != NULL)
			{
				if (*str != '\n')string_area_const[i]++;
			}
			rewind(in_const[i]);
		}
	}
	areas **area_const;	
	area_const=new areas*[nchr];
	if(area_const==NULL){printf("Not  enough memory!");return -1;}	
	for(i=0;i<nchr;i++)
	{
		if (data_present1[i] == '-' || data_present2[i] == '-')continue;
		area_const[i]=new areas[string_area_const[i]];
		if(area_const[i]==NULL){printf("Not  enough memory!");return -1;}	
	}
	int bin[BINS];
	for(i=0;i<BINS;i++)bin[i]=0;
	int bin_max=BINS-1;
	int **arealen;
	arealen=new int*[nchr];
	if(arealen==NULL){printf("Not  enough memory!");return -1;}	
	for(i=0;i<nchr;i++)
	{
		if (data_present1[i] == '-' || data_present2[i] == '-')continue;
		arealen[i]=new int[string_area_var[i]];
		if(arealen[i]==NULL){printf("Not  enough memory!");return -1;}
	}
	int **spacer;
	spacer=new int*[nchr];
	if(spacer==NULL){printf("Not  enough memory!");return -1;}	
	for(i=0;i<nchr;i++)
	{
		if (data_present1[i] == '-' || data_present2[i] == '-')continue;
		spacer[i]=new int[string_area_var[i]+1];
		if(spacer[i]==NULL){printf("Not  enough memory!");return -1;}
	}
	for(i=0;i<nchr;i++)
	{
		if (data_present1[i] == '-' || data_present2[i] == '-')continue;
		int end=0;
		j=0;
		while(fgets(str,sizeof(str),in_var[i])!=NULL)
		{
			DelChar(str,'\n');	
			int loc=StrNStr(str,'\t',1);
			int sta=atoi(&str[loc]);	
			spacer[i][j]=sta-end-1;
			loc=StrNStr(str,'\t',2);
			end=atoi(&str[loc]);
			arealen[i][j]=end-sta;
			j++;
		}
		spacer[i][string_area_var[i]]=chr_len[i]-end;
		fclose(in_var[i]);		
	}
	//**len_count
	int string_area_var_len = 0, string_area_const_len = 0;
	for(i=0;i<nchr;i++)
	{
		if (data_present1[i] == '-' || data_present2[i] == '-')continue;
		j=0;	
		while(fgets(str,sizeof(str),in_const[i])!=NULL)
		{
			RazborArea(str,&area_const[i][j]);
			string_area_const_len += area_const[i][j].pra - area_const[i][j].lev + 1;
			j++;
		}
		fclose(in_const[i]);
	}
	int string_area_var_max=0;
	for (i = 0; i < nchr; i++)
	{
		if (data_present1[i] == '-' || data_present2[i] == '-')continue;
		if (string_area_var_max < string_area_var[i])string_area_var_max = string_area_var[i];
	}
	areas *area_var;
	area_var=new areas[string_area_var_max];
	if(area_var==NULL){printf("Not  enough memory!");return -1;}
	srand( (unsigned)time( NULL ) );
	if((out=fopen(fileo,"at"))==NULL)
	{
 		printf("Input file %s can't be opened!\n",fileo);
		return -1;
	}
	int n;
	for(i=0;i<nchr;i++)
	{
		if (data_present1[i] == '-' || data_present2[i] == '-')continue;
		if(area_const[i][string_area_const[i]-1].pra>chr_len[i])
		{
			printf("Last area_right_edge %d or chr_len %d out of range\n",area_const[i][string_area_const[i]-1].pra,chr_len[i]);
			return -1;
		}
	}
	int cats_area0;
	double real;
	int cats_area;		
	int better=0;
	double rand_av=0, rand_sd=0;
	int n_cyc=0;
	int err_min_thr=100;
	int n_cyc_thr=10000;
	for(n=0;n<=ngen;n++)
	{
		cats_area=0;
		for(k=0;k<nchr;k++)
		{
			if (data_present1[k] == '-' || data_present2[k] == '-')continue;
			if(n>0)
			{
				BigMix1(arealen[k],string_area_var[k]);
				BigMix1(spacer[k],string_area_var[k]+1);			
			}			
			int end=spacer[k][0]+1;			
			for(i=0;i<string_area_var[k];i++)
			{
				//fprintf(out,"chr%s\t",chr);
				//fprintf(out,"%d\t",end);
				area_var[i].lev=end;
				end+=arealen[k][i];
				area_var[i].pra=end;
				//fprintf(out,"%d\n",end);
				end+=spacer[k][i+1]+1;				
			}		
			if(n==0)
			{
				for (i = 0; i<string_area_var[k]; i++)string_area_var_len += area_var[i].pra - area_var[i].lev + 1;
				if(area_var[string_area_var[k]-1].pra>chr_len[k])
				{
					printf("Last Pre-random area_right_edge %d or chr_len %d out of range\n",area_var[string_area_var[k]-1].pra,chr_len[k]);
					return -1;
				}
			}
			for(i=0;i<string_area_var[k];i++)
			{
				int lev=area_var[i].lev;
				int pra=area_var[i].pra;
				int cata=0;
				for(j=0;j<string_area_const[k];j++)
				{
					int olev=area_const[k][j].lev;
					int opra=area_const[k][j].pra;				
					if(olev>pra)break;
					int cats=-1;
					if((lev<=olev && olev<=pra) || (lev<=opra && opra<=pra))cats=1;
					if((olev<=lev && lev<=opra) || (olev<=pra && pra<=opra))cats=1;
					if(cats==1)
					{
						int min=Min(pra,opra);
						int max=Max(lev,olev);
						cata=min-max+1;
						cats_area+=cata;					
					}
				}			
			}	
		}
		if(n==0)
		{
			cats_area0=cats_area;
			real=(double)cats_area0/KBASE;
		}
		else
		{		
			if(cats_area>=cats_area0)better++;
			double rand=(double)cats_area/KBASE;
			rand_av+=rand;
			rand_sd+=rand*rand;
			int randi=(int)rand;
			int nbin=Min(randi,bin_max);
			bin[nbin]++;			
		}
		//fprintf(out,"%s\t%s\t%d\t%d\t%s\t%d\n",fileareai,fileareai_const,cats_area,inter_area,file_over_site,cats_site);		
		if(n>0)n_cyc++;
		int worse=n_cyc-better;
		int err_min=Min(better,worse);
		if(n%1000==0)
		{
			printf("\b\b\b\b\b\b\b\b\b\b\b\b\b%6d %6d",err_min,n);
		}
		if(err_min>err_min_thr && n_cyc>n_cyc_thr)break;
	}
	rand_av/=n_cyc;
	rand_sd=(rand_sd-n_cyc*rand_av*rand_av)/(n_cyc-1);
	rand_sd=sqrt(rand_sd);
	double pval_approx=1;	
	double z_score=fabs(real-rand_av)/rand_sd;
	//z_score = 10;
	if(z_score ==0)pval_approx = 1;
	{
		if(z_score>14)pval_approx=Log10Erf_approx(z_score);
		else
		{
			//if(z_score>2)
			{
				pval_approx=Laplace(z_score);
				pval_approx = -log10(pval_approx);
			}
		}
	}	
	int total_count_var=0, total_count_const=0;
	for(k=0;k<nchr;k++)total_count_var+=string_area_var[k];
	for(k=0;k<nchr;k++)total_count_const+=string_area_const[k];	
	if (real - rand_av < 0)
	{
		//pval_approx *= -1;
		z_score*= -1;
	}
	fprintf(out, "AreaVar\t%s\t%d\t%d\tAreaConst\t%s\t%d\t%d\tNcyc\t%d\t", filearea_var_base, total_count_var, string_area_var_len / KBASE, filearea_const_base, total_count_const, string_area_const_len / KBASE, n_cyc);
	fprintf(out, "Real\t%.3f\tAv\t%f\tSD\t%f\tZ\t%f\t-Log10[Pv]\t%g\n", real, rand_av, rand_sd, z_score, pval_approx);//(double)better / n_cyc, 1 - (double)better / n_cyc, //PvalueLarger\t%g\tPvalueSmaller\t%f\t
	fclose(out);
	if((outd=fopen(fileod,"at"))==NULL)
	{
 		printf("Input file %s can't be opened!\n",fileod);
		return -1;
	}
	fprintf(outd,"%s_%s_%f",filearea_var_base,filearea_const_base,real);
	for(i=0;i<BINS;i++)
	{	
	//	if(bin[i]>0)
		{
			//fprintf(outd,"%d\t",i);
			fprintf(outd,"\t%d",bin[i]);
		}		
	}
	fprintf(outd,"\n");
	fclose(outd);
	return 0;
}
