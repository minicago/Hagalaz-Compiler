/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 3 "yacc.y"
 
    #include <iostream>
    #include<ctype.h>
    #include "def.h"
    #include "AST.h"
    #define __SHOW__BISON__ACTION__
    #ifdef __SHOW__BISON__ACTION__ 
        #define BISON_LOG(X) printf(X)
    #else
        #define BISON_LOG(X)  
    #endif
    int yylex();			//调用词法分析器，每次返回一个TOKEN
    int yyerror(char* s);   
    extern int line_no;
    extern yytokentype decl_type;
    extern std::shared_ptr<Node> AST_root;

#line 89 "y.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    ASSIGN = 258,                  /* "="  */
    LT = 259,                      /* LT  */
    LE = 260,                      /* LE  */
    GT = 261,                      /* GT  */
    GE = 262,                      /* GE  */
    EQ = 263,                      /* EQ  */
    NE = 264,                      /* NE  */
    ADD = 265,                     /* "+"  */
    SUB = 266,                     /* "-"  */
    MUL = 267,                     /* "*"  */
    DIV = 268,                     /* "/"  */
    MOD = 269,                     /* "%"  */
    NOT = 270,                     /* "!"  */
    SEMI = 271,                    /* ";"  */
    COLON = 272,                   /* ":"  */
    COMMA = 273,                   /* ","  */
    OB = 274,                      /* "{"  */
    CB = 275,                      /* "}"  */
    LB = 276,                      /* "["  */
    RB = 277,                      /* "]"  */
    L = 278,                       /* "("  */
    R = 279,                       /* ")"  */
    CONST = 280,                   /* CONST  */
    IF = 281,                      /* IF  */
    ELSE = 282,                    /* ELSE  */
    WHILE = 283,                   /* WHILE  */
    BREAK = 284,                   /* BREAK  */
    RETURN = 285,                  /* RETURN  */
    CONTINUE = 286,                /* CONTINUE  */
    AND = 287,                     /* AND  */
    OR = 288,                      /* OR  */
    const_String_Val = 289,        /* const_String_Val  */
    Ident = 290,                   /* Ident  */
    INT = 291,                     /* INT  */
    FLOAT = 292,                   /* FLOAT  */
    VOID = 293,                    /* VOID  */
    const_Int_Val = 294,           /* const_Int_Val  */
    INTNUM = 295,                  /* INTNUM  */
    const_Float_Val = 296,         /* const_Float_Val  */
    FLOATNUM = 297                 /* FLOATNUM  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;

int yyparse (void);


#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_ASSIGN = 3,                     /* "="  */
  YYSYMBOL_LT = 4,                         /* LT  */
  YYSYMBOL_LE = 5,                         /* LE  */
  YYSYMBOL_GT = 6,                         /* GT  */
  YYSYMBOL_GE = 7,                         /* GE  */
  YYSYMBOL_EQ = 8,                         /* EQ  */
  YYSYMBOL_NE = 9,                         /* NE  */
  YYSYMBOL_ADD = 10,                       /* "+"  */
  YYSYMBOL_SUB = 11,                       /* "-"  */
  YYSYMBOL_MUL = 12,                       /* "*"  */
  YYSYMBOL_DIV = 13,                       /* "/"  */
  YYSYMBOL_MOD = 14,                       /* "%"  */
  YYSYMBOL_NOT = 15,                       /* "!"  */
  YYSYMBOL_SEMI = 16,                      /* ";"  */
  YYSYMBOL_COLON = 17,                     /* ":"  */
  YYSYMBOL_COMMA = 18,                     /* ","  */
  YYSYMBOL_OB = 19,                        /* "{"  */
  YYSYMBOL_CB = 20,                        /* "}"  */
  YYSYMBOL_LB = 21,                        /* "["  */
  YYSYMBOL_RB = 22,                        /* "]"  */
  YYSYMBOL_L = 23,                         /* "("  */
  YYSYMBOL_R = 24,                         /* ")"  */
  YYSYMBOL_CONST = 25,                     /* CONST  */
  YYSYMBOL_IF = 26,                        /* IF  */
  YYSYMBOL_ELSE = 27,                      /* ELSE  */
  YYSYMBOL_WHILE = 28,                     /* WHILE  */
  YYSYMBOL_BREAK = 29,                     /* BREAK  */
  YYSYMBOL_RETURN = 30,                    /* RETURN  */
  YYSYMBOL_CONTINUE = 31,                  /* CONTINUE  */
  YYSYMBOL_AND = 32,                       /* AND  */
  YYSYMBOL_OR = 33,                        /* OR  */
  YYSYMBOL_const_String_Val = 34,          /* const_String_Val  */
  YYSYMBOL_Ident = 35,                     /* Ident  */
  YYSYMBOL_INT = 36,                       /* INT  */
  YYSYMBOL_FLOAT = 37,                     /* FLOAT  */
  YYSYMBOL_VOID = 38,                      /* VOID  */
  YYSYMBOL_const_Int_Val = 39,             /* const_Int_Val  */
  YYSYMBOL_INTNUM = 40,                    /* INTNUM  */
  YYSYMBOL_const_Float_Val = 41,           /* const_Float_Val  */
  YYSYMBOL_FLOATNUM = 42,                  /* FLOATNUM  */
  YYSYMBOL_YYACCEPT = 43,                  /* $accept  */
  YYSYMBOL_CompUnit = 44,                  /* CompUnit  */
  YYSYMBOL_Decl = 45,                      /* Decl  */
  YYSYMBOL_ConstDecl = 46,                 /* ConstDecl  */
  YYSYMBOL_47_1 = 47,                      /* $@1  */
  YYSYMBOL_BType = 48,                     /* BType  */
  YYSYMBOL_ConstDef = 49,                  /* ConstDef  */
  YYSYMBOL_InitVal = 50,                   /* InitVal  */
  YYSYMBOL_InitValGroup = 51,              /* InitValGroup  */
  YYSYMBOL_VarDecl = 52,                   /* VarDecl  */
  YYSYMBOL_53_2 = 53,                      /* $@2  */
  YYSYMBOL_VarDefGroup = 54,               /* VarDefGroup  */
  YYSYMBOL_VarDef = 55,                    /* VarDef  */
  YYSYMBOL_ArrayList = 56,                 /* ArrayList  */
  YYSYMBOL_FuncDef = 57,                   /* FuncDef  */
  YYSYMBOL_FuncFParams = 58,               /* FuncFParams  */
  YYSYMBOL_FuncFParam = 59,                /* FuncFParam  */
  YYSYMBOL_Block = 60,                     /* Block  */
  YYSYMBOL_BlockGroup = 61,                /* BlockGroup  */
  YYSYMBOL_BlockItem = 62,                 /* BlockItem  */
  YYSYMBOL_Stmt = 63,                      /* Stmt  */
  YYSYMBOL_Exp = 64,                       /* Exp  */
  YYSYMBOL_Cond = 65,                      /* Cond  */
  YYSYMBOL_LVal = 66,                      /* LVal  */
  YYSYMBOL_Number = 67,                    /* Number  */
  YYSYMBOL_PrimaryExp = 68,                /* PrimaryExp  */
  YYSYMBOL_UnaryExp = 69,                  /* UnaryExp  */
  YYSYMBOL_UnaryOp = 70,                   /* UnaryOp  */
  YYSYMBOL_FuncParamsGroup = 71,           /* FuncParamsGroup  */
  YYSYMBOL_MulExp = 72,                    /* MulExp  */
  YYSYMBOL_AddExp = 73,                    /* AddExp  */
  YYSYMBOL_RelExp = 74,                    /* RelExp  */
  YYSYMBOL_EqExp = 75,                     /* EqExp  */
  YYSYMBOL_LAndExp = 76,                   /* LAndExp  */
  YYSYMBOL_LOrExp = 77                     /* LOrExp  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  12
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   243

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  43
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  35
/* YYNRULES -- Number of rules.  */
#define YYNRULES  91
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  160

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   297


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    63,    63,    69,    75,    81,    88,    91,    95,    95,
     103,   109,   112,   115,   119,   123,   128,   131,   135,   140,
     144,   150,   150,   158,   162,   168,   171,   174,   177,   182,
     186,   192,   199,   208,   212,   218,   221,   224,   229,   232,
     237,   241,   247,   249,   253,   257,   261,   265,   269,   273,
     277,   281,   285,   289,   293,   298,   303,   308,   311,   316,
     318,   322,   326,   329,   333,   336,   340,   344,   349,   352,
     355,   359,   364,   370,   373,   377,   381,   386,   389,   393,
     398,   401,   405,   409,   413,   418,   420,   423,   428,   430,
     435,   437
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "\"=\"", "LT", "LE",
  "GT", "GE", "EQ", "NE", "\"+\"", "\"-\"", "\"*\"", "\"/\"", "\"%\"",
  "\"!\"", "\";\"", "\":\"", "\",\"", "\"{\"", "\"}\"", "\"[\"", "\"]\"",
  "\"(\"", "\")\"", "CONST", "IF", "ELSE", "WHILE", "BREAK", "RETURN",
  "CONTINUE", "AND", "OR", "const_String_Val", "Ident", "INT", "FLOAT",
  "VOID", "const_Int_Val", "INTNUM", "const_Float_Val", "FLOATNUM",
  "$accept", "CompUnit", "Decl", "ConstDecl", "$@1", "BType", "ConstDef",
  "InitVal", "InitValGroup", "VarDecl", "$@2", "VarDefGroup", "VarDef",
  "ArrayList", "FuncDef", "FuncFParams", "FuncFParam", "Block",
  "BlockGroup", "BlockItem", "Stmt", "Exp", "Cond", "LVal", "Number",
  "PrimaryExp", "UnaryExp", "UnaryOp", "FuncParamsGroup", "MulExp",
  "AddExp", "RelExp", "EqExp", "LAndExp", "LOrExp", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-130)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     126,     0,  -130,  -130,  -130,     3,  -130,     8,   -26,  -130,
    -130,  -130,  -130,  -130,  -130,    22,    37,    47,    22,    11,
    -130,    48,    21,    45,  -130,    72,    64,   201,    49,    77,
      83,   -11,  -130,    64,    55,  -130,    47,  -130,  -130,  -130,
    -130,    58,   201,    82,  -130,  -130,  -130,  -130,  -130,  -130,
    -130,  -130,   201,    78,    56,    99,    64,   201,    97,  -130,
     103,     0,    77,  -130,    64,  -130,  -130,  -130,    91,   112,
     173,   117,  -130,   201,   201,   201,   201,   201,  -130,  -130,
     120,  -130,  -130,   121,   124,   127,   191,   132,  -130,  -130,
    -130,   130,  -130,  -130,   136,   151,   135,  -130,  -130,  -130,
      64,  -130,  -130,  -130,  -130,    -8,  -130,  -130,  -130,    78,
      78,  -130,   201,   201,  -130,  -130,   153,  -130,  -130,  -130,
    -130,   201,   150,  -130,   201,  -130,   152,    56,   213,    13,
     143,   144,   156,  -130,   165,   117,  -130,   163,   201,   201,
     201,   201,   201,   201,   201,   201,   163,  -130,   158,    56,
      56,    56,    56,   213,   213,    13,   143,  -130,   163,  -130
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       0,     0,    11,    12,    13,     0,     4,     6,     0,     7,
       2,     8,     1,     5,     3,     0,     0,     0,     0,     0,
      10,     0,    25,     0,    23,     0,     0,     0,     0,     0,
       0,     0,    33,     0,    27,    22,     0,     9,    68,    69,
      70,     0,     0,    57,    59,    60,    15,    16,    62,    63,
      64,    73,     0,    77,    55,     0,     0,     0,     0,    31,
      35,     0,     0,    26,     0,    24,    17,    19,     0,     0,
       0,    58,    67,     0,     0,     0,     0,     0,    29,    14,
       0,    45,    38,     0,     0,     0,     0,     0,    42,    21,
      47,     0,    40,    43,     0,    62,     0,    34,    32,    28,
       0,    18,    61,    65,    71,     0,    74,    75,    76,    78,
      79,    30,     0,     0,    51,    53,     0,    52,    39,    41,
      46,     0,    36,    20,     0,    66,     0,    80,    85,    88,
      90,    56,     0,    54,     0,    37,    72,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    44,    48,    81,
      83,    82,    84,    86,    87,    89,    91,    50,     0,    49
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -130,  -130,     6,  -130,  -130,     4,   169,   -29,  -130,  -130,
    -130,  -130,   154,   -20,   190,  -130,   138,    -9,  -130,   109,
    -129,   -27,    96,   -57,  -130,  -130,   -19,  -130,  -130,    38,
     -94,   -13,    60,    65,  -130
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_uint8 yydefgoto[] =
{
       0,     5,    88,     7,    18,     8,    20,    46,    68,     9,
      17,    23,    24,    28,    10,    31,    32,    90,    91,    92,
      93,    47,   126,    48,    49,    50,    51,    52,   105,    53,
      54,   128,   129,   130,   131
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      55,    95,    34,    12,    63,    11,     6,    61,   148,    16,
     124,    13,    67,    62,    26,    69,   125,   157,   127,   127,
      59,   142,   143,    71,    33,    30,    15,    79,     1,   159,
      80,    94,    27,    72,    95,    99,     2,     3,     4,     2,
       3,     4,    27,   104,   149,   150,   151,   152,   127,   127,
     127,   127,    56,    98,   106,   107,   108,    19,    64,   116,
      21,    35,    89,    36,    94,    30,    76,    77,    38,    39,
      57,   123,    29,    40,    38,    39,    57,    41,    66,    40,
      95,    42,    22,    41,     2,     3,     4,    42,    37,    95,
      73,    74,    75,    43,   134,    89,    58,   136,    44,    43,
      45,    95,   135,    27,    44,    70,    45,    38,    39,   100,
      94,   101,    40,    81,   109,   110,    58,    82,    60,    94,
      42,    78,     1,    83,    96,    84,    85,    86,    87,   153,
     154,    94,    43,     2,     3,     4,   102,    44,    57,    45,
      38,    39,   111,   114,   112,    40,    81,   113,   117,    58,
     118,     1,   120,    42,   121,     1,    83,   122,    84,    85,
      86,    87,     2,     3,     4,    43,     2,     3,     4,   133,
      44,    27,    45,    38,    39,   144,   137,   145,    40,    81,
     146,   147,    58,    38,    39,   158,    42,    25,    40,    83,
      65,    84,    85,    86,    87,    14,    42,   103,    43,    97,
     119,    38,    39,    44,   155,    45,    40,   115,    43,   132,
     156,    38,    39,    44,    42,    45,    40,   138,   139,   140,
     141,     0,     0,     0,    42,     0,    43,     0,     0,     0,
       0,    44,     0,    45,     0,     0,    43,     0,     0,     0,
       0,    44,     0,    45
};

