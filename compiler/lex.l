%{
#include<stdio.h>
#include "def.h"

extern int yyline;     //全局变量行数
#include <stdlib.h>     // For strtol
#include "AST.h"
%}
 
intnum [1-9][0-9]*|0[0-7]*|(0x|0X)[0-9a-fA-F]*
floatnum [0-9]+([Ee][+-]?[0-9]+)?([fFlL])?
id [a-zA-Z_][a-zA-Z0-9_]*
 
%s COMMENT        
%s LINECOMMENT    




%%
"/*"		{BEGIN(COMMENT);}
<COMMENT>"*/"  {BEGIN(INITIAL);}
<COMMENT>([^*]|\n)+|.
<COMMENT><<EOF>>   {printf("Unterminated comment\n"); return 0;}
"//" {BEGIN(LINECOMMENT);}
<LINECOMMENT>.*
<LINECOMMENT>\n {BEGIN(INITIAL);}
<LINECOMMENT><<EOF>> {BEGIN(INITIAL);}
 
[ \t]					{;}		//忽略空白符
\n					    {yylineno++;}    //匹配到换行符，行数+1
"int"					{yylval = std::make_shared<SimpleTokenNode>(INT); return (INT);} //添加副作用，输出以供我们调试。
"float"					{yylval = std::make_shared<SimpleTokenNode>(FLOAT); return (FLOAT);}
"const"                 {return (CONST);}
"void"                	{return (VOID);}
"break"					{return (BREAK);}
"continue"				{return (CONTINUE);}
"return"				{return (RETURN);}
"if" 					{return (IF);}
"else" 					{return (ELSE);}
"while" 				{return (WHILE);}
{intnum} {
    if (yytext[0] == '0' && (yytext[1] == 'x' || yytext[1] == 'X')) {
        // Hexadecimal
        yylval = std::make_shared<ConstIntNode>(strtol(yytext, NULL, 16));
    } else if (yytext[0] == '0') {
        // Octal
        yylval = std::make_shared<ConstIntNode>(strtol(yytext, NULL, 8));
    } else {
        // Decimal
        yylval = std::make_shared<ConstIntNode>(strtol(yytext, NULL, 10));
    }
    return (INTNUM);
}
{floatnum} {
    yylval = std::make_shared<ConstFloatNode>(strtod(yytext, NULL)); // Convert to double
    return (FLOATNUM);
}
"<"					{yylval = std::make_shared<SimpleTokenNode>(LT); return (LT);}
"<="				{yylval = std::make_shared<SimpleTokenNode>(LE); return (LE);}
">"					{yylval = std::make_shared<SimpleTokenNode>(GT); return (GT);}
">="				{yylval = std::make_shared<SimpleTokenNode>(GE); return (GE);}
"=="				{yylval = std::make_shared<SimpleTokenNode>(EQ); return (EQ);}
"!="				{yylval = std::make_shared<SimpleTokenNode>(NE); return (NE);}
"="					{return (ASSIGN);}
"+"					{yylval = std::make_shared<SimpleTokenNode>(ADD); return (ADD);}
"-"					{yylval = std::make_shared<SimpleTokenNode>(SUB); return (SUB);}
"*"					{yylval = std::make_shared<SimpleTokenNode>(MUL); return (MUL);}
"/"					{yylval = std::make_shared<SimpleTokenNode>(DIV); return (DIV);}
"%"					{yylval = std::make_shared<SimpleTokenNode>(MOD); return (MOD);}
"!"					{yylval = std::make_shared<SimpleTokenNode>(NOT); return (NOT);}
"&&"				{yylval = std::make_shared<SimpleTokenNode>(AND); return (AND);}
"||"				{yylval = std::make_shared<SimpleTokenNode>(OR); return (OR);}
";"					{return (SEMI);}
":"					{return (COLON);}
","					{return (COMMA);}
"("					{return (L);}
")"					{return (R);}
"{"					{return (OB);}
"}"					{return (CB);}
"["					{return (LB);}
"]"					{return (RB);}
{id}				{yylval = std::make_shared<IdentifierNode>(yytext); return (Ident);}


%%
int yywrap(){    //文件结束处理函数，如果返回值为1就停止解析。可以用来解析多个文件。
    return 1;
}