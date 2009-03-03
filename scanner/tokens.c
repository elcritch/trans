/* C code produced by gperf version 3.0.3 */
/* Command-line: gperf tokens.gperf  */
/* Computed positions: -k'1-2' */

#if !((' ' == 32) && ('!' == 33) && ('"' == 34) && ('#' == 35) \
      && ('%' == 37) && ('&' == 38) && ('\'' == 39) && ('(' == 40) \
      && (')' == 41) && ('*' == 42) && ('+' == 43) && (',' == 44) \
      && ('-' == 45) && ('.' == 46) && ('/' == 47) && ('0' == 48) \
      && ('1' == 49) && ('2' == 50) && ('3' == 51) && ('4' == 52) \
      && ('5' == 53) && ('6' == 54) && ('7' == 55) && ('8' == 56) \
      && ('9' == 57) && (':' == 58) && (';' == 59) && ('<' == 60) \
      && ('=' == 61) && ('>' == 62) && ('?' == 63) && ('A' == 65) \
      && ('B' == 66) && ('C' == 67) && ('D' == 68) && ('E' == 69) \
      && ('F' == 70) && ('G' == 71) && ('H' == 72) && ('I' == 73) \
      && ('J' == 74) && ('K' == 75) && ('L' == 76) && ('M' == 77) \
      && ('N' == 78) && ('O' == 79) && ('P' == 80) && ('Q' == 81) \
      && ('R' == 82) && ('S' == 83) && ('T' == 84) && ('U' == 85) \
      && ('V' == 86) && ('W' == 87) && ('X' == 88) && ('Y' == 89) \
      && ('Z' == 90) && ('[' == 91) && ('\\' == 92) && (']' == 93) \
      && ('^' == 94) && ('_' == 95) && ('a' == 97) && ('b' == 98) \
      && ('c' == 99) && ('d' == 100) && ('e' == 101) && ('f' == 102) \
      && ('g' == 103) && ('h' == 104) && ('i' == 105) && ('j' == 106) \
      && ('k' == 107) && ('l' == 108) && ('m' == 109) && ('n' == 110) \
      && ('o' == 111) && ('p' == 112) && ('q' == 113) && ('r' == 114) \
      && ('s' == 115) && ('t' == 116) && ('u' == 117) && ('v' == 118) \
      && ('w' == 119) && ('x' == 120) && ('y' == 121) && ('z' == 122) \
      && ('{' == 123) && ('|' == 124) && ('}' == 125) && ('~' == 126))
/* The character set is not based on ISO-646.  */
error "gperf generated tables don't work with this execution character set. Please report a bug to <bug-gnu-gperf@gnu.org>."
#endif

#line 4 "tokens.gperf"

#include "tokenentry.h"
#line 7 "tokens.gperf"
struct TokenEntry;
#include <string.h>

#define TOTAL_KEYWORDS 36
#define MIN_WORD_LENGTH 1
#define MAX_WORD_LENGTH 5
#define MIN_HASH_VALUE 1
#define MAX_HASH_VALUE 62
/* maximum key range = 62, duplicates = 0 */

#ifdef __GNUC__
__inline
#else
#ifdef __cplusplus
inline
#endif
#endif
static unsigned int
hash (str, len)
     register const char *str;
     register unsigned int len;
{
  static unsigned char asso_values[] =
    {
      63, 63, 63, 63, 63, 63, 63, 63, 63, 63,
      63, 63, 63, 63, 63, 63, 63, 63, 63, 63,
      63, 63, 63, 63, 63, 63, 63, 63, 63, 63,
      63, 63, 63, 50, 63, 63, 63, 63, 15, 63,
       2, 61, 40, 56, 63, 41, 63,  5, 63, 63,
      63, 63, 63, 63, 63, 63, 63, 63, 63, 60,
      35,  0, 25, 63, 63, 63, 63, 63, 63, 63,
      63, 63, 63, 63, 63, 63, 63, 63, 63, 63,
      63, 63, 63, 63, 63, 63, 63, 63, 63, 63,
      63, 55, 63, 45, 63, 63, 63, 20, 15, 63,
      10,  5,  0, 63, 10,  5, 63, 63,  5, 63,
       0,  5, 63, 63,  0, 63,  0, 63, 63,  0,
      63, 63, 63, 30, 10, 20, 63, 63, 63, 63,
      63, 63, 63, 63, 63, 63, 63, 63, 63, 63,
      63, 63, 63, 63, 63, 63, 63, 63, 63, 63,
      63, 63, 63, 63, 63, 63, 63, 63, 63, 63,
      63, 63, 63, 63, 63, 63, 63, 63, 63, 63,
      63, 63, 63, 63, 63, 63, 63, 63, 63, 63,
      63, 63, 63, 63, 63, 63, 63, 63, 63, 63,
      63, 63, 63, 63, 63, 63, 63, 63, 63, 63,
      63, 63, 63, 63, 63, 63, 63, 63, 63, 63,
      63, 63, 63, 63, 63, 63, 63, 63, 63, 63,
      63, 63, 63, 63, 63, 63, 63, 63, 63, 63,
      63, 63, 63, 63, 63, 63, 63, 63, 63, 63,
      63, 63, 63, 63, 63, 63, 63, 63, 63, 63,
      63, 63, 63, 63, 63, 63
    };
  register int hval = len;

  switch (hval)
    {
      default:
        hval += asso_values[(unsigned char)str[1]];
      /*FALLTHROUGH*/
      case 1:
        hval += asso_values[(unsigned char)str[0]];
        break;
    }
  return hval;
}

