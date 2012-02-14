/*
Copyright 1990-2008 Light Infocon Tecnologia S/A

Este arquivo é parte do programa LightBase - Banco de Dados Textual Documental

O LightBase é um software livre; você pode redistribui-lo e/ou modifica-lo dentro 
dos termos da Licença Pública Geral GNU como publicada pela Fundação do Software 
Livre (FSF); na versão 2 da Licença.

Este programa é distribuído na esperança que possa ser útil, mas SEM NENHUMA 
GARANTIA; sem uma garantia implícita de ADEQUAÇÃO a qualquer MERCADO ou APLICAÇÃO 
EM PARTICULAR. Veja a Licença Pública Geral GNU para maiores detalhes.

Você deve ter recebido uma cópia da Licença Pública Geral GNU versao 2, sob o título
"LICENCA.txt", junto com este programa, se não, escreva para a Fundação do Software 
Livre(FSF) Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
*/

/*** $#$#$#$#$#$#$#$#$#$ ***/
static	char	*_szStr;	/*** string de entrada para o parser ***/
static	long	_lStrPos;	/*** posicao corrente dentro de szStr ***/
static	int		_iStatus;		/*** status a ser devolvido ***/
char			*_szFinal;

#include	<string.h>
#include	<const.h> // GREEN

/*** $#$#$#$#$#$#$#$#$#$#$# ***/
# undef _RTLDLL

# include "stdio.h"
# define U(x) x
# define NLSTATE yyprevious=YYNEWLINE
# define BEGIN yybgin = yysvec + 1 +
# define INITIAL 0
# define YYLERR yysvec
# define YYSTATE (yyestate-yysvec-1)
# define YYOPTIM 1
# define LEXDEBUG 1
# define YYLMAX 200
# define output(c) putc(c,yyout)
/*** $#$#$#$#$#$#$#$ ***/
# undef output
# define output(c) ;

# define input() (((yytchar=yysptr>yysbuf?U(*--yysptr):getc(yyin))==10?(yylineno++,yytchar):yytchar)==EOF?0:yytchar)

/*** $#$#$#$#$#$#$#$ ***/
# undef input
# define input() (((yytchar=yysptr>yysbuf?U(*--yysptr):mygetc())==10?(yylineno++,yytchar):yytchar)==EOF?0:yytchar)
# define mygetc() ((_szFinal < _szStr[_lStrPos]) ? 0 : _szStr[_lStrPos++])

# define unput(c) {yytchar= (c);if(yytchar=='\n')yylineno--;*yysptr++=yytchar;}
# define yymore() (yymorfg=1)
# define ECHO fprintf(yyout, "%s",yytext)
# define REJECT { nstr = yyreject(); goto yyfussy;}
int yyleng; extern char yytext[];
int yymorfg;
extern char *yysptr, yysbuf[];
int yytchar;

/*** $#$#$#$#$#$ ***/
FILE *yyin = stdin;
FILE *yyout = {stdout};

extern int yylineno;
struct yysvf { 
	struct yywork *yystoff;
	struct yysvf *yyother;
	int *yystops;};
struct yysvf *yyestate;
extern struct yysvf yysvec[], *yybgin;
			