static const yytype_int16 yycheck[] =
{
      27,    58,    22,     0,    33,     1,     0,    18,   137,    35,
      18,     5,    41,    24,     3,    42,    24,   146,   112,   113,
      29,     8,     9,    43,     3,    21,    18,    56,    25,   158,
      57,    58,    21,    52,    91,    64,    36,    37,    38,    36,
      37,    38,    21,    70,   138,   139,   140,   141,   142,   143,
     144,   145,     3,    62,    73,    74,    75,    35,     3,    86,
      23,    16,    58,    18,    91,    61,    10,    11,    10,    11,
      21,   100,    24,    15,    10,    11,    21,    19,    20,    15,
     137,    23,    35,    19,    36,    37,    38,    23,    16,   146,
      12,    13,    14,    35,   121,    91,    19,   124,    40,    35,
      42,   158,   122,    21,    40,    23,    42,    10,    11,    18,
     137,    20,    15,    16,    76,    77,    19,    20,    35,   146,
      23,    22,    25,    26,    21,    28,    29,    30,    31,   142,
     143,   158,    35,    36,    37,    38,    24,    40,    21,    42,
      10,    11,    22,    16,    23,    15,    16,    23,    16,    19,
      20,    25,    16,    23,     3,    25,    26,    22,    28,    29,
      30,    31,    36,    37,    38,    35,    36,    37,    38,    16,
      40,    21,    42,    10,    11,    32,    24,    33,    15,    16,
      24,    16,    19,    10,    11,    27,    23,    18,    15,    26,
      36,    28,    29,    30,    31,     5,    23,    24,    35,    61,
      91,    10,    11,    40,   144,    42,    15,    16,    35,   113,
     145,    10,    11,    40,    23,    42,    15,     4,     5,     6,
       7,    -1,    -1,    -1,    23,    -1,    35,    -1,    -1,    -1,
      -1,    40,    -1,    42,    -1,    -1,    35,    -1,    -1,    -1,
      -1,    40,    -1,    42
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,    25,    36,    37,    38,    44,    45,    46,    48,    52,
      57,    48,     0,    45,    57,    18,    35,    53,    47,    35,
      49,    23,    35,    54,    55,    49,     3,    21,    56,    24,
      48,    58,    59,     3,    56,    16,    18,    16,    10,    11,
      15,    19,    23,    35,    40,    42,    50,    64,    66,    67,
      68,    69,    70,    72,    73,    64,     3,    21,    19,    60,
      35,    18,    24,    50,     3,    55,    20,    50,    51,    64,
      23,    56,    69,    12,    13,    14,    10,    11,    22,    50,
      64,    16,    20,    26,    28,    29,    30,    31,    45,    48,
      60,    61,    62,    63,    64,    66,    21,    59,    60,    50,
      18,    20,    24,    24,    64,    71,    69,    69,    69,    72,
      72,    22,    23,    23,    16,    16,    64,    16,    20,    62,
      16,     3,    22,    50,    18,    24,    65,    73,    74,    75,
      76,    77,    65,    16,    64,    56,    64,    24,     4,     5,
       6,     7,     8,     9,    32,    33,    24,    16,    63,    73,
      73,    73,    73,    74,    74,    75,    76,    63,    27,    63
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    43,    44,    44,    44,    44,    45,    45,    47,    46,
      46,    48,    48,    48,    49,    49,    50,    50,    50,    51,
      51,    53,    52,    54,    54,    55,    55,    55,    55,    56,
      56,    57,    57,    58,    58,    59,    59,    59,    60,    60,
      61,    61,    62,    62,    63,    63,    63,    63,    63,    63,
      63,    63,    63,    63,    63,    64,    65,    66,    66,    67,
      67,    68,    68,    68,    69,    69,    69,    69,    70,    70,
      70,    71,    71,    72,    72,    72,    72,    73,    73,    73,
      74,    74,    74,    74,    74,    75,    75,    75,    76,    76,
      77,    77
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     1,     2,     1,     1,     0,     5,
       3,     1,     1,     1,     4,     3,     1,     2,     3,     1,
       3,     0,     4,     1,     3,     1,     3,     2,     4,     3,
       4,     5,     6,     1,     3,     2,     4,     5,     2,     3,
       1,     2,     1,     1,     4,     1,     2,     1,     5,     7,
       5,     2,     2,     2,     3,     1,     1,     1,     2,     1,
       1,     3,     1,     1,     1,     3,     4,     2,     1,     1,
       1,     1,     3,     1,     3,     3,     3,     1,     3,     3,
       1,     3,     3,     3,     3,     1,     3,     3,     1,     3,
       1,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF

/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)


/* YYLOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

# ifndef YYLOCATION_PRINT

#  if defined YY_LOCATION_PRINT

   /* Temporary convenience wrapper in case some people defined the
      undocumented and private YY_LOCATION_PRINT macros.  */
#   define YYLOCATION_PRINT(File, Loc)  YY_LOCATION_PRINT(File, *(Loc))

#  elif defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
}

#   define YYLOCATION_PRINT  yy_location_print_

    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT(File, Loc)  YYLOCATION_PRINT(File, &(Loc))

#  else

#   define YYLOCATION_PRINT(File, Loc) ((void) 0)
    /* Temporary convenience wrapper in case some people defined the
       undocumented and private YY_LOCATION_PRINT macros.  */
#   define YY_LOCATION_PRINT  YYLOCATION_PRINT

#  endif
# endif /* !defined YYLOCATION_PRINT */


# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  YY_USE (yylocationp);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  YYLOCATION_PRINT (yyo, yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yykind, yyvaluep, yylocationp);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)],
                       &(yylsp[(yyi + 1) - (yynrhs)]));
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YY_USE (yyvaluep);
  YY_USE (yylocationp);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

    /* The location stack: array, bottom, top.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls = yylsa;
    YYLTYPE *yylsp = yyls;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

  /* The locations where the error started and ended.  */
  YYLTYPE yyerror_range[3];



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  yylsp[0] = yylloc;
  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      yyerror_range[1] = yylloc;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* CompUnit: FuncDef  */
