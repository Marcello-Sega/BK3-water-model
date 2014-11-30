#include <stdlib.h>
#include <stdio.h>
#include <math.h>
long double f(long double x, long double a12) { 
	if(x<1e-6) return 0.0;
        return (erfl(a12*x)-2./sqrtl(M_PI) *a12*x*expl(-x*x*a12*a12))/(x*x);
}

long double u(long double x, long double a12 ) { 
	if(x<1e-6) return 2.0*a12/sqrtl(M_PI) ;
        return erfl(a12*x)/x;
}

int main(int argc, char**argv){ 

	long double x, a1,a2,a12[2][2];
        double s1,s2;
        char name[256];
        int i,j;
        FILE * file ;

        if(argc!=5) exit(printf("Usage: %s <type1> <type2> <sigma1> <sigma2>\n",argv[0]));
        s1=atof(argv[3]); 
        s2=atof(argv[4]); 

        a1=1./sqrtl(2.0)/s1;
        a2=1./sqrtl(2.0)/s2;

        a12[0][0]= a1 /sqrt(2.);
        a12[1][1]= a2 /sqrt(2.);
        a12[0][1]= a1*a2 /sqrt(a1*a1+a2*a2);

        for(i=0;i<2;i++){
         for(j=i;j<2;j++){
           sprintf(name,"table_%s_%s.xvg",argv[i+1],argv[j+1]);
           file = fopen(name,"w");
           for(x=0; x<= 2.1 ; x+=0.002 ) 
		fprintf( file,"%.10Lf %.10Lf %.10Lf 0.0 0.0 0.0 0.0\n",x,u(x,a12[i][j]), f(x,a12[i][j])  ) ;
           fclose(file);
         }
        }
       
        file = fopen("table.xvg","w");
        for(x=0; x<= 2.1 ; x+=0.002 ) 
		fprintf( file,"%.10Lf 0.0 0.0 0.0 0.0 0.0 0.0\n",x ) ;
        fclose(file);
        return 0;
}