# define YYNEWLINE 10
yylex(){
int nstr; extern int yyprevious;
while((nstr = yylook()) >= 0)
yyfussy: switch(nstr){
case 0:
/* $#$#$#$#$ ***/
if(yywrap()) { _iStatus = PROCESS_END; return(0); } break;
case 1:
							HandleParagraphEnd();
/*** $#$#$#$#$# ***/
/*break;*/return(0);
case 2:
								HandleSentenceEnd();
/*** $#$#$#$#$# ***/
/*break;*/return(0);
case 3:
						HandleSentenceEnd();
/*** $#$#$#$#$# ***/
/*break;*/return(0);
case 4:
                               HandleNumber();
/*** $#$#$#$#$# ***/
/*break;*/return(0);
case 5:
                       	HandleNumber();
/*** $#$#$#$#$# ***/
/*break;*/return(0);
case 6:
                       	HandleNumber();
/*** $#$#$#$#$# ***/
/*break;*/return(0);
case 7:
            		HandleNumber();
/*** $#$#$#$#$# ***/
/*break;*/return(0);
case 8:
            		HandleNumber();
/*** $#$#$#$#$# ***/
/*break;*/return(0);
case 9:
			HandleDate();
/*** $#$#$#$#$# ***/
/*break;*/return(0);
case 10:
	 			HandleDate();
/*** $#$#$#$#$# ***/
/*break;*/return(0);
case 11:
	 			HandleDate();
/*** $#$#$#$#$# ***/
/*break;*/return(0);
case 12:
				HandleDate();
/*** $#$#$#$#$# ***/
/*break;*/return(0);
case 13:
	HandleDate();
/*** $#$#$#$#$# ***/
/*break;*/return(0);
case 14:
		HandleDate();
/*** $#$#$#$#$# ***/
/*break;*/return(0);
case 15:
          HandleDate();
/*** $#$#$#$#$# ***/
/*break;*/return(0);
case 16:
            	HandleDate();
/*** $#$#$#$#$# ***/
/*break;*/return(0);
case 17:
               HandleHour();
/*** $#$#$#$#$# ***/
/*break;*/return(0);
case 18:
                  HandleHour();
/*** $#$#$#$#$# ***/
/*break;*/return(0);
case 19:
                  HandleHour();
/*** $#$#$#$#$# ***/
/*break;*/return(0);
case 20:
                     HandleHour();
/*** $#$#$#$#$# ***/
/*break;*/return(0);
case 21:
                        HandleHour();
/*** $#$#$#$#$# ***/
/*break;*/return(0);
case 22:
                           HandleHour();
/*** $#$#$#$#$# ***/
/*break;*/return(0);
case 23:
                           HandleHour();
/*** $#$#$#$#$# ***/
/*break;*/return(0);
case 24:
                              HandleHour();
/*** $#$#$#$#$# ***/
/*break;*/return(0);
case 25:
                              HandleSpecial();
/*** $#$#$#$#$# ***/
break;/*return(0);*/
case 26:
                                   HandleWord();
/*** $#$#$#$#$# ***/
/*break;*/return(0);
case -1:
break;
default:
/*** $#$#$#$#$#$# ***/
/*fprintf(yyout,"bad switch yylook %d",nstr);*/
return( -1 );
}
/*** $#$#$#$#$#$# ***/
_iStatus = PROCESS_END;
return(0); }
/* end of yylex */

HandleParagraphEnd()
{
	_iStatus = PARAGRAPH_END;
//	printf( "FIM DE PARAGRAFO\n" );
	return( 0 );
}

HandleSentenceEnd()
{
	_iStatus = SENTENCE_END;
//	printf( "FIM DE FRASE (%s)\n", yytext );
	return( 0 );
}
 
HandleNumber()
{
	_iStatus = WORD_END;
//	printf( "numero %s\n",yytext );
	return( 0 );
}

HandleDate()
{
	_iStatus = WORD_END;
//	printf( "data %s\n", yytext );
	return( 0 );
}

HandleHour()
{
	_iStatus = WORD_END;
//	printf( "hora %s\n", yytext );
	return( 0 );
}

HandleSpecial()
{
//	printf( "\t\t\t----> ignorado %s\n", yytext );
	return( 0 );
}