#line 63 "yacc.y"
                  { 
            BISON_LOG("CompUnit -> FuncDef\n");
            yyval = std::make_shared<CompUnitNode>();
            AST_root = yyval;
            std::dynamic_pointer_cast<CompUnitNode>(yyval)->addDef(yyvsp[0]);
        }
#line 1493 "y.tab.c"
    break;

  case 3: /* CompUnit: CompUnit FuncDef  */
#line 69 "yacc.y"
                           {
            BISON_LOG("CompUnit -> CompUnit FuncDef\n");
            yyval = yyvsp[-1];
            AST_root = yyval;
            std::dynamic_pointer_cast<CompUnitNode>(yyval)->addDef(yyvsp[0]);
        }
#line 1504 "y.tab.c"
    break;

  case 4: /* CompUnit: Decl  */
#line 75 "yacc.y"
               {
            BISON_LOG("CompUnit -> Decl\n");
            yyval = std::make_shared<CompUnitNode>();
            AST_root = yyval;
            std::dynamic_pointer_cast<CompUnitNode>(yyval)->addDef((yyvsp[0]));
        }
#line 1515 "y.tab.c"
    break;

  case 5: /* CompUnit: CompUnit Decl  */
#line 81 "yacc.y"
                        {
            BISON_LOG("CompUnit -> CompUnit Decl\n");
            yyval = yyvsp[-1];
            AST_root = yyval;
            std::dynamic_pointer_cast<CompUnitNode>(yyval)->addDef(yyvsp[0]);
        }
#line 1526 "y.tab.c"
    break;

  case 6: /* Decl: ConstDecl  */
#line 88 "yacc.y"
                {
        BISON_LOG("Decl -> ConstDecl\n");
     }
#line 1534 "y.tab.c"
    break;

  case 7: /* Decl: VarDecl  */
#line 91 "yacc.y"
               {
        BISON_LOG("Decl -> VarDecl\n");
     }
#line 1542 "y.tab.c"
    break;

  case 8: /* $@1: %empty  */
#line 95 "yacc.y"
                       {
            BISON_LOG("ConstDecl -> CONST BType\n");
            decl_type = std::dynamic_pointer_cast<SimpleTokenNode>(yyvsp[0])->getType();
        }
#line 1551 "y.tab.c"
    break;

  case 9: /* ConstDecl: CONST BType $@1 ConstDef ";"  */
#line 98 "yacc.y"
                       {
            BISON_LOG("ConstDecl -> CONST BType ConstDef ;\n");
            yyval = std::make_shared<StmtListNode>();
            std::dynamic_pointer_cast<StmtListNode>(yyval)->addStmt(yyvsp[-1]);
        }
#line 1561 "y.tab.c"
    break;

  case 10: /* ConstDecl: ConstDecl "," ConstDef  */
#line 103 "yacc.y"
                                   {
            BISON_LOG("ConstDecl -> ConstDecl , ConstDef\n");
            yyval = yyvsp[-2];
            std::dynamic_pointer_cast<StmtListNode>(yyval)->addStmt(yyvsp[0]);
          }
#line 1571 "y.tab.c"
    break;

  case 11: /* BType: INT  */
#line 109 "yacc.y"
           {
        BISON_LOG("BType -> INT\n");
     }
#line 1579 "y.tab.c"
    break;

  case 12: /* BType: FLOAT  */
#line 112 "yacc.y"
             {
        BISON_LOG("BType -> FLOAT\n");
     }
#line 1587 "y.tab.c"
    break;

  case 13: /* BType: VOID  */
#line 115 "yacc.y"
            {
        BISON_LOG("BType -> VOID\n");
     }
#line 1595 "y.tab.c"
    break;

  case 14: /* ConstDef: Ident ArrayList "=" InitVal  */
#line 119 "yacc.y"
                                         {
            BISON_LOG("ConstDef -> Ident ArrayList ASSIGN InitVal\n");
            yyval = std::make_shared<DeclNode>(true, decl_type, std::dynamic_pointer_cast<IdentifierNode>(yyvsp[-3])->id, yyvsp[-2], yyvsp[0]);
        }
#line 1604 "y.tab.c"
    break;

  case 15: /* ConstDef: Ident "=" InitVal  */
#line 123 "yacc.y"
                               {
            BISON_LOG("ConstDef -> Ident ASSIGN InitVal\n");
            yyval = std::make_shared<DeclNode>(true, decl_type, std::dynamic_pointer_cast<IdentifierNode>(yyvsp[-2])->id, nullptr, yyvsp[0]);
        }
#line 1613 "y.tab.c"
    break;

  case 16: /* InitVal: Exp  */
#line 128 "yacc.y"
              {
            BISON_LOG("InitVal -> Exp\n");
        }
#line 1621 "y.tab.c"
    break;

  case 17: /* InitVal: "{" "}"  */