#ifdef __GNUC__
__inline
#ifdef __GNUC_STDC_INLINE__
__attribute__ ((__gnu_inline__))
#endif
#endif
struct TokenEntry *
in_word_set (str, len)
     register const char *str;
     register unsigned int len;
{
  static struct TokenEntry wordlist[] =
    {
      {""},
#line 41 "tokens.gperf"
      {"=",0,2},
#line 48 "tokens.gperf"
      {"==",TOK_EQ},
#line 26 "tokens.gperf"
      {"("},
#line 22 "tokens.gperf"
      {"true",TOK_true},
#line 14 "tokens.gperf"
      {"write",TOK_write},
#line 39 "tokens.gperf"
      {"/",0,2},
#line 19 "tokens.gperf"
      {"if",TOK_if},
#line 20 "tokens.gperf"
      {"int",TOK_int},
#line 21 "tokens.gperf"
      {"read",TOK_read},
#line 18 "tokens.gperf"
      {"float",TOK_float},
#line 44 "tokens.gperf"
      {"|",TOK_ERROR,2},
#line 53 "tokens.gperf"
      {"//",0,0,Past,""},
      {""},
#line 16 "tokens.gperf"
      {"else",TOK_else},
#line 13 "tokens.gperf"
      {"while",TOK_while},
#line 43 "tokens.gperf"
      {"&",TOK_ERROR,2},
#line 15 "tokens.gperf"
      {"do",TOK_do},
      {""}, {""},
#line 12 "tokens.gperf"
      {"break",TOK_break},
#line 35 "tokens.gperf"
      {"}"},
#line 51 "tokens.gperf"
      {"||",TOK_OR},
      {""}, {""},
#line 17 "tokens.gperf"
      {"false",TOK_false},
#line 38 "tokens.gperf"
      {">",0,2},
#line 49 "tokens.gperf"
      {">=",TOK_GE},
      {""}, {""}, {""},
#line 34 "tokens.gperf"
      {"{"},
#line 50 "tokens.gperf"
      {"&&",TOK_AND},
      {""}, {""}, {""},
#line 37 "tokens.gperf"
      {"<",0,2},
#line 46 "tokens.gperf"
      {"<=",TOK_LE},
      {""}, {""}, {""},
#line 28 "tokens.gperf"
      {"*"},
#line 30 "tokens.gperf"
      {"-"},
      {""}, {""}, {""},
#line 33 "tokens.gperf"
      {"]"},
#line 54 "tokens.gperf"
      {"/*",0,0,Past,"*/"},
      {""}, {""}, {""},
#line 40 "tokens.gperf"
      {"!",0,2},
#line 47 "tokens.gperf"
      {"!=",TOK_NE},
      {""}, {""}, {""},
#line 32 "tokens.gperf"
      {"["},
#line 29 "tokens.gperf"
      {"+"},
      {""}, {""}, {""},
#line 31 "tokens.gperf"
      {";"},
#line 27 "tokens.gperf"
      {")"}
    };

  if (len <= MAX_WORD_LENGTH && len >= MIN_WORD_LENGTH)
    {
      register int key = hash (str, len);

      if (key <= MAX_HASH_VALUE && key >= 0)
        {
          register const char *s = wordlist[key].name;

          if (*str == *s && !strncmp (str + 1, s + 1, len - 1) && s[len] == '\0')
            return &wordlist[key];
        }
    }
  return 0;
}