HandleWord()
{
	_iStatus = WORD_END;
//	printf( "palavra %s\n", yytext );
	return( 0 );
}
int yyvstop[] = {
0,
/* actions for state 2 */
1,
0,
/* actions for state 3 */
25,
0,
/* actions for state 4 */
3,
0,
/* actions for state 5 */
1,
25,
0,
/* actions for state 6 */
26,
0,
/* actions for state 7 */
25,
0,
/* actions for state 8 */
3,
0,
/* actions for state 9 */
4,
26,
0,
/* actions for state 10 */
3,
25,
26,
0,
/* actions for state 11 */
4,
0,
/* actions for state 16 */
4,
26,
0,
/* actions for state 18 */
2,
0,
/* actions for state 19 */
5,
0,
/* actions for state 20 */
6,
0,
/* actions for state 23 */
4,
26,
0,
/* actions for state 25 */
24,
0,
/* actions for state 31 */
23,
0,
/* actions for state 32 */
22,
0,
/* actions for state 34 */
7,
0,
/* actions for state 35 */
8,
0,
/* actions for state 40 */
21,
0,
/* actions for state 44 */
12,
0,
/* actions for state 51 */
20,
0,
/* actions for state 53 */
10,
0,
/* actions for state 54 */
11,
0,
/* actions for state 57 */
19,
0,
/* actions for state 58 */
18,
0,
/* actions for state 59 */
16,
0,
/* actions for state 62 */
9,
0,
/* actions for state 63 */
17,
0,
/* actions for state 64 */
14,
0,
/* actions for state 65 */
15,
0,
/* actions for state 67 */
13,
0,
0};
# define YYTYPE char
struct yywork { YYTYPE verify, advance; } yycrank[] = {
0,0,	0,0,	1,0,	1,0,	
1,0,	1,0,	1,0,	1,0,	
1,0,	1,0,	1,0,	1,3,	
1,0,	1,0,	1,0,	1,0,	
1,0,	1,0,	1,0,	1,0,	
1,0,	1,0,	1,0,	1,0,	
1,0,	1,0,	1,0,	1,0,	
1,0,	1,0,	1,0,	1,0,	
1,0,	1,4,	1,5,	1,6,	
1,7,	0,0,	1,0,	0,0,	
1,0,	1,0,	1,0,	1,0,	
1,0,	3,3,	1,8,	1,9,	
0,0,	1,10,	0,0,	0,0,	
0,0,	0,0,	0,0,	21,28,	
12,14,	9,13,	12,15,	13,19,	
20,27,	1,0,	1,0,	1,0,	
30,38,	40,48,	0,0,	0,0,	
0,0,	3,3,	8,12,	8,12,	
8,12,	8,12,	8,12,	8,12,	
8,12,	8,12,	8,12,	8,12,	
14,20,	14,20,	14,20,	14,20,	
14,20,	14,20,	14,20,	14,20,	
14,20,	14,20,	33,43,	41,49,	
1,0,	0,0,	1,0,	1,0,	
1,0,	1,0,	15,21,	15,21,	
15,21,	15,21,	15,21,	15,21,	
15,21,	15,21,	15,21,	15,21,	
16,22,	16,22,	16,22,	16,22,	
16,22,	16,22,	16,22,	16,22,	
16,22,	16,22,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
1,0,	1,11,	1,0,	1,0,	
1,0,	2,0,	2,0,	2,0,	
2,0,	2,0,	2,0,	2,0,	
2,0,	2,0,	0,0,	2,0,	
2,0,	2,0,	2,0,	2,0,	
2,0,	2,0,	2,0,	2,0,	
2,0,	2,0,	2,0,	2,0,	
2,0,	2,0,	2,0,	2,0,	
2,0,	2,0,	2,0,	2,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	2,0,	0,0,	2,0,	
2,0,	2,0,	2,0,	2,0,	
0,0,	2,8,	2,9,	18,26,	
18,26,	18,26,	18,26,	18,26,	
18,26,	18,26,	18,26,	18,26,	
18,26,	0,0,	0,0,	0,0,	
2,0,	2,0,	2,0,	22,29,	
22,30,	22,30,	22,30,	22,30,	
22,30,	22,30,	22,30,	22,30,	
22,30,	22,30,	23,31,	23,31,	
23,31,	23,31,	23,31,	23,31,	
23,31,	23,31,	23,31,	23,31,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	2,0,	
0,0,	2,0,	2,0,	2,0,	
2,0,	25,32,	25,32,	25,32,	
25,32,	25,32,	25,32,	25,32,	
25,32,	25,32,	25,32,	26,33,	
26,33,	26,33,	26,33,	26,33,	
26,33,	26,33,	26,33,	26,33,	
26,33,	26,34,	0,0,	0,0,	
0,0,	0,0,	0,0,	2,0,	
0,0,	2,0,	2,0,	2,0,	
7,0,	7,0,	7,0,	7,0,	
7,0,	7,0,	7,0,	7,0,	
7,0,	7,0,	7,0,	7,0,	
7,0,	7,0,	7,0,	7,0,	
7,0,	7,0,	7,0,	7,0,	
7,0,	7,0,	7,0,	7,0,	
7,0,	7,0,	7,0,	7,0,	
7,0,	7,0,	7,0,	7,0,	
7,0,	7,0,	7,7,	0,0,	
7,0,	0,0,	7,0,	7,0,	
7,0,	7,0,	7,0,	7,0,	
7,0,	7,0,	7,0,	7,7,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	7,0,	7,0,	7,0,	
7,0,	7,0,	7,0,	27,35,	
27,35,	27,35,	27,35,	27,35,	
27,35,	27,35,	27,35,	27,35,	
27,35,	28,36,	28,36,	28,36,	
28,36,	28,36,	28,36,	28,36,	
28,36,	28,36,	28,36,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	7,0,	7,0,	
7,0,	7,0,	7,0,	7,0,	
29,37,	29,37,	29,37,	29,37,	
29,37,	29,37,	29,37,	29,37,	
29,37,	29,37,	31,39,	31,40,	
31,40,	31,40,	31,40,	31,40,	
31,40,	31,40,	31,40,	31,40,	
31,40,	0,0,	0,0,	0,0,	
0,0,	0,0,	7,0,	7,7,	
7,0,	7,0,	7,0,	10,0,	
10,0,	10,0,	10,0,	10,0,	
10,0,	10,0,	10,0,	10,0,	
10,0,	10,0,	10,0,	10,0,	
10,0,	10,0,	10,0,	10,0,	
10,0,	10,0,	10,0,	10,0,	
10,0,	10,0,	10,0,	10,0,	
10,0,	10,0,	10,0,	10,0,	
10,0,	10,0,	10,0,	10,0,	
10,0,	0,0,	0,0,	10,0,	
0,0,	10,0,	10,0,	10,0,	
10,0,	10,0,	10,14,	10,0,	
10,15,	10,16,	10,17,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
10,18,	10,0,	10,0,	10,0,	
10,0,	10,0,	32,41,	32,41,	
32,41,	32,41,	32,41,	32,41,	
32,41,	32,41,	32,41,	32,41,	
32,42,	34,44,	34,44,	34,44,	
34,44,	34,44,	34,44,	34,44,	
34,44,	34,44,	34,44,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	10,0,	10,0,	10,0,	
10,0,	10,0,	10,0,	37,45,	
37,45,	37,45,	37,45,	37,45,	
37,45,	37,45,	37,45,	37,45,	
37,45,	38,46,	38,46,	38,46,	
38,46,	38,46,	38,46,	38,46,	
38,46,	38,46,	38,46,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	10,0,	0,0,	10,0,	
10,0,	10,0,	11,0,	11,0,	
11,0,	11,0,	11,0,	11,0,	
11,0,	11,0,	11,0,	11,0,	
11,0,	11,0,	11,0,	11,0,	
11,0,	11,0,	11,0,	11,0,	
11,0,	11,0,	11,0,	11,0,	
11,0,	11,0,	11,0,	11,0,	
11,0,	11,0,	11,0,	11,0,	
11,0,	11,0,	11,0,	11,0,	
0,0,	0,0,	11,0,	0,0,	
11,0,	11,0,	11,0,	11,0,	
11,0,	11,0,	11,0,	11,0,	
11,0,	39,47,	39,47,	39,47,	
39,47,	39,47,	39,47,	39,47,	
39,47,	39,47,	39,47,	11,0,	
11,0,	11,0,	11,0,	11,0,	
11,0,	42,50,	42,50,	42,50,	
42,50,	42,50,	42,50,	42,50,	
42,50,	42,50,	42,50,	43,51,	
43,51,	43,51,	43,51,	43,51,	
43,51,	43,51,	43,51,	43,51,	
43,51,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
11,0,	11,0,	11,0,	11,0,	
11,0,	11,0,	44,52,	44,52,	
44,52,	44,52,	44,52,	44,52,	
44,52,	44,52,	44,52,	44,52,	
45,53,	45,53,	45,53,	45,53,	
45,53,	45,53,	45,53,	45,53,	
45,53,	45,53,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
11,0,	0,0,	11,0,	11,0,	
11,0,	17,0,	17,0,	17,0,	
17,0,	17,0,	17,0,	17,0,	
17,0,	17,0,	17,0,	17,0,	
17,0,	17,0,	17,0,	17,0,	
17,0,	17,0,	17,0,	17,0,	
17,0,	17,0,	17,0,	17,0,	
17,0,	17,0,	17,0,	17,0,	
17,0,	17,0,	17,0,	17,0,	
17,0,	17,0,	17,0,	0,0,	
0,0,	17,0,	0,0,	17,0,	
17,0,	17,0,	17,0,	17,0,	
17,14,	17,0,	17,15,	17,23,	
17,24,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	17,25,	17,0,	
17,0,	17,0,	17,0,	17,0,	
46,54,	46,54,	46,54,	46,54,	
46,54,	46,54,	46,54,	46,54,	
46,54,	46,54,	47,55,	47,55,	
47,55,	47,55,	47,55,	47,55,	
47,55,	47,55,	47,55,	47,55,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	17,0,	
17,0,	17,0,	17,0,	17,0,	
17,0,	48,56,	48,56,	48,56,	
48,56,	48,56,	48,56,	48,56,	
48,56,	48,56,	48,56,	49,57,	
49,57,	49,57,	49,57,	49,57,	
49,57,	49,57,	49,57,	49,57,	
49,57,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	17,0,	
0,0,	17,0,	17,0,	17,0,	
24,0,	24,0,	24,0,	24,0,	
24,0,	24,0,	24,0,	24,0,	
24,0,	24,0,	24,0,	24,0,	
24,0,	24,0,	24,0,	24,0,	
24,0,	24,0,	24,0,	24,0,	
24,0,	24,0,	24,0,	24,0,	
24,0,	24,0,	24,0,	24,0,	
24,0,	24,0,	24,0,	24,0,	
24,0,	24,0,	0,0,	0,0,	
24,0,	0,0,	24,0,	24,0,	
24,0,	24,0,	24,0,	24,14,	
24,0,	24,15,	24,0,	24,24,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	24,0,	24,0,	24,0,	
24,0,	24,0,	24,0,	50,58,	
50,58,	50,58,	50,58,	50,58,	
50,58,	50,58,	50,58,	50,58,	
50,58,	51,59,	51,59,	51,59,	
51,59,	51,59,	51,59,	51,59,	
51,59,	51,59,	51,59,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	24,0,	24,0,	
24,0,	24,0,	24,0,	24,0,	
53,60,	53,60,	53,60,	53,60,	
53,60,	53,60,	53,60,	53,60,	
53,60,	53,60,	54,61,	54,61,	
54,61,	54,61,	54,61,	54,61,	
54,61,	54,61,	54,61,	54,61,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	24,0,	0,0,	
24,0,	24,0,	24,0,	55,62,	
55,62,	55,62,	55,62,	55,62,	
55,62,	55,62,	55,62,	55,62,	
55,62,	56,63,	56,63,	56,63,	
56,63,	56,63,	56,63,	56,63,	
56,63,	56,63,	56,63,	57,64,	
57,64,	57,64,	57,64,	57,64,	
57,64,	57,64,	57,64,	57,64,	
57,64,	61,65,	61,65,	61,65,	
61,65,	61,65,	61,65,	61,65,	
61,65,	61,65,	61,65,	62,66,	
62,66,	62,66,	62,66,	62,66,	
62,66,	62,66,	62,66,	62,66,	
62,66,	63,67,	63,67,	63,67,	
63,67,	63,67,	63,67,	63,67,	
63,67,	63,67,	63,67,	67,68,	
67,68,	67,68,	67,68,	67,68,	
67,68,	67,68,	67,68,	67,68,	
67,68,	0,0,	0,0,	0,0,	
0,0};
struct yysvf yysvec[] = {
0,	0,	0,
yycrank+-1,	0,		0,			/* state 0 */
yycrank+-128,	yysvec+1,	0,			/* state 1 */
yycrank+35,	0,		yyvstop+1,		/* state 2 */
yycrank+0,	0,		yyvstop+3,		/* state 3 */
yycrank+0,	0,		yyvstop+5,		/* state 4 */
yycrank+0,	yysvec+3,	yyvstop+7,		/* state 5 */
yycrank+-255,	0,		yyvstop+10,		/* state 6 */
yycrank+22,	0,		yyvstop+12,		/* state 7 */
yycrank+11,	0,		yyvstop+14,		/* state 8 */
yycrank+-382,	yysvec+7,	yyvstop+16,		/* state 9 */
yycrank+-509,	yysvec+7,	yyvstop+19,		/* state 10 */
yycrank+12,	yysvec+8,	yyvstop+23,		/* state 11 */
yycrank+13,	0,		0,			/* state 12 */
yycrank+32,	0,		0,			/* state 13 */
yycrank+50,	0,		0,			/* state 14 */
yycrank+60,	0,		0,			/* state 15 */
yycrank+-636,	yysvec+7,	yyvstop+25,		/* state 16 */
yycrank+127,	0,		0,			/* state 17 */
yycrank+0,	0,		yyvstop+28,		/* state 18 */
yycrank+14,	yysvec+14,	yyvstop+30,		/* state 19 */
yycrank+11,	yysvec+15,	yyvstop+32,		/* state 20 */
yycrank+144,	0,		0,			/* state 21 */
yycrank+154,	0,		0,			/* state 22 */
yycrank+-763,	yysvec+7,	yyvstop+34,		/* state 23 */
yycrank+177,	0,		0,			/* state 24 */
yycrank+187,	0,		yyvstop+37,		/* state 25 */
yycrank+271,	0,		0,			/* state 26 */
yycrank+281,	0,		0,			/* state 27 */
yycrank+304,	0,		0,			/* state 28 */
yycrank+17,	0,		0,			/* state 29 */
yycrank+315,	0,		0,			/* state 30 */
yycrank+398,	0,		yyvstop+39,		/* state 31 */
yycrank+32,	0,		yyvstop+41,		/* state 32 */
yycrank+409,	0,		0,			/* state 33 */
yycrank+0,	yysvec+27,	yyvstop+43,		/* state 34 */
yycrank+0,	yysvec+28,	yyvstop+45,		/* state 35 */
yycrank+431,	0,		0,			/* state 36 */
yycrank+441,	0,		0,			/* state 37 */
yycrank+509,	0,		0,			/* state 38 */
yycrank+18,	0,		0,			/* state 39 */
yycrank+33,	0,		yyvstop+47,		/* state 40 */
yycrank+525,	0,		0,			/* state 41 */
yycrank+535,	0,		0,			/* state 42 */
yycrank+558,	0,		0,			/* state 43 */
yycrank+568,	0,		yyvstop+49,		/* state 44 */
yycrank+652,	0,		0,			/* state 45 */
yycrank+662,	0,		0,			/* state 46 */
yycrank+685,	0,		0,			/* state 47 */
yycrank+695,	0,		0,			/* state 48 */
yycrank+779,	0,		0,			/* state 49 */
yycrank+789,	0,		0,			/* state 50 */
yycrank+0,	0,		yyvstop+51,		/* state 51 */
yycrank+812,	0,		0,			/* state 52 */
yycrank+822,	0,		yyvstop+53,		/* state 53 */
yycrank+843,	0,		yyvstop+55,		/* state 54 */
yycrank+853,	0,		0,			/* state 55 */
yycrank+863,	0,		0,			/* state 56 */
yycrank+0,	0,		yyvstop+57,		/* state 57 */
yycrank+0,	0,		yyvstop+59,		/* state 58 */
yycrank+0,	0,		yyvstop+61,		/* state 59 */
yycrank+873,	0,		0,			/* state 60 */
yycrank+883,	0,		0,			/* state 61 */
yycrank+893,	0,		yyvstop+63,		/* state 62 */
yycrank+0,	0,		yyvstop+65,		/* state 63 */
yycrank+0,	0,		yyvstop+67,		/* state 64 */
yycrank+0,	0,		yyvstop+69,		/* state 65 */
yycrank+903,	0,		0,			/* state 66 */
yycrank+0,	0,		yyvstop+71,		/* state 67 */
0,	0,	0};
struct yywork *yytop = yycrank+960;
struct yysvf *yybgin = yysvec+1;
char yymatch[] = {
00  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,012 ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
040 ,'!' ,'"' ,'#' ,'#' ,01  ,'#' ,01  ,
01  ,01  ,01  ,01  ,040 ,040 ,'!' ,040 ,
'0' ,'0' ,'0' ,'0' ,'0' ,'0' ,'0' ,'0' ,
'0' ,'0' ,'!' ,'!' ,01  ,01  ,01  ,'!' ,
'#' ,'#' ,'#' ,'#' ,'#' ,'#' ,'#' ,'#' ,
'#' ,'#' ,'#' ,'#' ,'#' ,'#' ,'#' ,'#' ,
'#' ,'#' ,'#' ,'#' ,'#' ,'#' ,'#' ,'#' ,
'#' ,'#' ,'#' ,01  ,040 ,01  ,01  ,01  ,
01  ,'#' ,'#' ,'#' ,'#' ,'#' ,'#' ,'#' ,
'#' ,'#' ,'#' ,'#' ,'#' ,'#' ,'#' ,'#' ,
'#' ,'#' ,'#' ,'#' ,'#' ,'#' ,'#' ,'#' ,
'#' ,'#' ,'#' ,01  ,'|' ,01  ,01  ,01  ,
0};
char yyextra[] = {
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0};
/*	ncform	4.10		*/