#line 131 "yacc.y"
                  {
            BISON_LOG("InitVal -> { }\n");
            yyval = nullptr;
        }
#line 1630 "y.tab.c"
    break;

  case 18: /* InitVal: "{" InitValGroup "}"  */
#line 135 "yacc.y"
                               {
            BISON_LOG("InitVal -> { InitValGroup }\n");
            yyval = yyvsp[-1];
        }
#line 1639 "y.tab.c"
    break;

  case 19: /* InitValGroup: InitVal  */
#line 140 "yacc.y"
                      {
    BISON_LOG("InitValGroup -> InitVal\n");
    yyval = std::make_shared<VectorNode> ();
    std::dynamic_pointer_cast<VectorNode> (yyval)->addNode(yyvsp[0]);
}
#line 1649 "y.tab.c"
    break;

  case 20: /* InitValGroup: InitValGroup "," InitVal  */
#line 144 "yacc.y"
                            {
    BISON_LOG("InitValGroup -> InitValGroup , InitVal\n");
    yyval = yyvsp[-2];
    std::dynamic_pointer_cast<VectorNode> (yyval)->addNode(yyvsp[0]);    
}
#line 1659 "y.tab.c"
    break;

  case 21: /* $@2: %empty  */
#line 150 "yacc.y"
                {
        BISON_LOG("VarDecl -> BType\n");
        decl_type = std::dynamic_pointer_cast<SimpleTokenNode>(yyvsp[0])->getType();
    }
#line 1668 "y.tab.c"
    break;

  case 22: /* VarDecl: BType $@2 VarDefGroup ";"  */
#line 153 "yacc.y"
                      {
        BISON_LOG("VarDecl -> BType VarDefGroup ;\n");
        yyval = yyvsp[-1]; 
}
#line 1677 "y.tab.c"
    break;

  case 23: /* VarDefGroup: VarDef  */
#line 158 "yacc.y"
                    {
    BISON_LOG("VarDefGroup -> VarDef\n");
    yyval = std::make_shared<StmtListNode>();
    std::dynamic_pointer_cast<StmtListNode>(yyval)->addStmt(yyvsp[0]);
}
#line 1687 "y.tab.c"
    break;

  case 24: /* VarDefGroup: VarDefGroup "," VarDef  */
#line 162 "yacc.y"
                          {
    BISON_LOG("VarDefGroup -> VarDefGroup , VarDef\n");
    yyval = yyvsp[-2];
    std::dynamic_pointer_cast<StmtListNode>(yyval)->addStmt(yyvsp[0]);
}
#line 1697 "y.tab.c"
    break;

  case 25: /* VarDef: Ident  */
#line 168 "yacc.y"
               {
    BISON_LOG("VarDef -> Ident\n");
    yyval = std::make_shared<DeclNode>(false, decl_type, std::dynamic_pointer_cast<IdentifierNode>(yyvsp[0])->id, nullptr, nullptr);
}
#line 1706 "y.tab.c"
    break;

  case 26: /* VarDef: Ident "=" InitVal  */
#line 171 "yacc.y"
                        {
    BISON_LOG("VarDef -> Ident ASSIGN InitVal\n");
    yyval = std::make_shared<DeclNode>(false, decl_type, std::dynamic_pointer_cast<IdentifierNode>(yyvsp[-2])->id, nullptr, yyvsp[0]);
}
#line 1715 "y.tab.c"
    break;

  case 27: /* VarDef: Ident ArrayList  */
#line 174 "yacc.y"
                   {
    BISON_LOG("VarDef -> Ident ArrayList\n");
    yyval = std::make_shared<DeclNode>(false, decl_type, std::dynamic_pointer_cast<IdentifierNode>(yyvsp[-1])->id, yyvsp[0], nullptr);
}
#line 1724 "y.tab.c"
    break;

  case 28: /* VarDef: Ident ArrayList "=" InitVal  */
#line 177 "yacc.y"
                                  {
    BISON_LOG("VarDef -> Ident ArrayList ASSIGN InitVal\n");
    yyval = std::make_shared<DeclNode>(false, decl_type, std::dynamic_pointer_cast<IdentifierNode>(yyvsp[-3])->id, yyvsp[-2], yyvsp[0]);
}
#line 1733 "y.tab.c"
    break;

  case 29: /* ArrayList: "[" Exp "]"  */
#line 182 "yacc.y"
                       {
    BISON_LOG("ArrayList -> [ Exp ]\n");
    yyval = std::make_shared<VectorNode> ();
    std::dynamic_pointer_cast<VectorNode> (yyval)->addNode(yyvsp[-1]);
}
#line 1743 "y.tab.c"
    break;

  case 30: /* ArrayList: ArrayList "[" Exp "]"  */
#line 186 "yacc.y"
                          {
    BISON_LOG("ArrayList -> ArrayList [ Exp ]\n");
    yyval = yyvsp[-3];
    std::dynamic_pointer_cast<VectorNode> (yyval)->addNode(yyvsp[-1]);  
}
#line 1753 "y.tab.c"
    break;

  case 31: /* FuncDef: BType Ident "(" ")" Block  */
#line 192 "yacc.y"
                                    {
    BISON_LOG("FuncDef -> BType Ident ( ) Block\n");
    yyval = std::make_shared<FuncDefNode> (
        std::dynamic_pointer_cast<SimpleTokenNode>(yyvsp[-4])->type,
        std::dynamic_pointer_cast<IdentifierNode>(yyvsp[-3])->id,
        nullptr,
        yyvsp[0] );
}
#line 1766 "y.tab.c"
    break;

  case 32: /* FuncDef: BType Ident "(" FuncFParams ")" Block  */
#line 199 "yacc.y"
                                          {
    BISON_LOG("FuncDef -> BType Ident ( FuncFParams ) Block\n");
    yyval = std::make_shared<FuncDefNode> (
        std::dynamic_pointer_cast<SimpleTokenNode>(yyvsp[-5])->type,
        std::dynamic_pointer_cast<IdentifierNode>(yyvsp[-4])->id,
        yyvsp[-2],
        yyvsp[0] );    
}
#line 1779 "y.tab.c"
    break;

  case 33: /* FuncFParams: FuncFParam  */
#line 208 "yacc.y"
                         {
    BISON_LOG("FuncFParams -> FuncFParam\n");
    yyval = std::make_shared<ParamListNode> ();
    std::dynamic_pointer_cast<ParamListNode> (yyval)->addParam(yyvsp[0]);
}
#line 1789 "y.tab.c"
    break;

  case 34: /* FuncFParams: FuncFParams "," FuncFParam  */
