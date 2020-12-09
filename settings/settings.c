#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include "settings.h"

typedef struct 
{
  char* name;
  char* val;
} cmd;  

static void
check_num_convert(const char* cmd_name, uint64 result)
{
  if (result != ULLONG_MAX)
    return;
  fprintf(stderr, "value of %s command should be unsigned number\n", cmd_name);
  exit(1);
}

static void
process_cmd(settings* s, cmd *cmd)
{
  if (!strcmp(cmd->name, "input"))
    s->input = cmd->val;
  else if (!strcmp(cmd->name, "output"))
    s->output = cmd->val;
  else if (!strcmp(cmd->name, "max_iter"))
    {
      s->max_iter = strtoull(cmd->val, NULL, 10);
      chech_num_convert(cmd->name, s->max_iter);
    }
  else if (!strcmp(cmd->name, "dump_freq"))
    {
      s->dump_freq = strtoull(cmd->val, NULL, 10);
      check_num_convert(cmd->name, s->dump_freq);
    }
  else
    {
      fprintf(stderr, "unknown command: %s\n", cmd->name); 
      exit(1);
    }
}
 
settings
get_settings(int argc, char* argv[]) 
{
  settings s;
  cmd cmd;
  for (int i = 1; i < argc; i += 2)
    {
      cmd.name = argv[i] + 2; // + 2 to skip prefix (--) 
      cmd.val = argv[i + 1];
      process_cmd(&s, &cmd);
    }
  return s;
} 
      