int yylineno =1;
# define YYU(x) x
# define NLSTATE yyprevious=YYNEWLINE
char yytext[YYLMAX];
struct yysvf *yylstate [YYLMAX], **yylsp, **yyolsp;
char yysbuf[YYLMAX];
char *yysptr = yysbuf;
int *yyfnd;
extern struct yysvf *yyestate;
int yyprevious = YYNEWLINE;
yylook(){
	register struct yysvf *yystate, **lsp;
	register struct yywork *yyt;
	struct yysvf *yyz;
	int yych;
	struct yywork *yyr;
# ifdef LEXDEBUG
	int debug;
# endif
	char *yylastch;
	/* start off machines */
# ifdef LEXDEBUG
	debug = 0;
# endif
	if (!yymorfg)
		yylastch = yytext;
	else {
		yymorfg=0;
		yylastch = yytext+yyleng;
		}
	for(;;){
		lsp = yylstate;
		yyestate = yystate = yybgin;
		if (yyprevious==YYNEWLINE) yystate++;
		for (;;){
# ifdef LEXDEBUG
			if(debug)fprintf(yyout,"state %d\n",yystate-yysvec-1);
# endif
			yyt = yystate->yystoff;
			if(yyt == yycrank){		/* may not be any transitions */
				yyz = yystate->yyother;
				if(yyz == 0)break;
				if(yyz->yystoff == yycrank)break;
				}
			*yylastch++ = yych = input();
		tryagain:
# ifdef LEXDEBUG
			if(debug){
				fprintf(yyout,"char ");
				allprint(yych);
				putchar('\n');
				}
# endif
			yyr = yyt;
			if ( (int)yyt > (int)yycrank){
				yyt = yyr + yych;
				if (yyt <= yytop && yyt->verify+yysvec == yystate){
					if(yyt->advance+yysvec == YYLERR)	/* error transitions */
						{unput(*--yylastch);break;}
					*lsp++ = yystate = yyt->advance+yysvec;
					goto contin;
					}
				}
# ifdef YYOPTIM
			else if((int)yyt < (int)yycrank) {		/* r < yycrank */
				yyt = yyr = yycrank+(yycrank-yyt);
# ifdef LEXDEBUG
				if(debug)fprintf(yyout,"compressed state\n");
# endif
				yyt = yyt + yych;
				if(yyt <= yytop && yyt->verify+yysvec == yystate){
					if(yyt->advance+yysvec == YYLERR)	/* error transitions */
						{unput(*--yylastch);break;}
					*lsp++ = yystate = yyt->advance+yysvec;
					goto contin;
					}
				yyt = yyr + YYU(yymatch[yych]);
# ifdef LEXDEBUG
				if(debug){
					fprintf(yyout,"try fall back character ");
					allprint(YYU(yymatch[yych]));
					putchar('\n');
					}
# endif
				if(yyt <= yytop && yyt->verify+yysvec == yystate){
					if(yyt->advance+yysvec == YYLERR)	/* error transition */
						{unput(*--yylastch);break;}
					*lsp++ = yystate = yyt->advance+yysvec;
					goto contin;
					}
				}
			if ((yystate = yystate->yyother) && (yyt= yystate->yystoff) != yycrank){
# ifdef LEXDEBUG
				if(debug)fprintf(yyout,"fall back to state %d\n",yystate-yysvec-1);
# endif
				goto tryagain;
				}
# endif
			else
				{unput(*--yylastch);break;}
		contin:
# ifdef LEXDEBUG
			if(debug){
				fprintf(yyout,"state %d char ",yystate-yysvec-1);
				allprint(yych);
				putchar('\n');
				}
# endif
			;
			}
# ifdef LEXDEBUG
		if(debug){
			fprintf(yyout,"stopped at %d with ",*(lsp-1)-yysvec-1);
			allprint(yych);
			putchar('\n');
			}
# endif
		while (lsp-- > yylstate){
			*yylastch-- = 0;
			if (*lsp != 0 && (yyfnd= (*lsp)->yystops) && *yyfnd > 0){
				yyolsp = lsp;
				if(yyextra[*yyfnd]){		/* must backup */
					while(yyback((*lsp)->yystops,-*yyfnd) != 1 && lsp > yylstate){
						lsp--;
						unput(*yylastch--);
						}
					}
				yyprevious = YYU(*yylastch);
				yylsp = lsp;
				yyleng = yylastch-yytext+1;
				yytext[yyleng] = 0;
# ifdef LEXDEBUG
				if(debug){
					fprintf(yyout,"\nmatch ");
					sprint(yytext);
					fprintf(yyout," action %d\n",*yyfnd);
					}
# endif
				return(*yyfnd++);
				}
			unput(*yylastch);
			}
		if (yytext[0] == 0  /* && feof(yyin) */)
			{
			yysptr=yysbuf;
			return(0);
			}
		yyprevious = yytext[0] = input();
		if (yyprevious>0)
			output(yyprevious);
		yylastch=yytext;
# ifdef LEXDEBUG
		if(debug)putchar('\n');
# endif
		}
	}