#line 212 "yacc.y"
                               {
    BISON_LOG("FuncFParams -> FuncFParams , FuncFParam\n");
    yyval = yyvsp[-2];
    std::dynamic_pointer_cast<ParamListNode> (yyval)->addParam(yyvsp[0]);
}
#line 1799 "y.tab.c"
    break;

  case 35: /* FuncFParam: BType Ident  */
#line 218 "yacc.y"
                        {
    BISON_LOG("FuncFParam -> BType Ident\n");
    yyval = std::make_shared<ParamNode> (std::dynamic_pointer_cast<SimpleTokenNode>(yyvsp[-1])->type, std::dynamic_pointer_cast<IdentifierNode>(yyvsp[0])->id, false, nullptr);
}
#line 1808 "y.tab.c"
    break;

  case 36: /* FuncFParam: BType Ident "[" "]"  */
#line 221 "yacc.y"
                        {
    BISON_LOG("FuncFParam -> BType Ident [ ]\n");
    yyval = std::make_shared<ParamNode> ( std::dynamic_pointer_cast<SimpleTokenNode>(yyvsp[-3])->type, std::dynamic_pointer_cast<IdentifierNode>(yyvsp[-2])->id, true, nullptr);
}
#line 1817 "y.tab.c"
    break;

  case 37: /* FuncFParam: BType Ident "[" "]" ArrayList  */
#line 224 "yacc.y"
                                  {
    BISON_LOG("FuncFParam -> BType Ident [ ] ArrayList\n");
    yyval = std::make_shared<ParamNode> (std::dynamic_pointer_cast<SimpleTokenNode>(yyvsp[-4])->type, std::dynamic_pointer_cast<IdentifierNode>(yyvsp[-3])->id, true, yyvsp[0]);
}
#line 1826 "y.tab.c"
    break;

  case 38: /* Block: "{" "}"  */
#line 229 "yacc.y"
                {
    BISON_LOG("Block -> { }\n");
    yyval = nullptr;
}
#line 1835 "y.tab.c"
    break;

  case 39: /* Block: "{" BlockGroup "}"  */
#line 232 "yacc.y"
                       {
    BISON_LOG("Block -> { BlockGroup }\n");
    yyval = yyvsp[-1];
}
#line 1844 "y.tab.c"
    break;

  case 40: /* BlockGroup: BlockItem  */
#line 237 "yacc.y"
                      {
    BISON_LOG("BlockGroup -> BlockItem\n");
    yyval = std::make_shared<BlockGroupNode> ();
    std::dynamic_pointer_cast<BlockGroupNode> (yyval)->addBlock(yyvsp[0]);
}
#line 1854 "y.tab.c"
    break;

  case 41: /* BlockGroup: BlockGroup BlockItem  */
#line 241 "yacc.y"
                        {
    BISON_LOG("BlockGroup -> BlockGroup BlockItem\n");
    yyval = yyvsp[-1];
    std::dynamic_pointer_cast<BlockGroupNode> (yyval)->addBlock(yyvsp[0]);
}
#line 1864 "y.tab.c"
    break;

  case 42: /* BlockItem: Decl  */
#line 247 "yacc.y"
                 {
    BISON_LOG("BlockItem -> Decl\n");
}
#line 1872 "y.tab.c"
    break;

  case 43: /* BlockItem: Stmt  */
#line 249 "yacc.y"
         {
    BISON_LOG("BlockItem -> Stmt\n");
}
#line 1880 "y.tab.c"
    break;

  case 44: /* Stmt: LVal "=" Exp ";"  */
#line 253 "yacc.y"
                         {
    BISON_LOG("Stmt -> LVal = Exp ;\n");
    yyval = std::make_shared<AssignNode> (yyvsp[-3], yyvsp[-1]);
}
#line 1889 "y.tab.c"
    break;

  case 45: /* Stmt: ";"  */
#line 257 "yacc.y"
          {
        BISON_LOG("Stmt -> ;\n");
        yyval = nullptr;
    }
#line 1898 "y.tab.c"
    break;

  case 46: /* Stmt: Exp ";"  */
#line 261 "yacc.y"
              {
        BISON_LOG("Stmt -> Exp ;\n");
        yyval = yyvsp[-1];
    }
#line 1907 "y.tab.c"
    break;

  case 47: /* Stmt: Block  */
#line 265 "yacc.y"
            {
        BISON_LOG("Stmt -> Block\n");
        yyval = yyvsp[0];
    }
#line 1916 "y.tab.c"
    break;

  case 48: /* Stmt: IF "(" Cond ")" Stmt  */
#line 269 "yacc.y"
                           {
        BISON_LOG("Stmt -> IF ( Cond ) Stmt\n");
        yyval = std::make_shared<IfElseNode> (yyvsp[-2], yyvsp[0], nullptr);
    }
#line 1925 "y.tab.c"
    break;

  case 49: /* Stmt: IF "(" Cond ")" Stmt ELSE Stmt  */
#line 273 "yacc.y"
                                     {
        BISON_LOG("Stmt -> IF ( Cond ) Stmt ELSE Stmt\n");
        yyval = std::make_shared<IfElseNode> (yyvsp[-4], yyvsp[-2], yyvsp[0]);
    }
#line 1934 "y.tab.c"
    break;

  case 50: /* Stmt: WHILE "(" Cond ")" Stmt  */
#line 277 "yacc.y"
                              {
        BISON_LOG("Stmt -> WHILE ( Cond ) Stmt\n");
        yyval = std::make_shared<WhileNode>(yyvsp[-2], yyvsp[0]);
    }
#line 1943 "y.tab.c"
    break;

  case 51: /* Stmt: BREAK ";"  */
#line 281 "yacc.y"
                {
        BISON_LOG("Stmt -> BREAK ;\n");
        yyval = std::make_shared<BreakNode>();
    }
#line 1952 "y.tab.c"
    break;

  case 52: /* Stmt: CONTINUE ";"  */
#line 285 "yacc.y"
                   {
        BISON_LOG("Stmt -> CONTINUE ;\n");
        yyval = std::make_shared<ContinueNode>();
    }
#line 1961 "y.tab.c"
    break;

  case 53: /* Stmt: RETURN ";"  */
#line 289 "yacc.y"
                 {
        BISON_LOG("Stmt -> RETURN ;\n");
        yyval = std::make_shared<ReturnNode>(nullptr);
    }
