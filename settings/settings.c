#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include "settings.h"

struct cmd 
{
  char* name;
  char* val;
};  

static void
parse_cmd_line_option(settings_t* s, struct cmd* cmd)
{
  if (!strcmp(cmd->name, "input"))
    s->input = cmd->val;
  if (!strcmp(cmd->name, "output"))
    s->output = cmd->val;
  if (!strcmp(cmd->name, "max_iter"))
      s->max_iter = strtoull(cmd->val, NULL, 10);
  if (!strcmp(cmd->name, "dump_freq"))
      s->dump_freq = strtoull(cmd->val, NULL, 10);
}

enum PARSE_RESULT 
{
  ALL_OK,
  MISSING_REQUIRED_PARAMS,
  INVALID_NUM_OPTION_VAL
};

static enum PARSE_RESULT
check_settings(settings_t* s)
{
  if (s->input == NULL || s->output == NULL)
    return MISSING_REQUIRED_PARAMS;
  if (s->max_iter == ULLONG_MAX || s->dump_freq == ULLONG_MAX)
    return INVALID_NUM_OPTION_VAL;
  return ALL_OK;
}

static void
print_err(enum PARSE_RESULT err_type)
{
  char* err_msg;
  if (err_type == INVALID_NUM_OPTION_VAL)
    err_msg = "\"--max_iter\" and \"--dump_freq\" options should be unsigned numbers"; 
  if (err_type == MISSING_REQUIRED_PARAMS)
    err_msg = "\"--input\" and \"--output\" options are required";
  fprintf(stderr, "%s\n", err_msg);
  exit(1);
}
 
settings_t
get_settings(int argc, char* argv[]) 
{
  settings_t s;
  struct cmd cmd;
  memset(&cmd, 0, sizeof cmd);
  for (int i = 1; i < argc; i += 2)
    {
      cmd.name = argv[i] + 2; // + 2 to skip prefix (--) 
      cmd.val = argv[i + 1];
      parse_cmd_line_option(&s, &cmd);
    }
  enum PARSE_RESULT parse_res = check_settings(&s);
  if (parse_res == MISSING_REQUIRED_PARAMS || parse_res == INVALID_NUM_OPTION_VAL)
    print_err(parse_res);
  return s;
} 
      