yyback(p, m)
	int *p;
{
if (p==0) return(0);
while (*p)
	{
	if (*p++ == m)
		return(1);
	}
return(0);
}
	/* the following are only used in the lex library */
yyinput(){
	return(input());
	}
yyoutput(c)
  int c; {
	output(c);
	}
yyunput(c)
   int c; {
	unput(c);
	}

#define printable(c)  ((c)>040 && (c) < 0177)

allprint(c)
  char c; {
	switch(c){
		case 014:
			printf("\\f");
			break;
		case '\n':
			printf("\\n");
			break;
		case '\t':
			printf("\\t");
			break;
		case '\b':
			printf("\\b");
			break;
		case ' ':
			printf("\\\bb");
			break;
		default:
			if(!printable(c)){
				printf("\\%-3o",c);
				}
			else
				putchar(c);
			break;
		}
	return;
	}

sprint(s)
char *s;
{
	fprintf(yyout," %s ",s);
}

yywrap()
{
	return -1;
}

/*** $#$#$#$#$#$#$#$#$#$#$#

	yylexmain eh uma funcao criada para fazer a interface entre
	a classe LBSC_Paser e a funcao yylex, deste arquivo.
	As variaveis globais _szStr, _lStrPos e _iStatus
	tambem foram criadas para este proposito e sao atualizadas
	pelas funcoes que tratam os tokens (Handle *) encontrados por yylex.
***/
int
yylexmain( char *szStr, long *plStrPos, char *szReturnTerm, int *piReturnStatus )
{

	_szStr = szStr;
	_lStrPos = (*plStrPos);
	yylex();
	strcpy( szReturnTerm, yytext );
	(*piReturnStatus) = _iStatus;
	(*plStrPos) = _lStrPos;
	return( 0 );
}