#line 1970 "y.tab.c"
    break;

  case 54: /* Stmt: RETURN Exp ";"  */
#line 293 "yacc.y"
                     {
        BISON_LOG("Stmt -> RETURN Exp ;\n");
        yyval = std::make_shared<ReturnNode>(yyvsp[-1]);
    }
#line 1979 "y.tab.c"
    break;

  case 55: /* Exp: AddExp  */
#line 298 "yacc.y"
             {
    BISON_LOG("Exp -> AddExp\n");
    yyval = yyvsp[0];
}
#line 1988 "y.tab.c"
    break;

  case 56: /* Cond: LOrExp  */
#line 303 "yacc.y"
              {
    BISON_LOG("Cond -> LOrExp\n");
    yyval = yyvsp[0];
}
#line 1997 "y.tab.c"
    break;

  case 57: /* LVal: Ident  */
#line 308 "yacc.y"
             {
    BISON_LOG("LVal -> Ident\n");
    yyval = std::make_shared<LvalNode> (std::dynamic_pointer_cast<IdentifierNode> (yyvsp[0])->id, nullptr);
}
#line 2006 "y.tab.c"
    break;

  case 58: /* LVal: Ident ArrayList  */
#line 311 "yacc.y"
                    {
    BISON_LOG("LVal -> Ident ArrayList\n");
    yyval = std::make_shared<LvalNode> (std::dynamic_pointer_cast<IdentifierNode> (yyvsp[-1])->id, yyvsp[0]);
}
#line 2015 "y.tab.c"
    break;

  case 59: /* Number: INTNUM  */
#line 316 "yacc.y"
                {
    BISON_LOG("Number -> INTNUM\n");
}
#line 2023 "y.tab.c"
    break;

  case 60: /* Number: FLOATNUM  */
#line 318 "yacc.y"
             {
    BISON_LOG("Number -> FLOATNUM\n");
}
#line 2031 "y.tab.c"
    break;

  case 61: /* PrimaryExp: "(" Exp ")"  */
#line 322 "yacc.y"
                         {
    BISON_LOG("PrimaryExp -> ( Exp )\n");
    yyval = yyvsp[-1];
}
#line 2040 "y.tab.c"
    break;

  case 62: /* PrimaryExp: LVal  */
#line 326 "yacc.y"
                  {
    BISON_LOG("PrimaryExp -> LVal\n");
}
#line 2048 "y.tab.c"
    break;

  case 63: /* PrimaryExp: Number  */
#line 329 "yacc.y"
                    {
    BISON_LOG("PrimaryExp -> Number\n");
}
#line 2056 "y.tab.c"
    break;

  case 64: /* UnaryExp: PrimaryExp  */
#line 333 "yacc.y"
                      {
    BISON_LOG("UnaryExp -> PrimaryExp\n");
}
#line 2064 "y.tab.c"
    break;

  case 65: /* UnaryExp: Ident "(" ")"  */
#line 336 "yacc.y"
                         {
    BISON_LOG("UnaryExp -> Ident ( )\n");
    yyval = std::make_shared<FuncCallNode> (std::dynamic_pointer_cast<IdentifierNode>(yyvsp[-2])->id, nullptr);
}
#line 2073 "y.tab.c"
    break;

  case 66: /* UnaryExp: Ident "(" FuncParamsGroup ")"  */
#line 340 "yacc.y"
                                         {
    BISON_LOG("UnaryExp -> Ident ( FuncParamsGroup )\n");
    yyval = std::make_shared<FuncCallNode> (std::dynamic_pointer_cast<IdentifierNode>(yyvsp[-3])->id, yyvsp[-1]);
}
#line 2082 "y.tab.c"
    break;

  case 67: /* UnaryExp: UnaryOp UnaryExp  */
#line 344 "yacc.y"
                            {
    BISON_LOG("UnaryExp -> UnaryOp UnaryExp\n");
    yyval =  std::make_shared<ExprNode> (std::dynamic_pointer_cast<SimpleTokenNode>(yyvsp[-1])->type, nullptr, yyvsp[0]);
}
#line 2091 "y.tab.c"
    break;

  case 68: /* UnaryOp: "+"  */
#line 349 "yacc.y"
              {
    BISON_LOG("UnaryOp -> ADD\n");
}
#line 2099 "y.tab.c"
    break;

  case 69: /* UnaryOp: "-"  */
#line 352 "yacc.y"
              {
    BISON_LOG("UnaryOp -> SUB\n");
}
#line 2107 "y.tab.c"
    break;

  case 70: /* UnaryOp: "!"  */
#line 355 "yacc.y"
              {
    BISON_LOG("UnaryOp -> NOT\n");
}
#line 2115 "y.tab.c"
    break;

  case 71: /* FuncParamsGroup: Exp  */
#line 359 "yacc.y"
                     {
    BISON_LOG("FuncParamsGroup -> Exp\n");
    yyval = std::make_shared<FuncCallParamNode> ();
    std::dynamic_pointer_cast<FuncCallParamNode> (yyval)->addParam(yyvsp[0]);    
}
#line 2125 "y.tab.c"
    break;

  case 72: /* FuncParamsGroup: FuncParamsGroup "," Exp  */
#line 364 "yacc.y"
                          {
    BISON_LOG("FuncParamsGroup -> FuncParamsGroup , Exp\n");
    yyval = yyvsp[-2];
    std::dynamic_pointer_cast<FuncCallParamNode> (yyval)->addParam(yyvsp[-1]);   
}
#line 2135 "y.tab.c"
    break;

  case 73: /* MulExp: UnaryExp  */
#line 370 "yacc.y"
                  {
    BISON_LOG("MulExp -> UnaryExp\n");
}
#line 2143 "y.tab.c"
    break;

  case 74: /* MulExp: MulExp "*" UnaryExp  */
#line 373 "yacc.y"
                             {
            BISON_LOG("MulExp -> MulExp MUL UnaryExp\n");
            yyval =  std::make_shared<ExprNode> (std::dynamic_pointer_cast<SimpleTokenNode>(yyvsp[-1])->type, yyvsp[-2], yyvsp[0]);
       }
#line 2152 "y.tab.c"
    break;

  case 75: /* MulExp: MulExp "/" UnaryExp  */
#line 377 "yacc.y"
                             {
            BISON_LOG("MulExp -> MulExp DIV UnaryExp\n");
            yyval =  std::make_shared<ExprNode> (std::dynamic_pointer_cast<SimpleTokenNode>(yyvsp[-1])->type, yyvsp[-2], yyvsp[0]);
       }
