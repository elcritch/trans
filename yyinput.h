#define YY_INPUT(buf,len,max) \
  rl_num_chars_to_read=max-1; \
  char *s=readline(0);        \
  if (s) {                    \
    add_history(s);           \
    len=strlen(s);            \
    strcpy(buf,s);            \
    buf[len++]='\n';          \
    free(s);                  \
  } else len=0;