void
main( int argc, char* argv[] )
{
	char	szTerminator[] = "\x15\x00\xA4\xD0\x2F\xA5\xE0\x3D\xA6\x08\x07\xA7\x08\x07\xA8\xA0\x05\xA9\xA0\x05\xAA";
	char	szBuffer[ 15000 ];
	char	*szPt;
	int		iStat = 0;
	long	lPos = 0;
	char	szRetStr[ 1024 ];
		
	
		
	if( argc > 1 ) {
		int i;
		int NaoAchou = TRUE;
		int NumZeros;

		yyin = fopen( argv[1], "rt" );
		fread( szBuffer, 11264, 1, yyin ); // coloca o arquivo de entrada num buffer na memoria.
		_szFinal = memchr( szBuffer, 0x15, 11264 ); // Tenta encontrar o primeiro caracter do string de final de texto.
		while( _szFinal ){
			if( memcmp( _szFinal, szTerminator, 21 ) == 0 ){
				break;
			}
			if( (_szFinal-szBuffer) > 0 ){
				_szFinal = memchr( _szFinal+1, 0x15, 11264 - (_szFinal-szBuffer) );
			} else {
				_szFinal = NULL;
			}
		}
		if( !_szFinal ){
			printf( "FUDEU! Nao achou o final...\n" );
			_szFinal = szBuffer + 11264;
		}
		
		// Vai procurar 92 zeros, que eh a quantidade de zeros antes do texto comecar.
		
	
		for( i = 0; i < 15000; i++ ) {
			
			NumZeros = 0;
			while( ( szBuffer[i] == '\x00' ) && ( NaoAchou ) ) {
				NumZeros++;
				if( NumZeros == 92 ) {
					NaoAchou = FALSE;
					
				}
				i++;
			}
			if( !NaoAchou ) {
				break;
			}
		}
		if( NaoAchou ) {
			printf( "FUDEU! Nao achou os zeros...\n" );
		}
		else {
			szPt = szBuffer + i; // Comeca a ler a partir de depois dos zeros.
			while( iStat != PROCESS_END ){
				yylexmain( szPt, &lPos, szRetStr, &iStat );
				printf( "Achei %s\n", szRetStr );
			}
			printf( "Terminou!!\n" );
		}
	
	}
	else {
		printf( "Digite o nome do arquivo, seu besta!\n" );
	}
	return;
} 