#line 2161 "y.tab.c"
    break;

  case 76: /* MulExp: MulExp "%" UnaryExp  */
#line 381 "yacc.y"
                             {
            BISON_LOG("MulExp -> MulExp MOD UnaryExp\n");
            yyval =  std::make_shared<ExprNode> (std::dynamic_pointer_cast<SimpleTokenNode>(yyvsp[-1])->type, yyvsp[-2], yyvsp[0]);
       }
#line 2170 "y.tab.c"
    break;

  case 77: /* AddExp: MulExp  */
#line 386 "yacc.y"
                {
    BISON_LOG("AddExp -> MulExp\n");
}
#line 2178 "y.tab.c"
    break;

  case 78: /* AddExp: AddExp "+" MulExp  */
#line 389 "yacc.y"
                           {
            BISON_LOG("AddExp -> AddExp ADD MulExp\n");
            yyval =  std::make_shared<ExprNode> (std::dynamic_pointer_cast<SimpleTokenNode>(yyvsp[-1])->type, yyvsp[-2], yyvsp[0]);
       }
#line 2187 "y.tab.c"
    break;

  case 79: /* AddExp: AddExp "-" MulExp  */
#line 393 "yacc.y"
                           {
            BISON_LOG("AddExp -> AddExp SUB MulExp\n");
            yyval =  std::make_shared<ExprNode> (std::dynamic_pointer_cast<SimpleTokenNode>(yyvsp[-1])->type, yyvsp[-2], yyvsp[0]);
       }
#line 2196 "y.tab.c"
    break;

  case 80: /* RelExp: AddExp  */
#line 398 "yacc.y"
                {
    BISON_LOG("RelExp -> AddExp\n");
}
#line 2204 "y.tab.c"
    break;

  case 81: /* RelExp: RelExp LT AddExp  */
#line 401 "yacc.y"
                          {
            BISON_LOG("RelExp -> RelExp LT AddExp\n");
            yyval =  std::make_shared<ExprNode> (std::dynamic_pointer_cast<SimpleTokenNode>(yyvsp[-1])->type, yyvsp[-2], yyvsp[0]);
       }
#line 2213 "y.tab.c"
    break;

  case 82: /* RelExp: RelExp GT AddExp  */
#line 405 "yacc.y"
                          {
            BISON_LOG("RelExp -> RelExp GT AddExp\n");
            yyval =  std::make_shared<ExprNode> (std::dynamic_pointer_cast<SimpleTokenNode>(yyvsp[-1])->type, yyvsp[-2], yyvsp[0]);
       }
#line 2222 "y.tab.c"
    break;

  case 83: /* RelExp: RelExp LE AddExp  */
#line 409 "yacc.y"
                          {
            BISON_LOG("RelExp -> RelExp LE AddExp\n");
            yyval =  std::make_shared<ExprNode> (std::dynamic_pointer_cast<SimpleTokenNode>(yyvsp[-1])->type, yyvsp[-2], yyvsp[0]);
       }
#line 2231 "y.tab.c"
    break;

  case 84: /* RelExp: RelExp GE AddExp  */
#line 413 "yacc.y"
                          {
            BISON_LOG("RelExp -> RelExp GE AddExp\n");
            yyval =  std::make_shared<ExprNode> (std::dynamic_pointer_cast<SimpleTokenNode>(yyvsp[-1])->type, yyvsp[-2], yyvsp[0]);
       }
#line 2240 "y.tab.c"
    break;

  case 85: /* EqExp: RelExp  */
#line 418 "yacc.y"
               {
    BISON_LOG("EqExp -> RelExp\n");
}
#line 2248 "y.tab.c"
    break;

  case 86: /* EqExp: EqExp EQ RelExp  */
#line 420 "yacc.y"
                    {
            BISON_LOG("EqExp -> EqExp EQ RelExp\n");
            yyval =  std::make_shared<ExprNode> (std::dynamic_pointer_cast<SimpleTokenNode>(yyvsp[-1])->type, yyvsp[-2], yyvsp[0]);
       }
#line 2257 "y.tab.c"
    break;

  case 87: /* EqExp: EqExp NE RelExp  */
#line 423 "yacc.y"
                          {
            BISON_LOG("EqExp -> EqExp NE RelExp\n");
            yyval =  std::make_shared<ExprNode> (std::dynamic_pointer_cast<SimpleTokenNode>(yyvsp[-1])->type, yyvsp[-2], yyvsp[0]);
       }
#line 2266 "y.tab.c"
    break;

  case 88: /* LAndExp: EqExp  */
#line 428 "yacc.y"
                {
    BISON_LOG("LAndExp -> EqExp\n");
}
#line 2274 "y.tab.c"
    break;

  case 89: /* LAndExp: LAndExp AND EqExp  */
#line 430 "yacc.y"
                      {
            BISON_LOG("LAndExp -> LAndExp AND EqExp\n");
            yyval =  std::make_shared<ExprNode> (std::dynamic_pointer_cast<SimpleTokenNode>(yyvsp[-1])->type, yyvsp[-2], yyvsp[0]);
       }
#line 2283 "y.tab.c"
    break;

  case 90: /* LOrExp: LAndExp  */
#line 435 "yacc.y"
                 {
    BISON_LOG("LOrExp -> LAndExp\n");
}
#line 2291 "y.tab.c"
    break;

  case 91: /* LOrExp: LOrExp OR LAndExp  */
#line 437 "yacc.y"
                      {
            BISON_LOG("LOrExp -> LOrExp OR LAndExp\n");
            yyval =  std::make_shared<ExprNode> (std::dynamic_pointer_cast<SimpleTokenNode>(yyvsp[-1])->type, yyvsp[-2], yyvsp[0]);
       }
#line 2300 "y.tab.c"
    break;


#line 2304 "y.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;
  *++yylsp = yyloc;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  yyerror_range[1] = yylloc;
  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval, &yylloc);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  ++yylsp;
  YYLLOC_DEFAULT (*yylsp, yyerror_range, 2);

  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp, yylsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 442 "yacc.y"


int main(int argc, char** argv){
    
    extern FILE* yyin;
    if(argc == 2){
	if((yyin = fopen(argv[1], "r")) == NULL){
	    printf("Can't open file %s\n", argv[1]);
	    return 1;
	}
    }
    yyparse();
    
	fclose(yyin);

    __main();

    
    return 0;
}

int yyerror(char* s)
{
    return 0;
}
